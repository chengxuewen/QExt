/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#ifndef _QEXTOSGIPLUGINDATABASEEXCEPTION_H
#define _QEXTOSGIPLUGINDATABASEEXCEPTION_H

#include <qextException.h>
#include <qextOsgiGlobal.h>

/**
 * \ingroup PluginFramework
 */
class QEXT_OSGI_API QExtOsgiPluginDatabaseException : public QExtRuntimeException
{
public:

    enum Type {
        UNSPECIFIED,
        DB_CONNECTION_INVALID,
        DB_NOT_OPEN_ERROR,
        DB_NOT_FOUND_ERROR,
        DB_CREATE_DIR_ERROR,
        DB_WRITE_ERROR,
        DB_FILE_INVALID,
        DB_SQL_ERROR
    };

    QExtOsgiPluginDatabaseException(const QString& msg, const Type& type = UNSPECIFIED);
    QExtOsgiPluginDatabaseException(const QString& msg, const Type& type, const QExtException& cause);
    QExtOsgiPluginDatabaseException(const QString& msg, const QExtException& cause);

    QExtOsgiPluginDatabaseException(const QExtOsgiPluginDatabaseException& o);
    QExtOsgiPluginDatabaseException& operator=(const QExtOsgiPluginDatabaseException& o);

    ~QExtOsgiPluginDatabaseException() throw();

    /**
   * @see QExtException::name()
   */
    const char* name() const throw();

    /**
   * @see QExtException::clone()
   */
    QExtOsgiPluginDatabaseException* clone() const;

    /**
   * @see QExtException::rethrow()
   */
    void rethrow() const;

    Type getType() const;

private:

    Type type;

};

#endif // _QEXTOSGIPLUGINDATABASEEXCEPTION_H
