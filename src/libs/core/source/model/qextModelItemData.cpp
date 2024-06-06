#include "qextModelItemData.h"

class QExtModelItemDataPrivate
{
public:
    explicit QExtModelItemDataPrivate(QExtModelItemData *q);
    virtual ~QExtModelItemDataPrivate();

    /**
     * @brief Check if variant is compatible
     * @param variant
     * @param role
     */
    void assureValidity(const QVariant &variant, int role);

    QExtModelItemData * const q_ptr;

    QExtModelItemData::Container m_values;

private:
    QEXT_DECL_PUBLIC(QExtModelItemData)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemDataPrivate)
};

QExtModelItemDataPrivate::QExtModelItemDataPrivate(QExtModelItemData *q)
    : q_ptr(q)
{

}

QExtModelItemDataPrivate::~QExtModelItemDataPrivate()
{

}

void QExtModelItemDataPrivate::assureValidity(const QVariant &variant, int role)
{

}

QExtModelItemData::QExtModelItemData()
    : dd_ptr(new QExtModelItemDataPrivate(this))
{

}

QExtModelItemData::~QExtModelItemData()
{

}

QVector<int> QExtModelItemData::roles() const
{
    Q_D(const QExtModelItemData);
    QVector<int> result;
    for (ConstIterator iter = d->m_values.begin(); iter != d->m_values.end(); ++iter)
    {
        result.append(iter->m_role);
    }
    return result;
}

bool QExtModelItemData::hasData(int role) const
{
    Q_D(const QExtModelItemData);
    for (ConstIterator iter = d->m_values.begin(); iter != d->m_values.end(); ++iter)
    {
        if (role == iter->m_role)
        {
            return true;
        }
    }
    return false;
}

QVariant QExtModelItemData::data(int role) const
{
    Q_D(const QExtModelItemData);
    for (ConstIterator iter = d->m_values.begin(); iter != d->m_values.end(); ++iter)
    {
        if (role == iter->m_role)
        {
            return iter->m_data;
        }
    }
    return QVariant();
}

bool QExtModelItemData::setData(const QVariant &value, int role)
{
    Q_D(QExtModelItemData);
    d->assureValidity(value, role);
    for (Iterator iter = d->m_values.begin(); iter != d->m_values.end(); ++iter)
    {
        if (role == iter->m_role)
        {
            if (value.isValid())
            {
                if (QExtVariantUtils::isTheSame(iter->m_data, value))
                {
                    return false;
                }
                iter->m_data = value;
            }
            else
            {
                d->m_values.erase(iter);
            }
            return true;
        }
    }
    d->m_values.push_back(QExtModelItemDataRole(value, role));
    return true;
}

QExtModelItemData::ConstIterator QExtModelItemData::begin() const
{
    Q_D(const QExtModelItemData);
    return d->m_values.begin();
}

QExtModelItemData::ConstIterator QExtModelItemData::end() const
{
    Q_D(const QExtModelItemData);
    return d->m_values.end();
}
