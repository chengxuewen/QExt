#include <qextModelTagInfo.h>
#include <qextContainerUtils.h>

#include <QDebug>

class QExtModelTagInfoPrivate
{
public:
    explicit QExtModelTagInfoPrivate(QExtModelTagInfo *q);
    virtual ~QExtModelTagInfoPrivate();

    QExtModelTagInfo * const q_ptr;

    int m_min;
    int m_max;
    QString m_name;
    QStringList m_modelTypes;

private:
    QEXT_DECL_PUBLIC(QExtModelTagInfo)
    QEXT_DISABLE_COPY_MOVE(QExtModelTagInfoPrivate)
};

QExtModelTagInfoPrivate::QExtModelTagInfoPrivate(QExtModelTagInfo *q)
    : q_ptr(q)
    , m_min(0)
    , m_max(-1)
{

}

QExtModelTagInfoPrivate::~QExtModelTagInfoPrivate()
{

}

QExtModelTagInfo::QExtModelTagInfo()
    : dd_ptr(new QExtModelTagInfoPrivate(this))
{

}

QExtModelTagInfo::QExtModelTagInfo(const QExtModelTagInfo &other)
    : dd_ptr(new QExtModelTagInfoPrivate(this))
{
    dd_ptr->m_name = other.dd_ptr->m_name;
    dd_ptr->m_min = other.dd_ptr->m_min;
    dd_ptr->m_max = other.dd_ptr->m_max;
    dd_ptr->m_modelTypes = other.dd_ptr->m_modelTypes;
}

QExtModelTagInfo::QExtModelTagInfo(const QString &name, int min, int max, const QStringList &modelTypes)
    : dd_ptr(new QExtModelTagInfoPrivate(this))
{
    dd_ptr->m_name = name;
    dd_ptr->m_min = min;
    dd_ptr->m_max = max;
    dd_ptr->m_modelTypes = modelTypes;
    if (min < 0 || (min > max && max >= 0) || name.isEmpty())
    {
        qCritical() << QString("Invalid constructor parameters %1 %2 %3").arg(name).arg(min).arg(max);
    }
}

QExtModelTagInfo::~QExtModelTagInfo()
{

}

QExtModelTagInfo &QExtModelTagInfo::operator =(const QExtModelTagInfo &other)
{
    if (this != &other)
    {
        dd_ptr->m_name = other.dd_ptr->m_name;
        dd_ptr->m_min = other.dd_ptr->m_min;
        dd_ptr->m_max = other.dd_ptr->m_max;
        dd_ptr->m_modelTypes = other.dd_ptr->m_modelTypes;
    }
    return *this;
}

void QExtModelTagInfo::swap(QExtModelTagInfo &other) noexcept
{
    if (this != &other)
    {
        dd_ptr.swap(other.dd_ptr);
    }
}

int QExtModelTagInfo::min() const
{
    Q_D(const QExtModelTagInfo);
    return d->m_min;
}

int QExtModelTagInfo::max() const
{
    Q_D(const QExtModelTagInfo);
    return d->m_max;
}

QString QExtModelTagInfo::name() const
{
    Q_D(const QExtModelTagInfo);
    return d->m_name;
}

QStringList QExtModelTagInfo::modelTypes() const
{
    Q_D(const QExtModelTagInfo);
    return d->m_modelTypes;
}

bool QExtModelTagInfo::isSinglePropertyTag() const
{
    Q_D(const QExtModelTagInfo);
    return d->m_min == 1 && d->m_max == 1;
}

bool QExtModelTagInfo::isValidChild(const QString &child) const
{
    Q_D(const QExtModelTagInfo);
    return d->m_modelTypes.isEmpty() ? true : QExtContainerUtils::contains(d->m_modelTypes, child);
}

bool QExtModelTagInfo::operator==(const QExtModelTagInfo &other) const
{
    Q_D(const QExtModelTagInfo);
    if (this != &other)
    {
        return d->m_name == other.dd_ptr->m_name
               && d->m_min == other.dd_ptr->m_min
               && d->m_max == other.dd_ptr->m_max
               && d->m_modelTypes == other.dd_ptr->m_modelTypes;
    }
    return true;
}

bool QExtModelTagInfo::operator!=(const QExtModelTagInfo &other) const
{
    return !(*this == other);
}

QExtModelTagInfo QExtModelTagInfo::universalTag(const QString &name, const QStringList &modelTypes)
{
    return QExtModelTagInfo(name, 0, -1, modelTypes);
}

QExtModelTagInfo QExtModelTagInfo::propertyTag(const QString &name, const QString &modelType)
{
    return QExtModelTagInfo(name, 0, -1, QStringList() << modelType);
}
