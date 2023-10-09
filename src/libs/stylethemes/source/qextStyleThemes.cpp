#include <private/qextStyleThemes_p.h>


QExtStyleThemePrivate::QExtStyleThemePrivate(QExtStyleTheme *q)
    : q_ptr(q)
{

}

QExtStyleThemePrivate::~QExtStyleThemePrivate()
{

}

QExtStyleTheme::QExtStyleTheme(QObject *parent)
{

}

QExtStyleTheme::~QExtStyleTheme()
{

}

void QExtStyleTheme::setStylesDirPath(const QString &path)
{

}

QString QExtStyleTheme::stylesDirPath() const
{


}

QString QExtStyleTheme::currentStyle() const
{

}

QString QExtStyleTheme::currentStylePath() const
{

}

const QStringList &QExtStyleTheme::styles() const
{

}

const QStringList &QExtStyleTheme::themes() const
{

}

const QMap<QString, QString> &QExtStyleTheme::themeColorVariables() const
{

}

QString QExtStyleTheme::path(eLocation location) const
{

}

QString QExtStyleTheme::outputDirPath() const
{

}

void QExtStyleTheme::setOutputDirPath(const QString &path)
{

}

QString QExtStyleTheme::currentStyleOutputPath() const
{

}

QString QExtStyleTheme::themeVariableValue(const QString &variableId) const
{

}

void QExtStyleTheme::setThemeVariableValue(const QString &variableId, const QString &value)
{

}

QColor QExtStyleTheme::themeColor(const QString &variableId) const
{

}

QString QExtStyleTheme::currentTheme() const
{

}

QString QExtStyleTheme::styleSheet() const
{

}

QString QExtStyleTheme::processStylesheetTemplate(const QString &templateText, const QString &outputFile)
{

}

const QIcon &QExtStyleTheme::styleIcon() const
{

}

QExtStyleTheme::eError QExtStyleTheme::error() const
{

}

QString QExtStyleTheme::errorString() const
{

}

QPalette QExtStyleTheme::generateThemePalette() const
{

}

const QJsonObject &QExtStyleTheme::styleParameters() const
{

}

bool QExtStyleTheme::isCurrentThemeDark() const
{

}

void QExtStyleTheme::replaceSvgColors(QByteArray &svgContent, const ColorReplaceVector &colorReplaceVector)
{

}

QIcon QExtStyleTheme::loadThemeAwareSvgIcon(const QString &filename)
{

}

bool QExtStyleTheme::setCurrentTheme(const QString &theme)
{

}

void QExtStyleTheme::setDefaultTheme()
{

}

bool QExtStyleTheme::setCurrentStyle(const QString &style)
{

}

bool QExtStyleTheme::updateStylesheet()
{

}

bool QExtStyleTheme::processStyleTemplate()
{

}

bool QExtStyleTheme::generateResources()
{

}

void QExtStyleTheme::updateApplicationPaletteColors()
{

}
