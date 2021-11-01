#ifndef QTKPLUGINBROWSEREDITORS_H
#define QTKPLUGINBROWSEREDITORS_H

#include <QObject>
#include <QTabWidget>

class QTKPluginBrowserEditors : public QObject
{
  Q_OBJECT

public:

  QTKPluginBrowserEditors(QWidget* editorArea);

  void openEditor(const QString& location, const QByteArray& content, const QString& title, const QString& tooltip = QString());

private:

  QStringList editorLocations;

  QTabWidget tabWidget;

private Q_SLOTS:

  void tabCloseRequested(int index);
};

#endif // QTKPLUGINBROWSEREDITORS_H
