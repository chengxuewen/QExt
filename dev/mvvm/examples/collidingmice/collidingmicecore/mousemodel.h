// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef COLLIDINGMICECORE_MOUSEMODEL_H
#define COLLIDINGMICECORE_MOUSEMODEL_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmSessionModel.h>

//! Domain object to hold mouse info.

class MouseItem : public ModelView::QExtMvvmCompoundItem {
public:
    static constexpr const char *P_COLOR = "P_COLOR";
    static constexpr const char *P_XPOS = "P_XPOS";
    static constexpr const char *P_YPOS = "P_YPOS";
    static constexpr const char *P_ANGLE = "P_ANGLE";
    static constexpr const char *P_SPEED = "P_SPEED";

    MouseItem();
};

//! Holds collection of mice.

class MouseModel : public ModelView::QExtMvvmSessionModel {
public:
    MouseModel();

    void loadFromFile(const QString& name);

    void saveToFile(const QString& name);

    //! Sets undo stack to given position.
    //! value=0   - first command in the stack (corresponds to the model status "in the past")
    //! value=100 - last command in the stack (corresponds to the status "now")
    void setUndoPosition(int value);

private:
    void populateModel();
};

#endif // COLLIDINGMICECORE_MOUSEMODEL_H
