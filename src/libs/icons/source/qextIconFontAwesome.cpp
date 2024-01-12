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
static QExtIconFontAwesome::FontOptionValueMap qextMergeFontOptions(const QExtIconFontAwesome::FontOptionValueMap &defaults,
                                                                    const QExtIconFontAwesome::FontOptionValueMap &override)
{
    QExtIconFontAwesome::FontOptionValueMap result = defaults;
    if (!override.isEmpty())
    {
        QExtIconFontAwesome::FontOptionValueMap::const_iterator iter;
        for (iter = override.begin(); iter != override.end(); ++iter)
        {
            result.insert(iter.key(), iter.value());
        }
    }
    return result;
}

}

/// The font-awesome icon painter
class QExtIconFontAwesomeCharIconPainter : public QExtIconFontAwesomeIconPainterInterface
{
public:
    virtual void paint(QExtIconFontAwesome *awesome, QPainter *painter, const QRect &rect, QIcon::Mode mode,
                       QIcon::State state, const QExtIconFontAwesome::FontOptionValueMap &options) QEXT_OVERRIDE
    {
        Q_UNUSED(state);
        Q_UNUSED(options);

        painter->save();

        // set the correct color
        QColor color = options.value(QExtIconFontAwesome::Option_Color).value<QColor>();
        QString text = options.value(QExtIconFontAwesome::Option_Text).toString();

        if (mode == QIcon::Disabled)
        {
            QExtIconFontAwesome::OptionType colorOption = (QIcon::On == state) ? QExtIconFontAwesome::Option_ColorDisabled :
                                                                                 QExtIconFontAwesome::Option_ColorDisabledOff;
            QExtIconFontAwesome::OptionType textOption = (QIcon::On == state) ? QExtIconFontAwesome::Option_TextDisabled :
                                                                                QExtIconFontAwesome::Option_TextDisabledOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        else if (mode == QIcon::Active)
        {
            QExtIconFontAwesome::OptionType colorOption = (QIcon::On == state) ? QExtIconFontAwesome::Option_ColorActive :
                                                                                 QExtIconFontAwesome::Option_ColorActiveOff;
            QExtIconFontAwesome::OptionType textOption = (QIcon::On == state) ? QExtIconFontAwesome::Option_TextActive :
                                                                                QExtIconFontAwesome::Option_TextActiveOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        else if (mode == QIcon::Selected)
        {
            QExtIconFontAwesome::OptionType colorOption = (QIcon::On == state) ? QExtIconFontAwesome::Option_ColorSelected :
                                                                                 QExtIconFontAwesome::Option_ColorSelectedOff;
            QExtIconFontAwesome::OptionType textOption = (QIcon::On == state) ? QExtIconFontAwesome::Option_TextSelected :
                                                                                QExtIconFontAwesome::Option_TextSelectedOff;
            color = options.value(colorOption).value<QColor>();
            QVariant alt = options.value(textOption);
            if (alt.isValid())
            {
                text = alt.toString();
            }
        }
        painter->setPen(color);

        // add some 'padding' around the icon
        int drawSize = qRound(rect.height() * options.value(QExtIconFontAwesome::Option_ScaleFactor).toFloat());

        painter->setFont(awesome->font(drawSize));
        painter->drawText(rect, text, QTextOption(Qt::AlignCenter | Qt::AlignVCenter));
        painter->restore();
    }
};

/// The painter icon engine.
class QExtIconFontAwesomeIconPainterIconEngine : public QIconEngine
{
public:
    QExtIconFontAwesomeIconPainterIconEngine(QExtIconFontAwesome *awesome,
                                              QExtIconFontAwesomeIconPainterInterface *painter,
                                              const QExtIconFontAwesome::FontOptionValueMap &options)
        : m_awesomeRef(awesome),
          m_iconPainterRef(painter),
          m_options(options)
    {
    }

    virtual ~QExtIconFontAwesomeIconPainterIconEngine() {}

    QExtIconFontAwesomeIconPainterIconEngine *clone() const override
    {
        return new QExtIconFontAwesomeIconPainterIconEngine(m_awesomeRef, m_iconPainterRef, m_options);
    }

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE
    {
        Q_UNUSED(mode);
        Q_UNUSED(state);
        m_iconPainterRef->paint(m_awesomeRef, painter, rect, mode, state, m_options);
    }

    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE
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
    QExtIconFontAwesome *m_awesomeRef;                         ///< a reference to the QExtIconFontAwesome instance
    QExtIconFontAwesomeIconPainterInterface *m_iconPainterRef; ///< a reference to the icon painter
    QExtIconFontAwesome::FontOptionValueMap m_options;                                 ///< the options for this icon painter
};

/// The default icon colors
QExtIconFontAwesome::QExtIconFontAwesome(QObject *parent) : QObject(parent)
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

    m_fontIconPainter = new QExtIconFontAwesomeCharIconPainter;
    m_fontNameTextMap = this->fontNameTextMap();

    static int fontAwesomeFontId = -1;
    // only load font-awesome once
    if (fontAwesomeFontId < 0)
    {
        // The macro below internally calls "qInitResources_QExtIconFontAwesome()". this initializes
        // the resource system. For a .pri project this isn't required, but when building and using a
        // static library the resource need to initialized first.
        ///
        // I've checked th qInitResource_* code and calling this method mutliple times shouldn't be any problem
        // (More info about this subject:  http://qt-project.org/wiki/QtResources)
        Q_INIT_RESOURCE(qextIcons);

        // load the font file
        QFile res(":/QExtIcons/fontawesome/fontawesome-webfont.ttf");
        if (!res.open(QIODevice::ReadOnly))
        {
            qWarning() << "QExtIconFontAwesome::QExtIconFontAwesome(): Font awesome font could not be loaded!";
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
        qWarning() << "QExtIconFontAwesome::QExtIconFontAwesome(): Font awesome font is empty?!";
        fontAwesomeFontId = -1; // restore the font-awesome id
    }
}

QExtIconFontAwesome::~QExtIconFontAwesome()
{
    delete m_fontIconPainter;
    qDeleteAll(m_painterMap);
}

int QExtIconFontAwesome::maiorVersion()
{
    return 4;
}

int QExtIconFontAwesome::minorVersion()
{
    return 7;
}

QString QExtIconFontAwesome::version() const
{
    return QString("%1.%2").arg(this->maiorVersion()).arg(this->minorVersion());
}

QString QExtIconFontAwesome::textFromKey(const QString &key)
{
    if(!key.isEmpty())
    {
        int index = this->staticMetaObject.indexOfEnumerator("FontType");
        return QChar(this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data()));
    }
    return QString();
}

QString QExtIconFontAwesome::textFromValue(const int &type)
{
    return QChar(type);
}

QList<QString> QExtIconFontAwesome::fontNamelist()
{
    QMetaEnum enumType = QExtIconFontAwesome::staticMetaObject.enumerator(QExtIconFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    QList<QString> list;
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        list.append(enumType.key(i));
    }
    return list;
}

QList<QString> QExtIconFontAwesome::fontTextlist()
{
    QMetaEnum enumType = QExtIconFontAwesome::staticMetaObject.enumerator(QExtIconFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    int index = this->staticMetaObject.indexOfEnumerator("FontType");
    QList<QString> list;
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        QString key = enumType.key(i);
        QString value = QChar(this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data()));
        list.append(value);
    }
    return list;
}

QExtIconFontAwesome::FontNameTextMap QExtIconFontAwesome::fontNameTextMap()
{
    FontNameTextMap nameTextMap;
    QMetaEnum enumType = QExtIconFontAwesome::staticMetaObject.enumerator(QExtIconFontAwesome::staticMetaObject.indexOfEnumerator("FontType"));
    int index = this->staticMetaObject.indexOfEnumerator("FontType");
    for(int i = 0; i < enumType.keyCount(); ++i)
    {
        QString key = enumType.key(i);
        FontType value = (FontType)this->staticMetaObject.enumerator(index).keysToValue(key.toLatin1().data());
        nameTextMap.insert(key, value);
    }
    return nameTextMap;
}

void QExtIconFontAwesome::setDefaultOption(const OptionType &option, const QVariant &value)
{
    m_defaultOptions.insert(option, value);
}

QVariant QExtIconFontAwesome::defaultOption(const OptionType &option)
{
    return m_defaultOptions.value(option);
}

QChar QExtIconFontAwesome::fontChar(QExtIconFontAwesome::FontType character)
{
    return QChar(character);
}

QIcon QExtIconFontAwesome::icon(FontType character, const FontOptionValueMap &options)
{
    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);
    optionMap.insert(Option_Text, QString(QChar(static_cast<int>(character))));

    return this->icon(m_fontIconPainter, optionMap);
}

QIcon QExtIconFontAwesome::icon(QExtIconFontAwesome::FontType character, const QColor &color)
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

QIcon QExtIconFontAwesome::icon(const QString &name, const FontOptionValueMap &options)
{
    // when it's a named codepoint
    if (m_fontNameTextMap.count(name))
    {
        return this->icon(m_fontNameTextMap.value(name), options);
    }

    // create a merged QVariantMap to have default options and icon-specific options
    FontOptionValueMap optionMap = qextMergeFontOptions(m_defaultOptions, options);

    // this method first tries to retrieve the icon
    QExtIconFontAwesomeIconPainterInterface *painter = m_painterMap.value(name);
    if (!painter)
    {
        return QIcon();
    }

    return this->icon(painter, optionMap);
}

QIcon QExtIconFontAwesome::icon(const QString &name, const QColor &color)
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
    QExtIconFontAwesomeIconPainterInterface *painter = m_painterMap.value(name);
    if (!painter)
    {
        return QIcon();
    }

    return this->icon(painter, optionMap);
}

QIcon QExtIconFontAwesome::icon(QExtIconFontAwesomeIconPainterInterface *painter, const FontOptionValueMap &optionMap)
{
    // Warning, when you use memoryleak detection. You should turn it of for the next call
    // QIcon's placed in gui items are often cached and not deleted when my memory-leak detection checks for leaks.
    // I'm not sure if it's a Qt bug or something I do wrong
    QExtIconFontAwesomeIconPainterIconEngine *engine = new QExtIconFontAwesomeIconPainterIconEngine(this, painter, optionMap);
    return QIcon(engine);
}

void QExtIconFontAwesome::give(const QString &name, QExtIconFontAwesomeIconPainterInterface *painter)
{
    delete m_painterMap.value(name); // delete the old one
    m_painterMap.insert(name, painter);
}

QFont QExtIconFontAwesome::font(int size)
{
    QFont font(m_fontName);
    font.setPixelSize(size);
    return font;
}

QString QExtIconFontAwesome::fontName()
{
    return m_fontName;
}

QExtIconFontAwesome *qextGlobalFontAwesome()
{
    static QExtIconFontAwesome *fontAwesome = QEXT_NULLPTR;
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (QEXT_NULLPTR == fontAwesome)
    {
        fontAwesome = new QExtIconFontAwesome(qApp);
    }
    return fontAwesome;
}
