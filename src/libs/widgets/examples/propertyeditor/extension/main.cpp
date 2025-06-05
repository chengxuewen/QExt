// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#include <QApplication>
#include <qextPEPropertyEditor.h>

class VariantManager : public QExtPEVariantPropertyManager
{
    Q_OBJECT
public:
    VariantManager(QObject *parent = 0);
    ~VariantManager();

    virtual QVariant value(const QExtPEProperty *property) const;
    virtual int valueType(int propertyType) const;
    virtual bool isPropertyTypeSupported(int propertyType) const;

    QString valueText(const QExtPEProperty *property) const;

public slots:
    virtual void setValue(QExtPEProperty *property, const QVariant &val);
protected:
    virtual void initializeProperty(QExtPEProperty *property);
    virtual void uninitializeProperty(QExtPEProperty *property);
private slots:
    void slotValueChanged(QExtPEProperty *property, const QVariant &value);
    void slotPropertyDestroyed(QExtPEProperty *property);
private:
    struct Data
    {
        QVariant value;
        QExtPEVariantProperty *x;
        QExtPEVariantProperty *y;
    };
    QMap<const QExtPEProperty *, Data> propertyToData;
    QMap<const QExtPEProperty *, QExtPEProperty *> xToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> yToProperty;
};

VariantManager::VariantManager(QObject *parent)
    : QExtPEVariantPropertyManager(parent)
{
    connect(this, SIGNAL(valueChanged(QExtPEProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QExtPEProperty *, const QVariant &)));
    connect(this, SIGNAL(propertyDestroyed(QExtPEProperty *)),
                this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

VariantManager::~VariantManager()
{

}

void VariantManager::slotValueChanged(QExtPEProperty *property, const QVariant &value)
{
    if (xToProperty.contains(property))
    {
        QExtPEProperty *pointProperty = xToProperty[property];
        QVariant v = this->value(pointProperty);
        QPointF p = v.value<QPointF>();
        p.setX(value.value<double>());
        this->setValue(pointProperty, p);
    }
    else if (yToProperty.contains(property))
    {
        QExtPEProperty *pointProperty = yToProperty[property];
        QVariant v = this->value(pointProperty);
        QPointF p = v.value<QPointF>();
        p.setY(value.value<double>());
        this->setValue(pointProperty, p);
    }
}

void VariantManager::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (xToProperty.contains(property))
    {
        QExtPEProperty *pointProperty = xToProperty[property];
        propertyToData[pointProperty].x = 0;
        xToProperty.remove(property);
    }
    else if (yToProperty.contains(property))
    {
        QExtPEProperty *pointProperty = yToProperty[property];
        propertyToData[pointProperty].y = 0;
        yToProperty.remove(property);
    }
}

bool VariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == QVariant::PointF)
    {
        return true;
    }
    return QExtPEVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int VariantManager::valueType(int propertyType) const
{
    if (propertyType == QVariant::PointF)
    {
        return QVariant::PointF;
    }
    return QExtPEVariantPropertyManager::valueType(propertyType);
}

QVariant VariantManager::value(const QExtPEProperty *property) const
{
    if (propertyToData.contains(property))
    {
        return propertyToData[property].value;
    }
    return QExtPEVariantPropertyManager::value(property);
}

QString VariantManager::valueText(const QExtPEProperty *property) const
{
    if (propertyToData.contains(property))
    {
        QVariant v = propertyToData[property].value;
        QPointF p = v.value<QPointF>();
        return QString(tr("(%1, %2)").arg(QString::number(p.x())).arg(QString::number(p.y())));
    }
    return QExtPEVariantPropertyManager::valueText(property);
}

void VariantManager::setValue(QExtPEProperty *property, const QVariant &val)
{
    if (propertyToData.contains(property))
    {
        if (val.type() != QVariant::PointF && !val.canConvert(QVariant::PointF))
        {
            return;
        }
        QPointF p = val.value<QPointF>();
        Data d = propertyToData[property];
        d.value = p;
        if (d.x)
        {
            d.x->setValue(p.x());
        }
        if (d.y)
        {
            d.y->setValue(p.y());
        }
        propertyToData[property] = d;
        emit propertyChanged(property);
        emit valueChanged(property, p);
        return;
    }
    QExtPEVariantPropertyManager::setValue(property, val);
}

void VariantManager::initializeProperty(QExtPEProperty *property)
{
    if (propertyType(property) == QVariant::PointF)
    {
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
    QExtPEVariantPropertyManager::initializeProperty(property);
}

void VariantManager::uninitializeProperty(QExtPEProperty *property)
{
    if (propertyToData.contains(property))
    {
        Data d = propertyToData[property];
        if (d.x)
        {
            xToProperty.remove(d.x);
        }
        if (d.y)
        {
            yToProperty.remove(d.y);
        }
        propertyToData.remove(property);
    }
    QExtPEVariantPropertyManager::uninitializeProperty(property);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    VariantManager *variantManager = new VariantManager();

    QExtPEVariantProperty *item = variantManager->addProperty(QVariant::PointF, "PointF Property");
    item->setValue(QPointF(2.5, 13.13));

    QExtPEVariantEditorFactory *variantFactory = new QExtPEVariantEditorFactory();

    QExtPEPropertyTreeEditor ed1;
    QExtPEVariantPropertyManager *varMan = variantManager;
    ed1.setFactoryForManager(varMan, variantFactory);
    ed1.addProperty(item);


    ed1.show();

    int ret = app.exec();

    delete variantFactory;
    delete variantManager;

    return ret;
}

#include "main.moc"
