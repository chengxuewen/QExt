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

#ifndef _QEXTOSGIDEBUGOPTIONSLISTENER_H
#define _QEXTOSGIDEBUGOPTIONSLISTENER_H

#include <QtPlugin>

struct QExtOsgiDebugOptions;

/**
 * A debug options listener is notified whenever one of its plug-in option-path entries is
 * changed.  A listener is registered as a service using the QExtOsgiDebugOptions#LISTENER_SYMBOLICNAME
 * service property to specify the symbolic name of the debug options listener.
 * <p>
 * The QExtOsgiDebugOptionsListener#optionsChanged(const QExtOsgiDebugOptions&) method will automatically
 * be called upon registration of the debug options listener service. This allows the
 * listener to obtain the initial debug options. This initial call to the listener
 * will happen even if debug is not enabled at the time of registration
 * QExtOsgiDebugOptions#isDebugEnabled() will return false in this case).
 * </p>
 * A debug options listener allows a plug-in to cache trace option values in boolean fields for performance
 * and code cleanliness. For example:
 * <pre>
 * class Activator : QExtOsgiPluginActivator, QExtOsgiDebugOptionsListener
 * {
 *   static bool DEBUG_FLAG = false;
 *
 *   void start(QExtOsgiPluginContext* context)
 *   {
 *     QExtOsgiDictionary props;
 *     props.insert(QExtOsgiDebugOptions::LISTENER_SYMBOLICNAME, "com.mycompany.mybundle");
 *     context->registerService<QExtOsgiDebugOptionsListener>(this, props);
 *   }
 *
 *   void optionsChanged(const QExtOsgiDebugOptions& options)
 *   {
 *     DEBUG_FLAG = options->getBooleanOption("com.mycompany.mybundle/debug", false);
 *   }
 *
 *   void doSomeWork()
 *   {
 *     if (DEBUG_FLAG) BERRY_INFO << "foo";
 *   }
 *   ...
 * }
 * </pre>
 */
struct QExtOsgiDebugOptionsListener
{
    virtual ~QExtOsgiDebugOptionsListener() {}

    /**
   * Notifies this listener that an option-path for its plug-in has changed.
   * This method is also called initially by the QExtOsgiDebugOptions implementation
   * when the listener is registered as a service.  This allows the listener
   * to obtain the initial set of debug options without the need to
   * acquire the debug options service.
   * @param options a reference to the QExtOsgiDebugOptions
   */
    virtual void optionsChanged(const QExtOsgiDebugOptions &options) = 0;
};
Q_DECLARE_INTERFACE(QExtOsgiDebugOptionsListener, "org.qext.service.debug.DebugOptionsListener")

#endif // _QEXTOSGIDEBUGOPTIONSLISTENER_H
