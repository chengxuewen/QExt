#include <qextIconFontAwesome.h>

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
static QEXTIconFontAwesome::FontOptionValueMap qextMergeFontOptions(const QEXTIconFontAwesome::FontOptionValueMap &defaults,
                                                                    const QEXTIconFontAwesome::FontOptionValueMap &override)
{
    QEXTIconFontAwesome::FontOptionValueMap result = defaults;
    if (!override.isEmpty())
    {
        QEXTIconFontAwesome::FontOptionValueMap::const_iterator iter;
        for (iter = override.begin(); iter != override.end(); ++iter)
        {
            result.insert(iter.key(), iter.value());
        }
    }
    return result;
}

}

/// The font-awesome icon painter
class QEXTIconFontAwesomeCharIconPainter : public QEXTIconFontAwesomeIconPainterInterface
{
public:
    virtual void paint(QEXTIconFontAwesome *awesome, QPainter *painter, const QRect &rect, QIcon::Mode mode,
                       QIcon::State state, const QEXTIconFontAwesome::FontOptionValueMap &options) QEXT_DECL_OVERRIDE
    {
        Q_UNUSED(state);
        Q_UNUSED(options);

        painter->save();

        // set the correct color
        QColor color = options.value(QEXTIconFontAwesome::Option_Color).value<QColor>();
        QString text = options.value(QEXTIconFontAwesome::Option_Text).toString();

        if (mode == QIcon::Disabled)
        {
            QEXTIconFontAwesome::OptionType colorOption = (QIcon::On == state) ? QEXTIconFontAwesome::Option_ColorDisabled :
                                                                                 QEXTIconFontAwesome::Option_ColorDisabledOff;
            QEXTIconFontAwesome::OptionType textOption = (QIcon::On == state) ? QEXTIconFontAwesome::Option_TextDisabled :
                                                                                QEXTIconFontAwesome::Option_TextDisabledOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        else if (mode == QIcon::Active)
        {
            QEXTIconFontAwesome::OptionType colorOption = (QIcon::On == state) ? QEXTIconFontAwesome::Option_ColorActive :
                                                                                 QEXTIconFontAwesome::Option_ColorActiveOff;
            QEXTIconFontAwesome::OptionType textOption = (QIcon::On == state) ? QEXTIconFontAwesome::Option_TextActive :
                                                                                QEXTIconFontAwesome::Option_TextActiveOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        else if (mode == QIcon::Selected)
        {
            QEXTIconFontAwesome::OptionType colorOption = (QIcon::On == state) ? QEXTIconFontAwesome::Option_ColorSelected :
                                                                                 QEXTIconFontAwesome::Option_ColorSelectedOff;
            QEXTIconFontAwesome::OptionType textOption = (QIcon::On == state) ? QEXTIconFontAwesome::Option_TextSelected :
                                                                                QEXTIconFontAwesome::Option_TextSelectedOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        painter->setPen(color);

        // add some 'padding' around the icon
        int drawSize = qRound(rect.height() * options.value(QEXTIconFontAwesome::Option_ScaleFactor).toFloat());

        painter->setFont(awesome->font(drawSize));
        painter->drawText(rect, text, QTextOption(Qt::AlignCenter | Qt::AlignVCenter));
        painter->restore();
    }
};

/// The painter icon engine.
class QEXTIconFontAwesomeIconPainterIconEngine : public QIconEngine
{
public:
    QEXTIconFontAwesomeIconPainterIconEngine(QEXTIconFontAwesome *awesome,
                                              QEXTIconFontAwesomeIconPainterInterface *painter,
                                              const QEXTIconFontAwesome::FontOptionValueMap &options)
        : m_awesomeRef(awesome),
          m_iconPainterRef(painter),
          m_options(options)
    {
    }

    virtual ~QEXTIconFontAwesomeIconPainterIconEngine() {}

    QEXTIconFontAwesomeIconPainterIconEngine *clone() const
    {
        return new QEXTIconFontAwesomeIconPainterIconEngine(m_awesomeRef, m_iconPainterRef, m_options);
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
    QEXTIconFontAwesome *m_awesomeRef;                         ///< a reference to the QEXTIconFontAwesome instance
    QEXTIconFontAwesomeIconPainterInterface *m_iconPainterRef; ///< a reference to the icon painter
    QEXTIconFontAwesome::FontOptionValueMap m_options;                                 ///< the options for this icon painter
};

/// The default icon colors
QEXTIconFontAwesome::QEXTIconFontAwesome(QObject *parent) : QObject(parent)
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

    m_fontIconPainter = new QEXTIconFontAwesomeCharIconPainter;
    m_fontNameTextMap = this->fontNameTextMap();

    static int fontAwesomeFontId = -1;
    // only load font-awesome once
    if (fontAwesomeFontId < 0)
    {
        // The macro below internally calls "qInitResources_QEXTIconsFontAwesome()". this initializes
        // the resource system. For a .pri project this isn't required, but when building and using a
        // static library the resource need to initialized first.
        ///
        // I've checked th qInitResource_* code and calling this method mutliple times shouldn't be any problem
        // (More info about this subject:  http://qt-project.org/wiki/QtResources)
        Q_INIT_RESOURCE(QEXTIconFont);

        // load the font file
        QFile res(":/QEXTIconFont/fontawesome/fontawesome-webfont.ttf");
        if (!res.open(QIODevice::ReadOnly))
        {
            qWarning() << "QEXTIconFontAwesome::QEXTIconFontAwesome(): Font awesome font could not be loaded!";
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
        qWarning() << "QEXTIconFontAwesome::QEXTIconFontAwesome(): Font awesome font is empty?!";
        fontAwesomeFontId = -1; // restore the font-awesome id
    }
}

QEXTIconFontAwesome::~QEXTIconFontAwesome()
{
    delete m_fontIconPainter;
    qDeleteAll(m_painterMap);
}

int QEXTIconFontAwesome::maiorVersion()
{
    return 4;
}

int QEXTIconFontAwesome::minorVersion()
{
    return 7;
}

QString QEXTIconFontAwesome::version() const
{
    return QString("%1.%2").arg(this->maiorVersion()).arg(this->minorVersion());
}

QString QEXTIconFontAwesome::textFromKey(const QString &key)
{
    if(!key.isEmpty())
    {
        int index = this->staticMetaObject.indexOfEnumerator("FontType");
        return QString(this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data()));
    }
    return QString();
}

QString QEXTIconFontAwesome::textFromValue(const int &type)
{
    return QString(type);
}

QList<QString> QEXTIconFontAwesome::fontNamelist()
{
    QMetaEnum enumType = QEXTIconFontAwesome::staticMetaObject.enumerator(QEXTIconFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    QList<QString> list;
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        list.append(enumType.key(i));
    }
    return list;
}

QList<QString> QEXTIconFontAwesome::fontTextlist()
{
    QMetaEnum enumType = QEXTIconFontAwesome::staticMetaObject.enumerator(QEXTIconFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
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

QEXTIconFontAwesome::FontNameTextMap QEXTIconFontAwesome::fontNameTextMap()
{
    FontNameTextMap nameTextMap;
    QMetaEnum enumType = QEXTIconFontAwesome::staticMetaObject.enumerator(QEXTIconFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    int index = this->staticMetaObject.indexOfEnumerator("FontType");
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        QString key = enumType.key(i);
        FontType value = (FontType)this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data());
        nameTextMap.insert(key, value);
    }
    return nameTextMap;
}

void QEXTIconFontAwesome::setDefaultOption(const OptionType &option, const QVariant &value)
{
    m_defaultOptions.insert(option, value);
}

QVariant QEXTIconFontAwesome::defaultOption(const OptionType &option)
{
    return m_defaultOptions.value(option);
}

QChar QEXTIconFontAwesome::fontChar(QEXTIconFontAwesome::FontType character)
{
    return QChar(character);
}

QIcon QEXTIconFontAwesome::icon(FontType character, const FontOptionValueMap &options)
{
    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);
    optionMap.insert(Option_Text, QString(QChar(static_cast<int>(character))));

    return this->icon(m_fontIconPainter, optionMap);
}

QIcon QEXTIconFontAwesome::icon(QEXTIconFontAwesome::FontType character, const QColor &color)
{
    FontOptionValueMap options;
    options.insert(Option_Color, color);
    options.insert(Option_ColorOff, color);
    options.insert(Option_ColorActive, color);
    options.insert(Option_ColorActiveOff, color);
    options.insert(Option_ColorDisabled, color);
    options.insert(Option_ColorDisabledOff, color);
    options.insert(Option_ColorSelected, color);
    options.insert(Option_ColorSelectedOff, color);

    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);
    optionMap.insert(Option_Text, QString(QChar(static_cast<int>(character))));

    return this->icon(m_fontIconPainter, optionMap);
}

QIcon QEXTIconFontAwesome::icon(const QString &name, const FontOptionValueMap &options)
{
    // when it's a named codepoint
    if (m_fontNameTextMap.count(name))
    {
        return this->icon(m_fontNameTextMap.value(name), options);
    }

    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);

    // this method first tries to retrieve the icon
    QEXTIconFontAwesomeIconPainterInterface *painter = m_painterMap.value(name);
    if (!painter)
    {
        return QIcon();
    }

    return this->icon(painter, optionMap);
}

QIcon QEXTIconFontAwesome::icon(const QString &name, const QColor &color)
{
    FontOptionValueMap options;
    options.insert(Option_Color, color);
    options.insert(Option_ColorOff, color);
    options.insert(Option_ColorActive, color);
    options.insert(Option_ColorActiveOff, color);
    options.insert(Option_ColorDisabled, color);
    options.insert(Option_ColorDisabledOff, color);
    options.insert(Option_ColorSelected, color);
    options.insert(Option_ColorSelectedOff, color);

    // when it's a named codepoint
    if (m_fontNameTextMap.count(name))
    {
        return this->icon(m_fontNameTextMap.value(name), options);
    }

    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);

    // this method first tries to retrieve the icon
    QEXTIconFontAwesomeIconPainterInterface *painter = m_painterMap.value(name);
    if (!painter)
    {
        return QIcon();
    }

    return this->icon(painter, optionMap);
}

QIcon QEXTIconFontAwesome::icon(QEXTIconFontAwesomeIconPainterInterface *painter, const FontOptionValueMap &optionMap)
{
    // Warning, when you use memoryleak detection. You should turn it of for the next call
    // QIcon's placed in gui items are often cached and not deleted when my memory-leak detection checks for leaks.
    // I'm not sure if it's a Qt bug or something I do wrong
    QEXTIconFontAwesomeIconPainterIconEngine *engine = new QEXTIconFontAwesomeIconPainterIconEngine(this, painter, optionMap);
    return QIcon(engine);
}

void QEXTIconFontAwesome::give(const QString &name, QEXTIconFontAwesomeIconPainterInterface *painter)
{
    delete m_painterMap.value(name); // delete the old one
    m_painterMap.insert(name, painter);
}

QFont QEXTIconFontAwesome::font(int size)
{
    QFont font(m_fontName);
    font.setPixelSize(size);
    return font;
}

QString QEXTIconFontAwesome::fontName()
{
    return m_fontName;
}

QEXTIconFontAwesome *qextGlobalFontAwesome()
{
    static QEXTIconFontAwesome *fontAwesome = QEXT_DECL_NULLPTR;
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (QEXT_DECL_NULLPTR == fontAwesome)
    {
        fontAwesome = new QEXTIconFontAwesome(qApp);
    }
    return fontAwesome;
}
