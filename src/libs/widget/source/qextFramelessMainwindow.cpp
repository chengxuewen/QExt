#pragma execution_character_set("utf-8")

#include <qextFramelessMainwindow.h>
#include <qextFramelessMainwindow_p.h>

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

    for (int i = 0; i < 8; ++i) {
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
    : QMainWindow(parent), d_ptr(new QEXTFramelessMainWindowPrivate(this))
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    d->m_flags = this->windowFlags();

    //设置背景透明 官方在5.3以后才彻底修复 WA_TranslucentBackground+FramelessWindowHint 并存不绘制的BUG
#if (QT_VERSION >= QT_VERSION_CHECK(5,3,0))
    this->setAttribute(Qt::WA_TranslucentBackground);
#endif
    //设置无边框属性
    this->setWindowFlags(d->m_flags | Qt::FramelessWindowHint);
    //安装事件过滤器识别拖动
    this->installEventFilter(this);

    //设置属性产生win窗体效果,移动到边缘半屏或者最大化等
    //设置以后会产生标题栏,需要在下面拦截消息WM_NCCALCSIZE重新去掉
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
    //解决有时候窗体重新显示的时候假死不刷新的BUG
    this->setAttribute(Qt::WA_Mapped);
    QMainWindow::showEvent(event);
}

void QEXTFramelessMainWindow::doWindowStateChange(QEvent *event)
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    //非最大化才能移动和拖动大小
    if (this->windowState() == Qt::WindowNoState) {
        d->m_moveEnable = true;
        d->m_resizeEnable = true;
    } else {
        d->m_moveEnable = false;
        d->m_resizeEnable = false;
    }

    //发出最大化最小化等改变事件,以便界面上更改对应的信息比如右上角图标和文字
    emit this->windowStateChanged(!d->m_moveEnable);

    //解决mac系统上无边框最小化失效的BUG
#ifdef Q_OS_MACOS
    if (this->windowState() & Qt::WindowMinimized) {
        d->m_isMin = true;
    } else {
        if (d->m_isMin) {
            //设置无边框属性
            this->setWindowFlags(d->m_flags | Qt::FramelessWindowHint);
            this->setVisible(true);
            d->m_isMin = false;
        }
    }
#endif
}

void QEXTFramelessMainWindow::doResizeEvent(QEvent *event)
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    //非win系统的无边框拉伸,win系统上已经采用了nativeEvent来处理拉伸
    //为何不统一用计算的方式因为在win上用这个方式往左拉伸会发抖妹的
#ifndef Q_OS_WIN
    if (event->type() == QEvent::Resize) {
        //重新计算八个描点的区域,描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
        int width = this->width();
        int height = this->height();

        //左侧描点区域
        d->m_pressedRect[0] = QRect(0, d->m_padding, d->m_padding, height - d->m_padding * 2);
        //右侧描点区域
        d->m_pressedRect[1] = QRect(width - d->m_padding, d->m_padding, d->m_padding, height - d->m_padding * 2);
        //上侧描点区域
        d->m_pressedRect[2] = QRect(d->m_padding, 0, width - d->m_padding * 2, d->m_padding);
        //下侧描点区域
        d->m_pressedRect[3] = QRect(d->m_padding, height - d->m_padding, width - d->m_padding * 2, d->m_padding);

        //左上角描点区域
        d->m_pressedRect[4] = QRect(0, 0, d->m_padding, d->m_padding);
        //右上角描点区域
        d->m_pressedRect[5] = QRect(width - d->m_padding, 0, d->m_padding, d->m_padding);
        //左下角描点区域
        d->m_pressedRect[6] = QRect(0, height - d->m_padding, d->m_padding, d->m_padding);
        //右下角描点区域
        d->m_pressedRect[7] = QRect(width - d->m_padding, height - d->m_padding, d->m_padding, d->m_padding);
    } else if (event->type() == QEvent::HoverMove) {
        //设置对应鼠标形状,这个必须放在这里而不是下面,因为可以在鼠标没有按下的时候识别
        QHoverEvent *hoverEvent = (QHoverEvent *)event;
        QPoint point = hoverEvent->pos();
        if (d->m_resizeEnable) {
            if (d->m_pressedRect.at(0).contains(point)) {
                this->setCursor(Qt::SizeHorCursor);
            } else if (d->m_pressedRect.at(1).contains(point)) {
                this->setCursor(Qt::SizeHorCursor);
            } else if (d->m_pressedRect.at(2).contains(point)) {
                this->setCursor(Qt::SizeVerCursor);
            } else if (d->m_pressedRect.at(3).contains(point)) {
                this->setCursor(Qt::SizeVerCursor);
            } else if (d->m_pressedRect.at(4).contains(point)) {
                this->setCursor(Qt::SizeFDiagCursor);
            } else if (d->m_pressedRect.at(5).contains(point)) {
                this->setCursor(Qt::SizeBDiagCursor);
            } else if (d->m_pressedRect.at(6).contains(point)) {
                this->setCursor(Qt::SizeBDiagCursor);
            } else if (d->m_pressedRect.at(7).contains(point)) {
                this->setCursor(Qt::SizeFDiagCursor);
            } else {
                this->setCursor(Qt::ArrowCursor);
            }
        }

        //根据当前鼠标位置,计算XY轴移动了多少
        int offsetX = point.x() - d->m_mousePoint.x();
        int offsetY = point.y() - d->m_mousePoint.y();

        //根据按下处的位置判断是否是移动控件还是拉伸控件
        if (d->m_moveEnable && d->m_mousePressed) {
            this->move(this->x() + offsetX, this->y() + offsetY);
        }

        if (d->m_resizeEnable) {
            int rectX = d->m_mouseRect.x();
            int rectY = d->m_mouseRect.y();
            int rectW = d->m_mouseRect.width();
            int rectH = d->m_mouseRect.height();

            if (d->m_pressedArea.at(0)) {
                int resizeW = this->width() - offsetX;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + offsetX, rectY, resizeW, rectH);
                }
            } else if (d->m_pressedArea.at(1)) {
                this->setGeometry(rectX, rectY, rectW + offsetX, rectH);
            } else if (d->m_pressedArea.at(2)) {
                int resizeH = this->height() - offsetY;
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(rectX, this->y() + offsetY, rectW, resizeH);
                }
            } else if (d->m_pressedArea.at(3)) {
                this->setGeometry(rectX, rectY, rectW, rectH + offsetY);
            } else if (d->m_pressedArea.at(4)) {
                int resizeW = this->width() - offsetX;
                int resizeH = this->height() - offsetY;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
                }
            } else if (d->m_pressedArea.at(5)) {
                int resizeW = rectW + offsetX;
                int resizeH = this->height() - offsetY;
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
                }
            } else if (d->m_pressedArea.at(6)) {
                int resizeW = this->width() - offsetX;
                int resizeH = rectH + offsetY;
                if (this->minimumWidth() <= resizeW) {
                    this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
                }
                if (this->minimumHeight() <= resizeH) {
                    this->setGeometry(this->x(), this->y(), resizeW, resizeH);
                }
            } else if (d->m_pressedArea.at(7)) {
                int resizeW = rectW + offsetX;
                int resizeH = rectH + offsetY;
                this->setGeometry(this->x(), this->y(), resizeW, resizeH);
            }
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        //记住鼠标按下的坐标+窗体区域
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        d->m_mousePoint = mouseEvent->pos();
        d->m_mouseRect = this->geometry();

        //判断按下的手柄的区域位置
        if (d->m_pressedRect.at(0).contains(d->m_mousePoint)) {
            d->m_pressedArea[0] = true;
        } else if (d->m_pressedRect.at(1).contains(d->m_mousePoint)) {
            d->m_pressedArea[1] = true;
        } else if (d->m_pressedRect.at(2).contains(d->m_mousePoint)) {
            d->m_pressedArea[2] = true;
        } else if (d->m_pressedRect.at(3).contains(d->m_mousePoint)) {
            d->m_pressedArea[3] = true;
        } else if (d->m_pressedRect.at(4).contains(d->m_mousePoint)) {
            d->m_pressedArea[4] = true;
        } else if (d->m_pressedRect.at(5).contains(d->m_mousePoint)) {
            d->m_pressedArea[5] = true;
        } else if (d->m_pressedRect.at(6).contains(d->m_mousePoint)) {
            d->m_pressedArea[6] = true;
        } else if (d->m_pressedRect.at(7).contains(d->m_mousePoint)) {
            d->m_pressedArea[7] = true;
        } else {
            d->m_mousePressed = true;
        }
    } else if (event->type() == QEvent::MouseMove) {
        //改成用HoverMove识别
    } else if (event->type() == QEvent::MouseButtonRelease) {
        //恢复所有
        this->setCursor(Qt::ArrowCursor);
        d->m_mousePressed = false;
        for (int i = 0; i < 8; ++i) {
            d->m_pressedArea[i] = false;
        }
    }
#endif
}

bool QEXTFramelessMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    if (watched == this) {
        if (event->type() == QEvent::WindowStateChange) {
            this->doWindowStateChange(event);
        } else {
            this->doResizeEvent(event);
        }
    } else if (watched == d->m_titleBar) {
        //双击标题栏发出双击信号给主界面
        //下面的 *result = HTCAPTION; 标志位也会自动识别双击标题栏
#ifndef Q_OS_WIN
        if (event->type() == QEvent::MouseButtonDblClick) {
            emit titleDoubleClicked();
        } else if (event->type() == QEvent::NonClientAreaMouseButtonDblClick) {
            emit titleDoubleClicked();
        }
#endif
    }

    return QMainWindow::eventFilter(watched, event);
}

void QEXTFramelessMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    QPainter painter(this);
//    QStyleOption opt;
//    opt.init(this);
//    this->style()->drawPrimitive(QStyle::PE_FrameWindow, &opt, &painter, this);
    QMainWindow::paintEvent(event);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool QEXTFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool QEXTFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    if (eventType == "windows_generic_MSG") {
#ifdef Q_OS_WIN
        MSG *msg = static_cast<MSG *>(message);
        //qDebug() << TIMEMS << "nativeEvent" << msg->wParam << msg->message;

        //不同的消息类型和参数进行不同的处理
        if (msg->message == WM_NCCALCSIZE) {
            *result = 0;
            return true;
        } else if (msg->message == WM_NCHITTEST) {
            //计算鼠标对应的屏幕坐标
            long x = LOWORD(msg->lParam);
            long y = HIWORD(msg->lParam);
            QPoint pos = mapFromGlobal(QPoint(x, y));

            //判断当前鼠标位置在哪个区域
            bool left = pos.x() < d->m_padding;
            bool right = pos.x() > width() - d->m_padding;
            bool top = pos.y() < d->m_padding;
            bool bottom = pos.y() > height() - d->m_padding;

            //鼠标移动到四个角,这个消息是当鼠标移动或者有鼠标键按下时候发出的
            *result = 0;
            if (resizeEnable) {
                if (left && top) {
                    *result = HTTOPLEFT;
                } else if (left && bottom) {
                    *result = HTBOTTOMLEFT;
                } else if (right && top) {
                    *result = HTTOPRIGHT;
                } else if (right && bottom) {
                    *result = HTBOTTOMRIGHT;
                } else if (left) {
                    *result = HTLEFT;
                } else if (right) {
                    *result = HTRIGHT;
                } else if (top) {
                    *result = HTTOP;
                } else if (bottom) {
                    *result = HTBOTTOM;
                }
            }

            //先处理掉拉伸
            if (0 != *result) {
                return true;
            }

            //识别标题栏拖动产生半屏全屏效果
            if (titleBar != 0 && titleBar->rect().contains(pos)) {
                QWidget *child = titleBar->childAt(pos);
                if (!child) {
                    *result = HTCAPTION;
                    return true;
                }
            }
        } else if (msg->wParam == PBT_APMSUSPEND && msg->message == WM_POWERBROADCAST) {
            //系统休眠的时候自动最小化可以规避程序可能出现的问题
            this->showMinimized();
        } else if (msg->wParam == PBT_APMRESUMEAUTOMATIC) {
            //休眠唤醒后自动打开
            this->showNormal();
        }
#endif
    } else if (eventType == "NSEvent") {
#ifdef Q_OS_MACOS
#endif
    } else if (eventType == "xcb_generic_event_t") {
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
    QEXT_DECL_D(QEXTFramelessMainWindow);
    if (d->m_padding != padding)
    {
        d->m_padding = padding;
        this->update();
    }
}

void QEXTFramelessMainWindow::setMoveEnable(bool moveEnable)
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    if (d->m_moveEnable != moveEnable)
    {
        d->m_moveEnable = moveEnable;
        this->update();
    }
}

void QEXTFramelessMainWindow::setResizeEnable(bool resizeEnable)
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    if (d->m_resizeEnable != resizeEnable)
    {
        d->m_resizeEnable = resizeEnable;
        this->update();
    }
}

void QEXTFramelessMainWindow::setTitleBar(QWidget *titleBar)
{
    QEXT_DECL_D(QEXTFramelessMainWindow);
    if (d->m_titleBar.data() != titleBar)
    {
        d->m_titleBar = titleBar;
        d->m_titleBar->installEventFilter(this);
        this->update();
    }
}
