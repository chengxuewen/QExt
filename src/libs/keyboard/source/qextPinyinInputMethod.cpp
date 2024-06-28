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

    State m_state;
    int m_fixedLen;
    int m_posDelSpl;
    int m_activeCmpsLen;
    int m_totalChoicesNum;
    bool m_isPosInSpl;
    bool m_finishSelection;
    QString m_surface;
    QString m_composingStr;
    QList<QString> m_candidatesList;
    QExtKeyboardInputContext *m_inputContext;
    QExtPinyinInputMethod::InputMode m_inputMode;
    QPointer<QExtPinyinDecoderService> m_pinyinDecoderService;

private:
    QEXT_DECL_PUBLIC(QExtPinyinInputMethod)
    QEXT_DISABLE_COPY_MOVE(QExtPinyinInputMethodPrivate)
};

class ScopedCandidateListUpdate
{
public:
    inline explicit ScopedCandidateListUpdate(QExtPinyinInputMethodPrivate *d)
        : d(d)
        , m_totalChoicesNum(d->m_totalChoicesNum)
        , m_candidatesList(d->m_candidatesList)
        , m_state(d->m_state)
    {
    }

    inline ~ScopedCandidateListUpdate()
    {
        if (m_totalChoicesNum != d->m_totalChoicesNum || m_state != d->m_state || m_candidatesList != d->m_candidatesList)
        {
            QList<QString> candidateList;
            for(int i = 0;i < d->m_totalChoicesNum;++i)
            {
                candidateList.append(d->candidateAt(i));
            }
            d->updateCandidateList();
        }
    }

private:
    Q_DISABLE_COPY(ScopedCandidateListUpdate)
    QExtPinyinInputMethodPrivate *d;
    int m_totalChoicesNum;
    QList<QString> m_candidatesList;
    QExtPinyinInputMethodPrivate::State m_state;
};


QExtPinyinInputMethodPrivate::QExtPinyinInputMethodPrivate(QExtPinyinInputMethod *q_ptr)
    : q_ptr(q_ptr)
    , m_state(Idle)
    , m_fixedLen(0)
    , m_posDelSpl(-1)
    , m_activeCmpsLen(0)
    , m_totalChoicesNum(0)
    , m_isPosInSpl(false)
    , m_finishSelection(true)
    , m_surface()
    , m_composingStr()
    , m_candidatesList()
    , m_inputContext(nullptr)
    , m_inputMode(QExtPinyinInputMethod::InputMode::Latin)
    , m_pinyinDecoderService(QExtPinyinDecoderService::instance())
{
    m_pinyinDecoderService->setUserDictionary(true);
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

    if (m_state == Idle)
    {
        return;
    }

    m_state = Idle;
    m_surface.clear();
    m_fixedLen = 0;
    m_finishSelection = true;
    m_composingStr.clear();
    if (inputContext)
    {
        inputContext->setPreeditText(QString());
    }
    m_activeCmpsLen = 0;
    m_posDelSpl = -1;
    m_isPosInSpl = false;

    this->resetCandidates();
}

bool QExtPinyinInputMethodPrivate::addSpellingChar(QChar ch, bool reset)
{
    if (reset)
    {
        m_surface.clear();
        m_pinyinDecoderService->resetSearch();
    }
    if (ch == Qt::Key_Apostrophe)
    {
        if (m_surface.isEmpty())
        {
            return false;
        }
        if (m_surface.endsWith(ch))
        {
            return true;
        }
    }
    m_surface.append(ch);
    return true;
}

bool QExtPinyinInputMethodPrivate::removeSpellingChar()
{
    if (m_surface.isEmpty())
    {
        return false;
    }
    QVector<int> splStart = m_pinyinDecoderService->spellingStartPositions();
    m_isPosInSpl = (m_surface.length() <= splStart[m_fixedLen + 1]);
    m_posDelSpl = m_isPosInSpl ? m_fixedLen - 1 : m_surface.length() - 1;
    return true;
}

void QExtPinyinInputMethodPrivate::chooseAndUpdate(int candId)
{
    Q_Q(QExtPinyinInputMethod);

    //联想状态选择联想词
    if (m_state == Predict)
    {
        this->choosePredictChoice(candId);
    }
    else//对输入按键解码
    {
        chooseDecodingCandidate(candId);
    }

    if (m_composingStr.length() > 0)
    {
        if ((candId >= 0 || m_finishSelection) && m_composingStr.length() == m_fixedLen)
        {
            QString resultStr = getComposingStrActivePart();
            this->tryPredict();
            q->inputContext()->commit(resultStr);
        }
        else if (m_state == Idle)
        {
            m_state = Input;
        }
    }
    else
    {
        this->tryPredict();
    }
}

bool QExtPinyinInputMethodPrivate::chooseAndFinish()
{
    if (m_state == Predict || !m_totalChoicesNum)
    {
        return false;
    }

    this->chooseAndUpdate(0);
    if (m_state != Predict && m_totalChoicesNum > 0)
    {
        this->chooseAndUpdate(0);
    }
    return true;
}

int QExtPinyinInputMethodPrivate::candidatesCount()
{
    return m_totalChoicesNum;
}

QString QExtPinyinInputMethodPrivate::candidateAt(int index)
{
    if (index < 0 || index >= m_totalChoicesNum)
    {
        return QString();
    }
    if (index >= m_candidatesList.size())
    {
        int fetchMore = qMin(index + 20, m_totalChoicesNum - m_candidatesList.size());
        m_candidatesList.append(m_pinyinDecoderService->fetchCandidates(m_candidatesList.size(), fetchMore, m_fixedLen));
        if (index == 0 && m_totalChoicesNum == 1)
        {
            int surfaceDecodedLen = m_pinyinDecoderService->pinyinStringLength(true);
            if (surfaceDecodedLen < m_surface.length())
            {
                m_candidatesList[0] = m_candidatesList[0] + m_surface.mid(surfaceDecodedLen).toLower();
            }
        }
    }
    return index < m_candidatesList.size() ? m_candidatesList[index] : QString();
}

void QExtPinyinInputMethodPrivate::chooseDecodingCandidate(int candId)
{
    Q_Q(QExtPinyinInputMethod);
    Q_ASSERT(m_state != Predict);

    int result = 0;
    if (candId < 0)
    {
        if (m_surface.length() > 0)
        {
            if (m_posDelSpl < 0)
            {
                result = m_pinyinDecoderService->search(m_surface);
            }
            else
            {
                result = m_pinyinDecoderService->deleteSearch(m_posDelSpl, m_isPosInSpl, false);
                m_posDelSpl = -1;
            }
        }
    }
    else
    {
        if (m_totalChoicesNum > 1)
        {
            result = m_pinyinDecoderService->chooceCandidate(candId);
        }
        else
        {
            QString resultStr;
            if (m_totalChoicesNum == 1)
            {
                QString undecodedStr = candId < m_candidatesList.length() ? m_candidatesList.at(candId) : QString();
                resultStr = m_pinyinDecoderService->candidateAt(0).mid(0, m_fixedLen) + undecodedStr;
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
    m_totalChoicesNum = result;

    m_surface = m_pinyinDecoderService->pinyinString(false);
    QVector<int> splStart = m_pinyinDecoderService->spellingStartPositions();
    QString fullSent = m_pinyinDecoderService->candidateAt(0);
    m_fixedLen = m_pinyinDecoderService->fixedLength();
    m_composingStr = fullSent.mid(0, m_fixedLen) + m_surface.mid(splStart[m_fixedLen + 1]);
    m_activeCmpsLen = m_composingStr.length();

    // Prepare the display string.
    QString composingStrDisplay;
    int surfaceDecodedLen = m_pinyinDecoderService->pinyinStringLength(true);
    if (!surfaceDecodedLen)
    {
        composingStrDisplay = m_composingStr.toLower();
        if (!m_totalChoicesNum)
        {
            m_totalChoicesNum = 1;
        }
    }
    else
    {
        m_activeCmpsLen = m_activeCmpsLen - (m_surface.length() - surfaceDecodedLen);
        composingStrDisplay = fullSent.mid(0, m_fixedLen);
        for (int pos = m_fixedLen + 1; pos < splStart.size() - 1; pos++)
        {
            composingStrDisplay += m_surface.mid(splStart[pos], splStart[pos + 1] - splStart[pos]).toUpper();
            if (splStart[pos + 1] < surfaceDecodedLen)
            {
                composingStrDisplay += QLatin1String("'");
            }
        }
        if (surfaceDecodedLen < m_surface.length())
        {
            composingStrDisplay += m_surface.mid(surfaceDecodedLen).toLower();
        }
    }

    q->inputContext()->setPreeditText(composingStrDisplay);

    m_finishSelection = splStart.size() == (m_fixedLen + 2);
    if (!m_finishSelection)
    {
        this->candidateAt(0);
    }
}

void QExtPinyinInputMethodPrivate::choosePredictChoice(int choiceId)
{
    Q_ASSERT(m_state == Predict);

    if (choiceId < 0 || choiceId >= m_totalChoicesNum)
    {
        return;
    }

    QString tmp = m_candidatesList.at(choiceId);

    this->resetCandidates();

    m_candidatesList.append(tmp);
    m_totalChoicesNum = 1;

    m_surface.clear();
    m_fixedLen = tmp.length();
    m_composingStr = tmp;
    m_activeCmpsLen = m_fixedLen;

    m_finishSelection = true;
}

QString QExtPinyinInputMethodPrivate::getComposingStrActivePart()
{
    return m_composingStr.mid(0, m_activeCmpsLen);
}

void QExtPinyinInputMethodPrivate::resetCandidates()
{
    //        Q_Q(QExtPinyinInputMethod);

    m_candidatesList.clear();
    if (m_totalChoicesNum)
    {
        m_totalChoicesNum = 0;
    }
}

void QExtPinyinInputMethodPrivate::updateCandidateList()
{
    Q_Q(QExtPinyinInputMethod);
    emit q->showCandidateList(m_candidatesList);
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
        if (m_state != Predict)
        {
            this->resetToIdleState();
        }
        //QVirtualKeyboardInputContext *inputContext = q->inputContext();
        //int cursorPosition = inputContext->cursorPosition();
        //int historyStart = qMax(0, cursorPosition - 3);
        //QString history = inputContext->surroundingText().mid(historyStart, cursorPosition - historyStart);
        //candidatesList = pinyinDecoderService->predictionList(history);
        m_totalChoicesNum = m_candidatesList.size();
        m_finishSelection = false;
        m_state = Predict;
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
    return d->m_inputContext;
}

void QExtPinyinInputMethod::setInputContext(QExtKeyboardInputContext * context)
{
    Q_D(QExtPinyinInputMethod);
    d->m_inputContext = context;
}

bool QExtPinyinInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers)
    Q_D(QExtPinyinInputMethod);

    if (d->m_inputMode == QExtPinyinInputMethod::InputMode::Pinyin)
    {
        ScopedCandidateListUpdate scopedCandidateListUpdate(d);
        Q_UNUSED(scopedCandidateListUpdate)

        if ((key >= Qt::Key_A && key <= Qt::Key_Z) || (key == Qt::Key_Apostrophe))
        {
            if (d->m_state == QExtPinyinInputMethodPrivate::Predict)
            {
                d->resetToIdleState();
            }
            if (d->addSpellingChar(text.at(0), d->m_state == QExtPinyinInputMethodPrivate::Idle))
            {
                d->chooseAndUpdate(-1);
                return true;
            }
        }
        else if (key == Qt::Key_Space)
        {
            if (d->m_state != QExtPinyinInputMethodPrivate::Predict && d->candidatesCount() > 0)
            {
                d->chooseAndUpdate(0);
                return true;
            }
        }
        else if (key == Qt::Key_Return)
        {
            if (d->m_state != QExtPinyinInputMethodPrivate::Predict && d->candidatesCount() > 0)
            {
                QString surface = d->m_surface;
                d->resetToIdleState();
                this->inputContext()->commit(surface);
                return true;
            }
        }
        else if (key == Qt::Key_Backspace)
        {
            if(d->m_state == d->Idle)
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
            if(d->m_state == d->Input)
            {
                if(text.isEmpty())
                {
                    d->chooseAndFinish();
                }
            }
            else if(d->m_state == d->Idle)
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
    if(d->m_inputMode == QExtAbstractInputMethod::InputMode::Pinyin)
    {
        d->m_inputMode = QExtAbstractInputMethod::InputMode::Latin;
        emit this->showLanguageName("English");
    }
    else
    {
        d->m_inputMode = QExtAbstractInputMethod::InputMode::Pinyin;
        emit this->showLanguageName("简体中文");
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
