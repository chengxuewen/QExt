#include <qextGuiGradient.h>
#include <qextGuiGradient_p.h>

void QEXTGuiGradientStop::updateGradient()
{
    if (QEXTGuiGradient *grad = qobject_cast<QEXTGuiGradient *>(this->parent()))
    {
        grad->doUpdate();
    }
}



const QGradient *QEXTGuiGradient::gradient() const
{
    if (!m_gradient && !m_stops.isEmpty())
    {
        m_gradient = new QLinearGradient(0, 0, 0, 1.0);
        for (int i = 0; i < m_stops.count(); ++i)
        {
            const QEXTGuiGradientStop *stop = m_stops.at(i);
            m_gradient->setCoordinateMode(QGradient::ObjectBoundingMode);
            m_gradient->setColorAt(stop->position(), stop->color());
        }
    }
    return m_gradient;
}

void QEXTGuiGradient::doUpdate()
{
    delete m_gradient;
    m_gradient = QEXT_DECL_NULLPTR;
    emit updated();
}
