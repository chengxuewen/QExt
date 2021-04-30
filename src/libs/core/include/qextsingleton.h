#ifndef QEXTSINGLETON_H
#define QEXTSINGLETON_H

#include <qextglobal.h>

template <class T>
class QEXT_CORE_API QEXTSingleton
{
public:
    static inline T *instance() {
        static T *instance = new T;
        return instance;
    }

protected:
    QEXTSingleton(void) {}
    ~QEXTSingleton(void) {}

    QEXT_DISABLE_COPY_MOVE(QEXTSingleton)
};


#endif // QEXTSINGLETON_H
