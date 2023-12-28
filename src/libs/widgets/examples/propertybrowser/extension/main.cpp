// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#include <QApplication>
#include <qextPropertyBrowser.h>

class VariantManager : public QExtVariantPropertyManager
{
    Q_OBJECT
public:
    VariantManager(QObject *parent = 0);
    ~VariantManager();

    virtual QVariant value(const QExtProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;

    QString valueText(const QExtProperty *property) const;

public slots:
    virtual void setValue(QExtProperty *property, const QVariant &val);
protected:
    virtual void initializeProperty(QExtProperty *property);
    virtual void uninitializeProperty(QExtProperty *property);
private slots:
    void slotValueChanged(QExtProperty *property, const QVariant &value);
    void slotPropertyDestroyed(QExtProperty *property);
private:
    struct Data {
        QVariant value;
        QExtVariantProperty *x;
        QExtVariantProperty *y;
    };
    QMap<const QExtProperty *, Data> propertyToData;
    QMap<const QExtProperty *, QExtProperty *> xToProperty;
    QMap<const QExtProperty *, QExtProperty *> yToProperty;
};

VariantManager::VariantManager(QObject *parent)
    : QExtVariantPropertyManager(parent)
{
    connect(this, SIGNAL(valueChanged(QExtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QExtProperty *, const QVariant &)));
    connect(this, SIGNAL(propertyDestroyed(QExtProperty *)),
                this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

VariantManager::~VariantManager()
{

}

void VariantManager::slotValueChanged(QExtProperty *property, const QVariant &value)
{
    if (xToProperty.contains(property)) {
        QExtProperty *pointProperty = xToProperty[property];
        QVariant v = this->value(pointProperty);
        QPointF p = v.value<QPointF>();
        p.setX(value.value<double>());
        setValue(pointProperty, p);
    } else if (yToProperty.contains(property)) {
        QExtProperty *pointProperty = yToProperty[property];
        QVariant v = this->value(pointProperty);
        QPointF p = v.value<QPointF>();
        p.setY(value.value<double>());
        setValue(pointProperty, p);
    }
}

void VariantManager::slotPropertyDestroyed(QExtProperty *property)
{
    if (xToProperty.contains(property)) {
        QExtProperty *pointProperty = xToProperty[property];
        propertyToData[pointProperty].x = 0;
        xToProperty.remove(property);
    } else if (yToProperty.contains(property)) {
        QExtProperty *pointProperty = yToProperty[property];
        propertyToData[pointProperty].y = 0;
        yToProperty.remove(property);
    }
}

bool VariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == QVariant::PointF)
        return true;
    return QExtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int VariantManager::valueType(int propertyType) const
{
    if (propertyType == QVariant::PointF)
        return QVariant::PointF;
    return QExtVariantPropertyManager::valueType(propertyType);
}

QVariant VariantManager::value(const QExtProperty *property) const
{
    if (propertyToData.contains(property))
        return propertyToData[property].value;
    return QExtVariantPropertyManager::value(property);
}

QString VariantManager::valueText(const QExtProperty *property) const
{
    if (propertyToData.contains(property)) {
        QVariant v = propertyToData[property].value;
        QPointF p = v.value<QPointF>();
        return QString(tr("(%1, %2)").arg(QString::number(p.x()))
                                 .arg(QString::number(p.y())));
    }
    return QExtVariantPropertyManager::valueText(property);
}

void VariantManager::setValue(QExtProperty *property, const QVariant &val)
{
    if (propertyToData.contains(property)) {
        if (val.type() != QVariant::PointF && !val.canConvert(QVariant::PointF))
            return;
        QPointF p = val.value<QPointF>();
        Data d = propertyToData[property];
        d.value = p;
        if (d.x)
            d.x->setValue(p.x());
        if (d.y)
            d.y->setValue(p.y());
        propertyToData[property] = d;
        emit propertyChanged(property);
        emit valueChanged(property, p);
        return;
    }
    QExtVariantPropertyManager::setValue(property, val);
}

void VariantManager::initializeProperty(QExtProperty *property)
{
    if (propertyType(property) == QVariant::PointF) {
        Data d;

        d.value = QPointF(0, 0);

        VariantManager *that = (VariantManager *)this;

        d.x = that->addProperty(QVariant::Double);
        d.x->setPropertyName(tr("Position X"));
        property->addSubProperty(d.x);
        xToProperty[d.x] = property;

        d.y = that->addProperty(QVariant::Double);
        d.y->setPropertyName(tr("Position Y"));
        property->addSubProperty(d.y);
        yToProperty[d.y] = property;

        propertyToData[property] = d;
    }
    QExtVariantPropertyManager::initializeProperty(property);
}

void VariantManager::uninitializeProperty(QExtProperty *property)
{
    if (propertyToData.contains(property)) {
        Data d = propertyToData[property];
        if (d.x)
            xToProperty.remove(d.x);
        if (d.y)
            yToProperty.remove(d.y);
        propertyToData.remove(property);
    }
    QExtVariantPropertyManager::uninitializeProperty(property);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    VariantManager *variantManager = new VariantManager();

    QExtVariantProperty *item = variantManager->addProperty(QVariant::PointF,
                "PointF Property");
    item->setValue(QPointF(2.5, 13.13));

    QExtVariantEditorFactory *variantFactory = new QExtVariantEditorFactory();

    QExtTreePropertyBrowser ed1;
    QExtVariantPropertyManager *varMan = variantManager;
    ed1.setFactoryForManager(varMan, variantFactory);
    ed1.addProperty(item);


    ed1.show();

    int ret = app.exec();

    delete variantFactory;
    delete variantManager;

    return ret;
}

#include "main.moc"
