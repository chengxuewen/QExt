/* qesptest.h
**************************************/
#ifndef _QESPTEST_H_
#define _QESPTEST_H_

#include <QWidget>

class QLineEdit;
class QTextEdit;
class QEXTSerialPort;
class QSpinBox;

class Test :  public QWidget
{
    Q_OBJECT
public:
    Test(QWidget *parent=0);

    virtual ~Test();

private:
    QLineEdit *message;
    QSpinBox *delaySpinBox;
    QTextEdit *received_msg;
    QEXTSerialPort *port;

private slots:
    void transmitMsg();
    void receiveMsg();
    void appendCR();
    void appendLF();
    void closePort();
    void openPort();
};

#endif
