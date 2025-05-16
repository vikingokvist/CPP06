#include "../includes/Serializer.hpp"

int main() 
{
    Data data;
    data.number = 42;
    data.c = 'A';

    uintptr_t raw = Serializer::serialize(&data);
    Data* ptr = Serializer::deserialize(raw);

    std::cout << "Data content: \n\tnumber = " << ptr->number << ", letter = " << ptr->c << std::endl;
    std::cout << std::endl;
    std::cout << "Original pointer: " << "\n\t\t" << &data << std::endl;
    std::cout << "Serialized value: " << "\n\t\t" << raw << std::endl;
    std::cout << "Deserialized pointer: " << "\n\t\t" << ptr << std::endl;
    std::cout << std::endl;



    std::cout << "Data content: \n\tnumber = " << ptr->number << ", letter = " << ptr->c << std::endl << std::endl;


    if (ptr == &data)
        std::cout << "Success: deserialized pointer matches original." << std::endl;
    else
        std::cout << "Error: deserialized pointer does not match original." << std::endl;

   

    return (0);
}