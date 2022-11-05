#include <iostream>
using namespace std;
int main (){
    int var = 7;
    // A pointer to variable 'var' or "stores the address of 'var'"
    int* ptr = &var;
    cout << "ptr = " << ptr << endl;   // ptr = 0x7fff1ffb7964
    cout << "*ptr = " << *ptr << endl; // *ptr = 7
    cout << "&ptr = " << &ptr << endl; // &ptr = 0x7fff1ffb7968
    // References or alias for i
    int& ref = var;
    cout << "ref = " << ref << endl;   // ref = 7
    cout << "&ref = " << &ref << endl; // *ref = 0x7fff1ffb7964
    cout << "*(&ref) = " << *(&ref) << endl; // *(&ref) = 7
    //The pointer has the freedom to move around and point to diff variables while a reference 
    // just looks up on constant place in memory
    return 0;
}



