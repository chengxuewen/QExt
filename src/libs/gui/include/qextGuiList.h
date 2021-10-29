#ifndef _QEXTGUILIST_H
#define _QEXTGUILIST_H

#include <qextGuiGlobal.h>

#include <QObject>

template<typename T>
class QEXTGuiListProperty {
public:
    typedef void (*AppendFunction)(QEXTGuiListProperty<T> *, T*);
    typedef int (*CountFunction)(QEXTGuiListProperty<T> *);
    typedef T *(*AtFunction)(QEXTGuiListProperty<T> *, int);
    typedef void (*ClearFunction)(QEXTGuiListProperty<T> *);

    QEXTGuiListProperty()
        : object(0), data(0), append(0), count(0), at(0), clear(0), dummy1(0), dummy2(0) {}
    QEXTGuiListProperty(QObject *o, QList<T *> &list)
        : object(o), data(&list), append(qlist_append), count(qlist_count), at(qlist_at),
          clear(qlist_clear), dummy1(0), dummy2(0) {}
    QEXTGuiListProperty(QObject *o, void *d, AppendFunction a, CountFunction c = 0, AtFunction t = 0,
                        ClearFunction r = 0)
        : object(o), data(d), append(a), count(c), at(t), clear(r), dummy1(0), dummy2(0) {}

    bool operator==(const QEXTGuiListProperty &o) const {
        return object == o.object &&
                data == o.data &&
                append == o.append &&
                count == o.count &&
                at == o.at &&
                clear == o.clear;
    }

    QObject *object;
    void *data;

    AppendFunction append;

    CountFunction count;
    AtFunction at;

    ClearFunction clear;

    void *dummy1;
    void *dummy2;

private:
    static void qlist_append(QEXTGuiListProperty *p, T *v) {
        reinterpret_cast<QList<T *> *>(p->data)->append(v);
    }
    static int qlist_count(QEXTGuiListProperty *p) {
        return reinterpret_cast<QList<T *> *>(p->data)->count();
    }
    static T *qlist_at(QEXTGuiListProperty *p, int idx) {
        return reinterpret_cast<QList<T *> *>(p->data)->at(idx);
    }
    static void qlist_clear(QEXTGuiListProperty *p) {
        return reinterpret_cast<QList<T *> *>(p->data)->clear();
    }
};

class QEXTGuiListReferencePrivate;
class QEXT_GUI_API QEXTGuiListReference
{
public:
    QEXTGuiListReference();
    //    QEXTGuiListReference(QObject *, const char *property, QDeclarativeEngine * = 0);
    QEXTGuiListReference(const QEXTGuiListReference &);
    QEXTGuiListReference &operator=(const QEXTGuiListReference &);
    ~QEXTGuiListReference();

    bool isValid() const;

    QObject *object() const;
    const QMetaObject *listElementType() const;

    bool canAppend() const;
    bool canAt() const;
    bool canClear() const;
    bool canCount() const;

    bool append(QObject *) const;
    QObject *at(int) const;
    bool clear() const;
    int count() const;

protected:
    QScopedPointer<QEXTGuiListReferencePrivate> d_ptr;

private:
    friend class QEXTGuiListReferencePrivate;
};

#endif // _QEXTGUILIST_H
