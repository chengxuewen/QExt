#include <private/qextPinyin_p.h>

#include "pinyinime/pinyinime.h"
//#include "pinyinime/userdict.h"

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
    if (decode_len == 1)
    {
        if (cand > 10)
        {
            cand = 10;
        }

        delete[] cand_buf;
        return cand;
    }

    for (i = 0; i < cand; i++)
    {
        im_get_candidate(i, cand_buf, maxOutputLen);
        if (strlen((char *)cand_buf) > 2)
        {
            multi++;
        }
        else
        {
            single++;
            if (single > 40)
            {
                break;
            }
        }
    }

    cand = multi + single;
    delete[] cand_buf;
    return cand;
}


QExtPinyinPrivate::QExtPinyinPrivate(QExtPinyin *q)
    : q_ptr(q)
{
    m_bOk = false;
    m_iMaxInputLength = 26;
    m_iMaxOutputLength = 26;
}

QExtPinyinPrivate::~QExtPinyinPrivate()
{

}

QExtPinyin::QExtPinyin(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtPinyinPrivate(this))
{

}

QExtPinyin::~QExtPinyin()
{
    delete dd_ptr;
}

bool QExtPinyin::open(const QString &strDBPath)
{
    //Load the input font file
    //    QString pyPath = QString("%1/dict_pinyin.dat").arg(dbPath);
    //    QString pyUserPath = QString("%1/dict_pinyin_user.dat").arg(dbPath);
    Q_UNUSED(strDBPath);
    Q_INIT_RESOURCE(qextPinyin);
    QString strPYPath = QString(":/QExtPinyin/dat/dict_pinyin.dat");
    QString strPYUserPath = QString(":/QExtPinyin/dat/dict_pinyin_user.dat");
    dd_ptr->m_bOk = im_open_decoder(strPYPath.toUtf8().constData(), strPYUserPath.toUtf8().constData());

    //Load the custom dictionary file
    if (!im_is_user_dictionary_enabled())
    {
        im_init_user_dictionary(strPYUserPath.toUtf8().constData());
    }

    if (dd_ptr->m_bOk)
    {
        im_set_max_lens(dd_ptr->m_iMaxInputLength, dd_ptr->m_iMaxOutputLength);
        im_reset_search();
    }
    else
    {
        qCritical() << "load GooglePinYin error";
    }

    return dd_ptr->m_bOk;
}

void QExtPinyin::close()
{
    im_close_decoder();
}

void QExtPinyin::cancel()
{
    im_flush_cache();
}

void QExtPinyin::flush()
{
    im_flush_cache();
}

void QExtPinyin::reset()
{
    im_reset_search();
}

int QExtPinyin::select(const QString &strPinyin)
{
    //Maximum support is 26 letters
    if (!dd_ptr->m_bOk || strPinyin.length() > 26)
    {
        return 0;
    }

    //Find the largest index of Chinese characters corresponding to the current pinyin
    QByteArray bytearray = strPinyin.toUtf8();
    char *pPy = bytearray.data();
    size_t count = im_search(pPy, bytearray.size());
    count = fix_cand_len(count, dd_ptr->m_iMaxOutputLength);
    return count;
}

QString QExtPinyin::getChinese(const int &iIndex)
{
    char16 *pCand_buf = new char16[dd_ptr->m_iMaxOutputLength];
    char16 *pCand;
    QString strCand;

    pCand = im_get_candidate(iIndex, pCand_buf, dd_ptr->m_iMaxOutputLength);
    if (pCand)
    {
        strCand = QString::fromUtf16(pCand);
        if (iIndex == 0)
        {
            strCand.remove(0, im_get_fixed_len());
        }
    }
    else
    {
        strCand = "";
    }

    delete[] pCand_buf;
    return strCand;
}

int QExtPinyin::deleteSelect(const int &iPos)
{
    if (!dd_ptr->m_bOk)
    {
        return 0;
    }

    size_t count = im_delsearch(iPos, false, false);
    count = fix_cand_len(count, dd_ptr->m_iMaxOutputLength);
    return count;
}

int QExtPinyin::getPosition()
{
    const uint16 *pStartPos;
    size_t pos_len;
    size_t fixed_len = im_get_fixed_len();

    pos_len = im_get_spl_start_pos(pStartPos);
    if (fixed_len <= pos_len)
    {
        return (pStartPos[fixed_len]);
    }

    return  0;
}
