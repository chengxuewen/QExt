#ifndef _QEXTGOOGLEPINYIN
#define _QEXTGOOGLEPINYIN

#include <qextGooglePinYinGlobal.h>

#include <QObject>

class QTKGooglePinYinPrivate;
class QEXT_GOOGLEPINYIN_API QTKGooglePinYin : public QObject
{
    Q_OBJECT
public:
    explicit QTKGooglePinYin(QObject *parent = 0);
    ~QTKGooglePinYin();

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

private:
    QTKGooglePinYinPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QTKGooglePinYin)
    Q_DISABLE_COPY(QTKGooglePinYin)
};

#endif // _QEXTGOOGLEPINYIN
