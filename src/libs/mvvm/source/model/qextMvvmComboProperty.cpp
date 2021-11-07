#include <qextMvvmComboProperty.h>
#include <qextMvvmComboProperty_p.h>
#include <qextMvvmUtils.h>

#include <sstream>
#include <stdexcept>

namespace
{
const QString VALUE_SEPARATOR = ";";
const QString SELECTION_SEPARATOR = ",";
const QString MUTIPLE_LABEL = "Multiple";
const QString NONE_LABEL = "None";

QVector<QString> qextMvvmTokenize(const QString &string, const QString &delimeter)
{
    QVector<QString> result;
    std::string stdString = string.toStdString();
    std::string stdDelimeter = delimeter.toStdString();
    size_t start = stdString.find_first_not_of(stdDelimeter);
    size_t end = start;
    while (start != std::string::npos)
    {
        // Find next occurence of delimiter
        end = stdString.find(stdDelimeter, start);
        // Push back the token found into vector
        result.append(QString::fromStdString(stdString.substr(start, end - start)));
        // Skip all occurences of the delimiter to find new start
        start = stdString.find_first_not_of(stdDelimeter, end);
    }
    return result;
}
} // namespace




QEXTMvvmComboPropertyPrivate::QEXTMvvmComboPropertyPrivate(QEXTMvvmComboProperty *q)
    : q_ptr(q)
{

}

QEXTMvvmComboPropertyPrivate::~QEXTMvvmComboPropertyPrivate()
{

}



QEXTMvvmComboProperty::QEXTMvvmComboProperty(QVector<QString> values)
    : d_ptr(new QEXTMvvmComboPropertyPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    d->m_values = values;
}

QEXTMvvmComboProperty::QEXTMvvmComboProperty()
    : d_ptr(new QEXTMvvmComboPropertyPrivate(this))
{

}

QEXTMvvmComboProperty::QEXTMvvmComboProperty(const QEXTMvvmComboProperty &other)
    : d_ptr(new QEXTMvvmComboPropertyPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    d->m_selectedIndices = other.d_func()->m_selectedIndices;
    d->m_toolTips = other.d_func()->m_toolTips;
    d->m_values = other.d_func()->m_values;
}

QEXTMvvmComboProperty::~QEXTMvvmComboProperty()
{

}

QEXTMvvmComboProperty QEXTMvvmComboProperty::createFrom(const QVector<QString> &values,
                                                        const QString &currentValue)
{
    QEXTMvvmComboProperty result(values);
    if (!currentValue.isEmpty())
    {
        result.setValue(currentValue);
    }
    else
    {
        result.setCurrentIndex(0);
    }
    return result;
}

QString QEXTMvvmComboProperty::value() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    return this->currentIndex() < 0 ? QString() : d->m_values.at(this->currentIndex());
}

void QEXTMvvmComboProperty::setValue(const QString &name)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    if (!d->m_values.contains(name))
    {
        throw std::runtime_error("QEXTMvvmComboProperty::setValue() -> Error. Combo doesn't contain value " + name.toStdString());
    }
    this->setCurrentIndex(d->m_values.indexOf(name));
}

QVector<QString> QEXTMvvmComboProperty::values() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    return d->m_values;
}

void QEXTMvvmComboProperty::setValues(const QVector<QString> &values)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    if (!values.isEmpty())
    {
        QString current = this->value();
        d->m_values = values;
        this->setCurrentIndex(d->m_values.contains(current) ? d->m_values.indexOf(current) : 0);
    }
}

//! returns list of tool tips for all values
QVector<QString> QEXTMvvmComboProperty::toolTips() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    return d->m_toolTips;
}

void QEXTMvvmComboProperty::setToolTips(const QVector<QString> &tooltips)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    d->m_toolTips = tooltips;
}

int QEXTMvvmComboProperty::currentIndex() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    return d->m_selectedIndices.empty() ? -1 : d->m_selectedIndices.at(0);
}

void QEXTMvvmComboProperty::setCurrentIndex(int index)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    if (index < 0 || index >= d->m_values.size())
    {
        throw std::runtime_error("QEXTMvvmComboProperty::setCurrentIndex(int index) -> Error. Invalid index");
    }
    d->m_selectedIndices.clear();
    d->m_selectedIndices.append(index);
}

QEXTMvvmComboProperty &QEXTMvvmComboProperty::operator<<(const QString &string)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    d->m_values.append(string);
    if (this->currentIndex() == -1)
    {
        this->setCurrentIndex(0);
    }
    return *this;
}

QEXTMvvmComboProperty &QEXTMvvmComboProperty::operator =(const QEXTMvvmComboProperty &other)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    if (this != &other)
    {
        d->m_selectedIndices = other.d_func()->m_selectedIndices;
        d->m_toolTips = other.d_func()->m_toolTips;
        d->m_values = other.d_func()->m_values;
    }
    return *this;
}

QEXTMvvmComboProperty &QEXTMvvmComboProperty::operator<<(const QVector<QString> &string)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    d->m_values.append(string);
    if (this->currentIndex() == -1)
    {
        this->setCurrentIndex(0);
    }
    return *this;
}

bool QEXTMvvmComboProperty::operator==(const QEXTMvvmComboProperty &other) const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    if (d->m_selectedIndices != other.d_func()->m_selectedIndices)
    {
        return false;
    }
    if (d->m_toolTips != other.d_func()->m_toolTips)
    {
        return false;
    }
    if (d->m_values != other.d_func()->m_values)
    {
        return false;
    }
    return true;
}

bool QEXTMvvmComboProperty::operator!=(const QEXTMvvmComboProperty &other) const
{
    return !(*this == other);
}

bool QEXTMvvmComboProperty::operator<(const QEXTMvvmComboProperty &other) const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    return d->m_selectedIndices < other.d_func()->m_selectedIndices
            && d->m_toolTips < other.d_func()->m_toolTips
            && d->m_values < other.d_func()->m_values;
}

//! Returns a single string containing values delimited with ';'.

QString QEXTMvvmComboProperty::stringOfValues() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    QString result;
    for (int i = 0; i < d->m_values.size(); ++i)
    {
        result.append(d->m_values.at(i));
        if (i != d->m_values.size() - 1)
        {
            result.append(VALUE_SEPARATOR);
        }
    }
    return result;
}

//! Sets values from the string containing delimeter ';'.

void QEXTMvvmComboProperty::setStringOfValues(const QString &values)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    QString current = this->value();
    d->m_values = qextMvvmTokenize(values, VALUE_SEPARATOR);
    this->setCurrentIndex(d->m_values.contains(current) ? d->m_values.indexOf(current) : 0);
}

//! Returns vector of selected indices.

QVector<int> QEXTMvvmComboProperty::selectedIndices() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    return d->m_selectedIndices;
}

//! Returns list of string with selected values;

QVector<QString> QEXTMvvmComboProperty::selectedValues() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    QVector<QString> result;
    for (int i = 0; i < d->m_selectedIndices.size(); ++i) {
        result.append(d->m_values.at(d->m_selectedIndices.at(i)));
    }
    return result;
}

//! Sets given index selection flag.
//! If false, index will be excluded from selection.

void QEXTMvvmComboProperty::setSelected(int index, bool value)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    if (index < 0 || index >= d->m_values.size())
    {
        return;
    }

    int pos = d->m_selectedIndices.indexOf(index);
    if (value)
    {
        if (pos == -1)
        {
            d->m_selectedIndices.append(index);
        }
    }
    else
    {
        if (pos != -1)
        {
            d->m_selectedIndices.remove(pos);
        }
    }
    qSort(d->m_selectedIndices.begin(), d->m_selectedIndices.end());
}

void QEXTMvvmComboProperty::setSelected(const QString &name, bool value)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    this->setSelected(d->m_values.indexOf(name), value);
}

//! Return string with coma separated list of selected indices.

QString QEXTMvvmComboProperty::stringOfSelections() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    QString result;
    for (int i = 0; i < d->m_selectedIndices.size(); ++i)
    {
        result.append(QString::number(d->m_selectedIndices.at(i)));
        if (i != d->m_selectedIndices.size() - 1)
        {
            result.append(SELECTION_SEPARATOR);
        }
    }
    return result;
}

//! Sets selected indices from string.

void QEXTMvvmComboProperty::setStringOfSelections(const QString &values)
{
    QEXT_DECL_D(QEXTMvvmComboProperty);
    d->m_selectedIndices.clear();
    if (!values.isEmpty())
    {
        QVector<QString> tokenize = qextMvvmTokenize(values, SELECTION_SEPARATOR);
        for (int i = 0; i < tokenize.size(); ++i) {
            int num = tokenize.at(i).toInt();
            this->setSelected(num, true);
        }
    }
}

//! Returns the label to show.

QString QEXTMvvmComboProperty::label() const
{
    QEXT_DECL_DC(QEXTMvvmComboProperty);
    if (d->m_selectedIndices.size() > 1)
    {
        return MUTIPLE_LABEL;
    }
    else if (d->m_selectedIndices.size() == 1)
    {
        return this->value();
    }
    else
    {
        return NONE_LABEL;
    }
}
