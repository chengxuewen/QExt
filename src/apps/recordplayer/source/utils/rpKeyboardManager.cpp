#include <rpKeyboardManager.h>
#include <rpConstants.h>

#include <qextVirtualKeyboard.h>
#include <qextOnceFlag.h>

#include <QApplication>

#define VIRTUAL_SOFT_KEYBOARD_ENABLE 1

class RPKeyboardManagerPrivate
{
public:
    explicit RPKeyboardManagerPrivate(RPKeyboardManager *q);
    virtual ~RPKeyboardManagerPrivate();

    RPKeyboardManager * const q_ptr;

    bool m_virtualSoftKeyboardEnable;

private:
    Q_DECLARE_PUBLIC(RPKeyboardManager)
    Q_DISABLE_COPY(RPKeyboardManagerPrivate)
};

RPKeyboardManagerPrivate::RPKeyboardManagerPrivate(RPKeyboardManager *q)
    : q_ptr(q)
    , m_virtualSoftKeyboardEnable(false)
{
}

RPKeyboardManagerPrivate::~RPKeyboardManagerPrivate()
{

}

RPKeyboardManager::~RPKeyboardManager()
{

}

bool RPKeyboardManager::isVirtualSoftKeyboardEnable() const
{
    Q_D(const RPKeyboardManager);
    return d->m_virtualSoftKeyboardEnable;
}

void RPKeyboardManager::setVirtualSoftKeyboardEnable(bool enable)
{
    Q_D(RPKeyboardManager);
    if (enable != d->m_virtualSoftKeyboardEnable)
    {
        d->m_virtualSoftKeyboardEnable = enable;
        emit this->virtualSoftKeyboardEnableChanged(enable);
#if VIRTUAL_SOFT_KEYBOARD_ENABLE
        QExtVirtualKeyboard::instance()->setEnabled(enable);
#endif
    }
}

void RPKeyboardManager::loadSettings(QSettings *settings)
{
    settings->beginGroup(RPConstants::SETTINGS_GROUP_KEYBOARDS);
    const auto enabled = settings->value(RPConstants::SETTINGS_KEY_KEYBOARD_ENABLE, false).toBool();
    this->setVirtualSoftKeyboardEnable(enabled);
    settings->endGroup();
}

void RPKeyboardManager::saveSettings(QSettings *settings)
{
    Q_D(RPKeyboardManager);
    settings->beginGroup(RPConstants::SETTINGS_GROUP_KEYBOARDS);
    settings->setValue(RPConstants::SETTINGS_KEY_KEYBOARD_ENABLE, d->m_virtualSoftKeyboardEnable);
    settings->endGroup();
}

RPKeyboardManager::RPKeyboardManager(QObject *parent)
    : QObject(parent)
    , dd_ptr(new RPKeyboardManagerPrivate(this))
{
#if VIRTUAL_SOFT_KEYBOARD_ENABLE
    auto fontInfo = QExtVirtualKeyboard::instance()->fontInfo();
    QExtVirtualKeyboard::instance()->setFontInfo(fontInfo.family(), 32, 16);
    QExtVirtualKeyboard::instance()->setFixedSize(800, 400);
    QExtVirtualKeyboard::instance()->setIconSize(26, 26);
    QExtVirtualKeyboard::instance()->setTopHeight(60);
    QExtVirtualKeyboard::instance()->setPopUpType(QExtVirtualKeyboard::PopUp_Control);
    QExtVirtualKeyboard::instance()->setStyleType(QExtVirtualKeyboard::Style_Black);
    QExtVirtualKeyboard::instance()->setEnabled(dd_ptr->m_virtualSoftKeyboardEnable);
#endif
}
