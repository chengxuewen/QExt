#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    #include <QLoggingCategory>
#endif

#include <navigationlistview.h>
#include <frmnavigationlistview.h>

#include <qextNavigationListView.h>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QApplication app(argc, argv);
    app.setFont(QFont("Microsoft Yahei", 9));

#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

//    QExtIconFontAwesome fa;
//    fa.initFontAwesome();

    QTabWidget w;
    w.addTab(new NavigationListView, "树状导航控件");
    w.addTab(new FrmNavigationListView, "树状导航界面");
    w.setWindowTitle("树状导航示例");
    w.resize(800, 600);
    w.show();

    return app.exec();
}

