#include "qextquickpalettetablemodel.h"

QEXTQmlQuickPaletteTableModel::QEXTQmlQuickPaletteTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_quickPalette = QEXTQmlQuickPalette::instance();
}

QVariant QEXTQmlQuickPaletteTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= 0 && index.row() < this->rowCount() && index.column() >= 0 && index.column() < this->columnCount()) {
        if (Qt::DisplayRole == role) {
            return m_quickPalette->materialColor(index.column(), index.row());
        } else if (role == Qt::UserRole) {
            return m_quickPalette->materialDepthTypeName(index.row());
        } else if (role == Qt::UserRole + 1) {
            return index.column();
        } else if (role == Qt::UserRole + 2) {
            return index.row();
        }
    }
    return QVariant();
}

int QEXTQmlQuickPaletteTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QEXTQmlQuickPalette::DepthTypeNum;
}

int QEXTQmlQuickPaletteTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QEXTQmlQuickPalette::ColorTypeNum;
}

QHash<int, QByteArray> QEXTQmlQuickPaletteTableModel::roleNames() const
{
    QHash<int, QByteArray> mapNames;
    mapNames[Qt::DisplayRole] = "colorName";
    mapNames[Qt::UserRole] = "colorDepth";
    mapNames[Qt::UserRole + 1] = "ColumnIndex";
    mapNames[Qt::UserRole + 2] = "RowIndex";
    return mapNames;
}

Qt::ItemFlags QEXTQmlQuickPaletteTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable;
}
