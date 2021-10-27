#include "qextVisitorTest.h"

#include <CppUTest/CommandLineTestRunner.h>

int main(int ac, char **av)
{
#ifndef QEXT_USE_MEMORYLEAK
    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
#endif
    return CommandLineTestRunner::RunAllTests(ac, av);
}
