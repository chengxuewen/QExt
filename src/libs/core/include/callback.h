#include <cstring>

#include <qextglobal.h>

class QEXT_CORE_API NCallbackBase {
public:
    typedef void (NCallbackBase::*_MemFunc)();
    typedef void (*_Func)();

    NCallbackBase()
        : func(0)
        , caller(0)
    {
    }

    NCallbackBase(const void* c, const void* f, size_t sz)
    {
        if (c) {
            caller = (void*)c;
            memcpy(memFunc, f, sz);
        }
        else {
            func = f;
        }
    }

//    operator int() const { return func || caller; }

    class DummyInit {
    };

    union {
        const void* func;
        char memFunc[sizeof(_MemFunc)];
    };

    void* caller;
};

template <typename RetType, typename... Params>
class QEXT_CORE_API NCallback : protected NCallbackBase {
public:
    NCallback(DummyInit* = 0) {}

    RetType operator()(Params... params) const
    {
        return callback(*this, params...);
    }

//    using NCallbackBase::operator int;

protected:
    typedef RetType (*Callback)(const NCallbackBase&, Params...);

    NCallback(Callback _callback, const void* _instance, const void* _fct, size_t _sz)
        : NCallbackBase(_instance, _fct, _sz)
        , callback(_callback)
    {
    }

private:
    Callback callback;
};

template <typename RetType, typename Func, typename... Params>
class QEXT_CORE_API FunctionTranslator : public NCallback<RetType, Params...> {
public:
    FunctionTranslator(Func fct)
        : NCallback<RetType, Params...>(callback, 0, (const void*)fct, 0)
    {
    }

    static RetType callback(const NCallbackBase& ftor, Params... params)
    {
        return (Func(ftor.func))(params...);
    }
};

template <typename RetType, typename Caller, typename MemFunc, typename... Params>
class QEXT_CORE_API MemberTranslator : public NCallback<RetType, Params...> {
public:
    MemberTranslator(Caller& _instance, const MemFunc& _method)
        : NCallback<RetType, Params...>(callback, &_instance, &_method, sizeof(MemFunc))
    {
    }

    static RetType callback(const NCallbackBase& ftor, Params... params)
    {
        Caller* caller = (Caller*)ftor.caller;
        MemFunc& memFunc(*(MemFunc*)(void*)(ftor.memFunc));
        return (caller->*memFunc)(params...);
    }
};

template <typename RetType, typename FuncType, typename... Params, typename... FuncParams>
inline FunctionTranslator<RetType, FuncType (*)(FuncParams...), Params...>
NGenerateCallback(NCallback<RetType, Params...>*, FuncType (*fct)(FuncParams...))
{
    return FunctionTranslator<RetType, FuncType (*)(FuncParams...), Params...>(fct);
}

template <typename RetType, typename Caller, typename FuncType, typename CallType, typename... Params, typename... FuncParams>
inline MemberTranslator<RetType, Caller, FuncType (CallType::*)(FuncParams...), Params...>
NGenerateCallback(NCallback<RetType, Params...>*, Caller& _instance, FuncType (CallType::*const& _method)(FuncParams...))
{
    typedef FuncType (CallType::*MemFunc)(FuncParams...);
    return MemberTranslator<RetType, Caller, MemFunc, Params...>(_instance, _method);
}

template <typename RetType, typename Caller, typename FuncType, typename CallType, typename... Params, typename... FuncParams>
inline MemberTranslator<RetType, const Caller, FuncType (CallType::*)(FuncParams...) const, Params...>
NGenerateCallback(NCallback<RetType, Params...>*, const Caller& _instance, FuncType (CallType::*const& _method)(FuncParams...) const)
{
    typedef FuncType (CallType::*MemFunc)(FuncParams...) const;
    return MemberTranslator<RetType, const Caller, MemFunc, Params...>(_instance, _method);
}
