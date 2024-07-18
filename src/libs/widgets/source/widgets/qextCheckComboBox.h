#ifndef _QEXTCHECKCOMBOBOX_H
#define _QEXTCHECKCOMBOBOX_H

#include <qextWidgetGlobal.h>

#include <QLineEdit>
#include <QComboBox>
#include <QAbstractListModel>

class QExtCheckComboBoxModelPrivate;
class QExtCheckComboBoxModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QExtCheckComboBoxModel(QObject *parent = QEXT_NULLPTR);
    ~QExtCheckComboBoxModel() QEXT_OVERRIDE;

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void removeItem(const QString &text);

    QStringList checkedItems() const;

    bool isItemChecked(const QString &text) const;
    void setItemChecked(const QString &text, bool checked = false);

    QStringList checkLockItems() const;
    void removeCheckLockItem(const QString &text);
    void appendCheckLockItem(const QString &text);
    void setCheckLockItems(const QStringList &texts);

protected:
    QScopedPointer<QExtCheckComboBoxModelPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtCheckComboBoxModel)
    QEXT_DISABLE_COPY_MOVE(QExtCheckComboBoxModel)
};

class QExtCheckComboBoxLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    QExtCheckComboBoxLineEdit(QWidget *parent = QEXT_NULLPTR) : QLineEdit(parent) {}
    ~QExtCheckComboBoxLineEdit() QEXT_OVERRIDE {}

Q_SIGNALS:
    void mousePressed();
    void mouseRelease();

protected:
    void mousePressEvent(QMouseEvent *event) QEXT_OVERRIDE
    {
        emit this->mousePressed();
        QLineEdit::mousePressEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent *event) QEXT_OVERRIDE
    {
        emit this->mouseRelease();
        QLineEdit::mouseReleaseEvent(event);
    }
};

class QExtCheckComboBoxPrivate;
class QEXT_WIDGETS_API QExtCheckComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit QExtCheckComboBox(QWidget *parent = QEXT_NULLPTR);
    ~QExtCheckComboBox() QEXT_OVERRIDE;

    QStringList checkLockItems() const;
    void removeCheckLockItem(const QString &text);
    void appendCheckLockItem(const QString &text);
    void setCheckLockItems(const QStringList &texts);

    QStringList checkedItems() const;
    void setCheckedItems(const QStringList &texts);

    bool isItemChecked(const QString &text);
    void setItemChecked(const QString &text, bool checked);

    void addItems(const QStringList &texts);
    void addItem(const QString &text, bool checked = false);

public Q_SLOTS:
    void hidePopup() QEXT_OVERRIDE;
    void showPopup() QEXT_OVERRIDE;

protected:
    void setModel(QAbstractItemModel *model);
    void setView(QAbstractItemView *itemView);

    bool eventFilter(QObject *watched, QEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtCheckComboBoxPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtCheckComboBox)
    QEXT_DISABLE_COPY_MOVE(QExtCheckComboBox)
};

#endif // _QEXTCHECKCOMBOBOX_H
