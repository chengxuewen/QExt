/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#include "qextVLCTrackModel.h"

QEXTVLCTrackModel::QEXTVLCTrackModel(QObject *parent)
    : QAbstractListModel(parent) {}

QEXTVLCTrackModel::QEXTVLCTrackModel(const QMap<int, QString> &tracks,
                             QObject *parent)
    : QAbstractListModel(parent),
      m_tracksMap(tracks) {}

QEXTVLCTrackModel::QEXTVLCTrackModel(const QEXTVLCTrackModel &other)
{
    m_tracksMap = other.m_tracksMap;
}

int QEXTVLCTrackModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_tracksMap.count();
}

QHash<int, QByteArray> QEXTVLCTrackModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, "id");
    roles.insert(TitleRole, "title");
    return roles;
}

QVariant QEXTVLCTrackModel::data(const QModelIndex &index,
                             int role) const
{
    if (!index.isValid())
        return QVariant();

    return data(index.row(), role);
}

QVariant QEXTVLCTrackModel::data(const int row,
                             int role) const
{
    if (row > (m_tracksMap.count() - 1))
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case TitleRole:
        return QVariant::fromValue(m_tracksMap.value(m_tracksMap.keys().at(row)));
    case IdRole:
        return QVariant::fromValue(m_tracksMap.keys().at(row));
    case Qt::DecorationRole:
    default:
        return QVariant();
    }
}

void QEXTVLCTrackModel::clear()
{
    if (!m_tracksMap.count())
        return;

    beginRemoveRows(QModelIndex(), 0, m_tracksMap.count() - 1);
    m_tracksMap.clear();
    endRemoveRows();
    emit countChanged();
}

void QEXTVLCTrackModel::load(const QMap<int, QString> &data)
{
    QMapIterator<int, QString> i(data);
    while (i.hasNext()) {
        i.next();
        insert(i.key(), i.value());
    }
}

void QEXTVLCTrackModel::insert(const int id,
                           const QString &title)
{
    beginInsertRows(QModelIndex(), m_tracksMap.size(), m_tracksMap.size());
    m_tracksMap.insert(id, title);
    endInsertRows();
    emit countChanged();
}

int QEXTVLCTrackModel::count() const
{
    return rowCount(QModelIndex());
}
