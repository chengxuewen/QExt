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

#include <qextDesignerAbstractWidgetBox.h>

QT_BEGIN_NAMESPACE

/*!
    \class QExtDesignerAbstractWidgetBox

    \brief The QExtDesignerAbstractWidgetBox class allows you to control
    the contents of Qt Designer's widget box.

    \inmodule QtDesigner

    QExtDesignerAbstractWidgetBox contains a collection of functions
    that is typically used to manipulate the contents of \QD's widget
    box.

    \QD uses an XML file to populate its widget box. The name of that
    file is one of the widget box's properties, and you can retrieve
    it using the fileName() function.

    QExtDesignerAbstractWidgetBox also provides the save() function that
    saves the contents of the widget box in the file specified by the
    widget box's file name property. If you have made changes to the
    widget box, for example by dropping a widget into the widget box,
    without calling the save() function, the original content can be
    restored by a simple invocation of the load() function:

    \snippet lib/tools_designer_src_lib_sdk_abstractwidgetbox.cpp 0

    The QExtDesignerAbstractWidgetBox class is not intended to be
    instantiated directly. You can retrieve an interface to Qt
    Designer's widget box using the
    QExtDesignerAbstractFormEditor::widgetBox() function. A pointer to
    \QD's current QExtDesignerAbstractFormEditor object (\c formEditor
    in the example above) is provided by the
    QDesignerCustomWidgetInterface::initialize() function's
    parameter. When implementing a custom widget plugin, you must
    subclass the QDesignerCustomWidgetInterface to expose your plugin
    to \QD.

    If you want to save your changes, and at the same time preserve
    the original contents, you can use the save() function combined
    with the setFileName() function to save your changes into another
    file. Remember to store the name of the original file first:

    \snippet lib/tools_designer_src_lib_sdk_abstractwidgetbox.cpp 1

    Then you can restore the original contents of the widget box by
    resetting the file name to the original file and calling load():

    \snippet lib/tools_designer_src_lib_sdk_abstractwidgetbox.cpp 2

    In a similar way, you can later use your customized XML file:

    \snippet lib/tools_designer_src_lib_sdk_abstractwidgetbox.cpp 3


    \sa QExtDesignerAbstractFormEditor
*/

/*!
    Constructs a widget box interface with the given \a parent and
    the specified window \a flags.
*/
QExtDesignerAbstractWidgetBox::QExtDesignerAbstractWidgetBox(QWidget *parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
{
}

/*!
    Destroys the widget box interface.
*/
QExtDesignerAbstractWidgetBox::~QExtDesignerAbstractWidgetBox()
{
}

/*!
    \internal
*/
int QExtDesignerAbstractWidgetBox::findOrInsertCategory(const QString &categoryName)
{
    int count = categoryCount();
    for (int index=0; index<count; ++index) {
        Category c = category(index);
        if (c.name() == categoryName)
            return index;
    }

    addCategory(Category(categoryName));
    return count;
}

/*!
    \internal
    \fn int QExtDesignerAbstractWidgetBox::categoryCount() const
*/

/*!
    \internal
    \fn Category QExtDesignerAbstractWidgetBox::category(int cat_idx) const
*/

/*!
    \internal
    \fn void QExtDesignerAbstractWidgetBox::addCategory(const Category &cat)
*/

/*!
    \internal
    \fn void QExtDesignerAbstractWidgetBox::removeCategory(int cat_idx)
*/

/*!
    \internal
    \fn int QExtDesignerAbstractWidgetBox::widgetCount(int cat_idx) const
*/

/*!
    \internal
    \fn Widget QExtDesignerAbstractWidgetBox::widget(int cat_idx, int wgt_idx) const
*/

/*!
    \internal
    \fn void QExtDesignerAbstractWidgetBox::addWidget(int cat_idx, const Widget &wgt)
*/

/*!
    \internal
    \fn void QExtDesignerAbstractWidgetBox::removeWidget(int cat_idx, int wgt_idx)
*/

/*!
    \internal
    \fn void QExtDesignerAbstractWidgetBox::dropWidgets(const QList<QExtDesignerDnDItemInterface*> &item_list, const QPoint &global_mouse_pos)

*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::setFileName(const QString &fileName)

    Sets the XML file that \QD will use to populate its widget box, to
    \a fileName. You must call load() to update the widget box with
    the new XML file.

    \sa fileName(), load()
*/

/*!
    \fn QString QExtDesignerAbstractWidgetBox::fileName() const

    Returns the name of the XML file \QD is currently using to
    populate its widget box.

    \sa setFileName()
*/

/*!
    \fn bool QExtDesignerAbstractWidgetBox::load()

    Populates \QD's widget box by loading (or reloading) the currently
    specified XML file. Returns true if the file is successfully
    loaded; otherwise false.

    \sa setFileName()
*/

/*!
    \fn bool QExtDesignerAbstractWidgetBox::save()

    Saves the contents of \QD's widget box in the file specified by
    the fileName() function. Returns true if the content is
    successfully saved; otherwise false.

    \sa fileName(), setFileName()
*/


/*!
    \internal

    \class QExtDesignerAbstractWidgetBox::Widget

    \brief The Widget class specified a widget in Qt Designer's widget
    box component.
*/

/*!
    \enum QExtDesignerAbstractWidgetBox::Widget::Type

    \value Default
    \value Custom
*/

/*!
    \fn QExtDesignerAbstractWidgetBox::Widget::Widget(const QString &aname, const QString &xml, const QString &icon_name, Type atype)
*/

/*!
    \fn QString QExtDesignerAbstractWidgetBox::Widget::name() const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Widget::setName(const QString &aname)
*/

/*!
    \fn QString QExtDesignerAbstractWidgetBox::Widget::domXml() const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Widget::setDomXml(const QString &xml)
*/

/*!
    \fn QString QExtDesignerAbstractWidgetBox::Widget::iconName() const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Widget::setIconName(const QString &icon_name)
*/

/*!
    \fn Type QExtDesignerAbstractWidgetBox::Widget::type() const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Widget::setType(Type atype)
*/

/*!
    \fn bool QExtDesignerAbstractWidgetBox::Widget::isNull() const
*/


/*!
    \class QExtDesignerAbstractWidgetBox::Category
    \brief The Category class specifies a category in Qt Designer's widget box component.
    \internal
*/

/*!
    \enum QExtDesignerAbstractWidgetBox::Category::Type

    \value Default
    \value Scratchpad
*/

/*!
    \fn QExtDesignerAbstractWidgetBox::Category::Category(const QString &aname, Type atype)
*/

/*!
    \fn QString QExtDesignerAbstractWidgetBox::Category::name() const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Category::setName(const QString &aname)
*/

/*!
    \fn int QExtDesignerAbstractWidgetBox::Category::widgetCount() const
*/

/*!
    \fn Widget QExtDesignerAbstractWidgetBox::Category::widget(int idx) const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Category::removeWidget(int idx)
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Category::addWidget(const Widget &awidget)
*/

/*!
    \fn Type QExtDesignerAbstractWidgetBox::Category::type() const
*/

/*!
    \fn void QExtDesignerAbstractWidgetBox::Category::setType(Type atype)
*/

/*!
    \fn bool QExtDesignerAbstractWidgetBox::Category::isNull() const
*/

/*!
    \typedef QExtDesignerAbstractWidgetBox::CategoryList
    \internal
*/

/*!
    \typedef QExtDesignerAbstractWidgetBox::WidgetList
    \internal
*/

QT_END_NAMESPACE
