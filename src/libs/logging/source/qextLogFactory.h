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

#ifndef _QEXTLOGFACTORY_H
#define _QEXTLOGFACTORY_H

#include <qextLoggingGlobal.h>

#include <QHash>
#include <QMutex>
#include <QStringList>

class QObject;
class QMetaProperty;

class QExtLogAppender;
class QExtLogFilter;
class QExtLogLayout;

/*!
 * \brief The class QExtLogFactory provides factories for QExtLogAppender, QExtLogFilter and
 *        QExtLogLayout objects.
 *
 * The functions createAppender(), createFilter() and createLayout()
 * allow to create objects by specifying their class names. By default
 * all classes of the package are recognised with their Log4j and Log4Qt
 * classanmes. For example an object of the class QExtLogFileAppender can be
 * craeted using "org.QExt.LogFileAppender" or "QExtLogFileAppender".
 * Additional classes can be registered using registerAppender(),
 * registerFilter() and registerLayout().
 *
 * An QObject property can be set from a string value with
 * setObjectProperty(). The function handles the required error checking
 * and type conversion.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \sa QExtLogPropertyConfigurator
 */
class QEXT_LOGGING_API QExtLogFactory
{
public:
    /*!
         * Prototype for an QExtLogAppender factory function. The function creates
         * an QExtLogAppender object on the heap and returns a pointer to it.
         *
         * \sa registerAppender(), createAppender()
     */
    typedef QExtLogAppender *(*AppenderFactoryFunc)();

    /*!
         * Prototype for a QExtLogFilter factory function. The function creates
         * a QExtLogFilter object on the heap and returns a pointer to it.
         *
         * \sa registerFilter(), createFilter()
     */
    typedef QExtLogFilter *(*FilterFactoryFunc)();

    /*!
         * Prototype for a QExtLogLayout factory function. The function creates
         * a QExtLogLayout object on the heap and returns a pointer to it.
         *
         * \sa registerLayout(), createLayout()
     */
    typedef QExtLogLayout *(*LayoutFactoryFunc)();

private:
    QExtLogFactory();
    QEXT_DISABLE_COPY_MOVE(QExtLogFactory)

public:
    /*!
     * Creates an object for the class \a appenderClassName on the heap
     * and returns a pointer to it. If the class has no registered factory
     * function a null pointer is returned.
     *
     * \sa registerAppender(), unregisterAppender(), registeredAppenders()
     */
    static QExtLogAppender *createAppender(const QString &appenderClassName);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static QExtLogAppender *createAppender(const char *appenderClassName);

    /*!
     * Creates an object for the class \a filterClassName on the heap
     * and returns a pointer to it. If the class has no registered factory
     * function a null pointer is returned.
     *
     * \sa registerFilter(), unregisterFilter(), registeredFilters()
     */
    static QExtLogFilter *createFilter(const QString &filterClassName);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static QExtLogFilter *createFilter(const char *filterClassName);

    /*!
     * Creates an object for the class \a layoutClassName on the heap
     * and returns a pointer to it. If the class has no registered factory
     * function a null pointer is returned.
     *
     * \sa registerLayout(), unregisterLayout(), registeredLayouts()
     */
    static QExtLogLayout *createLayout(const QString &layoutClassName);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static QExtLogLayout *createLayout(const char *layoutClassName);

    /*!
     * Returns the QExtLogFactory instance.
     */
    static QExtLogFactory *instance();

    /*!
    * Registers the QExtLogAppender factory function \a appenderFactoryFunc
    * for the class \a appenderClassName. If a registered factory
    * function exists for the class, it is replaced with
    * \a appenderFactoryFunc.
    *
    * \sa unregisterAppender(), registeredAppenders(), createAppender()
    */
    static void registerAppender(const QString &appenderClassName,
                                 AppenderFactoryFunc appenderFactoryFunc);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void registerAppender(const char *appenderClassName,
                                 AppenderFactoryFunc appenderFactoryFunc);

    /*!
     * Registers the QExtLogFilter factory function \a filterFactoryFunc
     * for the class \a filterClassName. If a registered factory
     * function exists for the class, it is replaced with
     * \a filterFactoryFunc.
     *
     * \sa unregisterFilter(), registeredFilters(), createFilter()
     */
    static void registerFilter(const QString &filterClassName,
                               FilterFactoryFunc filterFactoryFunc);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void registerFilter(const char *filterClassName,
                               FilterFactoryFunc filterFactoryFunc);

    /*!
     * Registers the QExtLogLayout factory function \a layoutFactoryFunc
     * for the class \a filterClassName. If a registered factory
     * function exists for the class, it is replaced with
     * \a layoutFactoryFunc.
     *
     * \sa unregisterLayout(), registeredLayout(), createLayout()
     */
    static void registerLayout(const QString &layoutClassName,
                               LayoutFactoryFunc layoutFactoryFunc);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void registerLayout(const char *layoutClassName,
                               LayoutFactoryFunc layoutFactoryFunc);

    /*!
    * Returns a list of the class names for registered QExtLogAppender factory
    * functions.
    *
    * \sa registerAppender(), unregisterAppender()
    */
    static QStringList registeredAppenders();

    /*!
     * Returns a list of the class names for registered QExtLogFilter factory
     * functions.
     *
     * \sa registerFilter(), unregisterFilter()
     */
    static QStringList registeredFilters();

    /*!
     * Returns a list of the class names for registered QExtLogLayout factory
     * functions.
     *
     * \sa registerLayout(), unregisterLayout()
     */
    static QStringList registeredLayouts();

    /*!
     * Sets the property \a rProperty of the object \a pObject to the
     * value \a rValue. The function will test that the property
     * \a rProperty is writeable and of a type the function can convert to.
     * The types bool, int, QExtLogLevel and QString are supported.
     *
     * \sa QExtLogOptionConverter
     */
    static void setObjectProperty(QObject *object,
                                  const QString &property,
                                  const QString &value);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void setObjectProperty(QObject *object,
                                  const char *property,
                                  const QString &value);

    /*!
    * Unregisters the QExtLogAppender factory function for the class
    * \a rAppenderClassName.
    *
    * \sa registerAppender(), registeredAppenders()
    */
    static void unregisterAppender(const QString &appenderClassName);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void unregisterAppender(const char *appenderClassName);

    /*!
     * Unregisters the QExtLogFilter factory function for the class
     * \a filterClassName.
     *
     * \sa registerFilter(), registeredFilters()
     */
    static void unregisterFilter(const QString &filterClassName);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void unregisterFilter(const char *filterClassName);

    /*!
     * Unregisters the QExtLogLayout factory function for the class
     * \a filterClassName.
     *
     * \sa registerLayout(), registeredLayouts()
     */
    static void unregisterLayout(const QString &filterClassName);

    /*!
     * This is an overloaded member function, provided for convenience.
     */
    static void unregisterLayout(const char *layoutClassName);

private:
    QExtLogAppender *doCreateAppender(const QString &appenderClassName);
    QExtLogFilter *doCreateFilter(const QString &filterClassName);
    QExtLogLayout *doCreateLayout(const QString &layoutClassName);
    void doRegisterAppender(const QString &appenderClassName,
                            AppenderFactoryFunc appenderFactoryFunc);
    void doRegisterFilter(const QString &filterClassName,
                          FilterFactoryFunc filterFactoryFunc);
    void doRegisterLayout(const QString &filterClassName,
                          LayoutFactoryFunc layoutFactoryFunc);
    void doSetObjectProperty(QObject *object,
                             const QString &property,
                             const QString &value);
    void doUnregisterAppender(const QString &appenderClassName);
    void doUnregisterFilter(const QString &filterClassName);
    void doUnregisterLayout(const QString &filterClassName);
    void registerDefaultAppenders();
    void registerDefaultFilters();
    void registerDefaultLayouts();
    bool validateObjectProperty(QMetaProperty &metaProperty,
                                const QString &property,
                                QObject *object);

private:
    mutable QMutex mObjectGuard;
    QHash<QString, AppenderFactoryFunc> mAppenderRegistry;
    QHash<QString, FilterFactoryFunc> mFilterRegistry;
    QHash<QString, LayoutFactoryFunc> mLayoutRegistry;
};

inline QExtLogAppender *QExtLogFactory::createAppender(const QString &appenderClassName)
{
    return instance()->doCreateAppender(appenderClassName);
}

inline QExtLogAppender *QExtLogFactory::createAppender(const char *appenderClassName)
{
    return instance()->doCreateAppender(QLatin1String(appenderClassName));
}

inline QExtLogFilter *QExtLogFactory::createFilter(const QString &filterClassName)
{
    return instance()->doCreateFilter(filterClassName);
}

inline QExtLogFilter *QExtLogFactory::createFilter(const char *layoutClassName)
{
    return instance()->doCreateFilter(QLatin1String(layoutClassName));
}

inline QExtLogLayout *QExtLogFactory::createLayout(const QString &layoutClassName)
{
    return instance()->doCreateLayout(layoutClassName);
}

inline QExtLogLayout *QExtLogFactory::createLayout(const char *layoutClassName)
{
    return instance()->doCreateLayout(QLatin1String(layoutClassName));
}

inline void QExtLogFactory::registerAppender(const QString &appenderClassName,
                                      AppenderFactoryFunc appenderFactoryFunc)
{
    instance()->doRegisterAppender(appenderClassName, appenderFactoryFunc);
}

inline void QExtLogFactory::registerAppender(const char *appenderClassName,
                                      AppenderFactoryFunc appenderFactoryFunc)
{
    instance()->doRegisterAppender(QLatin1String(appenderClassName), appenderFactoryFunc);
}

inline void QExtLogFactory::registerFilter(const QString &filterClassName,
                                    FilterFactoryFunc filterFactoryFunc)
{
    instance()->doRegisterFilter(filterClassName, filterFactoryFunc);
}

inline void QExtLogFactory::registerFilter(const char *filterClassName,
                                    FilterFactoryFunc filterFactoryFunc)
{
    instance()->doRegisterFilter(QLatin1String(filterClassName), filterFactoryFunc);
}

inline void QExtLogFactory::registerLayout(const QString &filterClassName,
                                    LayoutFactoryFunc layoutFactoryFunc)
{
    instance()->doRegisterLayout(filterClassName, layoutFactoryFunc);
}

inline void QExtLogFactory::registerLayout(const char *layoutClassName,
                                    LayoutFactoryFunc layoutFactoryFunc)
{
    instance()->doRegisterLayout(QLatin1String(layoutClassName), layoutFactoryFunc);
}

inline QStringList QExtLogFactory::registeredAppenders()
{
    QMutexLocker locker(&instance()->mObjectGuard);
    return instance()->mAppenderRegistry.keys();
}

inline QStringList QExtLogFactory::registeredFilters()
{
    QMutexLocker locker(&instance()->mObjectGuard);
    return instance()->mFilterRegistry.keys();
}

inline QStringList QExtLogFactory::registeredLayouts()
{
    QMutexLocker locker(&instance()->mObjectGuard);
    return instance()->mLayoutRegistry.keys();
}

inline void QExtLogFactory::setObjectProperty(QObject *object,
                                       const QString &property,
                                       const QString &value)
{
    instance()->doSetObjectProperty(object, property, value);
}

inline void QExtLogFactory::setObjectProperty(QObject *object,
                                       const char *property,
                                       const QString &value)
{
    instance()->doSetObjectProperty(object, QLatin1String(property), value);
}

inline void QExtLogFactory::unregisterAppender(const QString &appenderClassName)
{
    instance()->doUnregisterAppender(appenderClassName);
}

inline void QExtLogFactory::unregisterAppender(const char *appenderClassName)
{
    instance()->doUnregisterAppender(QLatin1String(appenderClassName));
}

inline void QExtLogFactory::unregisterFilter(const QString &filterClassName)
{
    instance()->doUnregisterFilter(filterClassName);
}

inline void QExtLogFactory::unregisterFilter(const char *filterClassName)
{
    instance()->doUnregisterFilter(QLatin1String(filterClassName));
}

inline void QExtLogFactory::unregisterLayout(const QString &filterClassName)
{
    instance()->doUnregisterLayout(filterClassName);
}

inline void QExtLogFactory::unregisterLayout(const char *layoutClassName)
{
    instance()->doUnregisterLayout(QLatin1String(layoutClassName));
}

#endif // _QEXTLOGFACTORY_H
