#ifndef _QEXTPEABSTRACTPROPERTYEDITOR_P_H
#define _QEXTPEABSTRACTPROPERTYEDITOR_P_H

#include <qextPEAbstractPropertyEditor.h>

#include <QLocale>
#include <QMetaEnum>

class QEXT_WIDGETS_API QExtPropertyBrowserUtils
{
public:
    static QPixmap brushValuePixmap(const QBrush &b);
    static QIcon brushValueIcon(const QBrush &b);
    static QString colorValueText(const QColor &c);
    static QPixmap fontValuePixmap(const QFont &f);
    static QIcon fontValueIcon(const QFont &f);
    static QString fontValueText(const QFont &f);
};

class QExtPEMetaEnumProvider
{
public:
    QExtPEMetaEnumProvider();

    QStringList policyEnumNames() const { return m_policyEnumNames; }
    QStringList languageEnumNames() const { return m_languageEnumNames; }
    QStringList countryEnumNames(QLocale::Language language) const { return m_countryEnumNames.value(language); }

    QSizePolicy::Policy indexToSizePolicy(int index) const;
    int sizePolicyToIndex(QSizePolicy::Policy policy) const;

    void indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const;
    void localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const;

private:
    void initLocale();

    QStringList m_policyEnumNames;
    QStringList m_languageEnumNames;
    QMap<QLocale::Language, QStringList> m_countryEnumNames;
    QMap<int, QLocale::Language> m_indexToLanguage;
    QMap<QLocale::Language, int> m_languageToIndex;
    QMap<int, QMap<int, QLocale::Country> > m_indexToCountry;
    QMap<QLocale::Language, QMap<QLocale::Country, int> > m_countryToIndex;
    QMetaEnum m_policyEnum;
};

class QExtMetaEnumWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSizePolicy::Policy policy READ policy CONSTANT)
public:
    QSizePolicy::Policy policy() const { return QSizePolicy::Ignored; }

private:
    QExtMetaEnumWrapper(QObject *parent) : QObject(parent) {}
    ~QExtMetaEnumWrapper() QEXT_OVERRIDE {}
};

class QExtPEAbstractPropertyEditorPrivate
{
    QExtPEAbstractPropertyEditor * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPEAbstractPropertyEditor)
    QEXT_DISABLE_COPY_MOVE(QExtPEAbstractPropertyEditorPrivate)
public:
    explicit QExtPEAbstractPropertyEditorPrivate(QExtPEAbstractPropertyEditor *q);
    virtual ~QExtPEAbstractPropertyEditorPrivate() {}

    void insertSubTree(QExtPEProperty *property, QExtPEProperty *parentProperty);
    void removeSubTree(QExtPEProperty *property, QExtPEProperty *parentProperty);
    void createBrowserIndexes(QExtPEProperty *property, QExtPEProperty *parentProperty,
                              QExtPEProperty *afterProperty);
    void removeBrowserIndexes(QExtPEProperty *property, QExtPEProperty *parentProperty);
    QExtPEPropertyItem *createBrowserIndex(QExtPEProperty *property, QExtPEPropertyItem *parentIndex,
                                           QExtPEPropertyItem *afterIndex);
    void removeBrowserIndex(QExtPEPropertyItem *index);
    void clearIndex(QExtPEPropertyItem *index);

    void slotPropertyInserted(QExtPEProperty *property, QExtPEProperty *parentProperty,
                              QExtPEProperty *afterProperty);
    void slotPropertyRemoved(QExtPEProperty *property, QExtPEProperty *parentProperty);
    void slotPropertyDestroyed(QExtPEProperty *property);
    void slotPropertyDataChanged(QExtPEProperty *property);

    QExtPEPropertyItem *mCurrentItem;

    QList<QExtPEProperty *> mSubItems;
    QMap<QExtPEProperty *, QList<QExtPEProperty *> > mPropertyToParents;
    QMap<QExtPEAbstractPropertyManager *, QList<QExtPEProperty *> > mManagerToProperties;

    QList<QExtPEPropertyItem *> mTopLevelIndexes;
    QMap<QExtPEProperty *, QExtPEPropertyItem *> mTopLevelPropertyToIndex;
    QMap<QExtPEProperty *, QList<QExtPEPropertyItem *> > mPropertyToIndexes;
};

#endif // _QEXTPEABSTRACTPROPERTYEDITOR_P_H
