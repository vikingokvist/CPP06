#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>
# include <string>
# include <sstream>
#include <cctype>

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& src);
        ScalarConverter& operator=(const ScalarConverter& src);
        ~ScalarConverter();

    public:
        static void convert(const std::string input);

};

std::string     intToStr(int input);
int             strToInt(const std::string& input);
std::string     intToChar(int input);
int             floatToInt(const std::string &input);
std::string     floatToDouble(std::string input);
int             parseInput(std::string& data_type, const std::string& input);
void            printConvertedDataTypes(std::string data_type, std::string data_src[]);
bool            isSpecialLiteral(const std::string& input);
void            handleSpecialLiterals(const std::string input, std::string data_strs[]);
void            handleConversions(const std::string input, std::string data_strs[], std::string data_type);

#endif