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


#ifndef _QEXTOSGITRACKEDSERVICE_H
#define _QEXTOSGITRACKEDSERVICE_H

#include <qextOsgiServiceEvent.h>
// #include <private/qextOsgiPluginAbstractTracked_p.h>
// #include <private/qextOsgiTrackedServiceListener_p.h>

#include <QtGlobal>

// /**
//  * \ingroup PluginFramework
//  */
// template<typename S, typename T>
// class QExtOsgiTrackedService : public QExtOsgiTrackedServiceListener,
//                                public QExtOsgiPluginAbstractTracked<QExtOsgiServiceReference, T, QExtOsgiServiceEvent>
// {
// public:
//     QExtOsgiTrackedService(QExtOsgiServiceTracker<S, T> *serviceTracker,
//                            QExtOsgiServiceTrackerCustomizer<T> *customizer);

//     /**
//    * Slot connected to service events for the
//    * <code>QExtOsgiServiceTracker</code> class. This method must NOT be
//    * synchronized to avoid deadlock potential.
//    *
//    * @param event <code>QExtOsgiServiceEvent</code> object from the framework.
//    */
//     void serviceChanged(const QExtOsgiServiceEvent &event);

// private:
//     typedef QExtOsgiPluginAbstractTracked<QExtOsgiServiceReference, T, QExtOsgiServiceEvent> Superclass;

//     QExtOsgiServiceTracker<S, T> *serviceTracker;
//     QExtOsgiServiceTrackerCustomizer<T> *customizer;

//     /**
//    * Increment the tracking count and tell the tracker there was a
//    * modification.
//    *
//    * @GuardedBy this
//    */
//     void modified();

//     /**
//    * Call the specific customizer adding method. This method must not be
//    * called while synchronized on this object.
//    *
//    * @param item Item to be tracked.
//    * @param related Action related object.
//    * @return Customized object for the tracked item or <code>null</code>
//    *         if the item is not to be tracked.
//    */
//     T customizerAdding(QExtOsgiServiceReference item, const QExtOsgiServiceEvent &related);

//     /**
//    * Call the specific customizer modified method. This method must not be
//    * called while synchronized on this object.
//    *
//    * @param item Tracked item.
//    * @param related Action related object.
//    * @param object Customized object for the tracked item.
//    */
//     void customizerModified(QExtOsgiServiceReference item,
//                             const QExtOsgiServiceEvent &related, T object) ;

//     /**
//    * Call the specific customizer removed method. This method must not be
//    * called while synchronized on this object.
//    *
//    * @param item Tracked item.
//    * @param related Action related object.
//    * @param object Customized object for the tracked item.
//    */
//     void customizerRemoved(QExtOsgiServiceReference item,
//                            const QExtOsgiServiceEvent &related, T object) ;
// };


// //----------------------------------------------------------------------------
// template<typename S, typename T>
// QExtOsgiTrackedService<S,T>::QExtOsgiTrackedService(QExtOsgiServiceTracker<S,T> *serviceTracker,
//                                                      QExtOsgiServiceTrackerCustomizer<T> *customizer)
//     : serviceTracker(serviceTracker), customizer(customizer)
// {

// }

// //----------------------------------------------------------------------------
// template<class S, class T>
// void QExtOsgiTrackedService<S,T>::serviceChanged(const QExtOsgiServiceEvent &event)
// {
//     /*
//    * Check if we had a delayed call (which could happen when we
//    * close).
//    */
//     if (this->closed)
//     {
//         return;
//     }

//     QExtOsgiServiceReference reference = event.getServiceReference();
//     if (serviceTracker->d_func()->DEBUG_FLAG)
//     {
//         qDebug() << "qextOsgiTrackedService::serviceChanged["
//                  << event.getType() << "]: " << reference;
//     }

//     switch (event.getType())
//     {
//     case QExtOsgiServiceEvent::REGISTERED :
//     case QExtOsgiServiceEvent::MODIFIED :
//     {
//         if (!serviceTracker->d_func()->listenerFilter.isNull())
//         { // service listener added with filter
//             this->track(reference, event);
//             /*
//        * If the customizer throws an unchecked exception, it
//        * is safe to let it propagate
//        */
//         }
//         else
//         { // service listener added without filter
//             if (serviceTracker->d_func()->filter.match(reference))
//             {
//                 this->track(reference, event);
//                 /*
//          * If the customizer throws an unchecked exception,
//          * it is safe to let it propagate
//          */
//             }
//             else
//             {
//                 this->untrack(reference, event);
//                 /*
//          * If the customizer throws an unchecked exception,
//          * it is safe to let it propagate
//          */
//             }
//         }
//         break;
//     }
//     case QExtOsgiServiceEvent::MODIFIED_ENDMATCH :
//     case QExtOsgiServiceEvent::UNREGISTERING :
//         this->untrack(reference, event);
//         /*
//      * If the customizer throws an unchecked exception, it is
//      * safe to let it propagate
//      */
//         break;
//     }
// }

// //----------------------------------------------------------------------------
// template<class S, class T>
// void QExtOsgiTrackedService<S,T>::modified()
// {
//     Superclass::modified(); /* increment the modification count */
//     serviceTracker->d_func()->modified();
// }

// //----------------------------------------------------------------------------
// template<class S, class T>
// T QExtOsgiTrackedService<S,T>::customizerAdding(QExtOsgiServiceReference item,
//                                                  const QExtOsgiServiceEvent &related)
// {
//     Q_UNUSED(related)
//     return customizer->addingService(item);
// }

// //----------------------------------------------------------------------------
// template<class S, class T>
// void QExtOsgiTrackedService<S,T>::customizerModified(QExtOsgiServiceReference item,
//                                                       const QExtOsgiServiceEvent &related,
//                                                       T object)
// {
//     Q_UNUSED(related)
//     customizer->modifiedService(item, object);
// }

// //----------------------------------------------------------------------------
// template<class S, class T>
// void QExtOsgiTrackedService<S,T>::customizerRemoved(QExtOsgiServiceReference item,
//                                                      const QExtOsgiServiceEvent &related,
//                                                      T object)
// {
//     Q_UNUSED(related)
//     customizer->removedService(item, object);
// }


#endif // _QEXTOSGITRACKEDSERVICE_H
