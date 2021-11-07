// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef USERINTERACTOR_H
#define USERINTERACTOR_H

#include <QString>


enum class SaveChangesAnswer;


class QWidget;
class RecentProjectSettings;

//! Provide save/discard/cancel and similar dialogs on user request.
//! Intended to work in pair with QEXTMvvmProjectManagerDecorator.

class UserInteractor
{
public:
    UserInteractor(RecentProjectSettings* settings, QWidget* parent);

    QString onSelectDirRequest();

    QString onCreateDirRequest();

    SaveChangesAnswer onSaveChangesRequest();

private:
    QString getExistingDirectory() const;

    RecentProjectSettings* m_settings{nullptr};
    QWidget* m_parent{nullptr};
};

#endif // USERINTERACTOR_H
