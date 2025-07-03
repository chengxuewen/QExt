/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright (C) 2007 - 2020 Log4Qt contributors
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <qextLogConfiguratorHelper.h>
#include <qextLogInitialisationHelper.h>

#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QTimer>
#include <QDebug>

QExtLogConfiguratorHelper::QExtLogConfiguratorHelper(QObject *parent) :
    QObject(parent),
    mConfigureFunc(nullptr),
    mConfigurationFileWatch(nullptr)
{
}


QExtLogConfiguratorHelper::~QExtLogConfiguratorHelper()
{
    delete mConfigurationFileWatch;
}

LOG4QT_IMPLEMENT_INSTANCE(QExtLogConfiguratorHelper)

void QExtLogConfiguratorHelper::doConfigurationFileChanged(const QString &fileName)
{
    if (!mConfigureFunc ||
        !QFileInfo::exists(mConfigurationFile.absoluteFilePath()))
        return;
    mConfigureFunc(fileName);
    Q_EMIT configurationFileChanged(fileName, mConfigureError.count() > 0);
}

void QExtLogConfiguratorHelper::doConfigurationFileDirectoryChanged(const QString &path)
{
    Q_UNUSED(path)
    QTimer::singleShot(100, this, &QExtLogConfiguratorHelper::tryToReAddConfigurationFile);
}

void QExtLogConfiguratorHelper::tryToReAddConfigurationFile()
{
    if (!mConfigurationFileWatch->files().contains(mConfigurationFile.absoluteFilePath()))
        mConfigurationFileWatch->addPath(mConfigurationFile.absoluteFilePath());
}

void QExtLogConfiguratorHelper::doSetConfigurationFile(const QString &fileName,
        ConfigureFunc pConfigureFunc)
{
    QMutexLocker locker(&mObjectGuard);
    mConfigurationFile.setFile(fileName);
    mConfigureFunc = nullptr;
    delete mConfigurationFileWatch;
    mConfigurationFileWatch = nullptr;
    if (fileName.isEmpty() || !QFileInfo::exists(fileName))
        return;

    mConfigureFunc = pConfigureFunc;
    mConfigurationFileWatch = new QFileSystemWatcher();

    if (mConfigurationFileWatch->addPath(mConfigurationFile.absoluteFilePath()))
    {
        mConfigurationFileWatch->addPath(mConfigurationFile.absolutePath());
        connect(mConfigurationFileWatch, &QFileSystemWatcher::fileChanged,
                this, &QExtLogConfiguratorHelper::doConfigurationFileChanged);
        connect(mConfigurationFileWatch, &QFileSystemWatcher::directoryChanged,
                this, &QExtLogConfiguratorHelper::doConfigurationFileDirectoryChanged);
    }
    else
        qWarning() << "Add Path '" << fileName << "' to file system watcher failed!";
}

// #include "moc_configuratorhelper.cpp"
