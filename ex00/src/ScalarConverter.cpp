#include "../includes/ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& src) {*this = src;}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& src) {(void)src; return (*this);}

ScalarConverter::~ScalarConverter() {}


void ScalarConverter::convert(const std::string input) {

    ScalarConverter converter;
    std::string data_strs[4];
    DataType    data_type = TYPE_UNKNOWN;

    converter.parseInput(data_type, input);
    if (converter.handleConversions(input, data_strs, data_type) == 1) {

        throw (ScalarConverter::ErrorException());
    }
    converter.printConvertedDataTypes(data_strs);
}

void    ScalarConverter::parseInput(DataType& data_type, const std::string& input) {

    bool    only_digits = true;
    bool    error = false;
    for (int i = 0; input[i]; i++) {

        if (i == 0 && (input[i] == '+' || input[i] == '-')) 
            continue ;
        if (!(std::isdigit(input[i])))
            only_digits = false;
        if (((data_type == TYPE_FLOAT && input[i + 1])) || (std::isalpha(input[i]) && input[i] != 'f'))
            error = true;
        else if (input[i] == '.' && input[i + 1] && std::isdigit(input[i + 1]) && input[i - 1] && std::isdigit(input[i - 1]))
            data_type = TYPE_DOUBLE;
        else if (input[i] == 'f' && data_type == TYPE_DOUBLE) {
            
            if (input[i + 1])
                error = true;
            data_type = TYPE_FLOAT;
        }
    }
    if (only_digits == true)
        data_type = TYPE_INT;
    if (error == true)
        data_type = TYPE_UNKNOWN;
    if (input == "nan" || input == "nanf")
        data_type = TYPE_NAN;
    else if (input == "+inff" || input == "+inf")
        data_type = TYPE_POS_INF;
    else if (input == "-inff" || input == "-inf")
        data_type = TYPE_NEG_INF;
    else if (input.length() == 1 && std::isprint(input[0]) && !std::isdigit(input[0]))
        data_type = TYPE_CHAR;
    return ;
}

int    ScalarConverter::handleConversions(const std::string input, std::string data_strs[], DataType& data_type) {

    if (data_type == TYPE_UNKNOWN)
        return (1);
    else if (data_type == TYPE_NAN) {
        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
        data_strs[2] = "nanf";
        data_strs[3] = "nan";
    } 
    else if (data_type == TYPE_POS_INF) {
        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
        data_strs[2] = "+inff";
        data_strs[3] = "+inf";
    }
    else if (data_type == TYPE_NEG_INF) {
        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
        data_strs[2] = "-inff";
        data_strs[3] = "-inf";
    }
    else if (data_type == TYPE_CHAR) {
        data_strs[0] = "\'" + input + "\'";
        data_strs[1] = intToStr(static_cast<int>(input[0]), input, false);
        data_strs[2] = intToStr(static_cast<int>(input[0]), input, false) + ".0f";
        data_strs[3] = intToStr(static_cast<int>(input[0]), input, false) + ".0";
    }
    else if (data_type == TYPE_INT) {
        data_strs[0] = intToChar(strToInt(input));
        data_strs[1] = intToStr(strToInt(input), input, true);
        data_strs[2] = intToStr(strToInt(input), input, true) + ".0f";
        data_strs[3] = intToStr(strToInt(input), input, true) + ".0";
    }
    else if (data_type == TYPE_FLOAT) {
        convertFromFloat(input, data_strs);
    }
    else if (data_type == TYPE_DOUBLE) {
        convertFromDouble(input, data_strs);
    }
    return (0);
}

std::string ScalarConverter::intToStr(int input, const std::string& original, bool preserve_negative) {

    if (preserve_negative && input == 0 && original.find('-') != std::string::npos )
        return ("-0");
    std::stringstream ss;
    ss << input;
    return (ss.str());
}

int ScalarConverter::strToInt(const std::string& input) {

    std::stringstream ss(input);
    int result = 0;
    ss >> result;
    return (result);
}

std::string ScalarConverter::intToChar(int input) {

    if (input >= 32 && input <= 126) {

        char c = static_cast<char>(input);
        return (std::string(1, c));
    }
    return ("Non displayable");
}

int ScalarConverter::floatToInt(const std::string &input) {
    
    std::stringstream ss(input);
    float f;
    ss >> f;
    return (static_cast<int>(f));
}

void ScalarConverter::convertFromDouble(const std::string& input, std::string data_strs[]) {

    double d;
    std::stringstream ss1;
    std::stringstream ss2;
    std::stringstream(input) >> d;
    float f = static_cast<float>(d);

    if (std::isnan(d) || std::isinf(d) || d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min()) {
        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
    }
    else {
        int i = static_cast<int>(d);
        data_strs[0] = intToChar(i);
        data_strs[1] = intToStr(i, input, false);
    }
    ss1 << std::fixed << std::showpoint << f << "f";
    data_strs[2] = ss1.str();
    ss2 << std::fixed << std::showpoint << d;
    data_strs[3] = ss2.str();
}

void ScalarConverter::convertFromFloat(const std::string& input, std::string data_strs[]) {

    float               f;
    std::stringstream   ss1;
    std::stringstream   ss2;
    std::stringstream(input) >> f;

    if (std::isnan(f) || std::isinf(f) || f > std::numeric_limits<int>::max() || f < std::numeric_limits<int>::min()) {
        data_strs[0] = "impossible";
        data_strs[1] = "impossible";
    }
    else {
        int i = static_cast<int>(f);
        data_strs[0] = intToChar(i);
        data_strs[1] = intToStr(i, input, false);
    } 
    ss1 << std::fixed << std::showpoint << f << "f";
    data_strs[2] = ss1.str();
    ss2 << std::fixed << std::showpoint << static_cast<double>(f);
    data_strs[3] = ss2.str();
}

void ScalarConverter::printConvertedDataTypes(std::string data_src[]) {

    std::cout << std::endl << "---------------------------------" << std::endl << std::endl;
    std::cout << "\tchar: " << data_src[0]  << std::endl; 
    std::cout << "\tint: " << data_src[1] << std::endl; 
    std::cout << "\tfloat: " << data_src[2] << std::endl; 
    std::cout << "\tdouble: " << data_src[3] << std::endl << std::endl;
    std::cout << "---------------------------------" << std::endl << std::endl;
}

const char *ScalarConverter::ErrorException::what(void) const throw()
{
	return ("Error: Impossible to print or input not convertable");
};
