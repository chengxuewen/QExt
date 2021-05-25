#include <iostream>
#include <string>
#include <QDebug>

#include <qextfunctor.h>
#include <qextmemberfunctor.h>
#include <qextbindreturn.h>
#include <qextbind.h>


int funcCallback()
{
    std::cout << "funcCallback" << std::endl;
    return 10;
}

void funcCallback0()
{
    std::cout << "funcCallback0" << std::endl;
}

void funcCallback1(int i)
{
    std::cout << "funcCallback1" << std::endl;
}

void funcCallback2(int i, int m)
{
    std::cout << "funcCallback2" << i << "--" << m << std::endl;
}

class MemberBase {
public:
    MemberBase(int id) : m_id(id) {}

    virtual void funcCallback() {
        std::cout << "MemberBase::funcCallback::" << m_id << std::endl;
    }

    void funcCallback0()
    {
        std::cout << "MemberBase::funcCallback0::" << m_id << std::endl;
    }

    void funcCallback1(int x)
    {
        std::cout << "MemberBase::funcCallback1" << m_id << ":" << x << std::endl;
    }

    void funcCallback2(int x, int y)
    {
        std::cout << "MemberBase::funcCallback2" << m_id << ":" << x << "-" << y << std::endl;
    }

protected:
    int m_id;
};

class Member : MemberBase
{
public:
    Member(int id) : MemberBase(id) {}

    void funcCallback() {
        std::cout << "Member::funcCallback::" << m_id << std::endl;
    }
};


int main()
{
    MemberBase memberBase1(1);
    MemberBase memberBase2(2);
    Member member1(1);

//    QEXTFunctor<int> ff = qextFunctor(&funcCallback);
    //    ff();

//    QEXTBindReturnFunctor<int, QEXTFunctor<int> > bindReturnFunctor(ff, 0);
//    qDebug() << "bindReturnFunctor=" << bindReturnFunctor();

//    QEXTFunctor<void> f1 = qextFunctor(&funcCallback0);
//    QEXTFunctor<void, int> f2 = qextFunctor(&funcCallback1);
//    QEXTFunctor<void, int, int> f3 = qextFunctor(&funcCallback2);
//    f1();
//    f2(1);
//    f3(1, 2);

    qextBind(&funcCallback2, 11)(22);
    qextBind<0>(&funcCallback2, 11)(22);
    qextBind<-1>(&funcCallback2, 11)(22);


//    QEXTMemberFunctor<void, MemberBase> functor1 = qextMemberFunctor(&MemberBase::funcCallback);
//    QEXTMemberFunctor<void, Member> functor2 = qextMemberFunctor(&Member::funcCallback);
//    functor1(&memberBase1);
//    functor1(reinterpret_cast<MemberBase *>(&member1));
//    functor2(&member1);


//    QEXTBoundMemberFunctor<void, MemberBase> boundFunctor0 = qextMemberFunctor(&memberBase1, &MemberBase::funcCallback0);
//    QEXTBoundMemberFunctor<void, MemberBase, int> boundFunctor1 = qextMemberFunctor(&memberBase1, &MemberBase::funcCallback1);
//    QEXTBoundMemberFunctor<void, MemberBase, int, int> boundFunctor2 = qextMemberFunctor(&memberBase1, &MemberBase::funcCallback2);
//    boundFunctor0();
//    boundFunctor1(1);
//    boundFunctor2(1, 2);

    return 0;
}
