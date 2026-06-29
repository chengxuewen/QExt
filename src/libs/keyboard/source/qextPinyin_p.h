#ifndef _QEXTPINYIN_P_H
#define _QEXTPINYIN_P_H

#include "qextPinyin.h"

class QEXT_KEYBOARD_API QExtPinyinPrivate
{
public:
    explicit QExtPinyinPrivate(QExtPinyin *q);
    virtual ~QExtPinyinPrivate();

    QExtPinyin *q_ptr;

    bool mOk;                 //If there is something wrong
    int mMaxInputLength;      //Maximum input length
    int mMaxOutputLength;     //Maximum output length

private:
    QEXT_DECLARE_PUBLIC(QExtPinyin)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPinyinPrivate)
};

#endif // _QEXTPINYIN_P_H
