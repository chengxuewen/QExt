#include <qextVLCError.h>

#include <vlc/vlc.h>

#include <QtCore/QDebug>

QString QEXTVLCError::errmsg()
{
    QString error;
    if (libvlc_errmsg())
    {
        error = QString::fromUtf8(libvlc_errmsg());
        libvlc_clearerr();
    }

    return error;
}

void QEXTVLCError::showErrMsg()
{
    // Outputs libvlc error message if there is any
    QString error = errmsg();
    if (!error.isEmpty())
    {
        qWarning() << "libvlc" << "Error:" << error;
    }
}

void QEXTVLCError::clearerr()
{

}
