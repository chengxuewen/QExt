#ifndef _QEXTEMITTER_H
#define _QEXTEMITTER_H

#include <qextGlobal.h>
#include <qextFunction.h>
#include <qextSignal.h>

template<typename T_emitter>
class QEXTEmitter
{
    struct EventHandlerBase
    {
        virtual ~EventHandlerBase() QEXT_DECL_NOEXCEPT {}
        virtual bool isEmpty() const QEXT_DECL_NOEXCEPT = 0;
        virtual void clear() QEXT_DECL_NOEXCEPT = 0;
    };

    template<typename T_event>
    struct EventHandler QEXT_DECL_FINAL: EventHandlerBase
    {
        typedef QEXTFunction<void, T_event &, T_emitter &>  Listener;
        typedef QEXTSignal<void, T_event &, T_emitter &>    Signal;
        typedef typename Signal::Iterator                   Iterator;

        bool isEmpty() const QEXT_DECL_NOEXCEPT QEXT_DECL_OVERRIDE
        {
            return m_singleSignal.isEmpty() && m_signal.isEmpty();
        }

        void clear() QEXT_DECL_NOEXCEPT QEXT_DECL_OVERRIDE
        {
            m_singleSignal.clear();
            m_signal.clear();
        }

        Iterator addSingleListener(const Listener &listener)
        {
            return m_singleSignal.connect(listener);
        }

        Iterator addListener(const Listener &listener)
        {
            return m_signal.connect(listener);
        }

        void eraseListener(Iterator iter) QEXT_DECL_NOEXCEPT
        {
            m_singleSignal.erase(iter);
            m_signal.erase(iter);
        }

        void sendEvent(T_event event, T_emitter &emitter)
        {
            m_singleSignal(event, emitter);
            m_singleSignal.clear();
            m_signal(event, emitter);
        }

    private:
        Signal m_singleSignal;
        Signal m_signal;
    };


    static int nextType() QEXT_DECL_NOEXCEPT
    {
        static int counter = 0;
        return counter++;
    }

    template<typename>
    static int eventType() QEXT_DECL_NOEXCEPT
    {
        static int value = QEXTEmitter::nextType();
        return value;
    }

    template<typename T_event>
    EventHandler<T_event> &handler() QEXT_DECL_NOEXCEPT
    {
        int type = QEXTEmitter::eventType<T_event>();

        if(!(type < m_eventHandlers.size()))
        {
            m_eventHandlers.resize(type + 1);
        }

        if(!m_eventHandlers[type])
        {
            m_eventHandlers[type] = new EventHandler<T_event>;
        }

        return static_cast<EventHandler<T_event>&>(*m_eventHandlers[type]);
    }

public:
    typedef T_emitter                                       Emitter;
    typedef QVector<EventHandlerBase *>                     EventHandlerVector;
    typedef typename EventHandlerVector::Iterator           Iterator;
    typedef typename EventHandlerVector::ConstIterator      ConstIterator;

    typedef void(*PublishPendingFunction)(void);

    QEXTEmitter() { }

    virtual ~QEXTEmitter() QEXT_DECL_NOEXCEPT
    {
        Iterator iter;
        for (iter = m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
        {
            delete *iter;
        }
        const bool value = QEXTIsBaseOf<QEXTEmitter<T_emitter>, T_emitter>::value;
        QEXT_STATIC_ASSERT(value);
    }

    /**
     * \brief Registers a long-lived listener with the event emitter.
     *
     * This method can be used to register a listener that is meant to be
     * invoked more than once for the given event type.<br/>
     * The Connection object returned by the method can be freely discarded. It
     * can be used later to disconnect the listener, if needed.
     *
     * Listener is usually defined as a callable object assignable to a
     * `std::function<void(const E &, T_emitter &)`, where `E` is the type of the event
     * and `T_emitter` is the type of the resource.
     *
     * \param f A valid listener to be registered.
     * \return Connection object to be used later to disconnect the listener.
     */
    template<typename T_event>
    typename EventHandler<T_event>::Iterator addListener(typename EventHandler<T_event>::Listener listener)
    {
        return this->handler<T_event>().addListener(listener);
    }

    /**
     * \brief Registers a short-lived listener with the event emitter.
     *
     * This method can be used to register a listener that is meant to be
     * invoked only once for the given event type.<br/>
     * The Connection object returned by the method can be freely discarded. It
     * can be used later to disconnect the listener, if needed.
     *
     * Listener is usually defined as a callable object assignable to a
     * `std::function<void(const E &, T_emitter &)`, where `E` is the type of the event
     * and `T_emitter` is the type of the resource.
     *
     * \param f A valid listener to be registered.
     * \return Connection object to be used later to disconnect the listener.
     */
    template<typename T_event>
    typename EventHandler<T_event>::Iterator addSingleListener(typename EventHandler<T_event>::Listener listener)
    {
        return this->handler<T_event>().addSingleListener(listener);
    }

    /**
     * \brief Disconnects a listener from the event emitter.
     * \param conn A valid Connection object
     */
    template<typename T_event>
    void erase(typename EventHandler<T_event>::Iterator iter) QEXT_DECL_NOEXCEPT
    {
        this->handler<T_event>().erase(iter);
    }

    /**
     * \brief Disconnects all the listeners for the given event type.
     */
    template<typename T_event>
    void clear() QEXT_DECL_NOEXCEPT
    {
        this->handler<T_event>().clear();
    }

    /**
     * \brief Disconnects all the listeners.
     */
    void clear() QEXT_DECL_NOEXCEPT
    {
        Iterator iter;
        for (iter = m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
        {
            if (*iter)
            {
                delete *iter;
            }
        }
        m_eventHandlers.clear();
    }

    /**
     * \brief Checks if there are listeners registered for the specific event.
     * \return True if there are no listeners registered for the specific event,
     * false otherwise.
     */
    template<typename T_event>
    bool isEmpty() const QEXT_DECL_NOEXCEPT
    {
        int type = QEXTEmitter::eventType<T_event>();
        bool empty = static_cast<EventHandler<T_event>&>(*m_eventHandlers[type]).isEmpty();
        return (!(type < m_eventHandlers.size()) || !m_eventHandlers[type] || empty);
    }

    /**
     * \brief Checks if there are listeners registered with the event emitter.
     * \return True if there are no listeners registered with the event emitter,
     * false otherwise.
     */
    bool isEmpty() const QEXT_DECL_NOEXCEPT
    {
        ConstIterator iter;
        for (iter = m_eventHandlers.begin(); iter < m_eventHandlers.end(); ++iter)
        {
            if (*iter && !(*iter)->isEmpty())
            {
                return false;
            }
        }
        return true;
    }

protected:
    template<typename T_event>
    void sendEvent(T_event event)
    {
        this->handler<T_event>().sendEvent(event, *static_cast<T_emitter *>(this));
    }

private:
    EventHandlerVector m_eventHandlers;
};

#endif // _QEXTEMITTER_H
