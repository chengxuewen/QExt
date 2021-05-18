#ifndef QEXTARGUMENT_H
#define QEXTARGUMENT_H

#include <qextglobal.h>



#define QEXT_ARG(type, data) QEXTArgument<type>(#type, data)
#define QEXT_RETURN_ARG(type, data) QReturnArgument<type>(#type, data)

class QEXT_CORE_API QEXTGenericArgument
{
public:
    inline QEXTGenericArgument(const char *name = QEXT_NULLPTR, const void *data = QEXT_NULLPTR)
        : m_data(data), m_name(name) {}
    inline void *data() const { return const_cast<void *>(m_data); }
    inline const char *name() const { return m_name; }

private:
    const void *m_data;
    const char *m_name;
};



class QEXT_CORE_API QEXTGenericReturnArgument: public QEXTGenericArgument
{
public:
    inline QEXTGenericReturnArgument(const char *name = QEXT_NULLPTR, void *data = QEXT_NULLPTR)
        : QEXTGenericArgument(name, data)
    {}
};


template <typename T>
class QEXT_CORE_API QEXTArgument: public QEXTGenericArgument
{
public:
    inline QEXTArgument(const char *name, const T &data)
        : QEXTGenericArgument(name, static_cast<const void *>(&data))
    {}
};



template <typename T>
class QEXT_CORE_API QEXTArgument<T &>: public QEXTGenericArgument
{
public:
    inline QEXTArgument(const char *name, T &data)
        : QEXTGenericArgument(name, static_cast<const void *>(&data))
    {}
};



template <typename T>
class QEXT_CORE_API QEXTReturnArgument: public QEXTGenericReturnArgument
{
public:
    inline QEXTReturnArgument(const char *name, T &data)
        : QEXTGenericReturnArgument(name, static_cast<void *>(&data))
    {}
};



#endif // QEXTARGUMENT_H
