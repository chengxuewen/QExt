#ifndef _QEXTPROPERTYBROWSER_H
#define _QEXTPROPERTYBROWSER_H

#include <qextWidgetGlobal.h>

#include <QSet>
#include <QIcon>
#include <QWidget>
#include <QLineEdit>

typedef QLineEdit::EchoMode EchoMode;

class QDate;
class QTime;
class QDateTime;
class QLocale;

class QExtAbstractPropertyManager;
class QExtPropertyPrivate;
class QEXT_WIDGETS_API QExtProperty
{
public:
    virtual ~QExtProperty();

    QList<QExtProperty *> subProperties() const;

    QExtAbstractPropertyManager *propertyManager() const;

    QString toolTip() const;
    QString statusTip() const;
    QString whatsThis() const;
    QString propertyName() const;
    bool isEnabled() const;
    bool isModified() const;

    bool hasValue() const;
    QIcon valueIcon() const;
    QString valueText() const;
    QString displayText() const;

    void setToolTip(const QString &text);
    void setStatusTip(const QString &text);
    void setWhatsThis(const QString &text);
    void setPropertyName(const QString &text);
    void setEnabled(bool enable);
    void setModified(bool modified);

    void addSubProperty(QExtProperty *property);
    void insertSubProperty(QExtProperty *property, QExtProperty *afterProperty);
    void removeSubProperty(QExtProperty *property);

protected:
    explicit QExtProperty(QExtAbstractPropertyManager *manager);
    void propertyChanged();

private:
    friend class QExtAbstractPropertyManager;
    QExtPropertyPrivate *d_ptr;
};

class QExtAbstractPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtAbstractPropertyManager : public QObject
{
    Q_OBJECT

public:
    explicit QExtAbstractPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtAbstractPropertyManager() QEXT_OVERRIDE;

    void clear() const;
    QSet<QExtProperty *> properties() const;
    QExtProperty *addProperty(const QString &name = QString());

Q_SIGNALS:
    void propertyChanged(QExtProperty *property);
    void propertyDestroyed(QExtProperty *property);
    void propertyRemoved(QExtProperty *property, QExtProperty *parent);
    void propertyInserted(QExtProperty *property, QExtProperty *parent, QExtProperty *after);

protected:
    virtual bool hasValue(const QExtProperty *property) const;
    virtual QIcon valueIcon(const QExtProperty *property) const;
    virtual QString valueText(const QExtProperty *property) const;
    virtual QString displayText(const QExtProperty *property) const;
    virtual EchoMode echoMode(const QExtProperty *) const;
    virtual void initializeProperty(QExtProperty *property) = 0;
    virtual void uninitializeProperty(QExtProperty *property);
    virtual QExtProperty *createProperty();

private:
    friend class QExtProperty;
    QExtAbstractPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtAbstractPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtAbstractPropertyManager)
};

class QEXT_WIDGETS_API QExtAbstractEditorFactoryBase : public QObject
{
    Q_OBJECT
public:
    virtual QWidget *createEditor(QExtProperty *property, QWidget *parent) = 0;

protected:
    explicit QExtAbstractEditorFactoryBase(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}

    virtual void breakConnection(QExtAbstractPropertyManager *manager) = 0;

protected Q_SLOTS:
    virtual void managerDestroyed(QObject *manager) = 0;

    friend class QExtAbstractPropertyBrowser;
};

template <typename PropertyManager>
class QExtAbstractEditorFactory : public QExtAbstractEditorFactoryBase
{
public:
    explicit QExtAbstractEditorFactory(QObject *parent) : QExtAbstractEditorFactoryBase(parent) {}
    ~QExtAbstractEditorFactory() QEXT_OVERRIDE {}

    QWidget *createEditor(QExtProperty *property, QWidget *parent) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> it(m_managers);
        while (it.hasNext())
        {
            PropertyManager *manager = it.next();
            if (manager == property->propertyManager())
            {
                return createEditor(manager, property, parent);
            }
        }
        return 0;
    }
    void addPropertyManager(PropertyManager *manager)
    {
        if (m_managers.contains(manager))
        {
            return;
        }
        m_managers.insert(manager);
        connectPropertyManager(manager);
        connect(manager, SIGNAL(destroyed(QObject *)), this, SLOT(managerDestroyed(QObject *)));
    }
    void removePropertyManager(PropertyManager *manager)
    {
        if (!m_managers.contains(manager))
            return;
        disconnect(manager, SIGNAL(destroyed(QObject *)),
                   this, SLOT(managerDestroyed(QObject *)));
        disconnectPropertyManager(manager);
        m_managers.remove(manager);
    }
    QSet<PropertyManager *> propertyManagers() const
    {
        return m_managers;
    }
    PropertyManager *propertyManager(QExtProperty *property) const
    {
        QExtAbstractPropertyManager *manager = property->propertyManager();
        QSetIterator<PropertyManager *> itManager(m_managers);
        while (itManager.hasNext())
        {
            PropertyManager *m = itManager.next();
            if (m == manager)
            {
                return m;
            }
        }
        return 0;
    }

protected:
    virtual void connectPropertyManager(PropertyManager *manager) = 0;
    virtual void disconnectPropertyManager(PropertyManager *manager) = 0;
    virtual QWidget *createEditor(PropertyManager *manager, QExtProperty *property, QWidget *parent) = 0;
    void managerDestroyed(QObject *manager) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> it(m_managers);
        while (it.hasNext())
        {
            PropertyManager *m = it.next();
            if (m == manager)
            {
                m_managers.remove(m);
                return;
            }
        }
    }

private:
    void breakConnection(QExtAbstractPropertyManager *manager) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> it(m_managers);
        while (it.hasNext())
        {
            PropertyManager *m = it.next();
            if (m == manager)
            {
                removePropertyManager(m);
                return;
            }
        }
    }

private:
    QSet<PropertyManager *> m_managers;
    friend class QtAbstractPropertyEditor;
};

class QExtAbstractPropertyBrowser;
class QExtBrowserItemPrivate;
class QEXT_WIDGETS_API QExtBrowserItem
{
public:
    QExtProperty *property() const;
    QExtBrowserItem *parent() const;
    QList<QExtBrowserItem *> children() const;
    QExtAbstractPropertyBrowser *browser() const;

private:
    explicit QExtBrowserItem(QExtAbstractPropertyBrowser *browser, QExtProperty *property, QExtBrowserItem *parent);
    ~QExtBrowserItem();

    QExtBrowserItemPrivate *d_ptr;
    friend class QExtAbstractPropertyBrowserPrivate;
};

class QExtAbstractPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtAbstractPropertyBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit QExtAbstractPropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtAbstractPropertyBrowser() QEXT_OVERRIDE;

    void clear();
    QList<QExtProperty *> properties() const;
    QList<QExtBrowserItem *> topLevelItems() const;
    QList<QExtBrowserItem *> items(QExtProperty *property) const;
    QExtBrowserItem *topLevelItem(QExtProperty *property) const;

    template <class PropertyManager>
    void setFactoryForManager(PropertyManager *manager, QExtAbstractEditorFactory<PropertyManager> *factory)
    {
        QExtAbstractPropertyManager *abstractManager = manager;
        QExtAbstractEditorFactoryBase *abstractFactory = factory;
        if (this->addFactory(abstractManager, abstractFactory))
        {
            factory->addPropertyManager(manager);
        }
    }

    void unsetFactoryForManager(QExtAbstractPropertyManager *manager);

    QExtBrowserItem *currentItem() const;
    void setCurrentItem(QExtBrowserItem *);

Q_SIGNALS:
    void currentItemChanged(QExtBrowserItem *);

public Q_SLOTS:
    void removeProperty(QExtProperty *property);
    QExtBrowserItem *addProperty(QExtProperty *property);
    QExtBrowserItem *insertProperty(QExtProperty *property, QExtProperty *afterProperty);

protected:
    virtual void itemRemoved(QExtBrowserItem *item) = 0;
    // can be tooltip, statustip, whatsthis, name, icon, text.
    virtual void itemChanged(QExtBrowserItem *item) = 0;
    virtual QWidget *createEditor(QExtProperty *property, QWidget *parent);
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) = 0;

private:
    bool addFactory(QExtAbstractPropertyManager *abstractManager, QExtAbstractEditorFactoryBase *abstractFactory);

    QExtAbstractPropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtAbstractPropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtAbstractPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QExtProperty *, QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDataChanged(QExtProperty *))
};


/***********************************************************************************************************************
** property manager
***********************************************************************************************************************/
class QEXT_WIDGETS_API QExtGroupPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtGroupPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtGroupPropertyManager() QEXT_OVERRIDE;

protected:    
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual bool hasValue(const QExtProperty *property) const QEXT_OVERRIDE;
};

class QExtIntPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtIntPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtIntPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtIntPropertyManager() QEXT_OVERRIDE;

    int value(const QExtProperty *property) const;
    int minimum(const QExtProperty *property) const;
    int maximum(const QExtProperty *property) const;
    int singleStep(const QExtProperty *property) const;
    bool isReadOnly(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, int val);
    void setMinimum(QExtProperty *property, int minVal);
    void setMaximum(QExtProperty *property, int maxVal);
    void setRange(QExtProperty *property, int minVal, int maxVal);
    void setSingleStep(QExtProperty *property, int step);
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, int val);
    void rangeChanged(QExtProperty *property, int minVal, int maxVal);
    void singleStepChanged(QExtProperty *property, int step);
    void readOnlyChanged(QExtProperty *property, bool readOnly);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtIntPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtIntPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtIntPropertyManager)
};

class QExtBoolPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtBoolPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtBoolPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtBoolPropertyManager() QEXT_OVERRIDE;

    bool value(const QExtProperty *property) const;
    bool textVisible(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, bool val);
    void setTextVisible(QExtProperty *property, bool textVisible);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, bool val);
    void textVisibleChanged(QExtProperty *property, bool);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtBoolPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtBoolPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtBoolPropertyManager)
};

class QExtDoublePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDoublePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtDoublePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDoublePropertyManager() QEXT_OVERRIDE;

    double value(const QExtProperty *property) const;
    double minimum(const QExtProperty *property) const;
    double maximum(const QExtProperty *property) const;
    double singleStep(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;
    bool isReadOnly(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, double val);
    void setMinimum(QExtProperty *property, double minVal);
    void setMaximum(QExtProperty *property, double maxVal);
    void setRange(QExtProperty *property, double minVal, double maxVal);
    void setSingleStep(QExtProperty *property, double step);
    void setDecimals(QExtProperty *property, int prec);
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, double val);
    void rangeChanged(QExtProperty *property, double minVal, double maxVal);
    void singleStepChanged(QExtProperty *property, double step);
    void decimalsChanged(QExtProperty *property, int prec);
    void readOnlyChanged(QExtProperty *property, bool readOnly);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtDoublePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDoublePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDoublePropertyManager)
};

class QExtStringPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtStringPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtStringPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtStringPropertyManager() QEXT_OVERRIDE;

    QString value(const QExtProperty *property) const;
    QRegExp regExp(const QExtProperty *property) const;
    bool isReadOnly(const QExtProperty *property) const;
    EchoMode echoMode(const QExtProperty *property) const QEXT_OVERRIDE;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QString &val);
    void setRegExp(QExtProperty *property, const QRegExp &regExp);
    void setEchoMode(QExtProperty *property, EchoMode echoMode);
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QString &val);
    void regExpChanged(QExtProperty *property, const QRegExp &regExp);
    void echoModeChanged(QExtProperty *property, const int);
    void readOnlyChanged(QExtProperty *property, bool);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    QString displayText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtStringPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtStringPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtStringPropertyManager)
};

class QExtDatePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDatePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtDatePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDatePropertyManager() QEXT_OVERRIDE;

    QDate value(const QExtProperty *property) const;
    QDate minimum(const QExtProperty *property) const;
    QDate maximum(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QDate &val);
    void setMinimum(QExtProperty *property, const QDate &minVal);
    void setMaximum(QExtProperty *property, const QDate &maxVal);
    void setRange(QExtProperty *property, const QDate &minVal, const QDate &maxVal);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QDate &val);
    void rangeChanged(QExtProperty *property, const QDate &minVal, const QDate &maxVal);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtDatePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDatePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDatePropertyManager)
};

class QExtTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtTimePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtTimePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtTimePropertyManager() QEXT_OVERRIDE;

    QTime value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QTime &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QTime &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtTimePropertyManager)
};

class QExtDateTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDateTimePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtDateTimePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDateTimePropertyManager() QEXT_OVERRIDE;

    QDateTime value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QDateTime &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QDateTime &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtDateTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDateTimePropertyManager)
};

class QExtKeySequencePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtKeySequencePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtKeySequencePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtKeySequencePropertyManager() QEXT_OVERRIDE;

    QKeySequence value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QKeySequence &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QKeySequence &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtKeySequencePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtKeySequencePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtKeySequencePropertyManager)
};

class QExtCharPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtCharPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtCharPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtCharPropertyManager() QEXT_OVERRIDE;

    QChar value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QChar &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QChar &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtCharPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCharPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtCharPropertyManager)
};

class QExtEnumPropertyManager;
class QExtLocalePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtLocalePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtLocalePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtLocalePropertyManager() QEXT_OVERRIDE;

    QExtEnumPropertyManager *subEnumPropertyManager() const;

    QLocale value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QLocale &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QLocale &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtLocalePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtLocalePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtLocalePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtPointPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPointPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtPointPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtPointPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QPoint value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QPoint &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QPoint &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtPointPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPointPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPointPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtPointFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPointFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtPointFPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtPointFPropertyManager() QEXT_OVERRIDE;

    QExtDoublePropertyManager *subDoublePropertyManager() const;

    QPointF value(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    void setDecimals(QExtProperty *property, int prec);
    void setValue(QExtProperty *property, const QPointF &val);

Q_SIGNALS:
    void decimalsChanged(QExtProperty *property, int prec);
    void valueChanged(QExtProperty *property, const QPointF &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtPointFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPointFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPointFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtSizePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtSizePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtSizePropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QSize value(const QExtProperty *property) const;
    QSize minimum(const QExtProperty *property) const;
    QSize maximum(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QSize &val);
    void setMinimum(QExtProperty *property, const QSize &minVal);
    void setMaximum(QExtProperty *property, const QSize &maxVal);
    void setRange(QExtProperty *property, const QSize &minVal, const QSize &maxVal);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QSize &val);
    void rangeChanged(QExtProperty *property, const QSize &minVal, const QSize &maxVal);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtSizePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtSizeFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizeFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    QExtSizeFPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtSizeFPropertyManager() QEXT_OVERRIDE;

    QExtDoublePropertyManager *subDoublePropertyManager() const;

    QSizeF value(const QExtProperty *property) const;
    QSizeF minimum(const QExtProperty *property) const;
    QSizeF maximum(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    void setDecimals(QExtProperty *property, int prec);
    void setValue(QExtProperty *property, const QSizeF &val);
    void setMinimum(QExtProperty *property, const QSizeF &minVal);
    void setMaximum(QExtProperty *property, const QSizeF &maxVal);
    void setRange(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

Q_SIGNALS:
    void decimalsChanged(QExtProperty *property, int prec);
    void valueChanged(QExtProperty *property, const QSizeF &val);
    void rangeChanged(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtSizeFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizeFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizeFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtRectPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtRectPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtRectPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtRectPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QRect value(const QExtProperty *property) const;
    QRect constraint(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QRect &val);
    void setConstraint(QExtProperty *property, const QRect &constraint);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QRect &val);
    void constraintChanged(QExtProperty *property, const QRect &constraint);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtRectPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtRectPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtRectPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtRectFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtRectFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtRectFPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtRectFPropertyManager() QEXT_OVERRIDE;

    QExtDoublePropertyManager *subDoublePropertyManager() const;

    QRectF value(const QExtProperty *property) const;
    QRectF constraint(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    void setDecimals(QExtProperty *property, int prec);
    void setValue(QExtProperty *property, const QRectF &val);
    void setConstraint(QExtProperty *property, const QRectF &constraint);

Q_SIGNALS:
    void decimalsChanged(QExtProperty *property, int prec);
    void valueChanged(QExtProperty *property, const QRectF &val);
    void constraintChanged(QExtProperty *property, const QRectF &constraint);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtRectFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtRectFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtRectFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtEnumPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtEnumPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtEnumPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtEnumPropertyManager() QEXT_OVERRIDE;

    int value(const QExtProperty *property) const;
    QStringList enumNames(const QExtProperty *property) const;
    QMap<int, QIcon> enumIcons(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, int val);
    void setEnumNames(QExtProperty *property, const QStringList &names);
    void setEnumIcons(QExtProperty *property, const QMap<int, QIcon> &icons);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, int val);
    void enumNamesChanged(QExtProperty *property, const QStringList &names);
    void enumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &icons);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtEnumPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtEnumPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtEnumPropertyManager)
};

class QExtFlagPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtFlagPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtFlagPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtFlagPropertyManager() QEXT_OVERRIDE;

    QExtBoolPropertyManager *subBoolPropertyManager() const;

    int value(const QExtProperty *property) const;
    QStringList flagNames(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, int val);
    void setFlagNames(QExtProperty *property, const QStringList &names);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, int val);
    void flagNamesChanged(QExtProperty *property, const QStringList &names);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtFlagPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFlagPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtFlagPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtSizePolicyPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizePolicyPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtSizePolicyPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtSizePolicyPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;
    QExtEnumPropertyManager *subEnumPropertyManager() const;

    QSizePolicy value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QSizePolicy &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QSizePolicy &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtSizePolicyPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizePolicyPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizePolicyPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtFontPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtFontPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtFontPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtFontPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;
    QExtEnumPropertyManager *subEnumPropertyManager() const;
    QExtBoolPropertyManager *subBoolPropertyManager() const;

    QFont value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QFont &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QFont &val);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtFontPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFontPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtFontPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotFontDatabaseChanged())
    Q_PRIVATE_SLOT(d_func(), void slotFontDatabaseDelayedChange())
};

class QExtColorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtColorPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtColorPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtColorPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QColor value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QColor &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QColor &val);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtColorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtColorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtColorPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtCursorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtCursorPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtCursorPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtCursorPropertyManager() QEXT_OVERRIDE;

#ifndef QT_NO_CURSOR
    QCursor value(const QExtProperty *property) const;
#endif

public Q_SLOTS:
    void setValue(QExtProperty *property, const QCursor &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QCursor &val);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtCursorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCursorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtCursorPropertyManager)
};


/***********************************************************************************************************************
** editor factory
***********************************************************************************************************************/
class QExtSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtSpinBoxFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    QExtSpinBoxFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtSpinBoxFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtIntPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtSpinBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSpinBoxFactory)
    QEXT_DISABLE_COPY_MOVE(QExtSpinBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtSliderFactoryPrivate;
class QEXT_WIDGETS_API QExtSliderFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    QExtSliderFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtSliderFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtIntPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtSliderFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSliderFactory)
    QEXT_DISABLE_COPY_MOVE(QExtSliderFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtScrollBarFactoryPrivate;
class QEXT_WIDGETS_API QExtScrollBarFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    QExtScrollBarFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtScrollBarFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtIntPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtScrollBarFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtScrollBarFactory)
    QEXT_DISABLE_COPY_MOVE(QExtScrollBarFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtCheckBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtCheckBoxFactory : public QExtAbstractEditorFactory<QExtBoolPropertyManager>
{
    Q_OBJECT

public:
    QExtCheckBoxFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtCheckBoxFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtBoolPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtBoolPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtBoolPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCheckBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCheckBoxFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCheckBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotTextVisibleChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(bool))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtDoubleSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtDoubleSpinBoxFactory : public QExtAbstractEditorFactory<QExtDoublePropertyManager>
{
    Q_OBJECT

public:
    QExtDoubleSpinBoxFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDoubleSpinBoxFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtDoublePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtDoublePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtDoublePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDoubleSpinBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDoubleSpinBoxFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDoubleSpinBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, double, double))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotDecimalsChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(double))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtLineEditFactoryPrivate;
class QEXT_WIDGETS_API QExtLineEditFactory : public QExtAbstractEditorFactory<QExtStringPropertyManager>
{
    Q_OBJECT

public:
    QExtLineEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtLineEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtStringPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtStringPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtStringPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtLineEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtLineEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtLineEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(QExtProperty *, const QRegExp &))
    Q_PRIVATE_SLOT(d_func(), void slotEchoModeChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtDateEditFactoryPrivate;
class QEXT_WIDGETS_API QExtDateEditFactory : public QExtAbstractEditorFactory<QExtDatePropertyManager>
{
    Q_OBJECT

public:
    QExtDateEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDateEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtDatePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtDatePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtDatePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDateEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDateEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QDate &, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtTimeEditFactory : public QExtAbstractEditorFactory<QExtTimePropertyManager>
{
    Q_OBJECT

public:
    QExtTimeEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtTimeEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtTimePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtTimePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtTimePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTimeEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtDateTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtDateTimeEditFactory : public QExtAbstractEditorFactory<QExtDateTimePropertyManager>
{
    Q_OBJECT

public:
    QExtDateTimeEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDateTimeEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtDateTimePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtDateTimePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtDateTimePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDateTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateTimeEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDateTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtKeySequenceEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtKeySequenceEditorFactory : public QExtAbstractEditorFactory<QExtKeySequencePropertyManager>
{
    Q_OBJECT

public:
    QExtKeySequenceEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtKeySequenceEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtKeySequencePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtKeySequencePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtKeySequencePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtKeySequenceEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtKeySequenceEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtKeySequenceEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtCharEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtCharEditorFactory : public QExtAbstractEditorFactory<QExtCharPropertyManager>
{
    Q_OBJECT

public:
    QExtCharEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtCharEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtCharPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtCharPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtCharPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCharEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCharEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCharEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtEnumEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtEnumEditorFactory : public QExtAbstractEditorFactory<QExtEnumPropertyManager>
{
    Q_OBJECT

public:
    QExtEnumEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtEnumEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtEnumPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtEnumPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtEnumPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtEnumEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtEnumEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtEnumEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumNamesChanged(QExtProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumIconsChanged(QExtProperty *, const QMap<int, QIcon> &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtCursorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtCursorEditorFactory : public QExtAbstractEditorFactory<QExtCursorPropertyManager>
{
    Q_OBJECT

public:
    QExtCursorEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtCursorEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtCursorPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtCursorPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtCursorPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCursorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCursorEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCursorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtColorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtColorEditorFactory : public QExtAbstractEditorFactory<QExtColorPropertyManager>
{
    Q_OBJECT

public:
    QExtColorEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtColorEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtColorPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtColorPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtColorPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtColorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtColorEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtColorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QColor &))
};

class QExtFontEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtFontEditorFactory : public QExtAbstractEditorFactory<QExtFontPropertyManager>
{
    Q_OBJECT
public:
    QExtFontEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtFontEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtFontPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtFontPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtFontPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtFontEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFontEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtFontEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QFont &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QFont &))
};


/***********************************************************************************************************************
** button property browser
***********************************************************************************************************************/
class QExtButtonPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtButtonPropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    QExtButtonPropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtButtonPropertyBrowser() QEXT_OVERRIDE;

    void setExpanded(QExtBrowserItem *item, bool expanded);
    bool isExpanded(QExtBrowserItem *item) const;

Q_SIGNALS:
    void collapsed(QExtBrowserItem *item);
    void expanded(QExtBrowserItem *item);

protected:
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;
    virtual void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;
    virtual void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

private:
    QExtButtonPropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtButtonPropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtButtonPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
    Q_PRIVATE_SLOT(d_func(), void slotToggled(bool))

};


/***********************************************************************************************************************
** groupbox property browser
***********************************************************************************************************************/
class QExtGroupBoxPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtGroupBoxPropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    QExtGroupBoxPropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtGroupBoxPropertyBrowser() QEXT_OVERRIDE;

protected:
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;
    virtual void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;
    virtual void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

private:
    QExtGroupBoxPropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtGroupBoxPropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtGroupBoxPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())

};


/***********************************************************************************************************************
** tree property browser
***********************************************************************************************************************/
class QTreeWidgetItem;
class QExtTreePropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtTreePropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT
    Q_ENUMS(ResizeMode)
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
    Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(bool headerVisible READ isHeaderVisible WRITE setHeaderVisible)
    Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
    Q_PROPERTY(int splitterPosition READ splitterPosition WRITE setSplitterPosition)
    Q_PROPERTY(bool propertiesWithoutValueMarked READ propertiesWithoutValueMarked WRITE setPropertiesWithoutValueMarked)

public:
    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents
    };

    QExtTreePropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtTreePropertyBrowser() QEXT_OVERRIDE;

    int indentation() const;
    void setIndentation(int i);

    bool rootIsDecorated() const;
    void setRootIsDecorated(bool show);

    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool enable);

    bool isHeaderVisible() const;
    void setHeaderVisible(bool visible);

    ResizeMode resizeMode() const;
    void setResizeMode(ResizeMode mode);

    int splitterPosition() const;
    void setSplitterPosition(int position);

    void setExpanded(QExtBrowserItem *item, bool expanded);
    bool isExpanded(QExtBrowserItem *item) const;

    bool isItemVisible(QExtBrowserItem *item) const;
    void setItemVisible(QExtBrowserItem *item, bool visible);

    void setBackgroundColor(QExtBrowserItem *item, const QColor &color);
    QColor backgroundColor(QExtBrowserItem *item) const;
    QColor calculatedBackgroundColor(QExtBrowserItem *item) const;

    void setPropertiesWithoutValueMarked(bool mark);
    bool propertiesWithoutValueMarked() const;

    void editItem(QExtBrowserItem *item);

Q_SIGNALS:
    void collapsed(QExtBrowserItem *item);
    void expanded(QExtBrowserItem *item);

protected:
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;
    virtual void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;
    virtual void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

private:
    QExtTreePropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTreePropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtTreePropertyBrowser)

    Q_PRIVATE_SLOT(d_func(), void slotCollapsed(const QModelIndex &))
    Q_PRIVATE_SLOT(d_func(), void slotExpanded(const QModelIndex &))
    Q_PRIVATE_SLOT(d_func(), void slotCurrentBrowserItemChanged(QExtBrowserItem *))
    Q_PRIVATE_SLOT(d_func(), void slotCurrentTreeItemChanged(QTreeWidgetItem *, QTreeWidgetItem *))

};


/***********************************************************************************************************************
** variant property
***********************************************************************************************************************/
typedef QMap<int, QIcon> QtIconMap;
class QExtVariantPropertyManager;
class QExtVariantPropertyPrivate;
class QEXT_WIDGETS_API QExtVariantProperty : public QExtProperty
{
public:
    ~QExtVariantProperty() QEXT_OVERRIDE;

    QVariant value() const;
    QVariant attributeValue(const QString &attribute) const;
    int valueType() const;
    int propertyType() const;

    void setValue(const QVariant &value);
    void setAttribute(const QString &attribute, const QVariant &value);

protected:
    QExtVariantProperty(QExtVariantPropertyManager *manager);

private:
    friend class QExtVariantPropertyManager;
    QExtVariantPropertyPrivate *d_ptr;
};

class QExtVariantPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtVariantPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    QExtVariantPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtVariantPropertyManager() QEXT_OVERRIDE;

    virtual QExtVariantProperty *addProperty(int propertyType, const QString &name = QString());

    int propertyType(const QExtProperty *property) const;
    int valueType(const QExtProperty *property) const;
    QExtVariantProperty *variantProperty(const QExtProperty *property) const;

    virtual bool isPropertyTypeSupported(int propertyType) const;
    virtual int valueType(int propertyType) const;
    virtual QStringList attributes(int propertyType) const;
    virtual int attributeType(int propertyType, const QString &attribute) const;

    virtual QVariant value(const QExtProperty *property) const;
    virtual QVariant attributeValue(const QExtProperty *property, const QString &attribute) const;

    static int enumTypeId();
    static int flagTypeId();
    static int groupTypeId();
    static int iconMapTypeId();

public Q_SLOTS:
    virtual void setValue(QExtProperty *property, const QVariant &val);
    virtual void setAttribute(QExtProperty *property, const QString &attribute, const QVariant &value);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QVariant &val);
    void attributeChanged(QExtProperty *property, const QString &attribute, const QVariant &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual bool hasValue(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual QExtProperty *createProperty() QEXT_OVERRIDE;

private:
    QExtVariantPropertyManagerPrivate *d_ptr;
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, double, double))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotDecimalsChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(QExtProperty *, const QRegExp &))
    Q_PRIVATE_SLOT(d_func(), void slotEchoModeChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QDate &, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QLocale &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QPoint &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QPointF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QSize &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QSize &, const QSize &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QSizeF &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QSizeF &, const QSizeF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QRect &))
    Q_PRIVATE_SLOT(d_func(), void slotConstraintChanged(QExtProperty *, const QRect &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QRectF &))
    Q_PRIVATE_SLOT(d_func(), void slotConstraintChanged(QExtProperty *, const QRectF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumNamesChanged(QExtProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumIconsChanged(QExtProperty *, const QMap<int, QIcon> &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QSizePolicy &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QFont &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotFlagNamesChanged(QExtProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotTextVisibleChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QExtProperty *, QExtProperty *))
    Q_DECLARE_PRIVATE(QExtVariantPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtVariantPropertyManager)
};

class QExtVariantEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtVariantEditorFactory : public QExtAbstractEditorFactory<QExtVariantPropertyManager>
{
    Q_OBJECT
public:
    QExtVariantEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtVariantEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtVariantPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtVariantPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtVariantPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtVariantEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtVariantEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtVariantEditorFactory)
};

Q_DECLARE_METATYPE(QIcon)
Q_DECLARE_METATYPE(QtIconMap)

#endif // _QEXTPROPERTYBROWSER_H
