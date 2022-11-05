#include <iostream>

#define LOG(x) std::cout << x << std::endl;

int main()
{
    // EAMPLE 1
    int var = 8;
    // the compiler will not allow this because
    // it doesn't know how much of the 32-bit int
    // should be kept for its void data type OR
    // if it should change the data type in the pointer
    // which could result in data loss if the original
    // data type is larger than the new one.
    // void* ptr = &var;
    // *ptr = 10;

    // if we change to an int then we are good
    int *ptr = &var;
    *ptr = 10;
    LOG(*ptr);
    LOG(ptr);


    // EXAMPLE 2
    // since one char is the size of a byte we are 
    // saying lets declare a buffer size of 64 bytes   
    char* buffer = new char[8];
    //memset fills a block of memory with data
    memset(buffer, 0, 8)



    // std::cin.get();
    return 0;
}