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


#ifndef _QEXTOSGIPLUGINTRACKERPRIVATE_H
#define _QEXTOSGIPLUGINTRACKERPRIVATE_H

#include <qextOsgiPlugin.h>

#include <QSharedPointer>
#include <QMutex>

/**
 * \ingroup PluginFramework
 */
template<class T>
class QExtOsgiPluginTrackerPrivate
{
public:
    QExtOsgiPluginTrackerPrivate(QExtOsgiPluginTracker<T>* pt,
                                 QExtOsgiPluginContext* context, QExtOsgiPlugin::States stateMask,
                                 QExtOsgiPluginTrackerCustomizer<T>* customizer);

    ~QExtOsgiPluginTrackerPrivate();

    /**
   * Accessor method for the current QExtOsgiTrackedPlugin object. This method is only
   * intended to be used by the unsynchronized methods which do not modify the
   * trackedPlugin field.
   *
   * @return The current QExtOsgiTrackedPlugin object.
   */
    QSharedPointer<QExtOsgiTrackedPlugin<T> > tracked() const;

    /* set this to true to compile in debug messages */
    static const bool DEBUG_FLAG; //	= false;

    /**
   * The Bundle Context used by this <code>QExtOsgiPluginTracker</code>.
   */
    QExtOsgiPluginContext* const context;

    /**
   * The <code>QExtOsgiPluginTrackerCustomizer</code> object for this tracker.
   */
    QExtOsgiPluginTrackerCustomizer<T>* customizer;

    /**
   * Tracked plugins: <code>QExtOsgiPlugin</code> object -> customized Object and
   * plugin listener slot.
   */
    QSharedPointer<QExtOsgiTrackedPlugin<T> > trackedPlugin;

    /**
   * State mask for plugins being tracked. This field contains the ORed values
   * of the plugin states being tracked.
   */
    QExtOsgiPlugin::States mask;

    mutable QMutex mutex;

private:

    inline QExtOsgiPluginTracker<T>* q_func()
    {
        return static_cast<QExtOsgiPluginTracker<T> *>(q_ptr);
    }

    inline const QExtOsgiPluginTracker<T>* q_func() const
    {
        return static_cast<const QExtOsgiPluginTracker<T> *>(q_ptr);
    }

    friend class QExtOsgiPluginTracker<T>;

    QExtOsgiPluginTracker<T> * const q_ptr;
};


//----------------------------------------------------------------------------
template<class T>
const bool QExtOsgiPluginTrackerPrivate<T>::DEBUG_FLAG = false;

//----------------------------------------------------------------------------
template<class T>
QExtOsgiPluginTrackerPrivate<T>::QExtOsgiPluginTrackerPrivate(
    QExtOsgiPluginTracker<T>* pt, QExtOsgiPluginContext* context,
    QExtOsgiPlugin::States stateMask, QExtOsgiPluginTrackerCustomizer<T>* customizer)
    : context(context), customizer(customizer), mask(stateMask), q_ptr(pt)
{
    this->customizer = customizer ? customizer : q_func();
}

//----------------------------------------------------------------------------
template<class T>
QExtOsgiPluginTrackerPrivate<T>::~QExtOsgiPluginTrackerPrivate()
{
    if (customizer != q_func())
    {
        delete customizer;
    }
}

//----------------------------------------------------------------------------
template<class T>
QSharedPointer<QExtOsgiTrackedPlugin<T> > QExtOsgiPluginTrackerPrivate<T>::tracked() const
{
    return trackedPlugin;
}


#endif // _QEXTOSGIPLUGINTRACKERPRIVATE_H
