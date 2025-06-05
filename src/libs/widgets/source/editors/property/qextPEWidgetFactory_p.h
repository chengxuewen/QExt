#ifndef _QEXTPEWIDGETFACTORY_P_H
#define _QEXTPEWIDGETFACTORY_P_H

#include <qextPEWidgetFactory.h>

#include <QLabel>
#include <QLayout>
#include <QSlider>
#include <QSpinBox>
#include <QListView>
#include <QComboBox>
#include <QScroller>
#include <QDateEdit>
#include <QCheckBox>
#include <QScrollBar>
#include <QApplication>
#include <QDoubleSpinBox>

/***********************************************************************************************************************
** qteditorfactory
***********************************************************************************************************************/

// Set a hard coded left margin to account for the indentation of the tree view icon when switching to an editor
static inline void setupTreeViewEditorMargin(QLayout *lt)
{
    enum { DecorationMargin = 4 };
    if (QApplication::layoutDirection() == Qt::LeftToRight)
    {
        lt->setContentsMargins(DecorationMargin, 0, 0, 0);
    }
    else
    {
        lt->setContentsMargins(0, 0, DecorationMargin, 0);
    }
}

// ---------- EditorFactoryPrivate :
// Base class for editor factory private classes. Manages mapping of properties to editors and vice versa.
template <class Editor>
class EditorFactoryPrivate
{
public:
    typedef QList<Editor *> EditorList;
    typedef QMap<QExtPEProperty *, EditorList> PropertyToEditorListMap;
    typedef QMap<Editor *, QExtPEProperty *> EditorToPropertyMap;

    Editor *createEditor(QExtPEProperty *property, QWidget *parent);
    void initializeEditor(QExtPEProperty *property, Editor *e);
    void slotEditorDestroyed(QObject *object);

    PropertyToEditorListMap  m_createdEditors;
    EditorToPropertyMap m_editorToProperty;
};

template <class Editor>
Editor *EditorFactoryPrivate<Editor>::createEditor(QExtPEProperty *property, QWidget *parent)
{
    Editor *editor = new Editor(parent);
    this->initializeEditor(property, editor);
    return editor;
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeEditor(QExtPEProperty *property, Editor *editor)
{
    typename PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
    {
        it = m_createdEditors.insert(property, EditorList());
    }
    it.value().append(editor);
    m_editorToProperty.insert(editor, property);
    // set scroller
    const QString className = editor->metaObject()->className();
    QObject *scrollerTarget = QEXT_NULLPTR;
    if (className == "QComboBox")
    {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox && !comboBox->view())
        {
            comboBox->setView(new QListView(comboBox));
        }
        scrollerTarget = comboBox->view();
    }
    if (scrollerTarget)
    {
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
        QScroller::scroller(scrollerTarget)->grabGesture(scrollerTarget, QScroller::LeftMouseButtonGesture);
#else
        QExtScroller::scroller(scrollerTarget)->grabGesture(scrollerTarget, QExtScroller::LeftMouseButtonGesture);
#endif
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotEditorDestroyed(QObject *object)
{
    typename EditorToPropertyMap::iterator itEditor;
    const typename EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
    for (itEditor = m_editorToProperty.begin(); itEditor !=  ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            Editor *editor = itEditor.key();
            QExtPEProperty *property = itEditor.value();
            const typename PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
            if (pit != m_createdEditors.end())
            {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                {
                    m_createdEditors.erase(pit);
                }
            }
            m_editorToProperty.erase(itEditor);
            return;
        }
    }
}


// ------------ QExtPESpinBoxFactory

class QExtPESpinBoxFactoryPrivate : public EditorFactoryPrivate<QSpinBox>
{
    QExtPESpinBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPESpinBoxFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, int value);
    void slotRangeChanged(QExtPEProperty *property, int min, int max);
    void slotSingleStepChanged(QExtPEProperty *property, int step);
    void slotReadOnlyChanged(QExtPEProperty *property, bool readOnly);
    void slotSetValue(int value);
};

// QExtPESliderFactory
class QExtPESliderFactoryPrivate : public EditorFactoryPrivate<QSlider>
{
    QExtPESliderFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPESliderFactory)
public:
    void slotPropertyChanged(QExtPEProperty *property, int value);
    void slotRangeChanged(QExtPEProperty *property, int min, int max);
    void slotSingleStepChanged(QExtPEProperty *property, int step);
    void slotSetValue(int value);
};

// QExtPESliderFactory
class QExtPEScrollBarFactoryPrivate : public  EditorFactoryPrivate<QScrollBar>
{
    QExtPEScrollBarFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEScrollBarFactory)
public:
    void slotPropertyChanged(QExtPEProperty *property, int value);
    void slotRangeChanged(QExtPEProperty *property, int min, int max);
    void slotSingleStepChanged(QExtPEProperty *property, int step);
    void slotSetValue(int value);
};


// QExtBoolEdit
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
// QExtPECheckBoxFactory
class QExtPECheckBoxFactoryPrivate : public EditorFactoryPrivate<QExtBoolEdit>
{
    QExtPECheckBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPECheckBoxFactory)
public:
    void slotPropertyChanged(QExtPEProperty *property, bool value);
    void slotTextVisibleChanged(QExtPEProperty *property, bool textVisible);
    void slotSetValue(bool value);
};

// QExtPEDoubleSpinBoxFactory
class QExtPEDoubleSpinBoxFactoryPrivate : public EditorFactoryPrivate<QDoubleSpinBox>
{
    QExtPEDoubleSpinBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEDoubleSpinBoxFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, double value);
    void slotRangeChanged(QExtPEProperty *property, double min, double max);
    void slotSingleStepChanged(QExtPEProperty *property, double step);
    void slotDecimalsChanged(QExtPEProperty *property, int prec);
    void slotReadOnlyChanged(QExtPEProperty *property, bool readOnly);
    void slotSetValue(double value);
};

// QExtPELineEditFactory
class QExtPELineEditFactoryPrivate : public EditorFactoryPrivate<QLineEdit>
{
    QExtPELineEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPELineEditFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QString &value);
    void slotRegExpChanged(QExtPEProperty *property, const QRegExp &regExp);
    void slotSetValue(const QString &value);
    void slotEchoModeChanged(QExtPEProperty *, int);
    void slotReadOnlyChanged(QExtPEProperty *, bool);
};

// QExtPEDateEditFactory
class QExtPEDateEditFactoryPrivate : public EditorFactoryPrivate<QDateEdit>
{
    QExtPEDateEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEDateEditFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QDate &value);
    void slotRangeChanged(QExtPEProperty *property, const QDate &min, const QDate &max);
    void slotSetValue(const QDate &value);
};

// QExtPETimeEditFactory
class QExtPETimeEditFactoryPrivate : public EditorFactoryPrivate<QTimeEdit>
{
    QExtPETimeEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPETimeEditFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QTime &value);
    void slotSetValue(const QTime &value);
};

// QExtPEDateTimeEditFactory
class QExtPEDateTimeEditFactoryPrivate : public EditorFactoryPrivate<QDateTimeEdit>
{
    QExtPEDateTimeEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEDateTimeEditFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QDateTime &value);
    void slotSetValue(const QDateTime &value);

};


// QExtKeySequenceEdit
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
// QExtPEKeySequenceEditorFactory
class QExtPEKeySequenceEditorFactoryPrivate : public EditorFactoryPrivate<QExtKeySequenceEdit>
{
    QExtPEKeySequenceEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEKeySequenceEditorFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QKeySequence &value);
    void slotSetValue(const QKeySequence &value);
};

// QExtCharEdit
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
// QExtPECharEditorFactory
class QExtPECharEditorFactoryPrivate : public EditorFactoryPrivate<QExtCharEdit>
{
    QExtPECharEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPECharEditorFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QChar &value);
    void slotSetValue(const QChar &value);

};

// QExtPEEnumEditorFactory
class QExtPEEnumEditorFactoryPrivate : public EditorFactoryPrivate<QComboBox>
{
    QExtPEEnumEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEEnumEditorFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, int value);
    void slotEnumNamesChanged(QExtPEProperty *property, const QStringList &);
    void slotEnumIconsChanged(QExtPEProperty *property, const QMap<int, QIcon> &);
    void slotSetValue(int value);
};



// QExtCursorDatabase
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
// QExtPECursorEditorFactory
class QExtPECursorEditorFactoryPrivate
{
    QExtPECursorEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPECursorEditorFactory)
public:
    QExtPECursorEditorFactoryPrivate();

    void slotPropertyChanged(QExtPEProperty *property, const QCursor &cursor);
    void slotEnumChanged(QExtPEProperty *property, int value);
    void slotEditorDestroyed(QObject *object);

    QExtPEEnumEditorFactory *m_enumEditorFactory;
    QExtPEEnumPropertyManager *m_enumPropertyManager;

    QMap<QExtPEProperty *, QExtPEProperty *> m_propertyToEnum;
    QMap<QExtPEProperty *, QExtPEProperty *> m_enumToProperty;
    QMap<QExtPEProperty *, QList<QWidget *> > m_enumToEditors;
    QMap<QWidget *, QExtPEProperty *> m_editorToEnum;
    bool m_updatingEnum;
};

// QExtColorEditWidget

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

// QExtPEColorEditorFactoryPrivate
class QExtPEColorEditorFactoryPrivate : public EditorFactoryPrivate<QExtColorEditWidget>
{
    QExtPEColorEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEColorEditorFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QColor &value);
    void slotSetValue(const QColor &value);
};


// QExtFontEditWidget

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

// QExtPEFontEditorFactoryPrivate
class QExtPEFontEditorFactoryPrivate : public EditorFactoryPrivate<QExtFontEditWidget>
{
    QExtPEFontEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEFontEditorFactory)
public:

    void slotPropertyChanged(QExtPEProperty *property, const QFont &value);
    void slotSetValue(const QFont &value);
};

#endif // _QEXTPEWIDGETFACTORY_P_H
