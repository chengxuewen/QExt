#include <qextGooglePinYin.h>

#include "googlepinyin/pinyinime.h"
#include "googlepinyin/userdict.h"

#include <QCoreApplication>
#include <QDebug>

using namespace ime_pinyin;

static size_t fix_cand_len(size_t cand, int maxOutputLen)
{
    size_t i;
    size_t decode_len;
    size_t single = 0;
    size_t multi = 0;
    char16 *cand_buf = new char16[maxOutputLen];

    im_get_sps_str(&decode_len);
    if (decode_len == 1) {
        if (cand > 10) {
            cand = 10;
        }

        delete[] cand_buf;
        return cand;
    }

    for (i = 0; i < cand; i++) {
        im_get_candidate(i, cand_buf, maxOutputLen);
        if (strlen((char *)cand_buf) > 2) {
            multi++;
        } else {
            single++;
            if (single > 40) {
                break;
            }
        }
    }

    cand = multi + single;
    delete[] cand_buf;
    return cand;
}

class QTKGooglePinYinPrivate
{
public:
    QTKGooglePinYinPrivate();
    ~QTKGooglePinYinPrivate();

private:
    QTKGooglePinYin *q_ptr;
    Q_DECLARE_PUBLIC(QTKGooglePinYin)


    bool m_bOk;                 //If there is something wrong
    int m_iMaxInputLength;      //Maximum input length
    int m_iMaxOutputLength;     //Maximum output length
};

QTKGooglePinYinPrivate::QTKGooglePinYinPrivate()
{
    m_bOk = false;
    m_iMaxInputLength = 26;
    m_iMaxOutputLength = 26;
}

QTKGooglePinYinPrivate::~QTKGooglePinYinPrivate()
{

}

QTKGooglePinYin::QTKGooglePinYin(QObject *parent) : QObject(parent)
{
    d_ptr = new QTKGooglePinYinPrivate();
    d_ptr->q_ptr = this;
}

QTKGooglePinYin::~QTKGooglePinYin()
{
    delete d_ptr;
}

bool QTKGooglePinYin::open(const QString &strDBPath)
{
    //Load the input font file
    //    QString pyPath = QString("%1/dict_pinyin.dat").arg(dbPath);
    //    QString pyUserPath = QString("%1/dict_pinyin_user.dat").arg(dbPath);
    Q_UNUSED(strDBPath);
    Q_INIT_RESOURCE(QEXTGooglePinYin);
    QString strPYPath = QString(":/QEXTGooglePinYin/dat/dict_pinyin.dat");
    QString strPYUserPath = QString(":/QEXTGooglePinYin/dat/dict_pinyin_user.dat");
    d_ptr->m_bOk = im_open_decoder(strPYPath.toUtf8().constData(), strPYUserPath.toUtf8().constData());

    //Load the custom dictionary file
    if (!im_is_user_dictionary_enabled()) {
        im_init_user_dictionary(strPYUserPath.toUtf8().constData());
    }

    if (d_ptr->m_bOk) {
        im_set_max_lens(d_ptr->m_iMaxInputLength, d_ptr->m_iMaxOutputLength);
        im_reset_search();
    } else {
        qCritical() << "load GooglePinYin error";
    }

    return d_ptr->m_bOk;
}

void QTKGooglePinYin::close()
{
    im_close_decoder();
}

void QTKGooglePinYin::cancel()
{
    im_flush_cache();
}

void QTKGooglePinYin::flush()
{
    im_flush_cache();
}

void QTKGooglePinYin::reset()
{
    im_reset_search();
}

int QTKGooglePinYin::select(const QString &strPinyin)
{
    //Maximum support is 26 letters
    if (!d_ptr->m_bOk || strPinyin.length() > 26) {
        return 0;
    }

    //Find the largest index of Chinese characters corresponding to the current pinyin
    QByteArray bytearray = strPinyin.toUtf8();
    char *pPy = bytearray.data();
    size_t count = im_search(pPy, bytearray.size());
    count = fix_cand_len(count, d_ptr->m_iMaxOutputLength);
    return count;
}

QString QTKGooglePinYin::getChinese(const int &iIndex)
{
    char16 *pCand_buf = new char16[d_ptr->m_iMaxOutputLength];
    char16 *pCand;
    QString strCand;

    pCand = im_get_candidate(iIndex, pCand_buf, d_ptr->m_iMaxOutputLength);
    if (pCand) {
        strCand = QString::fromUtf16(pCand);
        if (iIndex == 0) {
            strCand.remove(0, im_get_fixed_len());
        }
    } else {
        strCand = "";
    }

    delete[] pCand_buf;
    return strCand;
}

int QTKGooglePinYin::deleteSelect(const int &iPos)
{
    if (!d_ptr->m_bOk) {
        return 0;
    }

    size_t count = im_delsearch(iPos, false, false);
    count = fix_cand_len(count, d_ptr->m_iMaxOutputLength);
    return count;
}

int QTKGooglePinYin::getPosition()
{
    const uint16 *pStartPos;
    size_t pos_len;
    size_t fixed_len = im_get_fixed_len();

    pos_len = im_get_spl_start_pos(pStartPos);
    if (fixed_len <= pos_len) {
        return (pStartPos[fixed_len]);
    }

    return  0;
}

#include <moc_qextGooglePinYin.cpp>
