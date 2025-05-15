#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& src) {*this = src;}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& src) {(void)src; return (*this);}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string input) {

    std::string data_type = "Special Literal";
    std::string data_strs[4];

    if (isSpecialLiteral(input)) {
        
        handleSpecialLiterals(input, data_strs);
    }
    else {

        if (parseInput(data_type, input) == 1) {

            std::cout << "Unknown Characters in Input" << std::endl;
            return ;
        }
        handleConversions(input, data_strs, data_type);
    }
    printConvertedDataTypes(data_type, data_strs);
}

void    handleConversions(const std::string input, std::string data_strs[], std::string data_type) {

    if (data_type == "char") {

        data_strs[0] = input;
        data_strs[1] = intToStr(static_cast<int>(input[0]));
        data_strs[2] = intToStr(static_cast<int>(input[0])) + ".0f";
        data_strs[3] = intToStr(static_cast<int>(input[0])) + ".0";
    }
    else if (data_type == "int") {

        data_strs[0] = intToChar(strToInt(input));
        data_strs[1] = input;
        data_strs[2] = intToStr(strToInt(input)) + ".0f";
        data_strs[3] = intToStr(strToInt(input)) + ".0";
    }
    else if (data_type == "float") {

        data_strs[0] = intToChar(floatToInt(input));
        data_strs[1] = intToStr(floatToInt(input));
        data_strs[2] = input;
        data_strs[3] = floatToDouble(input);

    }
    else if (data_type == "double") {

        data_strs[0] = intToChar(floatToInt(input));
        data_strs[1] = intToStr(floatToInt(input));
        data_strs[2] = input + "f";
        data_strs[3] = input;
    }
    if (data_strs[0].length() == 1)
        data_strs[0] = "\'" + data_strs[0] + "\'";
}

void    handleSpecialLiterals(const std::string input, std::string data_strs[]) {

    if (input == "nan" || input == "nanf") {

        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
        data_strs[2] = "nanf";
        data_strs[3] = "nan";
    } 
    else if (input == "+inff" || input == "+inf") {

        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
        data_strs[2] = "+inff";
        data_strs[3] = "+inf";
    }
    else if (input == "-inff" || input == "-inf") {

        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
        data_strs[2] = "-inff";
        data_strs[3] = "-inf";
    }
}

int    parseInput(std::string& data_type, const std::string& input) {

    int error = 0;
    if (input.length() == 1 && std::isalpha(input[0])) {

        data_type = "char";
        return (0);
    }
    for (int i = 0; input[i]; i++) {

        if ((std::isalpha(input[i]) && input[i] != 'f' ) || (input[i] == '.' && !input[i + 1]))
            error++;
        if (input[i] == '.') {
            error++;
            data_type = "double";
        }
        if (input[i] == 'f' && data_type == "double")
            data_type = "float";
        if (data_type == "float" && input[i + 1])
            error++;
    }
    if (data_type != "char" && data_type != "double" && data_type != "float")
        data_type = "int";
    if (data_type.empty() || error > 1)
        return (1);
    return (0);
}

bool isSpecialLiteral(const std::string& input) {
    return (
        input == "nan" || input == "+inf" || input == "-inf" ||
        input == "nanf" || input == "+inff" || input == "-inff"
    );
}

std::string intToStr(int input) {
    
    std::stringstream ss;
    ss << input;
    return (ss.str());
}

int strToInt(const std::string& input) {

    std::stringstream ss(input);
    int result = 0;
    ss >> result;
    return (result);
}

std::string intToChar(int input) {

    if (input >= 32 && input <= 126) {

        char c = static_cast<char>(input);
        return (std::string(1, c));
    }
    return ("Non displayable");
}

int floatToInt(const std::string &input) {
    
    std::stringstream ss(input);
    float f;
    ss >> f;
    return (static_cast<int>(f));
}

std::string floatToDouble(std::string input) {

    return (input.substr(0, input.length() - 1));
}

void printConvertedDataTypes(std::string data_type, std::string data_src[]) {

    std::cout << "Data Type Detected: " << data_type << std::endl << std::endl;
    std::cout << "\tchar: " << data_src[0]  << std::endl; 
    std::cout << "\tint: " << data_src[1] << std::endl; 
    std::cout << "\tfloat: " << data_src[2] << std::endl; 
    std::cout << "\tdouble: " << data_src[3] << std::endl << std::endl; 
}