#include <QApplication>
#include <QLineEdit>
#include <QFontDatabase>

#include <qextKeyboard.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.resize(850, 370);

    QExtKeyboard keyboard;
    keyboard.show();

    QLineEdit textInput(&keyboard);
    textInput.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(&textInput, 1);
    v->addWidget(&keyboard, 5);

    window.setLayout(v);
    window.show();

    QWidget window2;
    window2.setWindowTitle(QStringLiteral(""));
    window2.resize(450, 370);

    QExtNumberKeyboard keyboard2;
    keyboard2.show();

    QLineEdit textInput2(&keyboard2);
    textInput2.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QVBoxLayout *v2 = new QVBoxLayout;
    v2->addWidget(&textInput2, 1);
    v2->addWidget(&keyboard2, 5);

    window2.setLayout(v2);
    window2.show();

    return a.exec();
}
