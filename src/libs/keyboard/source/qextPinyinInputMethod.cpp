#include <qextPinyinInputMethod.h>
#include <private/qextPinyinDecoderService_p.h>
#include <private/qextKeyboardInputContext_p.h>

#include <QDebug>
#include <QVector>
#include <QPointer>

class QExtPinyinInputMethodPrivate
{
public:
    enum State
    {
        Idle,
        Input,
        Predict
    };

    explicit QExtPinyinInputMethodPrivate(QExtPinyinInputMethod *q_ptr);
    virtual ~QExtPinyinInputMethodPrivate() {}

    void resetToIdleState();

    bool addSpellingChar(QChar ch, bool reset);
    bool removeSpellingChar();

    void chooseAndUpdate(int candId);
    bool chooseAndFinish();

    int candidatesCount();
    QString candidateAt(int index);

    void chooseDecodingCandidate(int candId);
    void choosePredictChoice(int choiceId);

    QString getComposingStrActivePart();

    void resetCandidates();
    void updateCandidateList();

    bool canDoPrediction();
    void tryPredict();

    QExtPinyinInputMethod * const q_ptr;

    State mState;
    int mFixedLen;
    int mPosDelSpl;
    int mActiveCmpsLen;
    int mTotalChoicesNum;
    bool mIsPosInSpl;
    bool mFinishSelection;
    QString mSurface;
    QString mComposingStr;
    QList<QString> mCandidatesList;
    QExtKeyboardInputContext *mInputContext;
    QExtPinyinInputMethod::InputMode mInputMode;
    QPointer<QExtPinyinDecoderService> mPinyinDecoderService;

private:
    QEXT_DECLARE_PUBLIC(QExtPinyinInputMethod)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPinyinInputMethodPrivate)
};

class ScopedCandidateListUpdate
{
public:
    inline explicit ScopedCandidateListUpdate(QExtPinyinInputMethodPrivate *d)
        : d(d)
        , mTotalChoicesNum(d->mTotalChoicesNum)
        , mCandidatesList(d->mCandidatesList)
        , mState(d->mState)
    {
    }

    inline ~ScopedCandidateListUpdate()
    {
        if (mTotalChoicesNum != d->mTotalChoicesNum || mState != d->mState || mCandidatesList != d->mCandidatesList)
        {
            QList<QString> candidateList;
            for(int i = 0;i < d->mTotalChoicesNum;++i)
            {
                candidateList.append(d->candidateAt(i));
            }
            d->updateCandidateList();
        }
    }

private:
    Q_DISABLE_COPY(ScopedCandidateListUpdate)
    QExtPinyinInputMethodPrivate *d;
    int mTotalChoicesNum;
    QList<QString> mCandidatesList;
    QExtPinyinInputMethodPrivate::State mState;
};


QExtPinyinInputMethodPrivate::QExtPinyinInputMethodPrivate(QExtPinyinInputMethod *q_ptr)
    : q_ptr(q_ptr)
    , mState(Idle)
    , mFixedLen(0)
    , mPosDelSpl(-1)
    , mActiveCmpsLen(0)
    , mTotalChoicesNum(0)
    , mIsPosInSpl(false)
    , mFinishSelection(true)
    , mSurface()
    , mComposingStr()
    , mCandidatesList()
    , mInputContext(QEXT_NULLPTR)
    , mInputMode(QExtPinyinInputMethod::InputMode::Latin)
    , mPinyinDecoderService(QExtPinyinDecoderService::instance())
{
    mPinyinDecoderService->setUserDictionary(true);
}

void QExtPinyinInputMethodPrivate::resetToIdleState()
{
    Q_Q(QExtPinyinInputMethod);

    QExtKeyboardInputContext *inputContext = q->inputContext();

    //        // Disable the user dictionary when entering sensitive data
    //        if (inputContext) {
    //            bool userDictionaryEnabled = !inputContext->inputMethodHints().testFlag(Qt::ImhSensitiveData);
    //            if (userDictionaryEnabled != pinyinDecoderService->isUserDictionaryEnabled())
    //                pinyinDecoderService->setUserDictionary(userDictionaryEnabled);
    //        }

    if (mState == Idle)
    {
        return;
    }

    mState = Idle;
    mSurface.clear();
    mFixedLen = 0;
    mFinishSelection = true;
    mComposingStr.clear();
    if (inputContext)
    {
        inputContext->setPreeditText(QString());
    }
    mActiveCmpsLen = 0;
    mPosDelSpl = -1;
    mIsPosInSpl = false;

    this->resetCandidates();
}

bool QExtPinyinInputMethodPrivate::addSpellingChar(QChar ch, bool reset)
{
    if (reset)
    {
        mSurface.clear();
        mPinyinDecoderService->resetSearch();
    }
    if (ch == Qt::Key_Apostrophe)
    {
        if (mSurface.isEmpty())
        {
            return false;
        }
        if (mSurface.endsWith(ch))
        {
            return true;
        }
    }
    mSurface.append(ch);
    return true;
}

bool QExtPinyinInputMethodPrivate::removeSpellingChar()
{
    if (mSurface.isEmpty())
    {
        return false;
    }
    QVector<int> splStart = mPinyinDecoderService->spellingStartPositions();
    mIsPosInSpl = (mSurface.length() <= splStart[mFixedLen + 1]);
    mPosDelSpl = mIsPosInSpl ? mFixedLen - 1 : mSurface.length() - 1;
    return true;
}

void QExtPinyinInputMethodPrivate::chooseAndUpdate(int candId)
{
    Q_Q(QExtPinyinInputMethod);

    //联想状态选择联想词
    if (mState == Predict)
    {
        this->choosePredictChoice(candId);
    }
    else//对输入按键解码
    {
        chooseDecodingCandidate(candId);
    }

    if (mComposingStr.length() > 0)
    {
        if ((candId >= 0 || mFinishSelection) && mComposingStr.length() == mFixedLen)
        {
            QString resultStr = getComposingStrActivePart();
            this->tryPredict();
            q->inputContext()->commit(resultStr);
        }
        else if (mState == Idle)
        {
            mState = Input;
        }
    }
    else
    {
        this->tryPredict();
    }
}

bool QExtPinyinInputMethodPrivate::chooseAndFinish()
{
    if (mState == Predict || !mTotalChoicesNum)
    {
        return false;
    }

    this->chooseAndUpdate(0);
    if (mState != Predict && mTotalChoicesNum > 0)
    {
        this->chooseAndUpdate(0);
    }
    return true;
}

int QExtPinyinInputMethodPrivate::candidatesCount()
{
    return mTotalChoicesNum;
}

QString QExtPinyinInputMethodPrivate::candidateAt(int index)
{
    if (index < 0 || index >= mTotalChoicesNum)
    {
        return QString();
    }
    if (index >= mCandidatesList.size())
    {
        int fetchMore = qMin(index + 20, mTotalChoicesNum - mCandidatesList.size());
        mCandidatesList.append(mPinyinDecoderService->fetchCandidates(mCandidatesList.size(), fetchMore, mFixedLen));
        if (index == 0 && mTotalChoicesNum == 1)
        {
            int surfaceDecodedLen = mPinyinDecoderService->pinyinStringLength(true);
            if (surfaceDecodedLen < mSurface.length())
            {
                mCandidatesList[0] = mCandidatesList[0] + mSurface.mid(surfaceDecodedLen).toLower();
            }
        }
    }
    return index < mCandidatesList.size() ? mCandidatesList[index] : QString();
}

void QExtPinyinInputMethodPrivate::chooseDecodingCandidate(int candId)
{
    Q_Q(QExtPinyinInputMethod);
    Q_ASSERT(mState != Predict);

    int result = 0;
    if (candId < 0)
    {
        if (mSurface.length() > 0)
        {
            if (mPosDelSpl < 0)
            {
                result = mPinyinDecoderService->search(mSurface);
            }
            else
            {
                result = mPinyinDecoderService->deleteSearch(mPosDelSpl, mIsPosInSpl, false);
                mPosDelSpl = -1;
            }
        }
    }
    else
    {
        if (mTotalChoicesNum > 1)
        {
            result = mPinyinDecoderService->chooceCandidate(candId);
        }
        else
        {
            QString resultStr;
            if (mTotalChoicesNum == 1)
            {
                QString undecodedStr = candId < mCandidatesList.length() ? mCandidatesList.at(candId) : QString();
                resultStr = mPinyinDecoderService->candidateAt(0).mid(0, mFixedLen) + undecodedStr;
            }
            this->resetToIdleState();
            if (!resultStr.isEmpty())
            {
                q->inputContext()->commit(resultStr);
            }
            return;
        }
    }

    this->resetCandidates();
    mTotalChoicesNum = result;

    mSurface = mPinyinDecoderService->pinyinString(false);
    QVector<int> splStart = mPinyinDecoderService->spellingStartPositions();
    QString fullSent = mPinyinDecoderService->candidateAt(0);
    mFixedLen = mPinyinDecoderService->fixedLength();
    mComposingStr = fullSent.mid(0, mFixedLen) + mSurface.mid(splStart[mFixedLen + 1]);
    mActiveCmpsLen = mComposingStr.length();

    // Prepare the display string.
    QString composingStrDisplay;
    int surfaceDecodedLen = mPinyinDecoderService->pinyinStringLength(true);
    if (!surfaceDecodedLen)
    {
        composingStrDisplay = mComposingStr.toLower();
        if (!mTotalChoicesNum)
        {
            mTotalChoicesNum = 1;
        }
    }
    else
    {
        mActiveCmpsLen = mActiveCmpsLen - (mSurface.length() - surfaceDecodedLen);
        composingStrDisplay = fullSent.mid(0, mFixedLen);
        for (int pos = mFixedLen + 1; pos < splStart.size() - 1; pos++)
        {
            composingStrDisplay += mSurface.mid(splStart[pos], splStart[pos + 1] - splStart[pos]).toUpper();
            if (splStart[pos + 1] < surfaceDecodedLen)
            {
                composingStrDisplay += QLatin1String("'");
            }
        }
        if (surfaceDecodedLen < mSurface.length())
        {
            composingStrDisplay += mSurface.mid(surfaceDecodedLen).toLower();
        }
    }

    q->inputContext()->setPreeditText(composingStrDisplay);

    mFinishSelection = splStart.size() == (mFixedLen + 2);
    if (!mFinishSelection)
    {
        this->candidateAt(0);
    }
}

void QExtPinyinInputMethodPrivate::choosePredictChoice(int choiceId)
{
    Q_ASSERT(mState == Predict);

    if (choiceId < 0 || choiceId >= mTotalChoicesNum)
    {
        return;
    }

    QString tmp = mCandidatesList.at(choiceId);

    this->resetCandidates();

    mCandidatesList.append(tmp);
    mTotalChoicesNum = 1;

    mSurface.clear();
    mFixedLen = tmp.length();
    mComposingStr = tmp;
    mActiveCmpsLen = mFixedLen;

    mFinishSelection = true;
}

QString QExtPinyinInputMethodPrivate::getComposingStrActivePart()
{
    return mComposingStr.mid(0, mActiveCmpsLen);
}

void QExtPinyinInputMethodPrivate::resetCandidates()
{
    //        Q_Q(QExtPinyinInputMethod);

    mCandidatesList.clear();
    if (mTotalChoicesNum)
    {
        mTotalChoicesNum = 0;
    }
}

void QExtPinyinInputMethodPrivate::updateCandidateList()
{
    Q_Q(QExtPinyinInputMethod);
    emit q->showCandidateList(mCandidatesList);
    //        emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
    //        emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList,
    //                                               totalChoicesNum > 0 && state == PinyinInputMethodPrivate::Input ? 0 : -1);
}

bool QExtPinyinInputMethodPrivate::canDoPrediction()
{
    //        Q_Q(QExtPinyinInputMethod);
    //        QVirtualKeyboardInputContext *inputContext = q->inputContext();
    //        return inputMode == QVirtualKeyboardInputEngine::InputMode::Pinyin &&
    //                composingStr.length() == fixedLen &&
    //                inputContext &&
    //                !inputContext->inputMethodHints().testFlag(Qt::ImhNoPredictiveText);

    return false;
}

void QExtPinyinInputMethodPrivate::tryPredict()
{
    // Try to get the prediction list.
    if (canDoPrediction())
    {
        //            Q_Q(QExtPinyinInputMethod);
        if (mState != Predict)
        {
            this->resetToIdleState();
        }
        //QVirtualKeyboardInputContext *inputContext = q->inputContext();
        //int cursorPosition = inputContext->cursorPosition();
        //int historyStart = qMax(0, cursorPosition - 3);
        //QString history = inputContext->surroundingText().mid(historyStart, cursorPosition - historyStart);
        //candidatesList = pinyinDecoderService->predictionList(history);
        mTotalChoicesNum = mCandidatesList.size();
        mFinishSelection = false;
        mState = Predict;
    }
    else
    {
        this->resetCandidates();
    }

    if (!this->candidatesCount())
    {
        this->resetToIdleState();
    }
}

QExtPinyinInputMethod::QExtPinyinInputMethod(QObject *parent)
    : QExtAbstractInputMethod(parent)
    , dd_ptr(new QExtPinyinInputMethodPrivate(this))
{
}

QExtPinyinInputMethod::~QExtPinyinInputMethod()
{
}

QExtKeyboardInputContext *QExtPinyinInputMethod::inputContext() const
{
    Q_D(const QExtPinyinInputMethod);
    return d->mInputContext;
}

void QExtPinyinInputMethod::setInputContext(QExtKeyboardInputContext * context)
{
    Q_D(QExtPinyinInputMethod);
    d->mInputContext = context;
}

bool QExtPinyinInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers)
    Q_D(QExtPinyinInputMethod);

    if (d->mInputMode == QExtPinyinInputMethod::InputMode::Pinyin)
    {
        ScopedCandidateListUpdate scopedCandidateListUpdate(d);
        Q_UNUSED(scopedCandidateListUpdate)

        if ((key >= Qt::Key_A && key <= Qt::Key_Z) || (key == Qt::Key_Apostrophe))
        {
            if (d->mState == QExtPinyinInputMethodPrivate::Predict)
            {
                d->resetToIdleState();
            }
            if (d->addSpellingChar(text.at(0), d->mState == QExtPinyinInputMethodPrivate::Idle))
            {
                d->chooseAndUpdate(-1);
                return true;
            }
        }
        else if (key == Qt::Key_Space)
        {
            if (d->mState != QExtPinyinInputMethodPrivate::Predict && d->candidatesCount() > 0)
            {
                d->chooseAndUpdate(0);
                return true;
            }
        }
        else if (key == Qt::Key_Return)
        {
            if (d->mState != QExtPinyinInputMethodPrivate::Predict && d->candidatesCount() > 0)
            {
                QString surface = d->mSurface;
                d->resetToIdleState();
                this->inputContext()->commit(surface);
                return true;
            }
        }
        else if (key == Qt::Key_Backspace)
        {
            if(d->mState == d->Idle)
            {
                this->inputContext()->sendKeyClick(key, text, modifiers);
            }
            else if (d->removeSpellingChar())
            {
                d->chooseAndUpdate(-1);
                return true;
            }
        }
        else
        {
            if(d->mState == d->Input)
            {
                if(text.isEmpty())
                {
                    d->chooseAndFinish();
                }
            }
            else if(d->mState == d->Idle)
            {
                this->inputContext()->sendKeyClick(key, text, modifiers);
            }
        }
    }
    else
    {
        this->inputContext()->sendKeyClick(key, text, modifiers);
    }
    return false;

}

void QExtPinyinInputMethod::reset()
{
    Q_D(QExtPinyinInputMethod);
    ScopedCandidateListUpdate scopedCandidateListUpdate(d);
    Q_UNUSED(scopedCandidateListUpdate)
    d->resetToIdleState();
}

void QExtPinyinInputMethod::changeLanguage()
{
    Q_D(QExtPinyinInputMethod);
    if(d->mInputMode == QExtAbstractInputMethod::InputMode::Pinyin)
    {
        d->mInputMode = QExtAbstractInputMethod::InputMode::Latin;
        emit this->showLanguageName("English");
    }
    else
    {
        d->mInputMode = QExtAbstractInputMethod::InputMode::Pinyin;
        emit this->showLanguageName("Chinese");
    }
    ScopedCandidateListUpdate scopedCandidateListUpdate(d);
    Q_UNUSED(scopedCandidateListUpdate)
    d->resetToIdleState();
    this->inputContext()->setPreeditText("");
}

void QExtPinyinInputMethod::chooseCandidate(int id)
{
    Q_D(QExtPinyinInputMethod);
    d->chooseAndUpdate(id);
    d->updateCandidateList();
}
