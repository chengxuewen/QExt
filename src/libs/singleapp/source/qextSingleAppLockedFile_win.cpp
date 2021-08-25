/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qextSingleAppLockedFile.h>

#ifdef Q_OS_WIN

#include <qt_windows.h>
#include <QFileInfo>

#define MUTEX_PREFIX "QEXTSingleAppLockedFile mutex "
// Maximum number of concurrent read locks. Must not be greater than MAXIMUM_WAIT_OBJECTS
#define MAX_READERS MAXIMUM_WAIT_OBJECTS

#if QT_VERSION >= 0x050000
#define QT_WA(unicode, ansi) unicode
#endif

Qt::HANDLE QEXTSingleAppLockedFile::getMutexHandle(int idx, bool doCreate)
{
    if (m_mutexname.isEmpty()) {
        QFileInfo fi(*this);
        m_mutexname = QString::fromLatin1(MUTEX_PREFIX)
                    + fi.absoluteFilePath().toLower();
    }
    QString mname(m_mutexname);
    if (idx >= 0)
        mname += QString::number(idx);

    Qt::HANDLE mutex;
    if (doCreate) {
        QT_WA( { mutex = CreateMutexW(NULL, FALSE, (TCHAR*)mname.utf16()); },
               { mutex = CreateMutexA(NULL, FALSE, mname.toLocal8Bit().constData()); } );
        if (!mutex) {
            qErrnoWarning("QEXTSingleAppLockedFile::lock(): CreateMutex failed");
            return 0;
        }
    }
    else {
        QT_WA( { mutex = OpenMutexW(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, (TCHAR*)mname.utf16()); },
               { mutex = OpenMutexA(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, mname.toLocal8Bit().constData()); } );
        if (!mutex) {
            if (GetLastError() != ERROR_FILE_NOT_FOUND)
                qErrnoWarning("QEXTSingleAppLockedFile::lock(): OpenMutex failed");
            return 0;
        }
    }
    return mutex;
}

bool QEXTSingleAppLockedFile::waitMutex(Qt::HANDLE mutex, bool doBlock)
{
    Q_ASSERT(mutex);
    DWORD res = WaitForSingleObject(mutex, doBlock ? INFINITE : 0);
    switch (res) {
    case WAIT_OBJECT_0:
    case WAIT_ABANDONED:
        return true;
        break;
    case WAIT_TIMEOUT:
        break;
    default:
        qErrnoWarning("QEXTSingleAppLockedFile::lock(): WaitForSingleObject failed");
    }
    return false;
}



bool QEXTSingleAppLockedFile::lock(LockMode mode, bool block)
{
    if (!isOpen()) {
        qWarning("QEXTSingleAppLockedFile::lock(): file is not opened");
        return false;
    }

    if (mode == NoLock)
        return unlock();

    if (mode == m_lockMode)
        return true;

    if (m_lockMode != NoLock)
        unlock();

    if (!m_wmutex && !(m_wmutex = getMutexHandle(-1, true)))
        return false;

    if (!waitMutex(m_wmutex, block))
        return false;

    if (mode == ReadLock) {
        int idx = 0;
        for (; idx < MAX_READERS; idx++) {
            m_rmutex = getMutexHandle(idx, false);
            if (!m_rmutex || waitMutex(m_rmutex, false))
                break;
            CloseHandle(m_rmutex);
        }
        bool ok = true;
        if (idx >= MAX_READERS) {
            qWarning("QEXTSingleAppLockedFile::lock(): too many readers");
            m_rmutex = 0;
            ok = false;
        }
        else if (!m_rmutex) {
            m_rmutex = getMutexHandle(idx, true);
            if (!m_rmutex || !waitMutex(m_rmutex, false))
                ok = false;
        }
        if (!ok && m_rmutex) {
            CloseHandle(m_rmutex);
            m_rmutex = 0;
        }
        ReleaseMutex(m_wmutex);
        if (!ok)
            return false;
    }
    else {
        Q_ASSERT(m_rmutexes.isEmpty());
        for (int i = 0; i < MAX_READERS; i++) {
            Qt::HANDLE mutex = getMutexHandle(i, false);
            if (mutex)
                m_rmutexes.append(mutex);
        }
        if (m_rmutexes.size()) {
            DWORD res = WaitForMultipleObjects(m_rmutexes.size(), m_rmutexes.constData(),
                                               TRUE, block ? INFINITE : 0);
            if (res != WAIT_OBJECT_0 && res != WAIT_ABANDONED) {
                if (res != WAIT_TIMEOUT)
                    qErrnoWarning("QEXTSingleAppLockedFile::lock(): WaitForMultipleObjects failed");
                m_lockMode = WriteLock;  // trick unlock() to clean up - semiyucky
                unlock();
                return false;
            }
        }
    }

    m_lockMode = mode;
    return true;
}

bool QEXTSingleAppLockedFile::unlock()
{
    if (!isOpen()) {
        qWarning("QEXTSingleAppLockedFile::unlock(): file is not opened");
        return false;
    }

    if (!isLocked())
        return true;

    if (m_lockMode == ReadLock) {
        ReleaseMutex(m_rmutex);
        CloseHandle(m_rmutex);
        m_rmutex = 0;
    }
    else {
        foreach(Qt::HANDLE mutex, m_rmutexes) {
            ReleaseMutex(mutex);
            CloseHandle(mutex);
        }
        m_rmutexes.clear();
        ReleaseMutex(m_wmutex);
    }

    m_lockMode = QEXTSingleAppLockedFile::NoLock;
    return true;
}

QEXTSingleAppLockedFile::~QEXTSingleAppLockedFile()
{
    if (isOpen())
        unlock();
    if (m_wmutex)
        CloseHandle(m_wmutex);
}

#endif // #ifdef Q_OS_WIN
