#include <qextFontAwesome.h>

#include <QDebug>
#include <QFile>
#include <QMutex>
#include <QMetaEnum>
#include <QMutexLocker>
#include <QFontDatabase>
#include <QCoreApplication>

namespace
{

// internal helper method to merge to option amps
static QEXTFontAwesome::FontOptionValueMap qextMergeFontOptions(const QEXTFontAwesome::FontOptionValueMap &defaults,
                                                                const QEXTFontAwesome::FontOptionValueMap &override)
{
    QEXTFontAwesome::FontOptionValueMap result = defaults;
    if (!override.isEmpty())
    {
        QEXTFontAwesome::FontOptionValueMap::const_iterator iter;
        for (iter = override.begin(); iter != override.end(); ++iter)
        {
            result.insert(iter.key(), iter.value());
        }
    }
    return result;
}

}

/// The font-awesome icon painter
class QEXTFontAwesomeCharIconPainter : public QEXTFontAwesomeIconPainterInterface
{
public:
    virtual void paint(QEXTFontAwesome *awesome, QPainter *painter, const QRect &rect, QIcon::Mode mode,
                       QIcon::State state, const QEXTFontAwesome::FontOptionValueMap &options) QEXT_DECL_OVERRIDE
    {
        Q_UNUSED(state);
        Q_UNUSED(options);

        painter->save();

        // set the correct color
        QColor color = options.value(QEXTFontAwesome::Option_Color).value<QColor>();
        QString text = options.value(QEXTFontAwesome::Option_Text).toString();

        if (mode == QIcon::Disabled)
        {
            QEXTFontAwesome::OptionType colorOption = (QIcon::On == state) ? QEXTFontAwesome::Option_ColorDisabled :
                                                                             QEXTFontAwesome::Option_ColorDisabledOff;
            QEXTFontAwesome::OptionType textOption = (QIcon::On == state) ? QEXTFontAwesome::Option_TextDisabled :
                                                                            QEXTFontAwesome::Option_TextDisabledOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        else if (mode == QIcon::Active)
        {
            QEXTFontAwesome::OptionType colorOption = (QIcon::On == state) ? QEXTFontAwesome::Option_ColorActive :
                                                                             QEXTFontAwesome::Option_ColorActiveOff;
            QEXTFontAwesome::OptionType textOption = (QIcon::On == state) ? QEXTFontAwesome::Option_TextActive :
                                                                            QEXTFontAwesome::Option_TextActiveOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        else if (mode == QIcon::Selected)
        {
            QEXTFontAwesome::OptionType colorOption = (QIcon::On == state) ? QEXTFontAwesome::Option_ColorSelected :
                                                                             QEXTFontAwesome::Option_ColorSelectedOff;
            QEXTFontAwesome::OptionType textOption = (QIcon::On == state) ? QEXTFontAwesome::Option_TextSelected :
                                                                            QEXTFontAwesome::Option_TextSelectedOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        painter->setPen(color);

        // add some 'padding' around the icon
        int drawSize = qRound(rect.height() * options.value(QEXTFontAwesome::Option_ScaleFactor).toFloat());

        painter->setFont(awesome->font(drawSize));
        painter->drawText(rect, text, QTextOption(Qt::AlignCenter | Qt::AlignVCenter));
        painter->restore();
    }
};

/// The painter icon engine.
class QEXTFontAwesomeIconPainterIconEngine : public QIconEngine
{
public:
    QEXTFontAwesomeIconPainterIconEngine(QEXTFontAwesome *awesome,
                                         QEXTFontAwesomeIconPainterInterface *painter,
                                         const QEXTFontAwesome::FontOptionValueMap &options)
        : m_awesomeRef(awesome),
          m_iconPainterRef(painter),
          m_options(options)
    {
    }

    virtual ~QEXTFontAwesomeIconPainterIconEngine() {}

    QEXTFontAwesomeIconPainterIconEngine *clone() const
    {
        return new QEXTFontAwesomeIconPainterIconEngine(m_awesomeRef, m_iconPainterRef, m_options);
    }

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE
    {
        Q_UNUSED(mode);
        Q_UNUSED(state);
        m_iconPainterRef->paint(m_awesomeRef, painter, rect, mode, state, m_options);
    }

    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE
    {
        QPixmap pm(size);
        pm.fill(Qt::transparent); // we need transparency
        {
            QPainter p(&pm);
            this->paint(&p, QRect(QPoint(0, 0), size), mode, state);
        }
        return pm;
    }

private:
    QEXTFontAwesome *m_awesomeRef;                         ///< a reference to the QEXTFontAwesome instance
    QEXTFontAwesomeIconPainterInterface *m_iconPainterRef; ///< a reference to the icon painter
    QEXTFontAwesome::FontOptionValueMap m_options;                                 ///< the options for this icon painter
};

/// The default icon colors
QEXTFontAwesome::QEXTFontAwesome(QObject *parent) : QObject(parent)
{
    // initialize the default options
    this->setDefaultOption(Option_ScaleFactor, 0.9);

    this->setDefaultOption(Option_Color, QColor(50, 50, 50));
    this->setDefaultOption(Option_ColorDisabled, QColor(70, 70, 70, 60));
    this->setDefaultOption(Option_ColorActive, QColor(10, 10, 10));
    this->setDefaultOption(Option_ColorSelected, QColor(10, 10, 10));

    this->setDefaultOption(Option_Text, QVariant());
    this->setDefaultOption(Option_TextDisabled, QVariant());
    this->setDefaultOption(Option_TextActive, QVariant());
    this->setDefaultOption(Option_TextSelected, QVariant());

    m_fontIconPainter = new QEXTFontAwesomeCharIconPainter;
    m_fontNameTextMap = this->fontNameTextMap();

    static int fontAwesomeFontId = -1;
    // only load font-awesome once
    if (fontAwesomeFontId < 0)
    {
        // The macro below internally calls "qInitResources_QEXTFontAwesome()". this initializes
        // the resource system. For a .pri project this isn't required, but when building and using a
        // static library the resource need to initialized first.
        ///
        // I've checked th qInitResource_* code and calling this method mutliple times shouldn't be any problem
        // (More info about this subject:  http://qt-project.org/wiki/QtResources)
        Q_INIT_RESOURCE(QEXTFontAwesome);

        // load the font file
        QFile res(":/QEXTFontAwesome/font/fontawesome-webfont.ttf");
        if (!res.open(QIODevice::ReadOnly))
        {
            qWarning() << "QEXTFontAwesome::QEXTFontAwesome(): Font awesome font could not be loaded!";
        }
        QByteArray fontData(res.readAll());
        res.close();

        // fetch the given font
        fontAwesomeFontId = QFontDatabase::addApplicationFontFromData(fontData);
    }

    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(fontAwesomeFontId);
    if (!loadedFontFamilies.empty())
    {
        m_fontName = loadedFontFamilies.at(0);
    }
    else
    {
        qWarning() << "QEXTFontAwesome::QEXTFontAwesome(): Font awesome font is empty?!";
        fontAwesomeFontId = -1; // restore the font-awesome id
    }
}

QEXTFontAwesome::~QEXTFontAwesome()
{
    delete m_fontIconPainter;
    qDeleteAll(m_painterMap);
}

int QEXTFontAwesome::maiorVersion()
{
    return 4;
}

int QEXTFontAwesome::minorVersion()
{
    return 7;
}

QString QEXTFontAwesome::version() const
{
    return QString("%1.%2").arg(this->maiorVersion()).arg(this->minorVersion());
}

QString QEXTFontAwesome::textFromKey(const QString &key)
{
    if(!key.isEmpty())
    {
        int index = this->staticMetaObject.indexOfEnumerator("FontType");
        return QString(this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data()));
    }
    return QString();
}

QString QEXTFontAwesome::textFromValue(const int &type)
{
    return QString(type);
}

QList<QString> QEXTFontAwesome::fontNamelist()
{
    QMetaEnum enumType = QEXTFontAwesome::staticMetaObject.enumerator(QEXTFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    QList<QString> list;
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        list.append(enumType.key(i));
    }
    return list;
}

QList<QString> QEXTFontAwesome::fontTextlist()
{
    QMetaEnum enumType = QEXTFontAwesome::staticMetaObject.enumerator(QEXTFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    int index = this->staticMetaObject.indexOfEnumerator("FontType");
    QList<QString> list;
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        QString key = enumType.key(i);
        QString value = QString(this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data()));
        list.append(value);
    }
    return list;
}

QEXTFontAwesome::FontNameTextMap QEXTFontAwesome::fontNameTextMap()
{
    FontNameTextMap nameTextMap;
    QMetaEnum enumType = QEXTFontAwesome::staticMetaObject.enumerator(QEXTFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    int index = this->staticMetaObject.indexOfEnumerator("FontType");
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        QString key = enumType.key(i);
        FontType value = (FontType)this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data());
        nameTextMap.insert(key, value);
    }
    return nameTextMap;
}

void QEXTFontAwesome::setDefaultOption(const OptionType &option, const QVariant &value)
{
    m_defaultOptions.insert(option, value);
}

QVariant QEXTFontAwesome::defaultOption(const OptionType &option)
{
    return m_defaultOptions.value(option);
}

QChar QEXTFontAwesome::fontChar(QEXTFontAwesome::FontType character)
{
    return QChar(character);
}

QIcon QEXTFontAwesome::icon(FontType character, const FontOptionValueMap &options)
{
    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);
    optionMap.insert(Option_Text, QString(QChar(static_cast<int>(character))));

    return this->icon(m_fontIconPainter, optionMap);
}

QIcon QEXTFontAwesome::icon(QEXTFontAwesome::FontType character, const QColor &color)
{
    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap;
    optionMap.insert(QEXTFontAwesome::Option_Color, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorOff, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorDisabled, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorDisabledOff, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorActive, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorActiveOff, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorSelected, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorSelectedOff, color);
    optionMap.insert(Option_Text, QString(QChar(static_cast<int>(character))));
    optionMap.insert(Option_TextOff, QString(QChar(static_cast<int>(character))));
    optionMap.insert(Option_TextDisabled, QString(QChar(static_cast<int>(character))));
    optionMap.insert(Option_TextDisabledOff, QString(QChar(static_cast<int>(character))));
    optionMap.insert(Option_TextSelected, QString(QChar(static_cast<int>(character))));
    optionMap.insert(Option_TextSelectedOff, QString(QChar(static_cast<int>(character))));
    optionMap = qextMergeFontOptions(m_defaultOptions, optionMap);
    return this->icon(m_fontIconPainter, optionMap);
}

QIcon QEXTFontAwesome::icon(const QString &name, const FontOptionValueMap &options)
{
    // when it's a named codepoint
    if (m_fontNameTextMap.count(name))
    {
        return this->icon(m_fontNameTextMap.value(name), options);
    }

    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);

    // this method first tries to retrieve the icon
    QEXTFontAwesomeIconPainterInterface *painter = m_painterMap.value(name);
    if (!painter)
    {
        return QIcon();
    }

    return this->icon(painter, optionMap);
}

QIcon QEXTFontAwesome::icon(const QString &name, const QColor &color)
{
    FontOptionValueMap optionMap;
    optionMap.insert(QEXTFontAwesome::Option_Color, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorOff, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorDisabled, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorDisabledOff, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorActive, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorActiveOff, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorSelected, color);
    optionMap.insert(QEXTFontAwesome::Option_ColorSelectedOff, color);
    optionMap = qextMergeFontOptions(m_defaultOptions, optionMap);

    // when it's a named codepoint
    if (m_fontNameTextMap.count(name))
    {
        return this->icon(m_fontNameTextMap.value(name), optionMap);
    }

    // this method first tries to retrieve the icon
    QEXTFontAwesomeIconPainterInterface *painter = m_painterMap.value(name);
    if (!painter)
    {
        return QIcon();
    }
    return this->icon(painter, optionMap);
}

QIcon QEXTFontAwesome::icon(QEXTFontAwesomeIconPainterInterface *painter, const FontOptionValueMap &optionMap)
{
    // Warning, when you use memoryleak detection. You should turn it of for the next call
    // QIcon's placed in gui items are often cached and not deleted when my memory-leak detection checks for leaks.
    // I'm not sure if it's a Qt bug or something I do wrong
    QEXTFontAwesomeIconPainterIconEngine *engine = new QEXTFontAwesomeIconPainterIconEngine(this, painter, optionMap);
    return QIcon(engine);
}

void QEXTFontAwesome::give(const QString &name, QEXTFontAwesomeIconPainterInterface *painter)
{
    delete m_painterMap.value(name); // delete the old one
    m_painterMap.insert(name, painter);
}

QFont QEXTFontAwesome::font(int size)
{
    QFont font(m_fontName);
    font.setPixelSize(size);
    return font;
}

QString QEXTFontAwesome::fontName()
{
    return m_fontName;
}

QEXTFontAwesome *qextGlobalFontAwesome()
{
    static QEXTFontAwesome *fontAwesome = QEXT_DECL_NULLPTR;
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (QEXT_DECL_NULLPTR == fontAwesome)
    {
        fontAwesome = new QEXTFontAwesome(qApp);
    }
    return fontAwesome;
}
