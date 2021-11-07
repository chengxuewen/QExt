#include "userinteractor.h"
#include "recentprojectsettings.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMap>
#include <qextMvvmProjectTypes.h>
#include <qextMvvmProjectUtils.h>
#include <qextMvvmUtils.h>


namespace
{
//! Map of standard Qt answers to what QEXTMvvmProjectManager expects.
QMap<QMessageBox::StandardButton, SaveChangesAnswer> answer_map()
{
    QMap<QMessageBox::StandardButton, SaveChangesAnswer> result = {
        {QMessageBox::Save, SaveChangesAnswer::SAVE},
        {QMessageBox::Discard, SaveChangesAnswer::DISCARD},
        {QMessageBox::Cancel, SaveChangesAnswer::CANCEL}};
    return result;
}
} // namespace

UserInteractor::UserInteractor(RecentProjectSettings* settings, QWidget* parent)
    : m_settings(settings), m_parent(parent)
{
}

//! Returns directory on disk selected by the user via QFileDialog.
//! Checks if selected directory can be the project directory.

QString UserInteractor::onSelectDirRequest()
{
    auto dirname = getExistingDirectory();

    if (dirname.isEmpty()) // no valid selection
        return {};

    if (!ProjectUtils::IsPossibleProjectDir(dirname)) {
        QMessageBox msgBox;
        msgBox.setText(
            "Selected directory doesn't look like a project directory, choose another one");
        msgBox.exec();
        return {};
    }

    return dirname;
}

//! Returns new directory on disk created by the user via QFileDialog.

QString UserInteractor::onCreateDirRequest()

{
    auto dirname = getExistingDirectory();

    if (dirname.isEmpty()) // no valid selection
        return {};

    if (!QEXTMvvmUtils::isEmpty(dirname)) {
        QMessageBox msgBox;
        msgBox.setText("The selected directory is not empty, choose another one.");
        msgBox.exec();
        return {};
    }

    return dirname;
}

//! Returns save/cancel/discard changes choice provided by the user.

SaveChangesAnswer UserInteractor::onSaveChangesRequest()
{
    static auto translate = answer_map();

    QMessageBox msgBox;
    msgBox.setText("The project has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    auto ret = static_cast<QMessageBox::StandardButton>(msgBox.exec());
    return translate[ret];
}

//! Summon dialog to select directory on disk. If selection is not empty,
//! save parent directory for later re-use.

QString UserInteractor::getExistingDirectory() const
{
    QString dirname = QFileDialog::getExistingDirectory(
        m_parent, "Select directory", m_settings->currentWorkdir(),
        QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly);

    if (!dirname.isEmpty())
        m_settings->updateWorkdirFromSelection(dirname);

    return dirname;
}
