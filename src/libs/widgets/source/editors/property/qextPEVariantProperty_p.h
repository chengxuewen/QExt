#ifndef _QEXTPEVARIANTPROPERTY_P_H
#define _QEXTPEVARIANTPROPERTY_P_H

#include <qextPEVariantProperty.h>

class QExtPEVariantPropertyPrivate
{
    QExtPEVariantProperty *q_ptr;
public:
    QExtPEVariantPropertyPrivate(QExtPEVariantPropertyManager *m) : manager(m) {}

    QExtPEVariantPropertyManager *manager;
};


class QExtPEVariantPropertyManagerPrivate
{
    QExtPEVariantPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEVariantPropertyManager)
public:
    QExtPEVariantPropertyManagerPrivate();

    bool m_creatingProperty;
    bool m_creatingSubProperties;
    bool m_destroyingSubProperties;
    int m_propertyType;

    void slotValueChanged(QExtPEProperty *property, int val);
    void slotRangeChanged(QExtPEProperty *property, int min, int max);
    void slotSingleStepChanged(QExtPEProperty *property, int step);
    void slotValueChanged(QExtPEProperty *property, double val);
    void slotRangeChanged(QExtPEProperty *property, double min, double max);
    void slotSingleStepChanged(QExtPEProperty *property, double step);
    void slotDecimalsChanged(QExtPEProperty *property, int prec);
    void slotValueChanged(QExtPEProperty *property, bool val);
    void slotValueChanged(QExtPEProperty *property, const QString &val);
    void slotRegExpChanged(QExtPEProperty *property, const QRegExp &regExp);
    void slotEchoModeChanged(QExtPEProperty *property, int);
    void slotValueChanged(QExtPEProperty *property, const QDate &val);
    void slotRangeChanged(QExtPEProperty *property, const QDate &min, const QDate &max);
    void slotValueChanged(QExtPEProperty *property, const QTime &val);
    void slotValueChanged(QExtPEProperty *property, const QDateTime &val);
    void slotValueChanged(QExtPEProperty *property, const QKeySequence &val);
    void slotValueChanged(QExtPEProperty *property, const QChar &val);
    void slotValueChanged(QExtPEProperty *property, const QLocale &val);
    void slotValueChanged(QExtPEProperty *property, const QPoint &val);
    void slotValueChanged(QExtPEProperty *property, const QPointF &val);
    void slotValueChanged(QExtPEProperty *property, const QSize &val);
    void slotRangeChanged(QExtPEProperty *property, const QSize &min, const QSize &max);
    void slotValueChanged(QExtPEProperty *property, const QSizeF &val);
    void slotRangeChanged(QExtPEProperty *property, const QSizeF &min, const QSizeF &max);
    void slotValueChanged(QExtPEProperty *property, const QRect &val);
    void slotConstraintChanged(QExtPEProperty *property, const QRect &val);
    void slotValueChanged(QExtPEProperty *property, const QRectF &val);
    void slotConstraintChanged(QExtPEProperty *property, const QRectF &val);
    void slotValueChanged(QExtPEProperty *property, const QColor &val);
    void slotEnumChanged(QExtPEProperty *property, int val);
    void slotEnumNamesChanged(QExtPEProperty *property, const QStringList &enumNames);
    void slotEnumIconsChanged(QExtPEProperty *property, const QMap<int, QIcon> &enumIcons);
    void slotValueChanged(QExtPEProperty *property, const QSizePolicy &val);
    void slotValueChanged(QExtPEProperty *property, const QFont &val);
    void slotValueChanged(QExtPEProperty *property, const QCursor &val);
    void slotFlagChanged(QExtPEProperty *property, int val);
    void slotFlagNamesChanged(QExtPEProperty *property, const QStringList &flagNames);
    void slotReadOnlyChanged(QExtPEProperty *property, bool readOnly);
    void slotTextVisibleChanged(QExtPEProperty *property, bool textVisible);
    void slotPropertyInserted(QExtPEProperty *property, QExtPEProperty *parent, QExtPEProperty *after);
    void slotPropertyRemoved(QExtPEProperty *property, QExtPEProperty *parent);

    void valueChanged(QExtPEProperty *property, const QVariant &val);

    int internalPropertyToType(QExtPEProperty *property) const;
    QExtPEVariantProperty *createSubProperty(QExtPEVariantProperty *parent, QExtPEVariantProperty *after,
                                           QExtPEProperty *internal);
    void removeSubProperty(QExtPEVariantProperty *property);

    QMap<int, QExtPEAbstractPropertyManager *> m_typeToPropertyManager;
    QMap<int, QMap<QString, int> > m_typeToAttributeToAttributeType;

    QMap<const QExtPEProperty *, QPair<QExtPEVariantProperty *, int> > m_propertyToType;

    QMap<int, int> m_typeToValueType;


    QMap<QExtPEProperty *, QExtPEVariantProperty *> m_internalToProperty;

    const QString m_constraintAttribute;
    const QString m_singleStepAttribute;
    const QString m_decimalsAttribute;
    const QString m_enumIconsAttribute;
    const QString m_enumNamesAttribute;
    const QString m_flagNamesAttribute;
    const QString m_maximumAttribute;
    const QString m_minimumAttribute;
    const QString m_regExpAttribute;
    const QString m_echoModeAttribute;
    const QString m_readOnlyAttribute;
    const QString m_textVisibleAttribute;
};


class QExtPEVariantEditorFactoryPrivate
{
    QExtPEVariantEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEVariantEditorFactory)
public:

    QExtPESpinBoxFactory           *m_spinBoxFactory;
    QExtPEDoubleSpinBoxFactory     *m_doubleSpinBoxFactory;
    QExtPECheckBoxFactory          *m_checkBoxFactory;
    QExtPELineEditFactory          *m_lineEditFactory;
    QExtPEDateEditFactory          *m_dateEditFactory;
    QExtPETimeEditFactory          *m_timeEditFactory;
    QExtPEDateTimeEditFactory      *m_dateTimeEditFactory;
    QExtPEKeySequenceEditorFactory *m_keySequenceEditorFactory;
    QExtPECharEditorFactory        *m_charEditorFactory;
    QExtPEEnumEditorFactory        *m_comboBoxFactory;
    QExtPECursorEditorFactory      *m_cursorEditorFactory;
    QExtPEColorEditorFactory       *m_colorEditorFactory;
    QExtPEFontEditorFactory        *m_fontEditorFactory;

    QMap<QExtPEAbstractWidgetFactoryBase *, int> m_factoryToType;
    QMap<int, QExtPEAbstractWidgetFactoryBase *> m_typeToFactory;
};


#endif // _QEXTPEVARIANTPROPERTY_P_H
