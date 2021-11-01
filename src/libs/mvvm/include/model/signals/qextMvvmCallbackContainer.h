#ifndef _QEXTMVVMCALLBACKCONTAINER_H
#define _QEXTMVVMCALLBACKCONTAINER_H

#include <algorithm>
#include <functional>
#include <list>
#include <qextMvvmGlobal.h>
#include <qextMvvmCallbackTypes.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;

//! Container to hold callbacks in the context of QEXTMvvmModelMapper.

template <typename T, typename U> class QEXTMvvmSignalBase
{
public:
    QEXTMvvmSignalBase() = default;

    void connect(T callback, U client);

    template <typename... Args> void operator()(Args... args);

    void remove_client(U client);

private:
    std::list<std::pair<T, U>> m_callbacks;
};

template <typename T, typename U> void QEXTMvvmSignalBase<T, U>::connect(T callback, U client)
{
    m_callbacks.push_back(std::make_pair(callback, client));
}

//! Notify clients using given list of arguments.
template <typename T, typename U>
template <typename... Args>
void QEXTMvvmSignalBase<T, U>::operator()(Args... args)
{
    for (const auto& f : m_callbacks) {
        f.first(args...);
    }
}

//! Remove client from the list to call back.

template <typename T, typename U> void QEXTMvvmSignalBase<T, U>::remove_client(U client)
{
    m_callbacks.remove_if(
        [client](const std::pair<T, U>& x) -> bool { return (x.second == client ? true : false); });
}

//! Callback container for specific client type.

template <typename T> class Signal : public QEXTMvvmSignalBase<T, Callbacks::slot_t>
{
};

} // namespace ModelView

#endif // _QEXTMVVMCALLBACKCONTAINER_H
