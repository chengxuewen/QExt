########################################################################################################################
#
# Library: QExt
#
# Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
#
# License: MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
# to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
########################################################################################################################


#-----------------------------------------------------------------------------------------------------------------------
# Add lib link libraries
#-----------------------------------------------------------------------------------------------------------------------
set(QEXT_LIB_LINK_LIBRARIES)
set(QEXT_LIB_NAME Logging)

if(QEXT_QT_VERSION_MAJOR EQUAL 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES Qt4::QtCore)
elseif(QEXT_QT_VERSION_MAJOR GREATER 4)
    list(APPEND QEXT_LIB_LINK_LIBRARIES
        Qt${QEXT_QT_VERSION_MAJOR}::Core
        Qt${QEXT_QT_VERSION_MAJOR}::Concurrent)
else()
    message(FATAL_ERROR "Not find Qt package")
endif()

list(APPEND QEXT_LIB_LINK_LIBRARIES QExt::Core QExt::CorePrivate)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib target
#-----------------------------------------------------------------------------------------------------------------------
qext_add_library(${QEXT_LIB_NAME}
    EXCEPTIONS
    SOURCES
    source/qextLogging.cpp
    source/qextLogging.h
    source/qextLoggingGlobal.h
    source/appender/qextLogAppender.cpp
    source/appender/qextLogAppender.h
    source/appender/qextLogAppenderAttachable.cpp
    source/appender/qextLogAppenderAttachable.h
    source/appender/qextLogAppenderSkeleton.cpp
    source/appender/qextLogAppenderSkeleton.h
    source/appender/qextLogAsyncAppender.cpp
    source/appender/qextLogAsyncAppender.h
    source/appender/qextLogBinaryFileAppender.cpp
    source/appender/qextLogBinaryFileAppender.h
    source/appender/qextLogBinaryWriterAppender.cpp
    source/appender/qextLogBinaryWriterAppender.h
    source/appender/qextLogConsoleAppender.cpp
    source/appender/qextLogConsoleAppender.h
    source/appender/qextLogDailyFileAppender.cpp
    source/appender/qextLogDailyFileAppender.h
    source/appender/qextLogDailyRollingFileAppender.cpp
    source/appender/qextLogDailyRollingFileAppender.h
    source/appender/qextLogDebugAppender.cpp
    source/appender/qextLogDebugAppender.h
    source/appender/qextLogFileAppender.cpp
    source/appender/qextLogFileAppender.h
    source/appender/qextLogListAppender.cpp
    source/appender/qextLogListAppender.h
    source/appender/qextLogMainThreadAppender.cpp
    source/appender/qextLogMainThreadAppender.h
    source/appender/qextLogNullAppender.cpp
    source/appender/qextLogNullAppender.h
    source/appender/qextLogRollingBinaryFileAppender.cpp
    source/appender/qextLogRollingBinaryFileAppender.h
    source/appender/qextLogRollingFileAppender.cpp
    source/appender/qextLogRollingFileAppender.h
    source/appender/qextLogSignalAppender.cpp
    source/appender/qextLogSignalAppender.h
    source/appender/qextLogSyslogAppender.cpp
    source/appender/qextLogSyslogAppender.h
    source/appender/qextLogWriterAppender.cpp
    source/appender/qextLogWriterAppender.h
    source/filter/qextLogBinaryEventFilter.cpp
    source/filter/qextLogBinaryEventFilter.h
    source/filter/qextLogDenyAllFilter.cpp
    source/filter/qextLogDenyAllFilter.h
    source/filter/qextLogFilter.cpp
    source/filter/qextLogFilter.h
    source/filter/qextLogLevelMatchFilter.cpp
    source/filter/qextLogLevelMatchFilter.h
    source/filter/qextLogLevelRangeFilter.cpp
    source/filter/qextLogLevelRangeFilter.h
    source/filter/qextLogStringMatchFilter.cpp
    source/filter/qextLogStringMatchFilter.h
    source/layout/qextLogBinaryLayout.cpp
    source/layout/qextLogBinaryLayout.h
    source/layout/qextLogBinaryToTextLayout.cpp
    source/layout/qextLogBinaryToTextLayout.h
    source/layout/qextLogLayout.cpp
    source/layout/qextLogLayout.h
    source/layout/qextLogPatternLayout.cpp
    source/layout/qextLogPatternLayout.h
    source/layout/qextLogSimpleLayout.cpp
    source/layout/qextLogSimpleLayout.h
    source/layout/qextLogSimpleTimeLayout.cpp
    source/layout/qextLogSimpleTimeLayout.h
    source/layout/qextLogTTCCLayout.cpp
    source/layout/qextLogTTCCLayout.h
    source/layout/qextLogXMLLayout.cpp
    source/layout/qextLogXMLLayout.h
    source/logger/qextLogBinaryClassLogger.cpp
    source/logger/qextLogBinaryClassLogger.h
    source/logger/qextLogBinaryLogger.cpp
    source/logger/qextLogBinaryLogger.h
    source/logger/qextLogClassLogger.cpp
    source/logger/qextLogClassLogger.h
    source/logger/qextLogger.cpp
    source/logger/qextLogger.h
    source/logger/qextLoggerRepository.cpp
    source/logger/qextLoggerRepository.h
    source/logger/qextQMLLogger.cpp
    source/logger/qextQMLLogger.h
    source/qextBinaryLoggingEvent.cpp
    source/qextBinaryLoggingEvent.h
    source/qextBinaryLogStream.cpp
    source/qextBinaryLogStream.h
    source/qextLogBasicConfigurator.cpp
    source/qextLogBasicConfigurator.h
    source/qextLogConfiguratorHelper.cpp
    source/qextLogConfiguratorHelper.h
    source/qextLogDateTime.cpp
    source/qextLogDatetime.h
    source/qextLogDispatcher.cpp
    source/qextLogDispatcher.h
    source/qextLogError.cpp
    source/qextLogError.h
    source/qextLogFactory.cpp
    source/qextLogFactory.h
    source/qextLogging.cpp
    source/qextLogging.h
    source/qextLoggingEvent.cpp
    source/qextLoggingEvent.h
    source/qextLoggingGlobal.h
    source/qextLogHierarchy.cpp
    source/qextLogHierarchy.h
    source/qextLogInitialisationHelper.cpp
    source/qextLogInitialisationHelper.h
    source/qextLogLevel.cpp
    source/qextLogLevel.h
    source/qextLogManager.cpp
    source/qextLogManager.h
    source/qextLogMDC.cpp
    source/qextLogMDC.h
    source/qextLogNDC.cpp
    source/qextLogNDC.h
    source/qextLogOptionConverter.cpp
    source/qextLogOptionConverter.h
    source/qextLogPatternFormatter.cpp
    source/qextLogPatternFormatter.h
    source/qextLogProperties.cpp
    source/qextLogProperties.h
    source/qextLogPropertyConfigurator.cpp
    source/qextLogPropertyConfigurator.h
    source/qextLogStream.cpp
    source/qextLogStream.h
    source/qextObjectSharedPointer.h
    resources/qextLogging.qrc
    PRECOMPILED_HEADER
    source/qextLoggingPch.h
    INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_SOURCE_DIR}/source/appender
    ${CMAKE_CURRENT_SOURCE_DIR}/source/filter
    ${CMAKE_CURRENT_SOURCE_DIR}/source/layout
    ${CMAKE_CURRENT_SOURCE_DIR}/source/logger
    PUBLIC_LIBRARIES
    ${QEXT_LIB_LINK_LIBRARIES})
qext_internal_extend_target(${QEXT_LIB_NAME}
    SOURCES
    source/appender/qextLogColorConsoleAppender.cpp
    source/appender/qextLogColorConsoleAppender.h
    source/appender/qextLogWDCAppender.cpp
    source/appender/qextLogWDCAppender.h
    CONDITION WIN32)
qext_internal_extend_target(${QEXT_LIB_NAME}
    SOURCES
    source/appender/qextLogDatabaseAppender.cpp
    source/appender/qextLogDatabaseAppender.h
    source/layout/qextLogDatabaseLayout.cpp
    source/layout/qextLogDatabaseLayout.h
    PUBLIC_LIBRARIES
    Qt${QEXT_QT_VERSION_MAJOR}::Sql
    CONDITION QEXT_FEATURE_USE_LOGGING_DATABASE)
qext_internal_extend_target(${QEXT_LIB_NAME}
    SOURCES
    source/appender/qextLogTelnetAppender.cpp
    source/appender/qextLogTelnetAppender.h
    PUBLIC_LIBRARIES
    Qt${QEXT_QT_VERSION_MAJOR}::Network
    CONDITION QEXT_FEATURE_USE_LOGGING_TELNET)


#-----------------------------------------------------------------------------------------------------------------------
# Add lib examples and tests
#-----------------------------------------------------------------------------------------------------------------------
qext_add_subdirectory(examples QEXT_BUILD_EXAMPLES)
qext_add_subdirectory(tests QEXT_BUILD_TESTS)
