/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LOG4QT_HIERARCHY_H
#define LOG4QT_HIERARCHY_H

#include <qextLoggerRepository.h>

#include <QHash>
#include <QReadWriteLock>

namespace Log4Qt
{

/*!
 * \brief The class Hierarchy implements a logger repository.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API Hierarchy : public LoggerRepository
{
public:
    Hierarchy();
    ~Hierarchy() override;

public:
    bool exists(const QString &name) const override;
    Logger *logger(const QString &name) override;
    QList<Logger *> loggers() const override;
    Logger *rootLogger() const override;
    QExtLogLevel threshold() const override;
    void setThreshold(QExtLogLevel level) override;
    void setThreshold(const QString &threshold) override;

    bool isDisabled(QExtLogLevel level) override;
    void resetConfiguration() override;
    void shutdown() override;

private:
    Logger *createLogger(const QString &name);
    void resetLogger(Logger *logger, QExtLogLevel level) const;

private:
    mutable QReadWriteLock mObjectGuard;
    QHash<QString, Logger *> mLoggers;
    QExtLogLevel mThreshold;
    Logger *mRootLogger;
};

inline Logger *Hierarchy::rootLogger() const
{
    return mRootLogger;
}

inline QExtLogLevel Hierarchy::threshold() const
{
    return mThreshold;
}

inline void Hierarchy::setThreshold(QExtLogLevel level)
{
    mThreshold = level;
}

inline bool Hierarchy::isDisabled(QExtLogLevel level)
{
    return level < mThreshold;
}

} // namespace Log4Qt

#endif // LOG4QT_HIERARCHY_H
