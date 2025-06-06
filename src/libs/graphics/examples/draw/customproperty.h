#ifndef CUSTOMPROPERTY
#define CUSTOMPROPERTY

#include <qextPEPropertyEditor.h>

#include <QAbstractItemDelegate>
#include <QPushButton>

QT_USE_NAMESPACE
class QComboBox;
class QSlider;
class QStyleOptionViewItem;
class QAbstractItemDelegate;
class QPushButton;

class ShadeWidget : public QWidget
{
    Q_OBJECT
public:
    ShadeWidget(QWidget *parent);
public slots:
    void colorChanged( const QColor & begin,const QColor & middle,const QColor & end) ;
    void positionChanged( int position );
    void typeChanged( int type );
protected:
    void paintEvent(QPaintEvent * event);
    int m_type;
    QColor m_colorBegin;
    QColor m_colorMiddle;
    QColor m_colorEnd;
    int m_midpoint;
};

class ColorButton :public QPushButton
{
    Q_OBJECT
public:
    explicit ColorButton( QWidget * parent );
    void setValue( const QColor & color ) { m_color = color; }
    QColor value() const { return m_color;}
protected:
    void paintEvent(QPaintEvent *);
private:
    QColor m_color;
};

class QtGradientEditor :public QWidget
{
    Q_OBJECT
public:
    QtGradientEditor( QWidget * parent );
public slots:
    void colorChanged( int ) ;
    void clicked() ;
signals:
    void colorChanged( const QColor & begin,const QColor & middle,const QColor & end) ;
private:
    QComboBox *m_gradientMode;
    ColorButton *m_colorBegin;
    ColorButton *m_colorMiddle;
    ColorButton *m_colorEnd;
    QSlider   *m_midpoint;
    ShadeWidget * m_shadewidget;
};

class QtPenPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT
public:
    QtPenPropertyManager(QObject * parent = 0);
    ~QtPenPropertyManager();

    QExtPEIntPropertyManager *subIntPropertyManager() const;
    QExtPEEnumPropertyManager *subEnumPropertyManager() const;
    QPen value(const QExtPEProperty *property) const;
public Q_SLOTS:
    void setValue(QExtPEProperty *property, const QPen &val);
    void slotIntChanged(QExtPEProperty *, int);
    void slotEnumChanged(QExtPEProperty *, int);
    void slotPropertyDestroyed(QExtPEProperty *);

Q_SIGNALS:
    void valueChanged(QExtPEProperty *property, const QPen &val);
protected:
    QString valueText(const QExtPEProperty *property) const;
    QIcon valueIcon(const QExtPEProperty *property) const;
    virtual void initializeProperty(QExtPEProperty *property);
    virtual void uninitializeProperty(QExtPEProperty *property);

private:
    typedef QMap<const QExtPEProperty *, QPen> PropertyValueMap;
    PropertyValueMap m_values;

    QExtPEIntPropertyManager *m_intPropertyManager;
    QExtPEEnumPropertyManager *m_enumPropertyManager;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToWidth;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToStyle;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToCapStyle;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_propertyToJoinStyle;

    QMap<const QExtPEProperty *, QExtPEProperty *> m_widthToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_styleToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_capStyleToProperty;
    QMap<const QExtPEProperty *, QExtPEProperty *> m_joinStyleToProperty;

    Q_DISABLE_COPY(QtPenPropertyManager)

};

#endif // CUSTOMPROPERTY

