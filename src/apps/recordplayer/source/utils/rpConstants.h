#ifndef _RPCONSTANTS_H
#define _RPCONSTANTS_H

#include <QString>

namespace RPConstants
{

/*serttings group*/
constexpr char SETTINGS_GROUP_PLOTS[] = "Plots";
constexpr char SETTINGS_GROUP_THEMES[] = "Themes";
constexpr char SETTINGS_GROUP_IODEVICE[] = "IODevice";
constexpr char SETTINGS_GROUP_LANGUAGES[] = "Languages";
constexpr char SETTINGS_GROUP_KEYBOARDS[] = "Keyboards";
constexpr char SETTINGS_GROUP_MAINWINDOW[] = "MainWindow";

constexpr char SETTINGS_KEY_IOTRANSCEIVER_IODEVICE[] = "IODevice";
// constexpr char SETTINGS_KEY_STYLETHEME[] = "StyleTheme";


/*settings key*/
constexpr char SETTINGS_KEY_VERSION[] = "Version";

constexpr char SETTINGS_KEY_LANGUAGETYPE[] = "LanguageType";
constexpr char SETTINGS_KEY_KEYBOARD_ENABLE[] = "KeyboardEnable";

// constexpr char SETTINGS_KEY_THEMETYPE[] = "ThemeEnum";

// constexpr char SETTINGS_KEY_REPORTDIALOG_GEOMETRY[] = "ReportDialogGeometry";

constexpr char SETTINGS_KEY_MAINWINDOW_GEOMETRY[] = "MainWindowGeometry";
constexpr char SETTINGS_KEY_MAINWINDOW_STATE[] = "MainWindowState";

}

#endif // _RPCONSTANTS_H
