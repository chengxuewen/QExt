// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemConverterFactory.h>
#include <qextMvvmJsonItemTypes.h>
#include <qextMvvmJsonItemConverter.h>

namespace ModelView
{

//! Creates JSON item converter intended for item cloning.
//! Saves full deep copy of item to JSON. When restoring from JSON, reconstruct everything,
//! including item's unique ID. Used for backup.

std::unique_ptr<QEXTMvvmJsonItemConverterInterface>
CreateItemCloneConverter(const QEXTMvvmItemFactoryInterface* item_factory)
{
    QEXTMvvmConverterContext context;
    context.m_factory = item_factory;
    context.m_mode = ConverterMode::clone;
    return make_unique<QEXTMvvmJsonItemConverter>(context);
}

//! Creates JSON item converter intended for item copying.
//! Saves full deep copy of item to JSON. When restoring from JSON, will regenerate item's ID
//! to make it unique. Used for copying of item together with its children.

std::unique_ptr<QEXTMvvmJsonItemConverterInterface>
CreateItemCopyConverter(const QEXTMvvmItemFactoryInterface* item_factory)
{
    QEXTMvvmConverterContext context;
    context.m_factory = item_factory;
    context.m_mode = ConverterMode::copy;
    return make_unique<QEXTMvvmJsonItemConverter>(context);
}

//! Creates JSON item converter intended for saving on disk.
//! When saving on disk:
//! + Only selected data roles of items are saved (i.e. DATA, IDENTIFIER)
//! + All tags with its content are saved as usual
//! When loading from disk:
//! + Only selected roles are taken from JSON (i.e. DATA, IDENTIFIER), other roles (e.g. TOOLTIPS)
//!   are taken from memory.
//! + Property tags are updated, universal tags reconstructed.

std::unique_ptr<QEXTMvvmJsonItemConverterInterface>
CreateItemProjectConverter(const QEXTMvvmItemFactoryInterface* item_factory)
{
    QEXTMvvmConverterContext context;
    context.m_factory = item_factory;
    context.m_mode = ConverterMode::project;
    return make_unique<QEXTMvvmJsonItemConverter>(context);
}

} // namespace ModelView
