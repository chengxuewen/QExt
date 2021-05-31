#ifndef QEXTMVVMCALLBACK_H
#define QEXTMVVMCALLBACK_H

#include <qextmvvmglobal.h>

#include <QListIterator>
#include <QString>
#include <QList>
#include <QPair>



class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmTagRow;

typedef const void * QEXTMvvmSlot_t;
typedef const void(*QEXTMvvmItem_t)(QEXTMvvmItem*);
typedef const void(*QEXTMvvmItem_int_t)(QEXTMvvmItem*, int);
typedef const void(*QEXTMvvmItem_str_t)(QEXTMvvmItem*, QString);
typedef const void(*QEXTMvvmItem_tagrow_t)(QEXTMvvmItem*, QEXTMvvmTagRow);
typedef const void(*QEXTMvvmModel_t)(QEXTMvvmModel*);


template <typename T, typename U>
class QEXT_MVVM_API QEXTMvvmAbstractSignal
{
public:
    QEXTMvvmAbstractSignal() QEXT_EQ_DEFAULT;

    void connect(T callback, U client);

    template <typename... Args> void operator()(Args... args);

    void remove_client(U client);

private:
    QList<QPair<T, U>> m_callbacks;
};


template <typename T, typename U>
void QEXTMvvmAbstractSignal<T, U>::connect(T callback, U client)
{
    m_callbacks.append(QPair<T, U>(callback, client));
}

//! Notify clients using given list of arguments.
template <typename T, typename U>
template <typename... Args>
void QEXTMvvmAbstractSignal<T, U>::operator()(Args... args)
{
    QListIterator<QPair<T, U>> iter(m_callbacks);
    while (iter.hasNext()) {
        iter.next().first();
    }
//    for (const auto& f : m_callbacks) {
//        f.first(args...);
//    }
}

//! Remove client from the list to call back.

template <typename T, typename U>
void QEXTMvvmAbstractSignal<T, U>::remove_client(U client)
{
    QMutableListIterator<QPair<T, U>> iter(m_callbacks);
    while (iter.hasNext()) {
        if (iter.next().second == client) {
            iter.remove();
        }
    }
}

//! Callback container for specific client type.

template <typename T>
class QEXTMvvmSignal : public QEXTMvvmAbstractSignal<T, QEXTMvvmSlot_t>
{

};



#endif // QEXTMVVMCALLBACK_H
