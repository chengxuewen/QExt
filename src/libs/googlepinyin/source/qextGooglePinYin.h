#ifndef _QEXTGOOGLEPINYIN_H
#define _QEXTGOOGLEPINYIN_H

#include "qextGooglePinYinGlobal.h"

#include <QObject>

class QExtGooglePinYinPrivate;
class QEXT_GOOGLEPINYIN_API QExtGooglePinYin : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtGooglePinYin)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtGooglePinYin)
public:
    explicit QExtGooglePinYin(QObject *parent = 0);
    ~QExtGooglePinYin();

public slots:
    //Open the input method core
    bool open(const QString &strDBPath);
    //Close the input method core
    void close();
    //Cancel the input
    void cancel();
    //Clear the cache
    void flush();
    //Reset the search
    void reset();

    //Find the Chinese characters corresponding to pinyin, return the number
    int select(const QString &strPinyin);
    //Gets the character for the specified index
    QString getChinese(const int &iIndex);

    //Delete the Chinese characters
    int deleteSelect(const int &iPos);
    //Current lookup position
    int getPosition();

protected:
    QExtGooglePinYinPrivate *dd_ptr;
};

#endif // _QEXTGOOGLEPINYIN_H
