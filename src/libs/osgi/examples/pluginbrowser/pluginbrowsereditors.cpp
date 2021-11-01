#include "qtkpluginbrowsereditors.h"

#include <QTextEdit>
#include <QVBoxLayout>

QTKPluginBrowserEditors::QTKPluginBrowserEditors(QWidget* editorArea)
    : QObject(editorArea), tabWidget(editorArea)
{
    editorArea->setLayout(new QVBoxLayout());
    editorArea->layout()->addWidget(&tabWidget);

    tabWidget.setTabsClosable(true);

    connect(&tabWidget, SIGNAL(tabCloseRequested(int)), SLOT(tabCloseRequested(int)));
}

void QTKPluginBrowserEditors::openEditor(const QString &location, const QByteArray& content,
                                         const QString& title, const QString& tooltip)
{
    Q_UNUSED(tooltip)

    if (editorLocations.contains(location))
    {
        int index = editorLocations.indexOf(location);
        tabWidget.setCurrentIndex(index);
    }
    else
    {
        QTextEdit* textEdit = new QTextEdit();
        textEdit->setReadOnly(true);
        textEdit->setPlainText(QString(content));
        int index = tabWidget.addTab(textEdit, title);
        editorLocations.insert(index, location);
        tabWidget.setCurrentIndex(index);
    }
}

void QTKPluginBrowserEditors::tabCloseRequested(int index)
{
    editorLocations.removeAt(index);
    tabWidget.removeTab(index);
}
