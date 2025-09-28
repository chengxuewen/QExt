#include "palettetablemodel.h"
#include <qextQmlThemeManager.h>

PaletteTableModel::PaletteTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    mPalette = QExtQmlThemeManager::instance()->palette();
}

QVariant PaletteTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= 0 && index.row() < this->rowCount() && index.column() >= 0 && index.column() < this->columnCount()) {
        if (Qt::DisplayRole == role) {
            return mPalette->materialColor(index.column(), index.row());
        } else if (role == Qt::UserRole) {
            return mPalette->materialDepthTypeName(index.row());
        } else if (role == Qt::UserRole + 1) {
            return index.column();
        } else if (role == Qt::UserRole + 2) {
            return index.row();
        }
    }
    return QVariant();
}

int PaletteTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QExtQmlThemePalette::DepthEnumCount;
}

int PaletteTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QExtQmlThemePalette::ColorEnumCount;
}

QHash<int, QByteArray> PaletteTableModel::roleNames() const
{
    QHash<int, QByteArray> mapNames;
    mapNames[Qt::DisplayRole] = "colorName";
    mapNames[Qt::UserRole] = "colorDepth";
    mapNames[Qt::UserRole + 1] = "ColumnIndex";
    mapNames[Qt::UserRole + 2] = "RowIndex";
    return mapNames;
}

Qt::ItemFlags PaletteTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable;
}
