/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "qextVLCModuleDescription.h"

QEXTVLCModuleDescription::QEXTVLCModuleDescription(Type type,
                                           const QString &name)
    : m_type(type),
      m_name(name) {}

QEXTVLCModuleDescription::~QEXTVLCModuleDescription() {} // LCOV_EXCL_LINE

void QEXTVLCModuleDescription::setShortName(const QString &name)
{
    if (m_shortName != name) {
        m_shortName = name;
    }
}

void QEXTVLCModuleDescription::setLongName(const QString &name)
{
    if (m_longName != name) {
        m_longName = name;
    }
}

void QEXTVLCModuleDescription::setHelp(const QString &help)
{
    if (m_help != help) {
        m_help = help;
    }
}
