#include <private/qextFramelessMainwindow_p.h>

#include <QStyleOption>
#include <QHoverEvent>
#include <QDateTime>
#include <QEvent>
#include <QPainter>
#include <QStyle>
#include <QDebug>



#ifdef Q_OS_WIN
#include "windows.h"
#pragma comment (lib,"user32.lib")
#endif

#define TIMEMS qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))


QEXTFramelessMainWindowPrivate::QEXTFramelessMainWindowPrivate(QEXTFramelessMainWindow *q)
    : q_ptr(q)
{
    m_padding = 8;
    m_moveEnable = true;
    m_resizeEnable = true;

    m_mousePressed = false;
    m_mousePoint = QPoint(0, 0);
    m_mouseRect = QRect(0, 0, 0, 0);

    for (int i = 0; i < 8; ++i)
    {
        m_pressedArea << false;
        m_pressedRect << QRect(0, 0, 0, 0);
    }

    m_isMin = false;
    m_titleBar = 0;
}

QEXTFramelessMainWindowPrivate::~QEXTFramelessMainWindowPrivate()
{

}


QEXTFramelessMainWindow::QEXTFramelessMainWindow(QWidget *parent)
    : QMainWindow(parent), dd_ptr(new QEXTFramelessMainWindowPrivate(this))
{
    Q_D(QEXTFramelessMainWindow);
    d->m_flags = this->windowFlags();

    this->setAttribute(Qt::WA_Hover);
    this->setWindowFlags(d->m_flags | Qt::FramelessWindowHint);

    this->installEventFilter(this);

    //Set properties to create win form effects, move to edge half screen or maximize, etc
    //After setting the title bar, you need to intercept the message WM_NCCALCSIZE below to remove it again
#ifdef Q_OS_WIN
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
#endif
}

QEXTFramelessMainWindow::~QEXTFramelessMainWindow()
{

}

void QEXTFramelessMainWindow::showEvent(QShowEvent *event)
{
    //Fixed the BUG that sometimes the window will not refresh when it is displayed again
    this->setAttribute(Qt::WA_Mapped);
    QMainWindow::showEvent(event);
}

void QEXTFramelessMainWindow::doWindowStateChange(QEvent */*event*/)
{
    Q_D(QEXTFramelessMainWindow);
    //Non-maximized to move and drag size
    if (this->windowState() == Qt::WindowNoState)
    {
        d->m_moveEnable = true;
        d->m_resizeEnable = true;
    }
    else
    {
        d->m_moveEnable = false;
        d->m_resizeEnable = false;
    }

    //Issue change events such as maximization and minimization to change corresponding
    //information such as ICONS and text in the upper right corner of the interface
    emit this->windowStateChanged(!d->m_moveEnable);

    //Fixed a BUG where borderless minimization failed on MAC systems
#ifdef Q_OS_MACOS
    if (this->windowState() & Qt::WindowMinimized)
    {
        d->m_isMin = true;
    }
    else
    {
        if (d->m_isMin)
        {
            //Sets the borderless property
            this->setWindowFlags(d->m_flags | Qt::FramelessWindowHint);
            this->setVisible(true);
            d->m_isMin = false;
        }
    }
#endif
}

void QEXTFramelessMainWindow::doResizeEvent(QEvent *event)
{
    Q_D(QEXTFramelessMainWindow);
    //For borderless stretching in non-WIN system, nativeEvent has been adopted to deal with stretching in WIN system
    //Why don't you just do it computationally because on Win you get a shiver when you stretch to the left
#ifndef Q_OS_WIN
    if (event->type() == QEvent::Resize)
    {
        //Recalculate the area of eight stroke points. The function of the stroke point area
        //is also to calculate whether the mouse coordinates are in a certain area
        int width = this->width();
        int height = this->height();

        //Left stroke point area
        d->m_pressedRect[0] = QRect(0, d->m_padding, d->m_padding, height - d->m_padding * 2);
        //Stroke point area on the right
        d->m_pressedRect[1] = QRect(width - d->m_padding, d->m_padding, d->m_padding, height - d->m_padding * 2);
        //Upper stroke point area
        d->m_pressedRect[2] = QRect(d->m_padding, 0, width - d->m_padding * 2, d->m_padding);
        //Lower side stroke point area
        d->m_pressedRect[3] = QRect(d->m_padding, height - d->m_padding, width - d->m_padding * 2, d->m_padding);

        //The upper left corner stroke point area
        d->m_pressedRect[4] = QRect(0, 0, d->m_padding, d->m_padding);
        //Stroke dot area in the upper right corner
        d->m_pressedRect[5] = QRect(width - d->m_padding, 0, d->m_padding, d->m_padding);
        //Stroke point area in the lower left corner
        d->m_pressedRect[6] = QRect(0, height - d->m_padding, d->m_padding, d->m_padding);
        //Stroke point area in the lower right corner
        d->m_pressedRect[7] = QRect(width - d->m_padding, height - d->m_padding, d->m_padding, d->m_padding);
    }
    else if (event->type() == QEvent::HoverMove)
    {
        //Set the corresponding mouse shape, this must be placed here and not below,
        //because it can be identified when the mouse is not down
        QHoverEvent *hoverEvent = (QHoverEvent *)event;
        QPoint point = hoverEvent->pos();
        if (d->m_resizeEnable)
        {
            if (d->m_pressedRect.at(0).contains(point))
            {
                this->setCursor(Qt::SizeHorCursor);
            }
            else if (d->m_pressedRect.at(1).contains(point))
            {
                this->setCursor(Qt::SizeHorCursor);
            }
            else if (d->m_pressedRect.at(2).contains(point))
            {
                this->setCursor(Qt::SizeVerCursor);
            }
            else if (d->m_pressedRect.at(3).contains(point))
            {
                this->setCursor(Qt::SizeVerCursor);
            }
            else if (d->m_pressedRect.at(4).contains(point))
            {
                this->setCursor(Qt::SizeFDiagCursor);
            }
            else if (d->m_pressedRect.at(5).contains(point))
            {
                this->setCursor(Qt::SizeBDiagCursor);
            }
            else if (d->m_pressedRect.at(6).contains(point))
            {
                this->setCursor(Qt::SizeBDiagCursor);
            }
            else if (d->m_pressedRect.at(7).contains(point))
            {
                this->setCursor(Qt::SizeFDiagCursor);
            }
            else
            {
                this->setCursor(Qt::ArrowCursor);
            }
        }

        //Calculate how much the XY axis has moved based on the current mouse position
        int offsetX = point.x() - d->m_mousePoint.x();
        int offsetY = point.y() - d->m_mousePoint.y();

        //Determine whether to move or stretch the control based on the position of the press
        if (d->m_moveEnable && d->m_mousePressed)
        {
            this->move(this->x() + offsetX, this->y() + offsetY);
        }

        if (d->m_resizeEnable)
        {
            int rectX = d->m_mouseRect.x();
            int rectY = d->m_mouseRect.y();
            int rectW = d->m_mouseRect.width();
            int rectH = d->m_mouseRect.height();

            if (d->m_pressedArea.at(0))
            {
                int resizeW = this->width() - offsetX;
                if (this->minimumWidth() <= resizeW)
                {
                    this->setGeometry(this->x() + offsetX, rectY, resizeW, rectH);
                }
            }
            else if (d->m_pressedArea.at(1))
            {
                this->setGeometry(rectX, rectY, rectW + offsetX, rectH);
            }
            else if (d->m_pressedArea.at(2))
            {
                int resizeH = this->height() - offsetY;
                if (this->minimumHeight() <= resizeH)
                {
                    this->setGeometry(rectX, this->y() + offsetY, rectW, resizeH);
                }
            }
            else if (d->m_pressedArea.at(3))
            {
                this->setGeometry(rectX, rectY, rectW, rectH + offsetY);
            }
            else if (d->m_pressedArea.at(4))
            {
                int resizeW = this->width() - offsetX;
                int resizeH = this->height() - offsetY;
                if (this->minimumWidth() <= resizeW)
                {
                    this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH)
                {
                    this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
                }
            }
            else if (d->m_pressedArea.at(5))
            {
                int resizeW = rectW + offsetX;
                int resizeH = this->height() - offsetY;
                if (this->minimumHeight() <= resizeH)
                {
                    this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
                }
            }
            else if (d->m_pressedArea.at(6))
            {
                int resizeW = this->width() - offsetX;
                int resizeH = rectH + offsetY;
                if (this->minimumWidth() <= resizeW)
                {
                    this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH)
                {
                    this->setGeometry(this->x(), this->y(), resizeW, resizeH);
                }
            }
            else if (d->m_pressedArea.at(7))
            {
                int resizeW = rectW + offsetX;
                int resizeH = rectH + offsetY;
                this->setGeometry(this->x(), this->y(), resizeW, resizeH);
            }
        }
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        //Remember the mouse-down coordinates + window area
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        d->m_mousePoint = mouseEvent->pos();
        d->m_mouseRect = this->geometry();

        //Determine the position of the region of the pressed handle
        if (d->m_pressedRect.at(0).contains(d->m_mousePoint))
        {
            d->m_pressedArea[0] = true;
        }
        else if (d->m_pressedRect.at(1).contains(d->m_mousePoint))
        {
            d->m_pressedArea[1] = true;
        }
        else if (d->m_pressedRect.at(2).contains(d->m_mousePoint))
        {
            d->m_pressedArea[2] = true;
        }
        else if (d->m_pressedRect.at(3).contains(d->m_mousePoint))
        {
            d->m_pressedArea[3] = true;
        }
        else if (d->m_pressedRect.at(4).contains(d->m_mousePoint))
        {
            d->m_pressedArea[4] = true;
        }
        else if (d->m_pressedRect.at(5).contains(d->m_mousePoint))
        {
            d->m_pressedArea[5] = true;
        }
        else if (d->m_pressedRect.at(6).contains(d->m_mousePoint))
        {
            d->m_pressedArea[6] = true;
        }
        else if (d->m_pressedRect.at(7).contains(d->m_mousePoint))
        {
            d->m_pressedArea[7] = true;
        }
        else
        {
            d->m_mousePressed = true;
        }
    }
    else if (event->type() == QEvent::MouseMove)
    {
        //Let's use HoverMove instead
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        //Restore all
        this->setCursor(Qt::ArrowCursor);
        d->m_mousePressed = false;
        for (int i = 0; i < 8; ++i)
        {
            d->m_pressedArea[i] = false;
        }
    }
#endif
}

bool QEXTFramelessMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QEXTFramelessMainWindow);
    if (watched == this)
    {
        if (event->type() == QEvent::WindowStateChange)
        {
            this->doWindowStateChange(event);
        }
        else
        {
            this->doResizeEvent(event);
        }
    }
    else if (watched == d->m_titleBar)
    {
        //Double - click the title bar to send a double - click signal to the home screen
        //*result = HTCAPTION; The flag bit is also automatically recognized by double-clicking the title bar
#ifndef Q_OS_WIN
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            emit titleDoubleClicked();
        }
        else if (event->type() == QEvent::NonClientAreaMouseButtonDblClick)
        {
            emit titleDoubleClicked();
        }
#endif
    }

    return QMainWindow::eventFilter(watched, event);
}

void QEXTFramelessMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_FrameWindow, &opt, &painter, this);
    QMainWindow::paintEvent(event);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool QEXTFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool QEXTFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
{
    Q_D(QEXTFramelessMainWindow);
    if (eventType == "windows_generic_MSG")
    {
#ifdef Q_OS_WIN
        MSG *msg = static_cast<MSG *>(message);
        //qDebug() << TIMEMS << "nativeEvent" << msg->wParam << msg->message;

        //Different message types and parameters are processed differently
        if (msg->message == WM_NCCALCSIZE)
        {
            *result = 0;
            return true;
        }
        else if (msg->message == WM_NCHITTEST)
        {
            //Compute the screen coordinates corresponding to the mouse
            long x = LOWORD(msg->lParam);
            long y = HIWORD(msg->lParam);
            QPoint pos = mapFromGlobal(QPoint(x, y));

            //Determine which area the current mouse position is in
            bool left = pos.x() < d->m_padding;
            bool right = pos.x() > width() - d->m_padding;
            bool top = pos.y() < d->m_padding;
            bool bottom = pos.y() > height() - d->m_padding;

            //Mouse moves to four corners. This message is sent when the mouse moves or a mouse button is pressed
            *result = 0;
            if (d->m_resizeEnable)
            {
                if (left && top)
                {
                    *result = HTTOPLEFT;
                }
                else if (left && bottom)
                {
                    *result = HTBOTTOMLEFT;
                }
                else if (right && top)
                {
                    *result = HTTOPRIGHT;
                }
                else if (right && bottom)
                {
                    *result = HTBOTTOMRIGHT;
                }
                else if (left)
                {
                    *result = HTLEFT;
                }
                else if (right)
                {
                    *result = HTRIGHT;
                }
                else if (top)
                {
                    *result = HTTOP;
                }
                else if (bottom)
                {
                    *result = HTBOTTOM;
                }
            }

            //Let's get rid of the stretching
            if (0 != *result)
            {
                return true;
            }

            //Identify the title bar drag to produce a half-screen full screen effect
            if (d->m_titleBar != 0 && d->m_titleBar->rect().contains(pos))
            {
                QWidget *child = d->m_titleBar->childAt(pos);
                if (!child)
                {
                    *result = HTCAPTION;
                    return true;
                }
            }
        }
        else if (msg->wParam == PBT_APMSUSPEND && msg->message == WM_POWERBROADCAST)
        {
            //Automatic minimization while the system is sleeping can avoid possible problems with the application
            this->showMinimized();
        }
        else if (msg->wParam == PBT_APMRESUMEAUTOMATIC)
        {
            //Sleep automatically opens when awakened
            this->showNormal();
        }
#endif
    }
    else if (eventType == "NSEvent")
    {
#ifdef Q_OS_MACOS
#endif
    }
    else if (eventType == "xcb_generic_event_t")
    {
#ifdef Q_OS_LINUX
#endif
    }
    return false;
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
bool QEXTFramelessMainWindow::winEvent(MSG *message, long *result)
{
    return this->nativeEvent("windows_generic_MSG", message, result);
}
#endif
#endif

void QEXTFramelessMainWindow::setPadding(int padding)
{
    Q_D(QEXTFramelessMainWindow);
    if (d->m_padding != padding)
    {
        d->m_padding = padding;
        this->update();
    }
}

void QEXTFramelessMainWindow::setMoveEnable(bool moveEnable)
{
    Q_D(QEXTFramelessMainWindow);
    if (d->m_moveEnable != moveEnable)
    {
        d->m_moveEnable = moveEnable;
        this->update();
    }
}

void QEXTFramelessMainWindow::setResizeEnable(bool resizeEnable)
{
    Q_D(QEXTFramelessMainWindow);
    if (d->m_resizeEnable != resizeEnable)
    {
        d->m_resizeEnable = resizeEnable;
        this->update();
    }
}

void QEXTFramelessMainWindow::setTitleBar(QWidget *titleBar)
{
    Q_D(QEXTFramelessMainWindow);
    if (d->m_titleBar.data() != titleBar)
    {
        d->m_titleBar = titleBar;
        d->m_titleBar->installEventFilter(this);
        this->update();
    }
}
