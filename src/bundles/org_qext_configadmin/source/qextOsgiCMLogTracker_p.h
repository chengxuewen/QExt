/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#ifndef _QEXTOSGICMLOGTRACKER_P_H
#define _QEXTOSGICMLOGTRACKER_P_H

#include <qextOsgiServiceTracker.h>
#include <qextOsgiLogService.h>

/**
 * This class encapsulates the QExtOsgiLogService
 * and handles all issues such as the service coming and going.
 */
class QExtOsgiCMLogTracker : public QExtOsgiServiceTracker<QExtOsgiLogService*>, public QExtOsgiLogService
{

public:

    /**
   * Create new QExtOsgiCMLogTracker.
   *
   * @param context QExtOsgiPluginContext of parent plugin.
   * @param out Default QIODevice to use if QExtOsgiLogService is unavailable.
   */
    QExtOsgiCMLogTracker(QExtOsgiPluginContext* context, QIODevice* out);

    /*
   * ----------------------------------------------------------------------
   *      LogService Interface implementation
   * ----------------------------------------------------------------------
   */

    void log(int level, const QString& message, const std::exception* exception = 0,
             const char* file = 0, const char* function = 0, int line = -1);

    void log(const QExtOsgiServiceReference& sr, int level, const QString& message,
             const std::exception* exception = 0,
             const char* file = 0, const char* function = 0, int line = -1);

    int getLogLevel() const;

protected:

    QExtOsgiLogService* addingService(const QExtOsgiServiceReference& reference);

    void removedService(const QExtOsgiServiceReference& reference, QExtOsgiLogService* service);

private:

    void logToAll(const QExtOsgiServiceReference& reference, int level, const QString& message,
                  const std::exception* exception, const char* file, const char* function, int line);

    /**
   * The QExtOsgiLogService is not available so we write the message to a QTextStream.
   *
   * @param reference QExtOsgiServiceReference associated with message or a default constructed one if none.
   * @param level Logging level.
   * @param message Log message.
   * @param exc Log exception or null if none.
   * @param file The file name where the log message came from.
   * @param function The function where the log message came from.
   * @param The line number where the log message came from.
   */
    void noLogService(const QExtOsgiServiceReference& reference, int level, const QString& message,
                      const std::exception* exc, const char* file, const char* function, int line);

    /** Output device to use if QExtOsgiLogService is unavailable */
    QTextStream out;

    QMutex mutex;

    int logLevel;
};

#endif // _QEXTOSGICMLOGTRACKER_P_H
