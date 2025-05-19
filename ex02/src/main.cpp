#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"
#include "../includes/D.hpp"

#include <cstdlib>
#include <ctime>
#include <unistd.h>

Base* generate(void) {

    std::srand(std::time(0));
    int ramdom_num = std::rand() % 3;

    switch (ramdom_num)
    {
        case 0:
            return (new A);
            break ;
        case 1:
            return (new B);
            break ;
        default:
            return (new C);
            break ;
    }
}

void identify(Base* p) {

    if (dynamic_cast<A*>(p)) {

        std::cout << "A" << std::endl;
    }
    else if (dynamic_cast<B*>(p)) {

        std::cout << "B" << std::endl;
    }
    else if (dynamic_cast<C*>(p)) {

        std::cout << "C" << std::endl;
    }
    else {

        std::cout << "Unknown Class type" << std::endl;
    }
}

void identify(Base& p) {

    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return ;
    } catch (std::exception& e) {}

    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return ;
    } catch (std::exception& e) {}

    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return ;
    } catch (std::exception& e) {}

    std::cout << "Unknown reference type" << std::endl;
}


int	main(void)
{
	Base* p1;
    Base* p2 = new D;

	p1 = generate();
    usleep(1000000);

	std::cout << std::endl << "1.- Pointer: ";
	identify(p1);
    std::cout << std::endl <<  "1.- Reference: ";
	identify(*p1);

    std::cout << std::endl << "2.- Pointer: ";
	identify(p2);
	std::cout << std::endl << "2.- Reference: ";
	identify(*p2);

	delete p1;
    delete p2;
	return (0);
}
