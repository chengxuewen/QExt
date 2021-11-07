#include <qextMvvmPath.h>

//! Constructs QEXTMvvmPath object from string containing sequence of integers ("0,0,1,3").

QEXTMvvmPath QEXTMvvmPath::fromString(const QString &str)
{
    QEXTMvvmPath result;
    QString strSpaces = str;
    strSpaces.replace(',', ' ');
    for (int i = 0; i < strSpaces.size(); ++i)
    {
        result.append(strSpaces.at(i).digitValue());
    }
    return result;
}

//! Constructs QEXTMvvmPath object from vector of integers..
QEXTMvvmPath QEXTMvvmPath::fromVector(const QVector<int> &data)
{
    QEXTMvvmPath result;
    for (int i = 0; i < data.size(); ++i) {
        result.append(data.at(i));
    }
    return result;
}

//! Returns string representing path ("0,0,1,3").

QString QEXTMvvmPath::string() const
{
    QString result;
    if (!m_data.isEmpty())
    {
        result.append(QString::number(m_data[0]));
        for (int i = 1; i < m_data.size(); ++i) {
            result.append(',' + QString::number(m_data[i]));
        }
    }
    return result;
}

void QEXTMvvmPath::append(QEXTMvvmPath::PathElement element)
{
    m_data.append(element);
}

void QEXTMvvmPath::prepend(QEXTMvvmPath::PathElement element)
{
    m_data.prepend(element);
}

QEXTMvvmPath::Iterator QEXTMvvmPath::begin()
{
    return m_data.begin();
}

QEXTMvvmPath::ConstIterator QEXTMvvmPath::begin() const
{
    return m_data.begin();
}

QEXTMvvmPath::Iterator QEXTMvvmPath::end()
{
    return m_data.end();
}

QEXTMvvmPath::ConstIterator QEXTMvvmPath::end() const
{
    return m_data.end();
}
