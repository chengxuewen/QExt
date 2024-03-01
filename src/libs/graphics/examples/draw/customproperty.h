#ifndef CUSTOMPROPERTY
#define CUSTOMPROPERTY

#include <qextPropertyBrowser.h>

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

class QtPenPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    QtPenPropertyManager(QObject * parent = 0);
    ~QtPenPropertyManager();

    QExtIntPropertyManager *subIntPropertyManager() const;
    QExtEnumPropertyManager *subEnumPropertyManager() const;
    QPen value(const QExtProperty *property) const;
public Q_SLOTS:
    void setValue(QExtProperty *property, const QPen &val);
    void slotIntChanged(QExtProperty *, int);
    void slotEnumChanged(QExtProperty *, int);
    void slotPropertyDestroyed(QExtProperty *);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QPen &val);
protected:
    QString valueText(const QExtProperty *property) const;
    QIcon valueIcon(const QExtProperty *property) const;
    virtual void initializeProperty(QExtProperty *property);
    virtual void uninitializeProperty(QExtProperty *property);

private:
    typedef QMap<const QExtProperty *, QPen> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;
    QExtEnumPropertyManager *m_enumPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToWidth;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToStyle;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToCapStyle;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToJoinStyle;

    QMap<const QExtProperty *, QExtProperty *> m_widthToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_styleToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_capStyleToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_joinStyleToProperty;

    Q_DISABLE_COPY(QtPenPropertyManager)

};

#endif // CUSTOMPROPERTY

