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


#ifndef _QEXTOSGISERVICETRACKERCUSTOMIZER_H
#define _QEXTOSGISERVICETRACKERCUSTOMIZER_H

#include <qextOsgiServiceReference.h>

/**
 * \ingroup PluginFramework
 *
 * The <code>QExtOsgiServiceTrackerCustomizer</code> interface allows a
 * <code>QExtOsgiServiceTracker</code> to customize the service objects that are
 * tracked. A <code>QExtOsgiServiceTrackerCustomizer</code> is called when a service is
 * being added to a <code>QExtOsgiServiceTracker</code>. The
 * <code>QExtOsgiServiceTrackerCustomizer</code> can then return an object for the
 * tracked service. A <code>QExtOsgiServiceTrackerCustomizer</code> is also called when
 * a tracked service is modified or has been removed from a
 * <code>QExtOsgiServiceTracker</code>.
 *
 * <p>
 * The methods in this interface may be called as the result of a
 * <code>QExtOsgiServiceEvent</code> being received by a <code>QExtOsgiServiceTracker</code>.
 * Since <code>QExtOsgiServiceEvent</code>s are synchronously delivered by the
 * Framework, it is highly recommended that implementations of these methods do
 * not register (<code>QExtOsgiPluginContext::registerService</code>), modify (
 * <code>QExtOsgiServiceRegistration::setProperties</code>) or unregister (
 * <code>QExtOsgiServiceRegistration::unregister</code>) a service while being
 * synchronized on any object.
 *
 * <p>
 * The <code>QExtOsgiServiceTracker</code> class is thread-safe. It does not call a
 * <code>QExtOsgiServiceTrackerCustomizer</code> while holding any locks.
 * <code>QExtOsgiServiceTrackerCustomizer</code> implementations must also be
 * thread-safe.
 *
 * \tparam T The type of the tracked object.
 * \remarks This class is thread safe.
 */
template<class T = QObject*>
struct QExtOsgiServiceTrackerCustomizer {

    virtual ~QExtOsgiServiceTrackerCustomizer() {}

    /**
   * A service is being added to the <code>QExtOsgiServiceTracker</code>.
   *
   * <p>
   * This method is called before a service which matched the search
   * parameters of the <code>QExtOsgiServiceTracker</code> is added to the
   * <code>QExtOsgiServiceTracker</code>. This method should return the service object
   * to be tracked for the specified <code>QExtOsgiServiceReference</code>. The
   * returned service object is stored in the <code>QExtOsgiServiceTracker</code> and
   * is available from the <code>getService</code> and
   * <code>getServices</code> methods.
   *
   * @param reference The reference to the service being added to the
   *        <code>QExtOsgiServiceTracker</code>.
   * @return The service object to be tracked for the specified referenced
   *         service or <code>0</code> if the specified referenced service
   *         should not be tracked.
   */
    virtual T addingService(const QExtOsgiServiceReference& reference) = 0;

    /**
   * A service tracked by the <code>QExtOsgiServiceTracker</code> has been modified.
   *
   * <p>
   * This method is called when a service being tracked by the
   * <code>QExtOsgiServiceTracker</code> has had it properties modified.
   *
   * @param reference The reference to the service that has been modified.
   * @param service The service object for the specified referenced service.
   */
    virtual void modifiedService(const QExtOsgiServiceReference& reference, T service) = 0;

    /**
   * A service tracked by the <code>QExtOsgiServiceTracker</code> has been removed.
   *
   * <p>
   * This method is called after a service is no longer being tracked by the
   * <code>QExtOsgiServiceTracker</code>.
   *
   * @param reference The reference to the service that has been removed.
   * @param service The service object for the specified referenced service.
   */
    virtual void removedService(const QExtOsgiServiceReference& reference, T service) = 0;
};

#endif // _QEXTOSGISERVICETRACKERCUSTOMIZER_H
