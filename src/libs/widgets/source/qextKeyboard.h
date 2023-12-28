#ifndef _QEXTKEYBOARD_H
#define _QEXTKEYBOARD_H

#include <qextWidgetGlobal.h>

#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>
#include <QListWidgetItem>


/***********************************************************************************************************************
** QExtKeyButton
***********************************************************************************************************************/
class QExtKeyButton : public QPushButton
{
    Q_OBJECT
public:
    enum Type { Auto = 0, LowerCase, UpperCase, SpecialChar };

    struct Mode
    {
        Mode() { }
        Mode(int _key, QString _value, QVariant _display = QString(), Type _type = Auto)
        {
            key     = _key;
            value   = _value;
            display = _display;
            type    = _type;
        }

        int key;          /* Qt::Key */
        QString value;    /* text */
        QVariant display;  /* display text or icon */
        Type type;        /* default: Auto */
    };

    QExtKeyButton(const QList<Mode> modes = QList<Mode>(), QWidget *parent = NULL);
    Mode mode();

    void onReponse(const QObject* receiverObj, const QString &receiver);

    void switchCapsLock();
    void switchSpecialChar();
    void switching(); /* Cycle switch. */

signals:
    void pressed(int key, QString value);

private slots:
    void onPressed();

private:
    Type find(const QString &value);
    Mode find(Type type);
    Mode findNext();
    void setDisplayContent(const QVariant &content);

private:
    Mode        m_preMode;
    Mode        m_mode;
    QList<Mode> m_modes;
};


/***********************************************************************************************************************
** QExtKeyButton
***********************************************************************************************************************/
class QExtAbstractKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit QExtAbstractKeyboard(QWidget *parent = QEXT_NULLPTR) : QWidget(parent) { }
    ~QExtAbstractKeyboard() QEXT_OVERRIDE { }

    const QString name() { return m_name; }
    void setName(const QString &name) { m_name = name; }

public slots:
    virtual void update(const QString &text) { Q_UNUSED(text); }

    void onKeyPressed(int key, QString value)
    {
        qDebug() << "key: " << key << "Value: " << value;
        QWidget *receiver = QApplication::focusWidget();
        if (!receiver)
        {
            return;
        }

        QKeyEvent keyPress(QEvent::KeyPress,     key, Qt::NoModifier, value);
        QKeyEvent keyRelease(QEvent::KeyRelease, key, Qt::NoModifier, value);

        QApplication::sendEvent(receiver, &keyPress);
        QApplication::sendEvent(receiver, &keyRelease);
    }

signals:
    void keyPressed(int key, QString value);

private:
    QString m_name;
};


/***********************************************************************************************************************
** QExtNumberKeyboard
***********************************************************************************************************************/
class QExtNumberKeyboard : public QExtAbstractKeyboard
{
    Q_OBJECT
public:
    QExtNumberKeyboard(QWidget *parent = NULL);

    QExtKeyButton *createButton(QList<QExtKeyButton::Mode> modes);

private slots:
    void onButtonPressed(const int &code, const QString &text);
};



/***********************************************************************************************************************
** QExtKeyButton
***********************************************************************************************************************/
class ChineseWidget : public QListWidget
{
    Q_OBJECT
public:
    ChineseWidget(QWidget *parent = NULL);
    void setText(const QString &text);

signals:
    void pressedChanged(int code, const QString &text);

private slots:
    void onItemClicked(QListWidgetItem *item);

private:
    void addOneItem(const QString &text);
    void loadChineseLib();
    void loadChinesePhraseLib();
    void loadGoogleChineseLib();

private:
    QMap<QString, QList<QPair<QString, QString> > > m_data;
};

class QExtKeyboardPrivate;
class QExtKeyboard : public QExtAbstractKeyboard
{
    Q_OBJECT
public:
    explicit QExtKeyboard(QWidget *parent = QEXT_NULLPTR);
    ~QExtKeyboard() QEXT_OVERRIDE;

protected:
    void resizeEvent(QResizeEvent *e) QEXT_OVERRIDE;

private slots:
    void switchCapsLock();
    void switchSpecialChar();
    void switchEnOrCh();
    void onButtonPressed(const int &code, const QString &text);
    void clearBufferText();

private:
    QExtKeyButton *createButton(QList<QExtKeyButton::Mode> modes);
    QWidget *createBar(const QList<QList<QExtKeyButton::Mode> > &modes);
    QWidget *chineseBar();
    QHBoxLayout *h1();
    QHBoxLayout *h2();
    QHBoxLayout *h3();
    QHBoxLayout *h4();
    QWidget *candidateList();
    void resizeButton();

private:
    bool m_isChinese;
    ChineseWidget *m_chineseWidget;
    QString m_bufferText;

protected:
    QScopedPointer<QExtKeyboardPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtKeyboard)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboard)
};

#endif // _QEXTKEYBOARD_H
