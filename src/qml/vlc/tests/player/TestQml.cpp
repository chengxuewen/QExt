#include <QtQuickTest/quicktest.h>

#include <qextQmlVLCLoader.h>

#include <qextQmlVLCTestConfig.h>

#ifndef QEXT_BUILD_SHARED_LIBS
#include <QtPlugin>
Q_IMPORT_PLUGIN(QEXTQmlVLC)
#endif

//QUICK_TEST_MAIN(player)
int main(int argc, char **argv)
{
//    QTEST_ADD_GPU_BLACKLIST_SUPPORT
//    QTEST_SET_MAIN_SOURCE_PATH
    return quick_test_main(argc, argv, "player", TEST_SOURCE_DIRS);
}
