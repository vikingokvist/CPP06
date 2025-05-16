#include "../includes/Base.hpp"

Base::Base() {}

Base::Base(const Base& src) {
    *this = src;
}

Base& Base::operator=(const Base& src) {
    if (this != &src) {

    }
    return *this;
}

Base::~Base() {}
