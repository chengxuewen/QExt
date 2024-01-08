/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
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


#ifndef _QEXTOSGILOGREADERSERVICE_H
#define _QEXTOSGILOGREADERSERVICE_H

#include <qextOsgiLogEntry.h>

#include <QList>

/**
 * \ingroup LogService
 *
 * Provides methods to retrieve <code>QExtOsgiLogEntry</code> objects from the log.
 * <p>
 * There are three ways to retrieve <code>QExtOsgiLogEntry</code> objects:
 * <ul>
 * <li>The primary way to retrieve <code>QExtOsgiLogEntry</code> objects is to register a
 * <code>QExtOsgiLogListener</code> object with the service registry whose
 * <code>QExtOsgiLogListener#logged()</code> method will
 * be called for each entry added to the log. This way you do not need to retrieve
 * any service object to express an interest in log entries.
 * <li>A Qt slot can be connected to the <code>QExtOsgiLogReaderService</code> by using
 * <code>connectLogListener()</code>.
 * <li>To retrieve past <code>QExtOsgiLogEntry</code> objects, the <code>getLog()</code>
 * method can be called which will return a QList of all
 * <code>QExtOsgiLogEntry</code> objects in the log.
 * </ul>
 *
 * @remarks This class is thread safe.
 * @see QExtOsgiLogEntry
 * @see QExtOsgiLogListener
 * @see QExtOsgiLogListener#logged(QExtOsgiLogEntryPtr)
 */
struct QExtOsgiLogReaderService
{
    virtual ~QExtOsgiLogReaderService() {}

    /**
   * Subscribes to <code>QExtOsgiLogEntry</code> objects.
   *
   * <p>
   * This method connects a Qt slot with the Log Reader
   * Service. The slot must take a <code>QExtOsgiLogEntryPtr</code> as the
   * only argument and will be
   * called for each <code>QExtOsgiLogEntry</code> object placed into the log.
   *
   * <p>
   * When a plugin which connects a Qt slot is stopped, the Log Reader
   * Service must disconnect all of the plugin's connected slots.
   *
   * <p>
   * If the same slot from the same object is already connected, this
   * method does nothing.
   *
   * @param receiver The object to connect to.
   * @param slot The name of the slot to be connected.
   * @returns <code>true</code> if the connection was successful;
   *          <code>false</code> otherwise.
   * @see QExtOsgiLogListener
   * @see QExtOsgiLogEntry
   * @see QExtOsgiLogListener#logged(QExtOsgiLogEntryPtr)
   */
    virtual bool connectLogListener(const QObject *receiver, const char *slot) = 0;

    /**
   * Returns a QList of all <code>QExtOsgiLogEntry</code> objects in
   * the log.
   *
   * <p>
   * Each element of the QList is a <code>QExtOsgiLogEntry</code> object, ordered
   * with the most recent entry first. Whether the list is of all
   * <code>QExtOsgiLogEntry</code> objects since the Log Service was started or some
   * recent past is implementation-specific. Also implementation-specific is
   * whether informational and debug <code>QExtOsgiLogEntry</code> objects are included
   * in the list.
   * @return A QList of all <code>QExtOsgiLogEntry</code> objects in
   * the log.
   */
    virtual QList<QExtOsgiLogEntryPtr> getLog() = 0;
};

Q_DECLARE_INTERFACE(QExtOsgiLogReaderService, "org.qext.service.log.LogReaderService")

#endif // _QEXTOSGILOGREADERSERVICE_H
