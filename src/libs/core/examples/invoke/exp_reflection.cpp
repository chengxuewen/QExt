#include <iostream>

template <class T, T N>
char const *pretty_string()
{
#ifdef _MSC_VER
    return __FUNCSIG__;
#else
    return __PRETTY_FUNCTION__;
#endif
}


int main(int argc, char *argv[])
{
    std::cout << pretty_string<int, 1>() << std::endl;
    return 0;
}

