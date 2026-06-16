#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QFile>
#include <QSocketNotifier>
#include <unistd.h>
#include <QDebug>

#include <iostream>

static const char *WID_PREFIX  = ">>>WID:";
static const char *WID_SUFFIX  = "<<<";
static const char *SHOW_MARKER = ">>>SHOW<<<";
static const char *SIZE_MARKER = ">>>SIZE:";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto *widget = new QWidget;
    widget->setWindowTitle("IPC Child Widget");
    // widget->setMinimumSize(300, 200);
    widget->setStyleSheet(
        "QWidget { background: qlineargradient(x1:0,y1:0,x2:1,y2:1,"
        "stop:0 #2ecc71, stop:1 #27ae60); border-radius: 8px; }");

    auto *layout = new QVBoxLayout(widget);
    auto *label = new QLabel("IPC Child Process\n\nWId will be sent to parent");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");
    layout->addWidget(label);

    WId wid = widget->winId();
    std::cout << WID_PREFIX << wid << WID_SUFFIX << std::endl;
    std::cout.flush();

    qDebug() << "[Child] WId sent:" << wid;

    auto *notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, &app);
    QObject::connect(notifier, &QSocketNotifier::activated, [&](int) 
    {
        QFile stdinFile;
        stdinFile.open(STDIN_FILENO, QIODevice::ReadOnly | QIODevice::Unbuffered);
        char buf[256];
        qint64 n = stdinFile.readLine(buf, sizeof(buf));
        while (n > 0) {
            QString line = QString::fromUtf8(buf, n).trimmed();
            if (line.startsWith(SIZE_MARKER))
            {
                int w = 0, h = 0;
                int pos1 = QString(SIZE_MARKER).length();
                int pos2 = line.indexOf(',', pos1);
                int pos3 = line.indexOf("<<<", pos2);
                if (pos1 > 0 && pos2 > pos1 && pos3 > pos2) {
                    w = line.mid(pos1, pos2 - pos1).toInt();
                    h = line.mid(pos2 + 1, pos3 - pos2 - 1).toInt();
                    if (w > 0 && h > 0) {
                        qDebug() << "[Child] Received SIZE:" << w << h;
                        widget->resize(w, h);
                    }
                }
            }
            else if (line.contains(SHOW_MARKER))
            {
                qDebug() << "[Child] Received SHOW";
                widget->show();
                notifier->setEnabled(false);
                return;
            }
            n = stdinFile.readLine(buf, sizeof(buf));
        }
    });

    QTimer::singleShot(5000, widget, [&]() 
    {
        if (!widget->isVisible()) 
        {
            qDebug() << "[Child] Timeout showing anyway";
            widget->show();
        }
    });

    return app.exec();
}