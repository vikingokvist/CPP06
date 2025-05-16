#include "../includes/ScalarConverter.hpp"

int main(int argc, char **argv) {

    if (argc != 2) {

        std::cout << "Wrong Amount of Arguments" << std::endl;
        std::cout << "\tUsage: ./convert 42.69f" << std::endl;
        return (1);
    }
    try
    {
        std::string input(argv[1]);
        ScalarConverter::convert(input);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}