/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#ifndef QTKPLUGINDATABASEEXCEPTION_H
#define QTKPLUGINDATABASEEXCEPTION_H

#include "qtkpluginframework_global.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginDatabaseException class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginDatabaseException : public QTKRuntimeException
{
public:
    enum Type {
        Type_Unspecified,
        Type_DBConnectionInvalid,
        Type_DBNotOpenError,
        Type_DBNotFoundError,
        Type_DBCreateDirError,
        Type_DBWriteError,
        Type_DBFileInvalid,
        Type_DBSqlError
    };

    QTKPluginDatabaseException(const QString &strMsg, const Type &eType = Type_Unspecified);
    QTKPluginDatabaseException(const QString &strMsg, const Type &eType, const QTKException &cause);
    QTKPluginDatabaseException(const QString &strMsg, const QTKException &cause);
    QTKPluginDatabaseException(const QTKPluginDatabaseException &other);
    ~QTKPluginDatabaseException() throw();

    QTKPluginDatabaseException& operator=(const QTKPluginDatabaseException &other);

    /**
     * @brief name
     * @return
     * @see QTKException::name()
     */
    const char* name() const throw();

    /**
     * @brief clone
     * @return
     * @see QTKException::clone()
     */
    QTKPluginDatabaseException* clone() const;

    /**
     * @brief rethrow
     * @see QTKException::rethrow()
     */
    void rethrow() const;

    Type getType() const;

private:
    Type m_eType;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINDATABASEEXCEPTION_H
