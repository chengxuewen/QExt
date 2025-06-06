#include <private/qextPEAbstractPropertyEditor_p.h>
#include <private/qextPEProperty_p.h>
#include <qextPEPropertyManager.h>

#include <QMap>
#include <QEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QFocusEvent>
#include <QHeaderView>
#include <QApplication>
#include <QGlobalStatic>
#include <QMetaProperty>


/***********************************************************************************************************************
** QExtPEMetaEnumProvider
***********************************************************************************************************************/

#if QT_VERSION < 0x040300

static QList<QLocale::Country> countriesForLanguage(QLocale::Language language)
{
    QList<QLocale::Country> countries;
    QLocale::Country country = QLocale::AnyCountry;
    while (country <= QLocale::LastCountry)
    {
        QLocale locale(language, country);
        if (locale.language() == language && !countries.contains(locale.country()))
        {
            countries << locale.country();
        }
        country = (QLocale::Country)((uint)country + 1); // ++country
    }
    return countries;
}

#endif

static QList<QLocale::Country> sortCountries(const QList<QLocale::Country> &countries)
{
    QMultiMap<QString, QLocale::Country> nameToCountry;
    QListIterator<QLocale::Country> itCountry(countries);
    while (itCountry.hasNext())
    {
        QLocale::Country country = itCountry.next();
        nameToCountry.insert(QLocale::countryToString(country), country);
    }
    return nameToCountry.values();
}

void QExtPEMetaEnumProvider::initLocale()
{
    QMultiMap<QString, QLocale::Language> nameToLanguage;
    QLocale::Language language = QLocale::C;
    while (language <= QLocale::LastLanguage)
    {
        QLocale locale(language);
        if (locale.language() == language)
        {
            nameToLanguage.insert(QLocale::languageToString(language), language);
        }
        language = (QLocale::Language)((uint)language + 1); // ++language
    }

    const QLocale system = QLocale::system();
    if (!nameToLanguage.contains(QLocale::languageToString(system.language())))
        nameToLanguage.insert(QLocale::languageToString(system.language()), system.language());

    QList<QLocale::Language> languages = nameToLanguage.values();
    QListIterator<QLocale::Language> itLang(languages);
    while (itLang.hasNext())
    {
        QLocale::Language language = itLang.next();
        QList<QLocale::Country> countries;
#if QT_VERSION < 0x040300
        countries = countriesForLanguage(language);
#else
        countries = QLocale::countriesForLanguage(language);
#endif
        if (countries.isEmpty() && language == system.language())
        {
            countries << system.country();
        }

        if (!countries.isEmpty() && !m_languageToIndex.contains(language))
        {
            countries = sortCountries(countries);
            int langIdx = m_languageEnumNames.count();
            m_indexToLanguage[langIdx] = language;
            m_languageToIndex[language] = langIdx;
            QStringList countryNames;
            QListIterator<QLocale::Country> it(countries);
            int countryIdx = 0;
            while (it.hasNext())
            {
                QLocale::Country country = it.next();
                countryNames << QLocale::countryToString(country);
                m_indexToCountry[langIdx][countryIdx] = country;
                m_countryToIndex[language][country] = countryIdx;
                ++countryIdx;
            }
            m_languageEnumNames << QLocale::languageToString(language);
            m_countryEnumNames[language] = countryNames;
        }
    }
}

QExtPEMetaEnumProvider::QExtPEMetaEnumProvider()
{
    QMetaProperty p;

    p = QExtMetaEnumWrapper::staticMetaObject.property(QExtMetaEnumWrapper::staticMetaObject.propertyOffset() + 0);
    m_policyEnum = p.enumerator();
    const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
    {
        m_policyEnumNames << QLatin1String(m_policyEnum.key(i));
    }

    this->initLocale();
}

QSizePolicy::Policy QExtPEMetaEnumProvider::indexToSizePolicy(int index) const
{
    return static_cast<QSizePolicy::Policy>(m_policyEnum.value(index));
}

int QExtPEMetaEnumProvider::sizePolicyToIndex(QSizePolicy::Policy policy) const
{
    const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
    {
        if (indexToSizePolicy(i) == policy)
        {
            return i;
        }
    }
    return -1;
}

void QExtPEMetaEnumProvider::indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language,
                                           QLocale::Country *country) const
{
    QLocale::Language l = QLocale::C;
    QLocale::Country c = QLocale::AnyCountry;
    if (m_indexToLanguage.contains(languageIndex))
    {
        l = m_indexToLanguage[languageIndex];
        if (m_indexToCountry.contains(languageIndex) && m_indexToCountry[languageIndex].contains(countryIndex))
        {
            c = m_indexToCountry[languageIndex][countryIndex];
        }
    }
    if (language)
    {
        *language = l;
    }
    if (country)
    {
        *country = c;
    }
}

void QExtPEMetaEnumProvider::localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex,
                                           int *countryIndex) const
{
    int l = -1;
    int c = -1;
    if (m_languageToIndex.contains(language))
    {
        l = m_languageToIndex[language];
        if (m_countryToIndex.contains(language) && m_countryToIndex[language].contains(country))
        {
            c = m_countryToIndex[language][country];
        }
    }

    if (languageIndex)
    {
        *languageIndex = l;
    }
    if (countryIndex)
    {
        *countryIndex = c;
    }
}

/***********************************************************************************************************************
** QExtPropertyBrowserUtils
***********************************************************************************************************************/
QPixmap QExtPropertyBrowserUtils::brushValuePixmap(const QBrush &b)
{
    QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);

    QPainter painter(&img);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(0, 0, img.width(), img.height(), b);
    QColor color = b.color();
    if (color.alpha() != 255)
    {
        // indicate alpha by an inset
        QBrush  opaqueBrush = b;
        color.setAlpha(255);
        opaqueBrush.setColor(color);
        painter.fillRect(img.width() / 4, img.height() / 4,
                         img.width() / 2, img.height() / 2, opaqueBrush);
    }
    painter.end();
    return QPixmap::fromImage(img);
}

QIcon QExtPropertyBrowserUtils::brushValueIcon(const QBrush &b)
{
    return QIcon(brushValuePixmap(b));
}

QString QExtPropertyBrowserUtils::colorValueText(const QColor &c)
{
    return QCoreApplication::translate("QExtPropertyBrowserUtils", "[%1, %2, %3] (%4)")
        .arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
}

QPixmap QExtPropertyBrowserUtils::fontValuePixmap(const QFont &font)
{
    QFont f = font;
    QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter p(&img);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::Antialiasing, true);
    f.setPointSize(13);
    p.setFont(f);
    QTextOption t;
    t.setAlignment(Qt::AlignCenter);
    p.drawText(QRect(0, 0, 16, 16), QString(QLatin1Char('A')), t);
    return QPixmap::fromImage(img);
}

QIcon QExtPropertyBrowserUtils::fontValueIcon(const QFont &f)
{
    return QIcon(fontValuePixmap(f));
}

QString QExtPropertyBrowserUtils::fontValueText(const QFont &f)
{
    return QCoreApplication::translate("QExtPropertyBrowserUtils", "[%1, %2]")
        .arg(f.family()).arg(f.pointSize());
}

/***********************************************************************************************************************
** QExtPEAbstractPropertyEditor
***********************************************************************************************************************/
typedef QMap<QExtPEAbstractPropertyEditor *, QMap<QExtPEAbstractPropertyManager *, QExtPEAbstractWidgetFactoryBase *> > Map1;
typedef QMap<QExtPEAbstractPropertyManager *, QMap<QExtPEAbstractWidgetFactoryBase *, QList<QExtPEAbstractPropertyEditor *> > > Map2;
Q_GLOBAL_STATIC(Map1, sgViewToManagerToFactory)
Q_GLOBAL_STATIC(Map2, sgManagerToFactoryToViews)

QExtPEAbstractPropertyEditorPrivate::QExtPEAbstractPropertyEditorPrivate(QExtPEAbstractPropertyEditor *q)
    : q_ptr(q), mCurrentItem(QEXT_NULLPTR)
{
}

void QExtPEAbstractPropertyEditorPrivate::insertSubTree(QExtPEProperty *property, QExtPEProperty *parentProperty)
{
    Q_Q(QExtPEAbstractPropertyEditor);
    if (mPropertyToParents.contains(property))
    {
        // property was already inserted, so its manager is connected
        // and all its children are inserted and theirs managers are connected
        // we just register new parent (parent has to be new).
        mPropertyToParents[property].append(parentProperty);
        // don't need to update m_managerToProperties map since
        // m_managerToProperties[manager] already contains property.
        return;
    }
    QExtPEAbstractPropertyManager *manager = property->propertyManager();
    if (mManagerToProperties[manager].isEmpty())
    {
        // connect manager's signals
        q->connect(manager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
                   q, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
        q->connect(manager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
                   q, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
        q->connect(manager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
                   q, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
        q->connect(manager, SIGNAL(propertyChanged(QExtPEProperty *)),
                   q, SLOT(slotPropertyDataChanged(QExtPEProperty *)));
    }
    mManagerToProperties[manager].append(property);
    mPropertyToParents[property].append(parentProperty);

    QList<QExtPEProperty *> subList = property->subProperties();
    QListIterator<QExtPEProperty *> iter(subList);
    while (iter.hasNext())
    {
        QExtPEProperty *subProperty = iter.next();
        insertSubTree(subProperty, property);
    }
}

void QExtPEAbstractPropertyEditorPrivate::removeSubTree(QExtPEProperty *property, QExtPEProperty *parentProperty)
{
    Q_Q(QExtPEAbstractPropertyEditor);
    if (!mPropertyToParents.contains(property))
    {
        // ASSERT
        return;
    }

    mPropertyToParents[property].removeAll(parentProperty);
    if (!mPropertyToParents[property].isEmpty())
    {
        return;
    }

    mPropertyToParents.remove(property);
    QExtPEAbstractPropertyManager *manager = property->propertyManager();
    mManagerToProperties[manager].removeAll(property);
    if (mManagerToProperties[manager].isEmpty())
    {
        // disconnect manager's signals
        q->disconnect(manager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
                      q, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
        q->disconnect(manager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
                      q, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
        q->disconnect(manager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
                      q, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
        q->disconnect(manager, SIGNAL(propertyChanged(QExtPEProperty *)),
                      q, SLOT(slotPropertyDataChanged(QExtPEProperty *)));

        mManagerToProperties.remove(manager);
    }

    QList<QExtPEProperty *> subList = property->subProperties();
    QListIterator<QExtPEProperty *> iter(subList);
    while (iter.hasNext())
    {
        QExtPEProperty *subProperty = iter.next();
        this->removeSubTree(subProperty, property);
    }
}

void QExtPEAbstractPropertyEditorPrivate::createBrowserIndexes(QExtPEProperty *property, QExtPEProperty *parentProperty,
                                                               QExtPEProperty *afterProperty)
{
    QHash<QExtPEPropertyItem *, QExtPEPropertyItem *> parentToAfter;
    if (afterProperty)
    {
        QMap<QExtPEProperty *, QList<QExtPEPropertyItem *> >::ConstIterator it = mPropertyToIndexes.find(afterProperty);
        if (it == mPropertyToIndexes.constEnd())
        {
            return;
        }

        QList<QExtPEPropertyItem *> indexes = it.value();
        QListIterator<QExtPEPropertyItem *> itIndex(indexes);
        while (itIndex.hasNext())
        {
            QExtPEPropertyItem *idx = itIndex.next();
            QExtPEPropertyItem *parentIdx = idx->parent();
            if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
            {
                parentToAfter[idx->parent()] = idx;
            }
        }
    }
    else if (parentProperty)
    {
        QMap<QExtPEProperty *, QList<QExtPEPropertyItem *> >::ConstIterator iter = mPropertyToIndexes.find(parentProperty);
        if (iter == mPropertyToIndexes.constEnd())
        {
            return;
        }

        QList<QExtPEPropertyItem *> indexes = iter.value();
        QListIterator<QExtPEPropertyItem *> iterIndex(indexes);
        while (iterIndex.hasNext())
        {
            QExtPEPropertyItem *idx = iterIndex.next();
            parentToAfter[idx] = QEXT_NULLPTR;
        }
    }
    else
    {
        parentToAfter[0] = QEXT_NULLPTR;
    }

    const QHash<QExtPEPropertyItem *, QExtPEPropertyItem *>::ConstIterator pcend = parentToAfter.constEnd();
    for (QHash<QExtPEPropertyItem *, QExtPEPropertyItem *>::ConstIterator it = parentToAfter.constBegin(); it != pcend; ++it)
    {
        this->createBrowserIndex(property, it.key(), it.value());
    }
}

QExtPEPropertyItem *QExtPEAbstractPropertyEditorPrivate::createBrowserIndex(QExtPEProperty *property,
                                                                            QExtPEPropertyItem *parentIndex,
                                                                            QExtPEPropertyItem *afterIndex)
{
    Q_Q(QExtPEAbstractPropertyEditor);
    QExtPEPropertyItem *newIndex = new QExtPEPropertyItem(q_ptr, property, parentIndex);
    if (parentIndex)
    {
        parentIndex->dd_ptr->addChild(newIndex, afterIndex);
    }
    else
    {
        mTopLevelPropertyToIndex[property] = newIndex;
        mTopLevelIndexes.insert(mTopLevelIndexes.indexOf(afterIndex) + 1, newIndex);
    }
    mPropertyToIndexes[property].append(newIndex);

    q->itemInserted(newIndex, afterIndex);

    QList<QExtPEProperty *> subItems = property->subProperties();
    QListIterator<QExtPEProperty *> itChild(subItems);
    QExtPEPropertyItem *afterChild = QEXT_NULLPTR;
    while (itChild.hasNext())
    {
        QExtPEProperty *child = itChild.next();
        afterChild = createBrowserIndex(child, newIndex, afterChild);
    }
    return newIndex;
}

void QExtPEAbstractPropertyEditorPrivate::removeBrowserIndexes(QExtPEProperty *property, QExtPEProperty *parentProperty)
{
    QList<QExtPEPropertyItem *> toRemove;
    QMap<QExtPEProperty *, QList<QExtPEPropertyItem *> >::ConstIterator it = mPropertyToIndexes.find(property);
    if (it == mPropertyToIndexes.constEnd())
    {
        return;
    }

    QList<QExtPEPropertyItem *> indexes = it.value();
    QListIterator<QExtPEPropertyItem *> itIndex(indexes);
    while (itIndex.hasNext())
    {
        QExtPEPropertyItem *idx = itIndex.next();
        QExtPEPropertyItem *parentIdx = idx->parent();
        if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
        {
            toRemove.append(idx);
        }
    }

    QListIterator<QExtPEPropertyItem *> itRemove(toRemove);
    while (itRemove.hasNext())
    {
        QExtPEPropertyItem *index = itRemove.next();
        this->removeBrowserIndex(index);
    }
}

void QExtPEAbstractPropertyEditorPrivate::removeBrowserIndex(QExtPEPropertyItem *index)
{
    QList<QExtPEPropertyItem *> children = index->children();
    for (int i = children.count(); i > 0; i--)
    {
        this->removeBrowserIndex(children.at(i - 1));
    }

    q_ptr->itemRemoved(index);

    if (index->parent())
    {
        index->parent()->dd_ptr->removeChild(index);
    }
    else
    {
        mTopLevelPropertyToIndex.remove(index->property());
        mTopLevelIndexes.removeAll(index);
    }

    QExtPEProperty *property = index->property();

    mPropertyToIndexes[property].removeAll(index);
    if (mPropertyToIndexes[property].isEmpty())
    {
        mPropertyToIndexes.remove(property);
    }

    delete index;
}

void QExtPEAbstractPropertyEditorPrivate::clearIndex(QExtPEPropertyItem *index)
{
    QList<QExtPEPropertyItem *> children = index->children();
    QListIterator<QExtPEPropertyItem *> itChild(children);
    while (itChild.hasNext())
    {
        clearIndex(itChild.next());
    }
    delete index;
}

void QExtPEAbstractPropertyEditorPrivate::slotPropertyInserted(QExtPEProperty *property,
                                                               QExtPEProperty *parentProperty,
                                                               QExtPEProperty *afterProperty)
{
    if (!mPropertyToParents.contains(parentProperty))
    {
        return;
    }
    this->createBrowserIndexes(property, parentProperty, afterProperty);
    this->insertSubTree(property, parentProperty);
    //q_ptr->propertyInserted(property, parentProperty, afterProperty);
}

void QExtPEAbstractPropertyEditorPrivate::slotPropertyRemoved(QExtPEProperty *property,
                                                              QExtPEProperty *parentProperty)
{
    if (!mPropertyToParents.contains(parentProperty))
    {
        return;
    }
    this->removeSubTree(property, parentProperty); // this line should be probably moved down after propertyRemoved call
    //q_ptr->propertyRemoved(property, parentProperty);
    this->removeBrowserIndexes(property, parentProperty);
}

void QExtPEAbstractPropertyEditorPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    Q_Q(QExtPEAbstractPropertyEditor);
    if (!mSubItems.contains(property))
    {
        return;
    }
    q->removeProperty(property);
}

void QExtPEAbstractPropertyEditorPrivate::slotPropertyDataChanged(QExtPEProperty *property)
{
    Q_Q(QExtPEAbstractPropertyEditor);
    if (!mPropertyToParents.contains(property))
    {
        return;
    }

    QMap<QExtPEProperty *, QList<QExtPEPropertyItem *> >::ConstIterator it = mPropertyToIndexes.find(property);
    if (it == mPropertyToIndexes.constEnd())
    {
        return;
    }

    QList<QExtPEPropertyItem *> indexes = it.value();
    QListIterator<QExtPEPropertyItem *> itIndex(indexes);
    while (itIndex.hasNext())
    {
        QExtPEPropertyItem *idx = itIndex.next();
        q->itemChanged(idx);
    }
    //q_ptr->propertyChanged(property);
}


QExtPEAbstractPropertyEditor::QExtPEAbstractPropertyEditor(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtPEAbstractPropertyEditorPrivate(this))
{
}

QExtPEAbstractPropertyEditor::~QExtPEAbstractPropertyEditor()
{
    Q_D(QExtPEAbstractPropertyEditor);
    QList<QExtPEPropertyItem *> indexes = this->topLevelItems();
    QListIterator<QExtPEPropertyItem *> itItem(indexes);
    while (itItem.hasNext())
    {
        d->clearIndex(itItem.next());
    }
}

QList<QExtPEProperty *> QExtPEAbstractPropertyEditor::properties() const
{
    Q_D(const QExtPEAbstractPropertyEditor);
    return d->mSubItems;
}

QList<QExtPEPropertyItem *> QExtPEAbstractPropertyEditor::items(QExtPEProperty *property) const
{
    Q_D(const QExtPEAbstractPropertyEditor);
    return d->mPropertyToIndexes.value(property);
}

QExtPEPropertyItem *QExtPEAbstractPropertyEditor::topLevelItem(QExtPEProperty *property) const
{
    Q_D(const QExtPEAbstractPropertyEditor);
    return d->mTopLevelPropertyToIndex.value(property);
}

QList<QExtPEPropertyItem *> QExtPEAbstractPropertyEditor::topLevelItems() const
{
    Q_D(const QExtPEAbstractPropertyEditor);
    return d->mTopLevelIndexes;
}

void QExtPEAbstractPropertyEditor::clear()
{
    QList<QExtPEProperty *> subList = this->properties();
    QListIterator<QExtPEProperty *> itSub(subList);
    itSub.toBack();
    while (itSub.hasPrevious())
    {
        QExtPEProperty *property = itSub.previous();
        this->removeProperty(property);
    }
}

QExtPEPropertyItem *QExtPEAbstractPropertyEditor::addProperty(QExtPEProperty *property)
{
    Q_D(const QExtPEAbstractPropertyEditor);
    QExtPEProperty *afterProperty = QEXT_NULLPTR;
    if (d->mSubItems.count() > 0)
    {
        afterProperty = d->mSubItems.last();
    }
    return this->insertProperty(property, afterProperty);
}

QExtPEPropertyItem *QExtPEAbstractPropertyEditor::insertProperty(QExtPEProperty *property,
                                                                 QExtPEProperty *afterProperty)
{
    Q_D(QExtPEAbstractPropertyEditor);
    if (!property)
    {
        return QEXT_NULLPTR;
    }

    // if item is already inserted in this item then cannot add.
    QList<QExtPEProperty *> pendingList = this->properties();
    int pos = 0;
    int newPos = 0;
    while (pos < pendingList.count())
    {
        QExtPEProperty *prop = pendingList.at(pos);
        if (prop == property)
        {
            return QEXT_NULLPTR;
        }
        if (prop == afterProperty)
        {
            newPos = pos + 1;
        }
        pos++;
    }
    d->createBrowserIndexes(property, 0, afterProperty);

    // traverse inserted subtree and connect to manager's signals
    d->insertSubTree(property, 0);

    d->mSubItems.insert(newPos, property);
    //propertyInserted(property, 0, properAfterProperty);
    return this->topLevelItem(property);
}

void QExtPEAbstractPropertyEditor::removeProperty(QExtPEProperty *property)
{
    Q_D(QExtPEAbstractPropertyEditor);
    if (!property)
    {
        return;
    }

    QList<QExtPEProperty *> pendingList = this->properties();
    int pos = 0;
    while (pos < pendingList.count())
    {
        if (pendingList.at(pos) == property)
        {
            d->mSubItems.removeAt(pos); //perhaps this two lines
            d->removeSubTree(property, 0); //should be moved down after propertyRemoved call.
            //propertyRemoved(property, 0);

            d->removeBrowserIndexes(property, 0);

            // when item is deleted, item will call removeItem for top level items,
            // and itemRemoved for nested items.
            return;
        }
        pos++;
    }
}

QWidget *QExtPEAbstractPropertyEditor::createEditor(QExtPEProperty *property, QWidget *parent)
{
    QExtPEAbstractWidgetFactoryBase *factory = QEXT_NULLPTR;
    QExtPEAbstractPropertyManager *manager = property->propertyManager();

    if (sgViewToManagerToFactory()->contains(this) && (*sgViewToManagerToFactory())[this].contains(manager))
    {
        factory = (*sgViewToManagerToFactory())[this][manager];
    }

    if (!factory)
    {
        return QEXT_NULLPTR;
    }
    return factory->createEditor(property, parent);
}

bool QExtPEAbstractPropertyEditor::addFactory(QExtPEAbstractPropertyManager *abstractManager,
                                              QExtPEAbstractWidgetFactoryBase *abstractFactory)
{
    bool connectNeeded = false;
    if (!sgManagerToFactoryToViews()->contains(abstractManager) ||
        !(*sgManagerToFactoryToViews())[abstractManager].contains(abstractFactory))
    {
        connectNeeded = true;
    }
    else if ((*sgManagerToFactoryToViews())[abstractManager][abstractFactory].contains(this))
    {
        return connectNeeded;
    }

    if (sgViewToManagerToFactory()->contains(this) && (*sgViewToManagerToFactory())[this].contains(abstractManager))
    {
        unsetFactoryForManager(abstractManager);
    }

    (*sgManagerToFactoryToViews())[abstractManager][abstractFactory].append(this);
    (*sgViewToManagerToFactory())[this][abstractManager] = abstractFactory;

    return connectNeeded;
}

void QExtPEAbstractPropertyEditor::unsetFactoryForManager(QExtPEAbstractPropertyManager *manager)
{
    if (!sgViewToManagerToFactory()->contains(this) || !(*sgViewToManagerToFactory())[this].contains(manager))
    {
        return;
    }

    QExtPEAbstractWidgetFactoryBase *abstractFactory = (*sgViewToManagerToFactory())[this][manager];
    (*sgViewToManagerToFactory())[this].remove(manager);
    if ((*sgViewToManagerToFactory())[this].isEmpty())
    {
        (*sgViewToManagerToFactory()).remove(this);
    }

    (*sgManagerToFactoryToViews())[manager][abstractFactory].removeAll(this);
    if ((*sgManagerToFactoryToViews())[manager][abstractFactory].isEmpty())
    {
        (*sgManagerToFactoryToViews())[manager].remove(abstractFactory);
        abstractFactory->breakConnection(manager);
        if ((*sgManagerToFactoryToViews())[manager].isEmpty())
        {
            (*sgManagerToFactoryToViews()).remove(manager);
        }
    }
}

QExtPEPropertyItem *QExtPEAbstractPropertyEditor::currentItem() const
{
    Q_D(const QExtPEAbstractPropertyEditor);
    return d->mCurrentItem;
}

void QExtPEAbstractPropertyEditor::setCurrentItem(QExtPEPropertyItem *item)
{
    Q_D(QExtPEAbstractPropertyEditor);
    QExtPEPropertyItem *oldItem = dd_ptr->mCurrentItem;
    d->mCurrentItem = item;
    if (oldItem != item)
    {
        emit  this->currentItemChanged(item);
    }
}



#include <moc_qextPEAbstractPropertyEditor.cpp>
