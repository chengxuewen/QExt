// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColorDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <qextMvvmColorEditor.h>
#include <qextMvvmCustomEventFilters.h>
#include <qextMvvmStyleUtils.h>
#include <qextMvvmCustomVariants.h>
#include <stdexcept>

using namespace ModelView;

QEXTMvvmColorEditor::QEXTMvvmColorEditor(QWidget* parent)
    : QEXTMvvmCustomEditor(parent), m_pixmapLabel(new QLabel), m_focusFilter(new QEXTMvvmLostFocusFilter(this))

{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    layout->addWidget(m_pixmapLabel);
    //    layout->addWidget(m_textLabel); // no color name, only color rectangle
    layout->addStretch(1);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);

    setLayout(layout);
}

void QEXTMvvmColorEditor::mousePressEvent(QMouseEvent*)
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);

    auto new_color = QColorDialog::getColor(currentColor());

    removeEventFilter(m_focusFilter);

    if (new_color.isValid()) {
        setDataIntern(new_color);
        update_components();
    }
}

QColor QEXTMvvmColorEditor::currentColor() const
{
    return m_data.value<QColor>();
}

void QEXTMvvmColorEditor::update_components()
{
    if (!QEXTMvvmUtils::IsColorVariant(m_data))
        throw std::runtime_error("ColorEditor::update_components() -> Error. Wrong variant type");

    QPixmap pixmap(QEXTMvvmStyle::DefaultPixmapSize(), QEXTMvvmStyle::DefaultPixmapSize());
    pixmap.fill(currentColor());
    //    m_textLabel->setText(currentColor().name());
    m_pixmapLabel->setPixmap(pixmap);
}
