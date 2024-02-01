#ifndef _QEXTPROPERTYBROWSER_P_H
#define _QEXTPROPERTYBROWSER_P_H

#include <qextPropertyBrowser.h>

#include <QMap>
#include <QIcon>
#include <QLabel>
#include <QWidget>
#include <QCheckBox>
#include <QTreeWidget>
#include <QPushButton>
#include <QStringList>
#include <QItemDelegate>

class QMouseEvent;
class QCheckBox;
class QLineEdit;

class QEXT_WIDGETS_API QExtCursorDatabase
{
public:
    QExtCursorDatabase();
    void clear();

    QStringList cursorShapeNames() const;
    QMap<int, QIcon> cursorShapeIcons() const;
    QString cursorToShapeName(const QCursor &cursor) const;
    QIcon cursorToShapeIcon(const QCursor &cursor) const;
    int cursorToValue(const QCursor &cursor) const;
#ifndef QT_NO_CURSOR
    QCursor valueToCursor(int value) const;
#endif
private:
    void appendCursor(Qt::CursorShape shape, const QString &name, const QIcon &icon);

    QStringList m_cursorNames;
    QMap<int, QIcon> m_cursorIcons;
    QMap<int, Qt::CursorShape> m_valueToCursorShape;
    QMap<Qt::CursorShape, int> m_cursorShapeToValue;
};

class QEXT_WIDGETS_API QExtPropertyBrowserUtils
{
public:
    static QPixmap brushValuePixmap(const QBrush &b);
    static QIcon brushValueIcon(const QBrush &b);
    static QString colorValueText(const QColor &c);
    static QPixmap fontValuePixmap(const QFont &f);
    static QIcon fontValueIcon(const QFont &f);
    static QString fontValueText(const QFont &f);
};

class QEXT_WIDGETS_API QExtBoolEdit : public QWidget
{
    Q_OBJECT
public:
    explicit QExtBoolEdit(QWidget *parent = QEXT_NULLPTR);
    ~QExtBoolEdit() QEXT_OVERRIDE {}

    bool textVisible() const { return m_textVisible; }
    void setTextVisible(bool textVisible);

    Qt::CheckState checkState() const;
    void setCheckState(Qt::CheckState state);

    bool isChecked() const;
    void setChecked(bool c);

    bool blockCheckBoxSignals(bool block);

Q_SIGNALS:
    void toggled(bool);

protected:
    void mousePressEvent(QMouseEvent * event) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;

private:
    QCheckBox *m_checkBox;
    bool m_textVisible;
};

class QEXT_WIDGETS_API QExtKeySequenceEdit : public QWidget
{
    Q_OBJECT
public:
    QExtKeySequenceEdit(QWidget *parent = QEXT_NULLPTR);
    ~QExtKeySequenceEdit() QEXT_OVERRIDE { }

    QKeySequence keySequence() const;
    bool eventFilter(QObject *o, QEvent *e) QEXT_OVERRIDE;

public Q_SLOTS:
    void setKeySequence(const QKeySequence &sequence);

Q_SIGNALS:
    void keySequenceChanged(const QKeySequence &sequence);

protected:
    void focusInEvent(QFocusEvent *e) QEXT_OVERRIDE;
    void focusOutEvent(QFocusEvent *e) QEXT_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) QEXT_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *e) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;
    bool event(QEvent *e) QEXT_OVERRIDE;

private slots:
    void slotClearShortcut();

private:
    void handleKeyEvent(QKeyEvent *e);
    int translateModifiers(Qt::KeyboardModifiers state, const QString &text) const;

    int m_num;
    QKeySequence m_keySequence;
    QLineEdit *m_lineEdit;
};


/***********************************************************************************************************************
** property manager
***********************************************************************************************************************/
class QExtMetaEnumWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSizePolicy::Policy policy READ policy)

public:
    QSizePolicy::Policy policy() const { return QSizePolicy::Ignored; }

private:
    QExtMetaEnumWrapper(QObject *parent) : QObject(parent) {}
    ~QExtMetaEnumWrapper() QEXT_OVERRIDE {}
};


/***********************************************************************************************************************
** editor factory
***********************************************************************************************************************/
class QExtCharEdit : public QWidget
{
    Q_OBJECT
public:
    QExtCharEdit(QWidget *parent = QEXT_NULLPTR);
    ~QExtCharEdit() QEXT_OVERRIDE {}

    QChar value() const;
    bool eventFilter(QObject *o, QEvent *e) QEXT_OVERRIDE;

public Q_SLOTS:
    void setValue(const QChar &value);

Q_SIGNALS:
    void valueChanged(const QChar &value);

protected:
    void focusInEvent(QFocusEvent *e) QEXT_OVERRIDE;
    void focusOutEvent(QFocusEvent *e) QEXT_OVERRIDE;
    void keyPressEvent(QKeyEvent *e) QEXT_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *e) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;
    bool event(QEvent *e) QEXT_OVERRIDE;

private slots:
    void slotClearChar();

private:
    void handleKeyEvent(QKeyEvent *e);

    QChar m_value;
    QLineEdit *m_lineEdit;
};


class QExtColorEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QExtColorEditWidget(QWidget *parent);
    ~QExtColorEditWidget() QEXT_OVERRIDE {}

    bool eventFilter(QObject *obj, QEvent *ev) QEXT_OVERRIDE;

public Q_SLOTS:
    void setValue(const QColor &value);

Q_SIGNALS:
    void valueChanged(const QColor &value);

protected:
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;
    void resizeEvent(QResizeEvent *event) QEXT_OVERRIDE;

private Q_SLOTS:
    void buttonClicked();

private:
    QColor m_color;
    QLabel *m_pixmapLabel;
    QLabel *m_label;
    QToolButton *m_button;
};


class QExtFontEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QExtFontEditWidget(QWidget *parent);
    ~QExtFontEditWidget() QEXT_OVERRIDE {}

    bool eventFilter(QObject *obj, QEvent *ev) QEXT_OVERRIDE;

public Q_SLOTS:
    void setValue(const QFont &value);

Q_SIGNALS:
    void valueChanged(const QFont &value);

protected:
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;
    void resizeEvent(QResizeEvent *event) QEXT_OVERRIDE;

private Q_SLOTS:
    void buttonClicked();

private:
    QFont m_font;
    QLabel *m_pixmapLabel;
    QLabel *m_label;
    QToolButton *m_button;
};


/***********************************************************************************************************************
** tree property browser
***********************************************************************************************************************/
class QExtPropertyEditorView : public QTreeWidget
{
    Q_OBJECT

public:
    explicit QExtPropertyEditorView(QWidget *parent = QEXT_NULLPTR);
    ~QExtPropertyEditorView() QEXT_OVERRIDE {}

    void setEditorPrivate(QExtTreePropertyBrowserPrivate *editorPrivate) { m_editorPrivate = editorPrivate; }
    QTreeWidgetItem *indexToItem(const QModelIndex &index) const { return this->itemFromIndex(index); }

    void paintEvent(QPaintEvent *paintEvent) QEXT_OVERRIDE;

protected:
    void keyPressEvent(QKeyEvent *event) QEXT_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) QEXT_OVERRIDE;
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

private:
    QExtTreePropertyBrowserPrivate *m_editorPrivate;
};

class QExtPropertyEditorDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    QExtPropertyEditorDelegate(QObject *parent = QEXT_NULLPTR)
        : QItemDelegate(parent), m_editorPrivate(0), m_editedItem(0), m_editedWidget(0), m_disablePainting(false)
        , m_itemMinimumHeight(-1)
    {}
    ~QExtPropertyEditorDelegate() QEXT_OVERRIDE {}

    void setEditorPrivate(QExtTreePropertyBrowserPrivate *editorPrivate) { m_editorPrivate = editorPrivate; }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const QEXT_OVERRIDE {}

    void setEditorData(QWidget *, const QModelIndex &) const QEXT_OVERRIDE {}

    bool eventFilter(QObject *object, QEvent *event) QEXT_OVERRIDE;

    void closeEditor(QExtProperty *property);

    QTreeWidgetItem *editedItem() const { return m_editedItem; }

    int itemMinimumHeight() const { return m_itemMinimumHeight; }
    void setItemMinimumHeight(int height) { m_itemMinimumHeight = height; }

protected:
    void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                        const QRect &rect, const QPixmap &pixmap) const QEXT_OVERRIDE;
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                     const QRect &rect, const QString &text) const QEXT_OVERRIDE;

private slots:
    void slotEditorDestroyed(QObject *object);

private:
    int indentation(const QModelIndex &index) const;

    typedef QMap<QWidget *, QExtProperty *> EditorToPropertyMap;
    mutable EditorToPropertyMap m_editorToProperty;

    typedef QMap<QExtProperty *, QWidget *> PropertyToEditorMap;
    mutable PropertyToEditorMap m_propertyToEditor;
    QExtTreePropertyBrowserPrivate *m_editorPrivate;
    mutable QTreeWidgetItem *m_editedItem;
    mutable QWidget *m_editedWidget;
    mutable bool m_disablePainting;
    int m_itemMinimumHeight;
};


#endif // _QEXTPROPERTYBROWSER_P_H
