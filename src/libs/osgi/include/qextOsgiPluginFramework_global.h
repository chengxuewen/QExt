/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#ifndef QTKPLUGINFRAMEWORK_GLOBAL_H
#define QTKPLUGINFRAMEWORK_GLOBAL_H

#include <qglobal.h>
#include <QHash>
#include <QVariant>
#include <QStringList>
#include <QSharedPointer>
#include <QLoggingCategory>

#include <QTKCore/QTKCoreGlobal>

#if defined(QTK_PLUGINFRAMEWORK_LIBRARY)
#  define QTK_PLUGINFRAMEWORK_EXPORT Q_DECL_EXPORT
#else
#  define QTK_PLUGINFRAMEWORK_EXPORT Q_DECL_IMPORT
#endif

#define QTK_PLUGINFRAMEWORK_NAMESPACE QTK_NAMESPACE::pluginframework

#define QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE namespace QTK_NAMESPACE { namespace pluginframework {
#define QTK_PLUGINFRAMEWORK_END_NAMESPACE }}
#define QTK_PLUGINFRAMEWORK_USE_NAMESPACE using namespace QTK_PLUGINFRAMEWORK_NAMESPACE;


Q_DECLARE_LOGGING_CATEGORY(qtkpluginframework)

/**
 * @ingroup QTKPluginFramework
 * @{
 */
typedef QHash<QString, QVariant> QTKProperties;
typedef QTKProperties QTKDictionary;

#if QT_VERSION < 0x040700
#include <QSharedPointer>
template<class T>
inline uint qHash(const QSharedPointer<T>& ptr)
{
  return qHash<T>(ptr.data());
}
#endif

template<class A>
QStringList getIIDs()
{
  return QStringList(qobject_interface_iid<A*>());
}

template<class A, class B>
QStringList getIIDs()
{
  QStringList ids;
  ids << qobject_interface_iid<A*>();
  ids << qobject_interface_iid<B*>();
  return ids;
}

template<class A, class B, class C>
QStringList getIIDs()
{
  QStringList ids;
  ids << qobject_interface_iid<A*>();
  ids << qobject_interface_iid<B*>();
  ids << qobject_interface_iid<C*>();
  return ids;
}

template<class A, class B, class C, class D>
QStringList getIIDs()
{
  QStringList ids;
  ids << qobject_interface_iid<A*>();
  ids << qobject_interface_iid<B*>();
  ids << qobject_interface_iid<C*>();
  ids << qobject_interface_iid<D*>();
  return ids;
}

/** @}*/

#endif // QTKPLUGINFRAMEWORK_GLOBAL_H
