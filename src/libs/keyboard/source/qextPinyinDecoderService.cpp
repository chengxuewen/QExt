/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/qextPinyinDecoderService_p.h>
#include <qextOnceFlag.h>
#include <qextSpinlock.h>

#include <pinyinime.h>
#include <dictdef.h>

#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QStandardPaths>
#include <QLoggingCategory>

using namespace ime_pinyin;

class QExtPinyinDecoderServicePrivate
{
public:
    explicit QExtPinyinDecoderServicePrivate(QExtPinyinDecoderService *q);
    virtual ~QExtPinyinDecoderServicePrivate();

    QExtPinyinDecoderService * const q_ptr;

    bool m_initDone;
    QExtSpinLock m_spinLock;

private:
    QEXT_DECLARE_PUBLIC(QExtPinyinDecoderService)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPinyinDecoderServicePrivate)
};

QExtPinyinDecoderServicePrivate::QExtPinyinDecoderServicePrivate(QExtPinyinDecoderService *q)
    : q_ptr(q)
    , m_initDone(false)
{
}

QExtPinyinDecoderServicePrivate::~QExtPinyinDecoderServicePrivate()
{
    if (m_initDone)
    {
        im_close_decoder();
        m_initDone = false;
    }
}

QExtPinyinDecoderService::QExtPinyinDecoderService(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtPinyinDecoderServicePrivate(this))
{
}

QExtPinyinDecoderService::~QExtPinyinDecoderService()
{
}

QExtPinyinDecoderService *QExtPinyinDecoderService::instance()
{
    static QExtOnceFlag onceFlag;
    static QScopedPointer<QExtPinyinDecoderService> instance;
    if (onceFlag.enter())
    {
        instance.reset(new QExtPinyinDecoderService);
        instance->init();
        onceFlag.leave();
    }
    return instance.data();
}

bool QExtPinyinDecoderService::init()
{
    Q_D(QExtPinyinDecoderService);
    QExtSpinLock::Locker locker(d->m_spinLock);
    if (d->m_initDone)
    {
        return true;
    }

    //    QString sysDict(qEnvironmentVariable("QT_VIRTUALKEYBOARD_PINYIN_DICTIONARY"));
    QString sysDict(qgetenv("QT_VIRTUALKEYBOARD_PINYIN_DICTIONARY"));
    if (!QFileInfo::exists(sysDict))
    {
        sysDict = QLatin1String(":/QExtKeyboard/dict/dict_pinyin.dat");
        if (!QFileInfo::exists(sysDict))
        {
            sysDict = QLibraryInfo::location(QLibraryInfo::DataPath) + QLatin1String("/QExtKeyboard/pinyin/dict_pinyin.dat");
        }
    }

    QString usrDictPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QFileInfo usrDictInfo(usrDictPath + QLatin1String("/QExtKeyboard/pinyin/usr_dict.dat"));
    if (!usrDictInfo.exists())
    {
        qWarning() << "QExtPinyinDecoderService::init(): creating directory for user dictionary" << usrDictInfo.absolutePath();
        QDir().mkpath(usrDictInfo.absolutePath());
    }

    d->m_initDone = im_open_decoder(sysDict.toUtf8().constData(), usrDictInfo.absoluteFilePath().toUtf8().constData());
    if (!d->m_initDone)
    {
        qWarning() << "Could not initialize pinyin engine. sys_dict:" << sysDict << "usr_dict:" << usrDictInfo.absoluteFilePath();
    }

    return d->m_initDone;
}

void QExtPinyinDecoderService::setUserDictionary(bool enabled)
{
    if (enabled == im_is_user_dictionary_enabled())
    {
        return;
    }
    if (enabled)
    {
        QString usrDictPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
        QFileInfo usrDictInfo(usrDictPath + QLatin1String("/QExtKeyboard/pinyin/usr_dict.dat"));
        im_init_user_dictionary(usrDictInfo.absoluteFilePath().toUtf8().constData());
    }
    else
    {
        im_init_user_dictionary(QEXT_NULLPTR);
    }
}

bool QExtPinyinDecoderService::isUserDictionaryEnabled() const
{
    return im_is_user_dictionary_enabled();
}

void QExtPinyinDecoderService::setLimits(int maxSpsLen, int maxHzsLen)
{
    if (maxSpsLen <= 0)
    {
        maxSpsLen = kMaxSearchSteps - 1;
    }
    if (maxHzsLen <= 0)
    {
        maxHzsLen = kMaxSearchSteps;
    }
    im_set_max_lens(size_t(maxSpsLen), size_t(maxHzsLen));
}

int QExtPinyinDecoderService::search(const QString &spelling)
{
    QByteArray spellingBuf = spelling.toLatin1();
    return int(im_search(spellingBuf.constData(), spellingBuf.length()));
}

int QExtPinyinDecoderService::deleteSearch(int pos, bool isPosInSpellingId, bool clearFixedInThisStep)
{
    if (pos <= 0)
    {
        pos = 0;
    }
    return int(im_delsearch(size_t(pos), isPosInSpellingId, clearFixedInThisStep));
}

void QExtPinyinDecoderService::resetSearch()
{
    im_reset_search();
}

QString QExtPinyinDecoderService::pinyinString(bool decoded)
{
    size_t py_len;
    const char *py = im_get_sps_str(&py_len);
    if (!decoded)
    {
        py_len = strlen(py);
    }

    return QString(QLatin1String(py, (int)py_len));
}

int QExtPinyinDecoderService::pinyinStringLength(bool decoded)
{
    size_t py_len;
    const char *py = im_get_sps_str(&py_len);
    if (!decoded)
    {
        py_len = strlen(py);
    }
    return (int)py_len;
}

QVector<int> QExtPinyinDecoderService::spellingStartPositions()
{
    const unsigned short *spl_start;
    int len;
    // There will be len + 1 elements in the buffer when len > 0.
    len = (int)im_get_spl_start_pos(spl_start);

    QVector<int> arr;
    arr.resize(len + 2);
    arr[0] = len; // element 0 is used to store the length of buffer.
    for (int i = 0; i <= len; i++)
    {
        arr[i + 1] = spl_start[i];
    }
    return arr;
}

QString QExtPinyinDecoderService::candidateAt(int index)
{
    Q_ASSERT(index >= 0);
    QVector<QChar> candidateBuf;
    candidateBuf.resize(kMaxSearchSteps + 1);
    if (!im_get_candidate(size_t(index), (char16 *)candidateBuf.data(), candidateBuf.length() - 1))
    {
        return QString();
    }
    candidateBuf.last() = QChar(0);
    return QString(candidateBuf.data());
}

QList<QString> QExtPinyinDecoderService::fetchCandidates(int index, int count, int sentFixedLen)
{
    QList<QString> candidatesList;
    for (int i = index; i < index + count; i++)
    {
        QString retStr = candidateAt(i);
        if (0 == i)
        {
            retStr.remove(0, sentFixedLen);
        }
        candidatesList.append(retStr);
    }
    return candidatesList;
}

int QExtPinyinDecoderService::chooceCandidate(int index)
{
    return int(im_choose(index));
}

int QExtPinyinDecoderService::cancelLastChoice()
{
    return int(im_cancel_last_choice());
}

int QExtPinyinDecoderService::fixedLength()
{
    return (int)im_get_fixed_len();
}

void QExtPinyinDecoderService::flushCache()
{
    im_flush_cache();
}

QList<QString> QExtPinyinDecoderService::predictionList(const QString &history)
{
    QList<QString> predictList;
    char16 (*predictItems)[kMaxPredictSize + 1] = QEXT_NULLPTR;
    int predictNum = int(im_get_predicts(history.utf16(), predictItems));
    predictList.reserve(predictNum);
    for (int i = 0; i < predictNum; i++)
    {
        predictList.append(QString((QChar *)predictItems[i]));
    }
    return predictList;
}
