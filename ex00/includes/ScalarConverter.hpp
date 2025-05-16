#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <exception>
# include <cctype>
# include <limits>
# include <cmath>
# include <iomanip>

# include "./toolsScalarConverter.h"

class ScalarConverter
{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& src);
        ScalarConverter& operator=(const ScalarConverter& src);
        ~ScalarConverter();

        std::string intToChar(int input);
        int         strToInt(const std::string& input);
        int         floatToInt(const std::string &input);
        void        printConvertedDataTypes(std::string data_src[]);
        void        parseInput(DataType& data_type, const std::string& input);
        void        convertFromFloat(const std::string& input, std::string data_strs[]);
        void        convertFromDouble(const std::string& input, std::string data_strs[]);
        std::string intToStr(int input, const std::string& original, bool preserve_negative);
        int         handleConversions(const std::string input, std::string data_strs[], DataType& data_type);

        class ErrorException : public std::exception
        {
            public:
                const char *what() const throw();
        };

    public:
        static void convert(const std::string input);

};


#endif