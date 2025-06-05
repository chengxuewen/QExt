// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#include <QApplication>
#include <QMap>
#include <QDoubleSpinBox>

#include <qextPEPropertyEditor.h>

class DecoratedDoublePropertyManager : public QExtPEDoublePropertyManager
{
    Q_OBJECT
public:
    DecoratedDoublePropertyManager(QObject *parent = 0);
    ~DecoratedDoublePropertyManager();

    QString prefix(const QExtPEProperty *property) const;
    QString suffix(const QExtPEProperty *property) const;
public Q_SLOTS:
    void setPrefix(QExtPEProperty *property, const QString &prefix);
    void setSuffix(QExtPEProperty *property, const QString &suffix);
Q_SIGNALS:
    void prefixChanged(QExtPEProperty *property, const QString &prefix);
    void suffixChanged(QExtPEProperty *property, const QString &suffix);
protected:
    QString valueText(const QExtPEProperty *property) const;
    virtual void initializeProperty(QExtPEProperty *property);
    virtual void uninitializeProperty(QExtPEProperty *property);
private:
    struct Data {
        QString prefix;
        QString suffix;
    };
    QMap<const QExtPEProperty *, Data> propertyToData;
};

DecoratedDoublePropertyManager::DecoratedDoublePropertyManager(QObject *parent)
    : QExtPEDoublePropertyManager(parent)
{
}

DecoratedDoublePropertyManager::~DecoratedDoublePropertyManager()
{
}

QString DecoratedDoublePropertyManager::prefix(const QExtPEProperty *property) const
{
    if (!propertyToData.contains(property))
        return QString();
    return propertyToData[property].prefix;
}

QString DecoratedDoublePropertyManager::suffix(const QExtPEProperty *property) const
{
    if (!propertyToData.contains(property))
        return QString();
    return propertyToData[property].suffix;
}

void DecoratedDoublePropertyManager::setPrefix(QExtPEProperty *property, const QString &prefix)
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

void DecoratedDoublePropertyManager::setSuffix(QExtPEProperty *property, const QString &suffix)
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

QString DecoratedDoublePropertyManager::valueText(const QExtPEProperty *property) const
{
    QString text = QExtPEDoublePropertyManager::valueText(property);
    if (!propertyToData.contains(property))
        return text;

    DecoratedDoublePropertyManager::Data data = propertyToData[property];
    text = data.prefix + text + data.suffix;

    return text;
}

void DecoratedDoublePropertyManager::initializeProperty(QExtPEProperty *property)
{
    propertyToData[property] = DecoratedDoublePropertyManager::Data();
    QExtPEDoublePropertyManager::initializeProperty(property);
}

void DecoratedDoublePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    propertyToData.remove(property);
    QExtPEDoublePropertyManager::uninitializeProperty(property);
}


class DecoratedDoubleSpinBoxFactory : public QExtPEAbstractWidgetFactory<DecoratedDoublePropertyManager>
{
    Q_OBJECT
public:
    DecoratedDoubleSpinBoxFactory(QObject *parent = 0);
    ~DecoratedDoubleSpinBoxFactory();
protected:
    void connectPropertyManager(DecoratedDoublePropertyManager *manager);
    QWidget *createEditor(DecoratedDoublePropertyManager *manager, QExtPEProperty *property,
                QWidget *parent);
    void disconnectPropertyManager(DecoratedDoublePropertyManager *manager);
private slots:

    void slotPrefixChanged(QExtPEProperty *property, const QString &prefix);
    void slotSuffixChanged(QExtPEProperty *property, const QString &prefix);
    void slotEditorDestroyed(QObject *object);
private:
    /* We delegate responsibilities for QExtPEDoublePropertyManager, which is a base class
       of DecoratedDoublePropertyManager to appropriate QExtPEDoubleSpinBoxFactory */
    QExtPEDoubleSpinBoxFactory *originalFactory;
    QMap<QExtPEProperty *, QList<QDoubleSpinBox *> > createdEditors;
    QMap<QDoubleSpinBox *, QExtPEProperty *> editorToProperty;
};

DecoratedDoubleSpinBoxFactory::DecoratedDoubleSpinBoxFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<DecoratedDoublePropertyManager>(parent)
{
    originalFactory = new QExtPEDoubleSpinBoxFactory(this);
}

DecoratedDoubleSpinBoxFactory::~DecoratedDoubleSpinBoxFactory()
{
    // not need to delete editors because they will be deleted by originalFactory in its destructor
}

void DecoratedDoubleSpinBoxFactory::connectPropertyManager(DecoratedDoublePropertyManager *manager)
{
    originalFactory->addPropertyManager(manager);
    connect(manager, SIGNAL(prefixChanged(QExtPEProperty *, const QString &)), this, SLOT(slotPrefixChanged(QExtPEProperty *, const QString &)));
    connect(manager, SIGNAL(suffixChanged(QExtPEProperty *, const QString &)), this, SLOT(slotSuffixChanged(QExtPEProperty *, const QString &)));
}

QWidget *DecoratedDoubleSpinBoxFactory::createEditor(DecoratedDoublePropertyManager *manager, QExtPEProperty *property,
        QWidget *parent)
{
    QExtPEAbstractWidgetFactoryBase *base = originalFactory;
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
    disconnect(manager, SIGNAL(prefixChanged(QExtPEProperty *, const QString &)), this, SLOT(slotPrefixChanged(QExtPEProperty *, const QString &)));
    disconnect(manager, SIGNAL(suffixChanged(QExtPEProperty *, const QString &)), this, SLOT(slotSuffixChanged(QExtPEProperty *, const QString &)));
}

void DecoratedDoubleSpinBoxFactory::slotPrefixChanged(QExtPEProperty *property, const QString &prefix)
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

void DecoratedDoubleSpinBoxFactory::slotSuffixChanged(QExtPEProperty *property, const QString &prefix)
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
    QMap<QDoubleSpinBox *, QExtPEProperty *>::ConstIterator itEditor =
                editorToProperty.constBegin();
    while (itEditor != editorToProperty.constEnd()) {
        if (itEditor.key() == object) {
            QDoubleSpinBox *editor = itEditor.key();
            QExtPEProperty *property = itEditor.value();
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

    QExtPEDoublePropertyManager *undecoratedManager = new QExtPEDoublePropertyManager();
    QExtPEProperty *undecoratedProperty = undecoratedManager->addProperty("Undecorated");
    undecoratedManager->setValue(undecoratedProperty, 123.45);

    DecoratedDoublePropertyManager *decoratedManager = new DecoratedDoublePropertyManager();
    QExtPEProperty *decoratedProperty = decoratedManager->addProperty("Decorated");
    decoratedManager->setPrefix(decoratedProperty, "speed: ");
    decoratedManager->setSuffix(decoratedProperty, " km/h");
    decoratedManager->setValue(decoratedProperty, 123.45);

    QExtPEDoubleSpinBoxFactory *undecoratedFactory = new QExtPEDoubleSpinBoxFactory();
    DecoratedDoubleSpinBoxFactory *decoratedFactory = new DecoratedDoubleSpinBoxFactory();

    QExtPEPropertyTreeEditor *editor = new QExtPEPropertyTreeEditor();
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
