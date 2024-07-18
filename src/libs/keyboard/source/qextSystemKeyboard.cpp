#include <qextSystemKeyboard.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QTextCodec>
#include <QApplication>

#ifdef QEXT_OS_WIN
#   include <Windows.h>
#   include <dwmapi.h>
#   include <tchar.h>

namespace detail
{
constexpr auto kKeyboardWindowClass = "IPTip_Main_Window";
constexpr auto kWindowParentClass = "ApplicationFrameWindow";
constexpr auto kWindowClass = "Windows.UI.Core.CoreWindow";
constexpr auto kWindowCaption = "Microsoft Text Input Application";
constexpr auto kTabTipPath = "C:\\Program Files\\Common Files\\Microsoft Shared\\ink\\TabTip.exe";
constexpr auto kTabletTipSubKey = "Software\\Microsoft\\TabletTip";
constexpr auto kTabletTipOption = "EnableDesktopModeAutoInvoke";

QString Utf8ToUnicode(const QByteArray &utf8)
{
    QTextCodec *utf8Codec = QTextCodec::codecForName("UTF-8");
    QString unicode = utf8Codec->toUnicode(utf8);
    return unicode;
}

QByteArray UnicodeToUtf8(const QString &unicode)
{
    QTextCodec *utf8Codec = QTextCodec::codecForName("UTF-8");
    QByteArray utf8 = utf8Codec->fromUnicode(unicode);
    return utf8;
}

bool OpenOskKeyboard()
{
    PVOID OldValue = NULL;
    //64位系统中32位程序要访问本机system32文件夹,需取消重定向到Syswow64
    BOOL bRet = Wow64DisableWow64FsRedirection(&OldValue);
    ShellExecuteW(NULL, L"open", L"osk.exe", NULL, NULL, SW_SHOWNORMAL);
    if (bRet)
    {
        Wow64RevertWow64FsRedirection(OldValue);
        return true;
    }
    else
    {
        qWarning() << "Wow64DisableWow64FsRedirection fail err code:" << GetLastError();
        return false;
    }
}

bool IsNewTabTipKeyboardVisable()
{
    //win10下父窗口是ApplicationFrameWindow子窗口是Windows.UI.Core.CoreWindow
    HWND parent = FindWindowExA(NULL, NULL, kWindowParentClass, NULL);
    if (!parent)
    {
        qWarning() << "no more windows, keyboard state is unknown. class:"
                   << UnicodeToUtf8(kWindowParentClass);
        return false;
    }

    HWND wnd = FindWindowExA(parent, NULL, kWindowClass, kWindowCaption);
    if (!wnd)
    {
        qWarning() << "it's a child of a WindowParentClass1709 window - the keyboard is open. class:"
                   << UnicodeToUtf8(kWindowClass)
                   << " caption"
                   << UnicodeToUtf8(kWindowCaption);
        return false;
    }

    //触摸键盘显示和隐藏不能用IsWindowVisible判断,判断方式可参考
    //https://stackoverflow.com/questions/32149880/how-to-identify-windows-10-background-store-processes-that-have-non-displayed-wi
    int cloaked = 0;
    if (DwmGetWindowAttribute(wnd, DWMWA_CLOAKED, &cloaked, DWM_CLOAKED_INHERITED) != S_OK)
    {
        qWarning() << "DwmGetWindowAttribute err:" << GetLastError();
        return false;
    }
    qWarning() << "DwmGetWindowAttribute cloaked=" << cloaked;
    return 0 == cloaked;
}


bool IsOldTabTipKeyboardVisable()
{
    HWND touchhWnd = FindWindowA(kKeyboardWindowClass, NULL);
    if (!touchhWnd)
    {
        qWarning() << "without window:" << UnicodeToUtf8(kKeyboardWindowClass);
        return false;
    }

    unsigned long style = GetWindowLong(touchhWnd, GWL_STYLE);
    // 由于有的系统在键盘不显示时候只是多返回一个WS_DISABLED这个字段。所以加一个它的判断
    qWarning() << "WS_CLIPSIBLINGS:" << (style & WS_CLIPSIBLINGS)
               << " WS_VISIBLE:" << (style & WS_VISIBLE)
               << " WS_POPUP:" << (style & WS_POPUP)
               << " WS_DISABLED:" << !(style & WS_DISABLED);
    return (style & WS_CLIPSIBLINGS) && (style & WS_VISIBLE) && (style & WS_POPUP) && !(style & WS_DISABLED);
}

bool OpenTabTipByProcess(const std::string &tabTipPath)
{
    //将进程TabTip.exe拉起，如果是进程存在的情况下，再次调用会直接显示键盘界面
    if (!ShellExecuteA(NULL, "open", tabTipPath.c_str(), NULL, NULL, SW_SHOWNORMAL))
    {
        qWarning() << "ShellExecuteW tabTip err:" << GetLastError();
        return false;
    }
    qWarning() << "ShellExecuteW tabTip success";
    return true;
}

// bool OpenScreenKeyboard()
// {
//     if (!IsTabTipAutoInvokeOnDesktopMode())
//     {
//         return OpenTabTip();
//     }


//     //触摸键盘有一设置项:不处于平板电脑模式且未连接键盘时显示触摸键盘，增加延迟避开系统调用键盘
//     std::thread([]() {
//         PublicUtils::Sleep(std::chrono::milliseconds(500));
//         OpenTabTip();
//     }).detach();
//     return true;
// }

bool OpenTabTip()
{
    // auto version = PublicUtils::Environment::OsVersion();
    // qWarning() << "os version:" << version.ToString();
    // if (IsNewTabTipKeyboardVisable() || IsOldTabTipKeyboardVisable())
    // {
    //     // qWarning() << "keyboard is visible";
    //     return true;
    // }
    //系统版本大于等于win10 10.0.14393.0，需要使用com组件的接口才能将键盘界面显示出来
    // if (10 == version.GetMajor() && version.GetPatch() >= 14393)
    // {
    //     return OpenTabTipByCom(kTabTipPath);
    // }
    // else
    // {
        return OpenTabTipByProcess(kTabTipPath);
    // }
}
} // namespace detail
#endif

class QExtSystemKeyboardPrivate
{
public:
    explicit QExtSystemKeyboardPrivate(QExtSystemKeyboard *q);
    virtual ~QExtSystemKeyboardPrivate();

    QExtSystemKeyboard * const q_ptr;

private:
    QEXT_DECL_PUBLIC(QExtSystemKeyboard)
    QEXT_DISABLE_COPY_MOVE(QExtSystemKeyboardPrivate)
};

QExtSystemKeyboardPrivate::QExtSystemKeyboardPrivate(QExtSystemKeyboard *q)
    : q_ptr(q)
{
}

QExtSystemKeyboardPrivate::~QExtSystemKeyboardPrivate()
{
}

QExtSystemKeyboard *QExtSystemKeyboard::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtSystemKeyboard *instance = QEXT_NULLPTR;
    if (onceFlag.enter())
    {
        instance = new QExtSystemKeyboard;
        onceFlag.leave();
    }
    return instance;
}

QExtSystemKeyboard::~QExtSystemKeyboard()
{
}

void QExtSystemKeyboard::hideKeyboard()
{

}

void QExtSystemKeyboard::showKeyboard()
{
#ifdef QEXT_OS_WIN
    detail::OpenTabTip();
#else
    QInputMethod *inputMethod = QApplication::inputMethod();
    if (inputMethod)
    {
        inputMethod->show();
    }
#endif
}

QExtSystemKeyboard::QExtSystemKeyboard(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtSystemKeyboardPrivate(this))
{
}
