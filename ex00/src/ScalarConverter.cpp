#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& src) {*this = src;}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& src) {(void)src; return (*this);}

ScalarConverter::~ScalarConverter() {}

static int    parseInput(std::string data_type, const std::string input) {

    if (input.length() == 1 && std::isalpha(input[0])) {

        data_type = "char";
        return (0);
    }
    for (int i = 0; i < input.length(); i++) {

        if (input[i] == '.')
            data_type = "double";
        else if (input[i] == 'f')
            data_type = "float";
    }
    if (data_type != "char" || data_type != "double" || data_type != "float") {

        data_type = "int";
        return (0);
    }
    return (1);
}


static std::string intToStr(int input) {
    
    std::stringstream ss;
    ss << input;
    return (ss.str());
}

static int strToInt(const std::string& input) {

    std::stringstream ss(input);
    int result = 0;
    ss >> result;
    return (result);
}

static std::string intToChar(int input) {

    if (input >= 32 && input <= 126) {

        char c = static_cast<char>(input);
        return (std::string(1, c));
    }
    return ("Non displayable");
}


void ScalarConverter::convert(const std::string input) {

    std::string data_type;
    std::string data_strs[] = {};
    char    c;
    double  d;
    float   f;
    int     i;

    if (parseInput(data_type, input) == 1) {

        std::cout << "Input has Unrecognized Characters" << std::endl;
        return ;
    }
    if (data_type == "char") {
        data_strs[0] = input;
        data_strs[1] = intToStr(strToInt(input));
        data_strs[2] = intToStr(strToInt(input)) + ".0f";
        data_strs[3] = intToStr(strToInt(input)) + ".0";
    }
    else if (data_type == "int") {
        data_strs[0] = intToChar(strToInt(input));
        data_strs[1] = input;
        data_strs[2] = intToStr(strToInt(input)) + ".0f";
        data_strs[3] = intToStr(strToInt(input)) + ".0";
    }
    else if (data_type == "double") {
        
    }


}
