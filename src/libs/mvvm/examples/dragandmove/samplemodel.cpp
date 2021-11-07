// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"
#include <QColor>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmUtils.h>
#include <qextMvvmWidgetUtils.h>

namespace DragAndView
{

    namespace
    {
        QEXTMvvmItemCatalogue *qextMvvmCreateToyItemCatalogue()
        {
            QEXTMvvmItemCatalogue *result = new QEXTMvvmItemCatalogue;
            result->registerItem<DemoItem>();
            result->registerItem<DemoContainerItem>();
            return result;
        }

        QString random_name()
        {
            static const QString alphabet = "abcdefgh";
            const size_t len(3);

            QString result;
            for (size_t i = 0; i < len; ++i)
            {
                int randomIndex = QEXTMvvmUtils::RandInt(0, static_cast<int>(alphabet.size() - 1));
                result.append(alphabet[randomIndex]);
            }

            return result;
        }
    } // namespace

    SampleModel::SampleModel() : QEXTMvvmModel("SampleModel")
    {
        setItemCatalogue(qextMvvmCreateToyItemCatalogue());
        init_model_content();
        setUndoRedoEnabled(true);
    }

    void SampleModel::append_random_item(QEXTMvvmItem *container)
    {
        auto item = insertItem<DemoItem>(container);
        item->setProperty(DemoItem::P_COLOR_PROPERTY, QEXTMvvmWidgetUtils::RandomColor());
        item->setProperty(DemoItem::P_STRING_PROPERTY, random_name());
        item->setProperty(DemoItem::P_INTEGER_PROPERTY, QEXTMvvmUtils::RandInt(0, 10));
    }

//! Generates initial model content.

    void SampleModel::init_model_content()
    {
        auto container = insertItem<DemoContainerItem>();
        append_random_item(container);
        append_random_item(container);
        append_random_item(container);

        container = insertItem<DemoContainerItem>();
        append_random_item(container);
        append_random_item(container);
    }

} // namespace DragAndView
