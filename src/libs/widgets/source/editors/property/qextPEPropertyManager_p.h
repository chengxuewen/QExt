#ifndef _QEXTPEPROPERTYMANAGER_P_H
#define _QEXTPEPROPERTYMANAGER_P_H

#include <qextPEPropertyManager.h>

#include <QSet>
#include <QDateTime>
#include <QCheckBox>
#include <QColorDialog>
#include <QApplication>
#include <QStylePainter>
#include <QStyleOptionButton>
template <class PrivateData, class Value>
static void setSimpleMinimumData(PrivateData *data, const Value &minVal)
{
    data->minVal = minVal;
    if (data->maxVal < data->minVal)
    {
        data->maxVal = data->minVal;
    }

    if (data->val < data->minVal)
    {
        data->val = data->minVal;
    }
}

template <class PrivateData, class Value>
static void setSimpleMaximumData(PrivateData *data, const Value &maxVal)
{
    data->maxVal = maxVal;
    if (data->minVal > data->maxVal)
    {
        data->minVal = data->maxVal;
    }

    if (data->val > data->maxVal)
    {
        data->val = data->maxVal;
    }
}

template <class PrivateData, class Value>
static void setSizeMinimumData(PrivateData *data, const Value &newMinVal)
{
    data->minVal = newMinVal;
    if (data->maxVal.width() < data->minVal.width())
    {
        data->maxVal.setWidth(data->minVal.width());
    }
    if (data->maxVal.height() < data->minVal.height())
    {
        data->maxVal.setHeight(data->minVal.height());
    }

    if (data->val.width() < data->minVal.width())
    {
        data->val.setWidth(data->minVal.width());
    }
    if (data->val.height() < data->minVal.height())
    {
        data->val.setHeight(data->minVal.height());
    }
}

template <class PrivateData, class Value>
static void setSizeMaximumData(PrivateData *data, const Value &newMaxVal)
{
    data->maxVal = newMaxVal;
    if (data->minVal.width() > data->maxVal.width())
    {
        data->minVal.setWidth(data->maxVal.width());
    }
    if (data->minVal.height() > data->maxVal.height())
    {
        data->minVal.setHeight(data->maxVal.height());
    }

    if (data->val.width() > data->maxVal.width())
    {
        data->val.setWidth(data->maxVal.width());
    }
    if (data->val.height() > data->maxVal.height())
    {
        data->val.setHeight(data->maxVal.height());
    }
}

class QExtPEAbstractPropertyManagerPrivate
{
    QExtPEAbstractPropertyManager * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPEAbstractPropertyManager)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEAbstractPropertyManagerPrivate)
public:
    explicit QExtPEAbstractPropertyManagerPrivate(QExtPEAbstractPropertyManager *q);
    virtual ~QExtPEAbstractPropertyManagerPrivate() {}

    void propertyChanged(QExtPEProperty *property);
    void propertyDestroyed(QExtPEProperty *property);
    void propertyRemoved(QExtPEProperty *property, QExtPEProperty *parentProperty);
    void propertyInserted(QExtPEProperty *property, QExtPEProperty *parentProperty, QExtPEProperty *afterProperty);

    QSet<QExtPEProperty *> mProperties;
};



class QExtPEIntPropertyManagerPrivate
{
    QExtPEIntPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEIntPropertyManager)
public:

    struct Data
    {
        Data() : val(0), minVal(-INT_MAX), maxVal(INT_MAX), singleStep(1), readOnly(false) {}
        int val;
        int minVal;
        int maxVal;
        int singleStep;
        bool readOnly;
        int minimumValue() const { return minVal; }
        int maximumValue() const { return maxVal; }
        void setMinimumValue(int newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(int newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};


class QExtPEDoublePropertyManagerPrivate
{
    QExtPEDoublePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEDoublePropertyManager)
public:

    struct Data
    {
        Data() : val(0), minVal(-INT_MAX), maxVal(INT_MAX), singleStep(1), decimals(2), readOnly(false) {}
        double val;
        double minVal;
        double maxVal;
        double singleStep;
        int decimals;
        bool readOnly;
        double minimumValue() const { return minVal; }
        double maximumValue() const { return maxVal; }
        void setMinimumValue(double newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(double newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};


class QExtPEStringPropertyManagerPrivate
{
    QExtPEStringPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEStringPropertyManager)
public:

    struct Data
    {
        Data()
            : regExp(QString(QLatin1Char('*')))
            , echoMode(QLineEdit::Normal), readOnly(false)
        {
        }
        QString val;
        QExtRegExp regExp;
        int echoMode;
        bool readOnly;
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    QMap<const QExtPEProperty *, Data> m_values;
};

static QIcon drawCheckBox(bool value)
{
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    const QStyle *style = QApplication::style();
    // Figure out size of an indicator and make sure it is not scaled down in a list view item
    // by making the pixmap as big as a list view icon and centering the indicator in it.
    // (if it is smaller, it can't be helped)
    const int indicatorWidth = style->pixelMetric(QStyle::PM_IndicatorWidth, &opt);
    const int indicatorHeight = style->pixelMetric(QStyle::PM_IndicatorHeight, &opt);
    const int listViewIconSize = indicatorWidth;
    const int pixmapWidth = indicatorWidth;
    const int pixmapHeight = qMax(indicatorHeight, listViewIconSize);

    opt.rect = QRect(0, 0, indicatorWidth, indicatorHeight);
    QPixmap pixmap = QPixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    {
        // use QStylePainter not QPainter, to draw QStyleSheetStyle IndicatorCheckBox pixmap
        QCheckBox checkBox;
        QStylePainter stylePainter(&pixmap, &checkBox);
        stylePainter.drawPrimitive(QStyle::PE_IndicatorCheckBox, opt);
    }
    return QIcon(pixmap);
}

class QExtPEBoolPropertyManagerPrivate
{
    QExtPEBoolPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEBoolPropertyManager)
public:
    QExtPEBoolPropertyManagerPrivate();

    struct Data
    {
        Data() : val(false), textVisible(true) {}
        bool val;
        bool textVisible;
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QIcon m_checkedIcon;
    QIcon m_uncheckedIcon;
};

class QExtPEDatePropertyManagerPrivate
{
    QExtPEDatePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEDatePropertyManager)
public:

    struct Data
    {
        Data() : val(QDate::currentDate()), minVal(QDate(1752, 9, 14)),
            maxVal(QDate(7999, 12, 31)) {}
        QDate val;
        QDate minVal;
        QDate maxVal;
        QDate minimumValue() const { return minVal; }
        QDate maximumValue() const { return maxVal; }
        void setMinimumValue(const QDate &newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(const QDate &newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    QString m_format;

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    QMap<const QExtPEProperty *, Data> m_values;
};

class QExtPETimePropertyManagerPrivate
{
    QExtPETimePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPETimePropertyManager)
public:

    QString m_format;

    typedef QMap<const QExtPEProperty *, QTime> PropertyValueMap;
    PropertyValueMap m_values;
};


class QExtPEDateTimePropertyManagerPrivate
{
    QExtPEDateTimePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEDateTimePropertyManager)
public:

    QString m_format;

    typedef QMap<const QExtPEProperty *, QDateTime> PropertyValueMap;
    PropertyValueMap m_values;
};


class QExtPEKeySequencePropertyManagerPrivate
{
    QExtPEKeySequencePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEKeySequencePropertyManager)
public:

    QString m_format;

    typedef QMap<const QExtPEProperty *, QKeySequence> PropertyValueMap;
    PropertyValueMap m_values;
};


class QExtPECharPropertyManagerPrivate
{
    QExtPECharPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPECharPropertyManager)
public:

    typedef QMap<const QExtPEProperty *, QChar> PropertyValueMap;
    PropertyValueMap m_values;
};



class QExtPELocalePropertyManagerPrivate
{
    QExtPELocalePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPELocalePropertyManager)
public:

    QExtPELocalePropertyManagerPrivate();

    void slotEnumChanged(QExtPEProperty *property, int value);
    void slotPropertyDestroyed(QExtPEProperty *property);

    typedef QMap<const QExtPEProperty *, QLocale> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEEnumPropertyManager *m_enumPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToLanguage;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToCountry;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_languageToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_countryToProperty;
};



class QExtPEPointPropertyManagerPrivate
{
    QExtPEPointPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEPointPropertyManager)
public:

    void slotIntChanged(QExtPEProperty *property, int value);
    void slotPropertyDestroyed(QExtPEProperty *property);

    typedef QMap<const QExtPEProperty *, QPoint> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToX;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToY;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_xToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_yToProperty;
};


class QExtPEPointFPropertyManagerPrivate
{
    QExtPEPointFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEPointFPropertyManager)
public:

    struct Data
    {
        Data() : decimals(2) {}
        QPointF val;
        int decimals;
    };

    void slotDoubleChanged(QExtPEProperty *property, double value);
    void slotPropertyDestroyed(QExtPEProperty *property);

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEDoublePropertyManager *m_doublePropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToX;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToY;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_xToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_yToProperty;
};


class QExtPESizePropertyManagerPrivate
{
    QExtPESizePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPESizePropertyManager)
public:

    void slotIntChanged(QExtPEProperty *property, int value);
    void slotPropertyDestroyed(QExtPEProperty *property);
    void setValue(QExtPEProperty *property, const QSize &val);
    void setRange(QExtPEProperty *property, const QSize &minVal, const QSize &maxVal, const QSize &val);

    struct Data
    {
        Data() : val(QSize(0, 0)), minVal(QSize(0, 0)), maxVal(QSize(INT_MAX, INT_MAX)) {}
        QSize val;
        QSize minVal;
        QSize maxVal;
        QSize minimumValue() const { return minVal; }
        QSize maximumValue() const { return maxVal; }
        void setMinimumValue(const QSize &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSize &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToW;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToH;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_wToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_hToProperty;
};


class QExtPESizeFPropertyManagerPrivate
{
    QExtPESizeFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPESizeFPropertyManager)
public:

    void slotDoubleChanged(QExtPEProperty *property, double value);
    void slotPropertyDestroyed(QExtPEProperty *property);
    void setValue(QExtPEProperty *property, const QSizeF &val);
    void setRange(QExtPEProperty *property,
                  const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val);

    struct Data
    {
        Data() : val(QSizeF(0, 0)), minVal(QSizeF(0, 0)), maxVal(QSizeF(INT_MAX, INT_MAX)), decimals(2) {}
        QSizeF val;
        QSizeF minVal;
        QSizeF maxVal;
        int decimals;
        QSizeF minimumValue() const { return minVal; }
        QSizeF maximumValue() const { return maxVal; }
        void setMinimumValue(const QSizeF &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSizeF &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEDoublePropertyManager *m_doublePropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToW;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToH;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_wToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_hToProperty;
};


class QExtPERectPropertyManagerPrivate
{
    QExtPERectPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPERectPropertyManager)
public:

    void slotIntChanged(QExtPEProperty *property, int value);
    void slotPropertyDestroyed(QExtPEProperty *property);
    void setConstraint(QExtPEProperty *property, const QRect &constraint, const QRect &val);

    struct Data
    {
        Data() : val(0, 0, 0, 0) {}
        QRect val;
        QRect constraint;
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToX;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToY;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToW;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToH;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_xToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_yToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_wToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_hToProperty;
};


class QExtPERectFPropertyManagerPrivate
{
    QExtPERectFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPERectFPropertyManager)
public:

    void slotDoubleChanged(QExtPEProperty *property, double value);
    void slotPropertyDestroyed(QExtPEProperty *property);
    void setConstraint(QExtPEProperty *property, const QRectF &constraint, const QRectF &val);

    struct Data
    {
        Data() : val(0, 0, 0, 0), decimals(2) {}
        QRectF val;
        QRectF constraint;
        int decimals;
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEDoublePropertyManager *m_doublePropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToX;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToY;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToW;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToH;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_xToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_yToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_wToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_hToProperty;
};


class QExtPEEnumPropertyManagerPrivate
{
    QExtPEEnumPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEEnumPropertyManager)
public:

    struct Data
    {
        Data() : val(-1) {}
        int val;
        QStringList enumNames;
        QMap<int, QIcon> enumIcons;
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};


class QExtPEFlagPropertyManagerPrivate
{
    QExtPEFlagPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEFlagPropertyManager)
public:

    void slotBoolChanged(QExtPEProperty *property, bool value);
    void slotPropertyDestroyed(QExtPEProperty *property);

    struct Data
    {
        Data() : val(-1) {}
        int val;
        QStringList flagNames;
    };

    typedef QMap<const QExtPEProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEBoolPropertyManager *m_boolPropertyManager;

    QMap<const QExtPEProperty *, QList<QExtPEProperty *> > m_propertyToFlags;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_flagToProperty;
};


class QExtPESizePolicyPropertyManagerPrivate
{
    QExtPESizePolicyPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPESizePolicyPropertyManager)
public:

    QExtPESizePolicyPropertyManagerPrivate();

    void slotIntChanged(QExtPEProperty *property, int value);
    void slotEnumChanged(QExtPEProperty *property, int value);
    void slotPropertyDestroyed(QExtPEProperty *property);

    typedef QMap<const QExtPEProperty *, QSizePolicy> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;
    QExtPEEnumPropertyManager *m_enumPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToHPolicy;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToVPolicy;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToHStretch;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToVStretch;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_hPolicyToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_vPolicyToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_hStretchToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_vStretchToProperty;
};

class QExtPEFontPropertyManagerPrivate
{
    QExtPEFontPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEFontPropertyManager)
public:

    QExtPEFontPropertyManagerPrivate();

    void slotIntChanged(QExtPEProperty *property, int value);
    void slotEnumChanged(QExtPEProperty *property, int value);
    void slotBoolChanged(QExtPEProperty *property, bool value);
    void slotPropertyDestroyed(QExtPEProperty *property);
    void slotFontDatabaseChanged();
    void slotFontDatabaseDelayedChange();

    QStringList m_familyNames;

    typedef QMap<const QExtPEProperty *, QFont> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;
    QExtPEEnumPropertyManager *m_enumPropertyManager;
    QExtPEBoolPropertyManager *m_boolPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToFamily;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToPointSize;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToBold;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToItalic;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToUnderline;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToStrikeOut;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToKerning;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_familyToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_pointSizeToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_boldToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_italicToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_underlineToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_strikeOutToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_kerningToProperty;

    bool m_settingValue;
    QTimer *m_fontDatabaseChangeTimer;
};


class QExtPEColorPropertyManagerPrivate
{
    QExtPEColorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEColorPropertyManager)
public:

    void slotIntChanged(QExtPEProperty *property, int value);
    void slotPropertyDestroyed(QExtPEProperty *property);

    typedef QMap<const QExtPEProperty *, QColor> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToR;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToG;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToB;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToA;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_rToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_gToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_bToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_aToProperty;
};


class QExtPECursorPropertyManagerPrivate
{
    QExtPECursorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPECursorPropertyManager)
public:
    typedef QMap<const QExtPEProperty *, QCursor> PropertyValueMap;
    PropertyValueMap m_values;
};


#endif // _QEXTPEPROPERTYMANAGER_P_H
