#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <string>

class Base
{
    private:

    public:
        Base();
        Base(const Base& src);
        Base& operator=(const Base& src);
        ~Base();
};

#endif
