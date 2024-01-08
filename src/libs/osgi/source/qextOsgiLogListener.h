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


#ifndef _QEXTOSGILOGLISTENER_H
#define _QEXTOSGILOGLISTENER_H

#include <qextOsgiLogEntry.h>

/**
 * \ingroup LogService
 *
 * Subscribes to <code>QExtOsgiLogEntry</code> objects from the <code>QExtOsgiLogReaderService</code>.
 *
 * <p>
 * <code>QExtOsgiLogListener</code> objects may be registered with the Framework service
 * registry. After the listener is registered, the <code>logged(QExtOsgiLogEntryPtr)</code>
 * method will be called for each <code>QExtOsgiLogEntry</code> object created.
 *
 * <p>
 * Qt slots can also be used to be notified about new <code>QExtOsgiLogEntry</code>
 * objects. See <code>QExtOsgiLogReaderService#connectLogListener()</code>.
 *
 * @remarks This class is thread safe.
 * @see QExtOsgiLogReaderService
 * @see QExtOsgiLogEntry
 * @see QExtOsgiLogReaderService#connectLogListener()
 * @see QExtOsgiLogReaderService#disconnectLogListener()
 */
struct QExtOsgiLogListener
{
    virtual ~QExtOsgiLogListener() {}

    /**
   * Listener method called for each QExtOsgiLogEntry object created.
   *
   * <p>
   * As with all event listeners, this method should return to its caller as
   * soon as possible.
   *
   * @param entry A <code>QExtOsgiLogEntry</code> object containing log information.
   * @see QExtOsgiLogEntry
   */
    virtual void logged(QExtOsgiLogEntryPtr entry) = 0;
};

Q_DECLARE_INTERFACE(QExtOsgiLogListener, "org.qext.service.log.LogListener")

#endif // _QEXTOSGILOGLISTENER_H
