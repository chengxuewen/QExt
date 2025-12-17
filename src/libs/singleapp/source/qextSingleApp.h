#ifndef _QEXTSINGLEAPP_H
#define _QEXTSINGLEAPP_H

#include <qextSingleAppGlobal.h>

#include <QObject>

class QExtSingleAppPrivate;
class QEXT_SINGLEAPP_API QExtSingleApp : public QObject
{
    Q_OBJECT
public:
    QExtSingleApp(int &argc, char *argv[]);
    ~QExtSingleApp() QEXT_OVERRIDE;

    /**
     * @brief Sends a message to the primary instance
     * @param message data to send
     * @returns `true` on success
     * @note sendMessage() will return false if invoked from the primary instance
     */
    bool sendMessage(const QByteArray &message);

Q_SIGNALS:
    /**
     * @brief Triggered whenever a new instance had been started,
     * except for secondary instances if the `Mode::SecondaryNotification` flag is not specified
     */
    void instanceStarted();

    /**
     * @brief Triggered whenever there is a message received from a secondary instance
     */
    void receivedMessage(quint32 instanceId, QByteArray message);

protected:
    QScopedPointer<QExtSingleAppPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtSingleApp)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtSingleApp)
};

#endif //_QEXTSINGLEAPP_H
