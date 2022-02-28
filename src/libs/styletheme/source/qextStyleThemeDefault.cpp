#include <qextStyleThemeDefault.h>
#include <qextStyleThemeConstants.h>

#include <QFile>
#include <QDebug>

struct ThemeRoleDict
{
    int id;
    const char *text;
};

class QEXTStyleThemeDefaultPrivate
{
public:
    explicit QEXTStyleThemeDefaultPrivate(QEXTStyleThemeDefault *q);
    virtual ~QEXTStyleThemeDefaultPrivate();

    QString currentRoleText(int role) const;

    QEXTStyleThemeDefault * const q_ptr;

    QEXTStyleThemeDefault::ThemeType m_themeType;
    QString m_additionalStyle;

    static QMap<int, QString> sm_themeRoleMap;
    static ThemeRoleDict sm_themeRoleDict[];

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleThemeDefaultPrivate)
    QEXT_DECL_PUBLIC(QEXTStyleThemeDefault)
};

QMap<int, QString> QEXTStyleThemeDefaultPrivate::sm_themeRoleMap;

ThemeRoleDict QEXTStyleThemeDefaultPrivate::sm_themeRoleDict[] =
{
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_StyleName, "flatwhite"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_TextColor, "#57595B"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_PanelColor, "#FFFFFF"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_BorderColor, "#B6B6B6"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_HighColor, "#575959"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_NormalStartColor, "#E4E4E4"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_NormalEndColor, "#E4E4E4"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_DarkStartColor, "#F6F6F6"},
    {QEXTStyleThemeDefault::Theme_FlatWhite * 100 + QEXTStyleThemeDefault::Role_DarkEndColor, "#F6F6F6"},

    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_StyleName, "lightblue"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_TextColor, "#386487"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_PanelColor, "#EAF7FF"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_BorderColor, "#C0DCF2"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_HighColor, "#386488"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_NormalStartColor, "#DEF0FE"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_NormalEndColor, "#C0DEF6"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_DarkStartColor, "#F2F9FF"},
    {QEXTStyleThemeDefault::Theme_LightBlue * 100 + QEXTStyleThemeDefault::Role_DarkEndColor, "#DAEFFF"},

    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_StyleName, "psblack"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_TextColor, "#DCDCDC"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_PanelColor, "#444444"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_BorderColor, "#242424"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_HighColor, "#AAAAAA"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_NormalStartColor, "#484848"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_NormalEndColor, "#383838"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_DarkStartColor, "#646464"},
    {QEXTStyleThemeDefault::Theme_PSBlack * 100 + QEXTStyleThemeDefault::Role_DarkEndColor, "#525252"},
};

QEXTStyleThemeDefaultPrivate::QEXTStyleThemeDefaultPrivate(QEXTStyleThemeDefault *q)
    : q_ptr(q)
    , m_themeType(QEXTStyleThemeDefault::Theme_FlatWhite)
{
    if (sm_themeRoleMap.isEmpty())
    {
        int count = sizeof(sm_themeRoleDict) / sizeof(ThemeRoleDict);
        for (int i = 0; i < count; ++i)
        {
            sm_themeRoleMap.insert(sm_themeRoleDict[i].id, sm_themeRoleDict[i].text);
        }
    }
}

QEXTStyleThemeDefaultPrivate::~QEXTStyleThemeDefaultPrivate()
{

}

QString QEXTStyleThemeDefaultPrivate::currentRoleText(int role) const
{
    return sm_themeRoleMap.value(m_themeType * 100 + role, "");
}




const int QEXTStyleThemeDefault::RoleNum = 9;
const int QEXTStyleThemeDefault::ThemeNum = 3;

QEXTStyleThemeDefault::QEXTStyleThemeDefault(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTStyleThemeDefaultPrivate(this))
{

}

QEXTStyleThemeDefault::~QEXTStyleThemeDefault()
{

}

QString QEXTStyleThemeDefault::styleName() const
{
    return "Default";
}

QString QEXTStyleThemeDefault::themeName(int type) const
{
    switch (type)
    {
    case Theme_FlatWhite: return "FlatWhite";
    case Theme_LightBlue: return "LightBlue";
    case Theme_PSBlack: return "PSBlack";
    default: break;
    }
    return "";
}

int QEXTStyleThemeDefault::currentTheme() const
{
    Q_D(const QEXTStyleThemeDefault);
    return d->m_themeType;
}

void QEXTStyleThemeDefault::setCurrentTheme(int type)
{
    Q_D(QEXTStyleThemeDefault);
    if (type >= 0 && type < ThemeNum)
    {
        d->m_themeType = ThemeType(type);
    }
    else
    {
        qWarning() << "QEXTStyleThemeDefault::setCurrentTheme():type out of range";
    }
}

QString QEXTStyleThemeDefault::styleSheet() const
{
    Q_D(const QEXTStyleThemeDefault);
    QFile file(":/QEXTStyleTheme/default/default.css");
    QString qssString;
    if (file.open(QFile::ReadOnly))
    {
        QTextStream stream(&file);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
        stream.setCodec("utf-8");
#endif
        QStringList list;
        while (!stream.atEnd())
        {
            QString line;
            stream >> line;
            list << line;
        }
        list.append(d->m_additionalStyle);
        qssString = list.join("\n");
        file.close();
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_NAME, d->currentRoleText(Role_StyleName));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_TEXT_COLOR, d->currentRoleText(Role_TextColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_PANEL_COLOR, d->currentRoleText(Role_PanelColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_BORDER_COLOR, d->currentRoleText(Role_BorderColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_HIGHT_COLOR, d->currentRoleText(Role_HighColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_NORMAL_START_COLOR, d->currentRoleText(Role_NormalStartColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_NORMAL_END_COLOR, d->currentRoleText(Role_NormalEndColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_DARK_START_COLOR, d->currentRoleText(Role_DarkStartColor));
        qssString.replace(QEXTStyleThemeConstants::DEFAULT_STYLE_DARK_END_COLOR, d->currentRoleText(Role_DarkEndColor));
    }
    return qssString;
}

QString QEXTStyleThemeDefault::additionalStyle() const
{
    Q_D(const QEXTStyleThemeDefault);
    return d->m_additionalStyle;
}

void QEXTStyleThemeDefault::setAdditionalStyle(const QString &style)
{
    Q_D(QEXTStyleThemeDefault);
    if (style != d->m_additionalStyle)
    {
        d->m_additionalStyle = style;
    }
}

void QEXTStyleThemeDefault::addAdditionalStyle(const QString &style)
{
    Q_D(QEXTStyleThemeDefault);
    d->m_additionalStyle.append(style);
}
