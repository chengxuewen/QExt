#include <QApplication>
#include <QTreeView>

#include <cfMvvmModel.h>
#include <cfMvvmItemMapper.h>
#include <cfMvvmCompoundItem.h>
#include <cfMvvmUtils.h>

#include <cfMvvmQtViewModel.h>
#include <cfMvvmQtDefaultViewModel.h>
#include <cfMvvmQtViewModelDelegate.h>

#include <cfPointerFunctor.h>
#include <cfLog.h>

#include <string>

CF_USE_NAMESPACE

void onItemPropertyChanged(CFMvvmItem *item, const std::string &name)
{
    if (name == "Hello")
    {
        item->setProperty("Your answer is", item->property<std::string>("Hello") == "World!");
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CFMvvmModel model;
    CFMvvmCompoundItem *item = model.insertItem<CFMvvmCompoundItem>();
    item->setDisplayName("Item");
    item->addProperty("Hello", "World!");
    item->addProperty("Your answer is", true);
    item->addProperty("test", 1.2);

    CFMvvmItem *item1 = model.insertItem<CFMvvmItem>();
    item1->setDisplayName("Item1");

    CFSlot<void, CFMvvmItem *, std::string> slot = cfPointerFunctor(&onItemPropertyChanged);
    item->mapper()->setOnPropertyChange(slot);

    CFMvvmQtDefaultViewModel viewmodel(&model);
    CFMvvmQtViewModelDelegate delegate;

    QTreeView view;
    view.setModel(&viewmodel);
//    view.setItemDelegate(&delegate);
    view.show();

    return app.exec();
}
