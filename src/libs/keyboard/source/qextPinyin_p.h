#ifndef _QEXTPINYIN_P_H
#define _QEXTPINYIN_P_H

#include "qextPinyin.h"

class QEXT_KEYBOARD_API QExtPinyinPrivate
{
public:
    explicit QExtPinyinPrivate(QExtPinyin *q);
    virtual ~QExtPinyinPrivate();

    QExtPinyin *q_ptr;

    bool m_bOk;                 //If there is something wrong
    int m_iMaxInputLength;      //Maximum input length
    int m_iMaxOutputLength;     //Maximum output length

private:
    QEXT_DECLARE_PUBLIC(QExtPinyin)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPinyinPrivate)
};

#endif // _QEXTPINYIN_P_H
