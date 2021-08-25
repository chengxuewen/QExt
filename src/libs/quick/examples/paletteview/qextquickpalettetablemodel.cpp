#include "qextquickpalettetablemodel.h"

QEXTQuickPaletteTableModel::QEXTQuickPaletteTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_quickPalette = QEXTQuickPalette::instance();
}

QVariant QEXTQuickPaletteTableModel::data(const QModelIndex &index, int role) const
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

int QEXTQuickPaletteTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QEXTQuickPalette::DepthTypeNum;
}

int QEXTQuickPaletteTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QEXTQuickPalette::ColorTypeNum;
}

QHash<int, QByteArray> QEXTQuickPaletteTableModel::roleNames() const
{
    QHash<int, QByteArray> mapNames;
    mapNames[Qt::DisplayRole] = "colorName";
    mapNames[Qt::UserRole] = "colorDepth";
    mapNames[Qt::UserRole + 1] = "ColumnIndex";
    mapNames[Qt::UserRole + 2] = "RowIndex";
    return mapNames;
}

Qt::ItemFlags QEXTQuickPaletteTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable;
}
