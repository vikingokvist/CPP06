#include "../includes/ScalarConverter.hpp"

int main(int argc, char **argv) {

    if (argc != 2) {

        std::cout << "Wrong Amount of Arguments" << std::endl;
        return (1);
    }
    std::string input(argv[1]);
    ScalarConverter::convert(input);
    return (0);
}