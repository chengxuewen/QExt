/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/qextDesignerAbstractIntrospection_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QExtDesignerMetaEnumInterface
    \internal
    \since 4.4

    \brief QExtDesignerMetaEnumInterface is part of \QD's introspection interface and represents an enumeration.

    \inmodule QtDesigner

    The QExtDesignerMetaEnumInterface class provides meta-data about an enumerator.

    \sa QExtDesignerMetaObjectInterface
*/

/*!
    Constructs a QExtDesignerMetaEnumInterface object.
*/

QExtDesignerMetaEnumInterface::QExtDesignerMetaEnumInterface() = default;

/*!
    Destroys the QExtDesignerMetaEnumInterface object.
*/
QExtDesignerMetaEnumInterface::~QExtDesignerMetaEnumInterface() = default;

/*!
    \fn bool QExtDesignerMetaEnumInterface::isFlag() const

    Returns true if this enumerator is used as a flag.
*/

/*!
    \fn QString QExtDesignerMetaEnumInterface::key(int index) const

    Returns the key with the given \a index.
*/

/*!
    \fn int QExtDesignerMetaEnumInterface::keyCount() const

    Returns the number of keys.
*/

/*!
    \fn int QExtDesignerMetaEnumInterface::keyToValue(const QString &key) const

    Returns the integer value of the given enumeration \a key, or -1 if \a key is not defined.
*/

/*!
    \fn int QExtDesignerMetaEnumInterface::keysToValue(const QString &keys) const

    Returns the value derived from combining together the values of the \a keys using the OR operator, or -1 if keys is not defined. Note that the strings in \a keys must be '|'-separated.
*/

/*!
    \fn QString QExtDesignerMetaEnumInterface::name() const

    Returns the name of the enumerator (without the scope).
*/

/*!
    \fn QString QExtDesignerMetaEnumInterface::scope() const

    Returns the scope this enumerator was declared in.
*/

/*!
    \fn QString QExtDesignerMetaEnumInterface::separator() const

    Returns the separator to be used when building enumeration names.
*/

/*!
    \fn int QExtDesignerMetaEnumInterface::value(int index) const

    Returns the value with the given \a index; or returns -1 if there is no such value.
*/

/*!
    \fn QString QExtDesignerMetaEnumInterface::valueToKey(int value) const

    Returns the string that is used as the name of the given enumeration \a value, or QString::null if value is not defined.
*/

/*!
    \fn QString QExtDesignerMetaEnumInterface::valueToKeys(int value) const

    Returns a byte array of '|'-separated keys that represents the given \a value.
*/

/*!
    \class QExtDesignerMetaPropertyInterface
    \internal
    \since 4.4

    \brief QExtDesignerMetaPropertyInterface is part of \QD's introspection interface and represents a property.

    \inmodule QtDesigner

    The QExtDesignerMetaPropertyInterface class provides meta-data about a property.

    \sa QExtDesignerMetaObjectInterface
*/

/*!
    Constructs a QExtDesignerMetaPropertyInterface object.
*/

QExtDesignerMetaPropertyInterface::QExtDesignerMetaPropertyInterface() = default;

/*!
    Destroys the QExtDesignerMetaPropertyInterface object.
*/

QExtDesignerMetaPropertyInterface::~QExtDesignerMetaPropertyInterface() = default;

/*!
    \enum QExtDesignerMetaPropertyInterface::Kind

   This enum indicates whether the property is of a special type.

    \value EnumKind      The property is of an enumeration type
    \value FlagKind      The property is of an flag type
    \value OtherKind     The property is of another type
 */

/*!
    \enum QExtDesignerMetaPropertyInterface::AccessFlag

    These flags specify the access the property provides.

    \value  ReadAccess   Property can be read
    \value  WriteAccess  Property can be written
    \value  ResetAccess  Property can be reset to a default value
 */

/*!
    \enum QExtDesignerMetaPropertyInterface::Attribute

    Various attributes of the  property.

    \value DesignableAttribute  Property is designable (visible  in \QD)
    \value ScriptableAttribute  Property is scriptable
    \value StoredAttribute      Property is stored, that is, not calculated
    \value UserAttribute        Property is the property that the user can edit for the QObject
 */

/*!
    \fn const QExtDesignerMetaEnumInterface *QExtDesignerMetaPropertyInterface::enumerator() const

     Returns the enumerator if this property's type is an enumerator type;
*/

/*!
    \fn Kind QExtDesignerMetaPropertyInterface::kind() const

     Returns the type of the property.
*/

/*!
    \fn AccessFlags QExtDesignerMetaPropertyInterface::accessFlags() const

     Returns a combination of access flags.
*/

/*!
    \fn Attributes QExtDesignerMetaPropertyInterface::attributes(const QObject *object) const

     Returns the attributes of the property for the gives \a object.
*/

/*!
    \fn QVariant::Type QExtDesignerMetaPropertyInterface::type() const

    Returns the type of the property.
*/

/*!
    \fn QString QExtDesignerMetaPropertyInterface::name() const

    Returns the name of the property.
*/

/*!
    \fn QString QExtDesignerMetaPropertyInterface::typeName() const

    Returns the name of this property's type.
*/


/*!
    \fn int QExtDesignerMetaPropertyInterface::userType() const

    Returns this property's user type.
*/

/*!
    \fn bool QExtDesignerMetaPropertyInterface::hasSetter() const

    Returns whether getter and setter methods exist for this property.
*/

/*!
    \fn QVariant QExtDesignerMetaPropertyInterface::read(const QObject *object) const

    Reads the property's value from the given \a object. Returns the value if it was able to read it; otherwise returns an invalid variant.
*/

/*!
    \fn bool QExtDesignerMetaPropertyInterface::reset(QObject *object) const

    Resets the property for the given \a object with a reset method. Returns true if the reset worked; otherwise returns false.
*/

/*!
    \fn bool QExtDesignerMetaPropertyInterface::write(QObject *object, const QVariant &value) const

    Writes \a value as the property's value to the given \a object. Returns true if the write succeeded; otherwise returns false.
*/

/*!
    \class QExtDesignerMetaMethodInterface
    \internal
    \since 4.4

    \brief QExtDesignerMetaMethodInterface is part of \QD's introspection interface and represents a member function.

    \inmodule QtDesigner

    The QExtDesignerMetaMethodInterface class provides meta-data about a member function.

    \sa QExtDesignerMetaObjectInterface
*/

/*!
    Constructs a QExtDesignerMetaMethodInterface object.
*/

QExtDesignerMetaMethodInterface::QExtDesignerMetaMethodInterface() = default;

/*!
    Destroys the QExtDesignerMetaMethodInterface object.
*/

QExtDesignerMetaMethodInterface::~QExtDesignerMetaMethodInterface() = default;

/*!
    \enum QExtDesignerMetaMethodInterface::MethodType

    This enum specifies the type of the method

    \value Method  The function is a plain member function.
    \value Signal  The function is a signal.
    \value Slot    The function is a slot.
    \value Constructor The function is a constructor.

*/

/*!
    \enum QExtDesignerMetaMethodInterface::Access

    This enum represents the access specification of the method

    \value Private   A private member function
    \value Protected A protected member function
    \value Public    A public member function
*/

/*!
    \fn  QExtDesignerMetaMethodInterface::Access  QExtDesignerMetaMethodInterface::access() const

     Returns the access specification of this method.
*/


/*!
    \fn  QExtDesignerMetaMethodInterface::MethodType  QExtDesignerMetaMethodInterface::methodType() const

    Returns the type of this method.
*/

/*!
    \fn QStringList QExtDesignerMetaMethodInterface::parameterNames() const

    Returns a list of parameter names.
*/

/*!
    \fn QStringList QExtDesignerMetaMethodInterface::parameterTypes() const

    Returns a list of parameter types.
*/

/*!
    \fn QString QExtDesignerMetaMethodInterface::signature() const

    Returns the signature of this method.
*/

/*!
    \fn QString QExtDesignerMetaMethodInterface::normalizedSignature() const

     Returns the normalized signature of this method (suitable as signal/slot specification).
*/


/*!
    \fn QString QExtDesignerMetaMethodInterface::tag() const

    Returns the tag associated with this method.
*/

/*!
    \fn QString QExtDesignerMetaMethodInterface::typeName() const

    Returns the return type of this method, or an empty string if the return type is void.
*/

/*!
    \class QExtDesignerMetaObjectInterface
    \internal
    \since 4.4

    \brief QExtDesignerMetaObjectInterface is part of \QD's introspection interface and provides meta-information about Qt objects

    \inmodule QtDesigner

    The QExtDesignerMetaObjectInterface class provides meta-data about Qt objects. For a given object, it can be obtained
    by querying QExtDesignerIntrospectionInterface.

    \sa QExtDesignerIntrospectionInterface
*/

/*!
    Constructs a QExtDesignerMetaObjectInterface object.
*/

QExtDesignerMetaObjectInterface::QExtDesignerMetaObjectInterface() = default;

/*!
    Destroys the QExtDesignerMetaObjectInterface object.
*/

QExtDesignerMetaObjectInterface::~QExtDesignerMetaObjectInterface() = default;

/*!
    \fn QString QExtDesignerMetaObjectInterface::className() const

    Returns the class name.
*/

/*!
    \fn const QExtDesignerMetaEnumInterface *QExtDesignerMetaObjectInterface::enumerator(int index) const

    Returns the meta-data for the enumerator with the given \a index.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::enumeratorCount() const

    Returns the number of enumerators in this class.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::enumeratorOffset() const

    Returns the enumerator offset for this class; i.e. the index position of this class's first enumerator.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::indexOfEnumerator(const QString &name) const

    Finds enumerator \a name and returns its index; otherwise returns -1.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::indexOfMethod(const QString &method) const

    Finds \a method and returns its index; otherwise returns -1.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::indexOfProperty(const QString &name) const

    Finds property \a name and returns its index; otherwise returns -1.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::indexOfSignal(const QString &signal) const

    Finds \a signal and returns its index; otherwise returns -1.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::indexOfSlot(const QString &slot) const

    Finds \a slot and returns its index; otherwise returns -1.
*/

/*!
    \fn const QExtDesignerMetaMethodInterface *QExtDesignerMetaObjectInterface::method(int index) const

    Returns the meta-data for the method with the given \a index.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::methodCount() const

    Returns the number of methods in this class. These include ordinary methods, signals, and slots.
*/

/*!
    \fn int QExtDesignerMetaObjectInterface::methodOffset() const

    Returns the method offset for this class; i.e. the index position of this class's first member function.
*/

/*!
    \fn const  QExtDesignerMetaPropertyInterface *QExtDesignerMetaObjectInterface::property(int index) const

    Returns the meta-data for the property with the given \a index.
*/
/*!
    \fn int QExtDesignerMetaObjectInterface::propertyCount() const

    Returns the number of properties in this class.
*/
/*!
    \fn int QExtDesignerMetaObjectInterface::propertyOffset() const

    Returns the property offset for this class; i.e. the index position of this class's first property.
*/

/*!
    \fn const QExtDesignerMetaObjectInterface *QExtDesignerMetaObjectInterface::superClass() const

    Returns the meta-object of the superclass, or 0 if there is no such object.
*/

/*!
    \fn const QExtDesignerMetaPropertyInterface *QExtDesignerMetaObjectInterface::userProperty() const

    Returns the property that has the USER flag set to true.
*/

/*!
    \class QExtDesignerIntrospectionInterface
    \internal
    \since 4.4

    \brief QExtDesignerIntrospectionInterface provides access to a QExtDesignerMetaObjectInterface for a given Qt object.

    \inmodule QtDesigner

    QExtDesignerIntrospectionInterface is the main class of \QD's introspection interface. These
    interfaces provide a layer of abstraction around QMetaObject and related classes to allow for the integration
    of other programming languages.

    An instance of QExtDesignerIntrospectionInterface can be obtained from the core.

    \sa QExtDesignerMetaObjectInterface
*/

/*!
    Constructs a QExtDesignerIntrospectionInterface object.
*/

QExtDesignerIntrospectionInterface::QExtDesignerIntrospectionInterface()
{
}

/*!
    Destroys the QExtDesignerIntrospectionInterface object.
*/

QExtDesignerIntrospectionInterface::~QExtDesignerIntrospectionInterface()
{
}

/*!
   \fn const QExtDesignerMetaObjectInterface* QExtDesignerIntrospectionInterface::metaObject(const QObject *object) const

   Returns the meta object of this \a object.
*/

QT_END_NAMESPACE
