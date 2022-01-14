// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QLocale>
#include <QTreeView>

#include <qextMvvmCompoundItem.h>
#include <qextMvvmPropertyItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmItemMapper.h>
#include <viewmodel/qextMvvmDefaultViewModel.h>
#include <viewmodel/qextMvvmViewModelDelegate.h>

using namespace ModelView;

int main(int argc, char** argv)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    QApplication app(argc, argv);

    QEXTMvvmSessionModel model;
    auto item = model.insertItem<QEXTMvvmCompoundItem>();
    item->setDisplayName("Item");

    item->addProperty("Hello", "World!");
    item->addProperty("Your answer is", true);

    auto on_property = [](QEXTMvvmSessionItem* item, const std::string& name) {
        if (name == "Hello")
            item->setProperty("Your answer is", item->property<std::string>("Hello") == "World!");
    };
    item->mapper()->setOnPropertyChange(on_property, nullptr);

    QEXTMvvmDefaultViewModel viewmodel(&model);
    QEXTMvvmViewModelDelegate delegate;

    QTreeView view;
    view.setModel(&viewmodel);
    view.setItemDelegate(&delegate);
    view.show();

    return app.exec();
}
