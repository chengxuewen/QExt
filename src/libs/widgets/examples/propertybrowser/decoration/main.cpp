// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#include <QApplication>
#include <QMap>
#include <QDoubleSpinBox>

#include <qextPropertyBrowser.h>

class DecoratedDoublePropertyManager : public QExtDoublePropertyManager
{
    Q_OBJECT
public:
    DecoratedDoublePropertyManager(QObject *parent = 0);
    ~DecoratedDoublePropertyManager();

    QString prefix(const QExtProperty *property) const;
    QString suffix(const QExtProperty *property) const;
public Q_SLOTS:
    void setPrefix(QExtProperty *property, const QString &prefix);
    void setSuffix(QExtProperty *property, const QString &suffix);
Q_SIGNALS:
    void prefixChanged(QExtProperty *property, const QString &prefix);
    void suffixChanged(QExtProperty *property, const QString &suffix);
protected:
    QString valueText(const QExtProperty *property) const;
    virtual void initializeProperty(QExtProperty *property);
    virtual void uninitializeProperty(QExtProperty *property);
private:
    struct Data {
        QString prefix;
        QString suffix;
    };
    QMap<const QExtProperty *, Data> propertyToData;
};

DecoratedDoublePropertyManager::DecoratedDoublePropertyManager(QObject *parent)
    : QExtDoublePropertyManager(parent)
{
}

DecoratedDoublePropertyManager::~DecoratedDoublePropertyManager()
{
}

QString DecoratedDoublePropertyManager::prefix(const QExtProperty *property) const
{
    if (!propertyToData.contains(property))
        return QString();
    return propertyToData[property].prefix;
}

QString DecoratedDoublePropertyManager::suffix(const QExtProperty *property) const
{
    if (!propertyToData.contains(property))
        return QString();
    return propertyToData[property].suffix;
}

void DecoratedDoublePropertyManager::setPrefix(QExtProperty *property, const QString &prefix)
{
    if (!propertyToData.contains(property))
        return;

    DecoratedDoublePropertyManager::Data data = propertyToData[property];
    if (data.prefix == prefix)
        return;

    data.prefix = prefix;
    propertyToData[property] = data;

    emit propertyChanged(property);
    emit prefixChanged(property, prefix);
}

void DecoratedDoublePropertyManager::setSuffix(QExtProperty *property, const QString &suffix)
{
    if (!propertyToData.contains(property))
        return;

    DecoratedDoublePropertyManager::Data data = propertyToData[property];
    if (data.suffix == suffix)
        return;

    data.suffix = suffix;
    propertyToData[property] = data;

    emit propertyChanged(property);
    emit suffixChanged(property, suffix);
}

QString DecoratedDoublePropertyManager::valueText(const QExtProperty *property) const
{
    QString text = QExtDoublePropertyManager::valueText(property);
    if (!propertyToData.contains(property))
        return text;

    DecoratedDoublePropertyManager::Data data = propertyToData[property];
    text = data.prefix + text + data.suffix;

    return text;
}

void DecoratedDoublePropertyManager::initializeProperty(QExtProperty *property)
{
    propertyToData[property] = DecoratedDoublePropertyManager::Data();
    QExtDoublePropertyManager::initializeProperty(property);
}

void DecoratedDoublePropertyManager::uninitializeProperty(QExtProperty *property)
{
    propertyToData.remove(property);
    QExtDoublePropertyManager::uninitializeProperty(property);
}


class DecoratedDoubleSpinBoxFactory : public QExtAbstractEditorFactory<DecoratedDoublePropertyManager>
{
    Q_OBJECT
public:
    DecoratedDoubleSpinBoxFactory(QObject *parent = 0);
    ~DecoratedDoubleSpinBoxFactory();
protected:
    void connectPropertyManager(DecoratedDoublePropertyManager *manager);
    QWidget *createEditor(DecoratedDoublePropertyManager *manager, QExtProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(DecoratedDoublePropertyManager *manager);
private slots:

    void slotPrefixChanged(QExtProperty *property, const QString &prefix);
    void slotSuffixChanged(QExtProperty *property, const QString &prefix);
    void slotEditorDestroyed(QObject *object);
private:
    /* We delegate responsibilities for QExtDoublePropertyManager, which is a base class
       of DecoratedDoublePropertyManager to appropriate QExtDoubleSpinBoxFactory */
    QExtDoubleSpinBoxFactory *originalFactory;
    QMap<QExtProperty *, QList<QDoubleSpinBox *> > createdEditors;
    QMap<QDoubleSpinBox *, QExtProperty *> editorToProperty;
};

DecoratedDoubleSpinBoxFactory::DecoratedDoubleSpinBoxFactory(QObject *parent)
    : QExtAbstractEditorFactory<DecoratedDoublePropertyManager>(parent)
{
    originalFactory = new QExtDoubleSpinBoxFactory(this);
}

DecoratedDoubleSpinBoxFactory::~DecoratedDoubleSpinBoxFactory()
{
    // not need to delete editors because they will be deleted by originalFactory in its destructor
}

void DecoratedDoubleSpinBoxFactory::connectPropertyManager(DecoratedDoublePropertyManager *manager)
{
    originalFactory->addPropertyManager(manager);
    connect(manager, SIGNAL(prefixChanged(QExtProperty *, const QString &)), this, SLOT(slotPrefixChanged(QExtProperty *, const QString &)));
    connect(manager, SIGNAL(suffixChanged(QExtProperty *, const QString &)), this, SLOT(slotSuffixChanged(QExtProperty *, const QString &)));
}

QWidget *DecoratedDoubleSpinBoxFactory::createEditor(DecoratedDoublePropertyManager *manager, QExtProperty *property,
        QWidget *parent)
{
    QExtAbstractEditorFactoryBase *base = originalFactory;
    QWidget *w = base->createEditor(property, parent);
    if (!w)
        return 0;

    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox *>(w);
    if (!spinBox)
        return 0;

    spinBox->setPrefix(manager->prefix(property));
    spinBox->setSuffix(manager->suffix(property));

    createdEditors[property].append(spinBox);
    editorToProperty[spinBox] = property;

    return spinBox;
}

void DecoratedDoubleSpinBoxFactory::disconnectPropertyManager(DecoratedDoublePropertyManager *manager)
{
    originalFactory->removePropertyManager(manager);
    disconnect(manager, SIGNAL(prefixChanged(QExtProperty *, const QString &)), this, SLOT(slotPrefixChanged(QExtProperty *, const QString &)));
    disconnect(manager, SIGNAL(suffixChanged(QExtProperty *, const QString &)), this, SLOT(slotSuffixChanged(QExtProperty *, const QString &)));
}

void DecoratedDoubleSpinBoxFactory::slotPrefixChanged(QExtProperty *property, const QString &prefix)
{
    if (!createdEditors.contains(property))
        return;

    DecoratedDoublePropertyManager *manager = propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->setPrefix(prefix);
    }
}

void DecoratedDoubleSpinBoxFactory::slotSuffixChanged(QExtProperty *property, const QString &prefix)
{
    if (!createdEditors.contains(property))
        return;

    DecoratedDoublePropertyManager *manager = propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->setSuffix(prefix);
    }
}

void DecoratedDoubleSpinBoxFactory::slotEditorDestroyed(QObject *object)
{
    QMap<QDoubleSpinBox *, QExtProperty *>::ConstIterator itEditor =
                editorToProperty.constBegin();
    while (itEditor != editorToProperty.constEnd()) {
        if (itEditor.key() == object) {
            QDoubleSpinBox *editor = itEditor.key();
            QExtProperty *property = itEditor.value();
            editorToProperty.remove(editor);
            createdEditors[property].removeAll(editor);
            if (createdEditors[property].isEmpty())
                createdEditors.remove(property);
            return;
        }
        itEditor++;
    }
}


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QExtDoublePropertyManager *undecoratedManager = new QExtDoublePropertyManager();
    QExtProperty *undecoratedProperty = undecoratedManager->addProperty("Undecorated");
    undecoratedManager->setValue(undecoratedProperty, 123.45);

    DecoratedDoublePropertyManager *decoratedManager = new DecoratedDoublePropertyManager();
    QExtProperty *decoratedProperty = decoratedManager->addProperty("Decorated");
    decoratedManager->setPrefix(decoratedProperty, "speed: ");
    decoratedManager->setSuffix(decoratedProperty, " km/h");
    decoratedManager->setValue(decoratedProperty, 123.45);

    QExtDoubleSpinBoxFactory *undecoratedFactory = new QExtDoubleSpinBoxFactory();
    DecoratedDoubleSpinBoxFactory *decoratedFactory = new DecoratedDoubleSpinBoxFactory();

    QExtTreePropertyBrowser *editor = new QExtTreePropertyBrowser();
    editor->setFactoryForManager(undecoratedManager, undecoratedFactory);
    editor->setFactoryForManager(decoratedManager, decoratedFactory);
    editor->addProperty(undecoratedProperty);
    editor->addProperty(decoratedProperty);
    editor->show();

    int ret = app.exec();

    delete decoratedFactory;
    delete decoratedManager;
    delete undecoratedFactory;
    delete undecoratedManager;
    delete editor;

    return ret;
}

#include "main.moc"
