#include <iostream>
#include <vector>

using namespace std;

int main()
{

    // Polymorphism

    struct sSomeBaseObject
    {
        // virtual allows the super class method to be overridden
        virtual const char *IdentifyYourself()
        {
            return "BaseObject";
        }
    };

    struct sSomeSubObjectA : public sSomeBaseObject
    {
        const char *IdentifyYourself()
        {
            return "SubObject A";
        }
    };

    struct sSomeSubObjectB : public sSomeBaseObject
    {
        const char *IdentifyYourself()
        {
            return "SubObject B";
        }
    };

    // EXAMPLE 1
    // This wont allow us you use polymorphism and see the subclass'
    // trait IdentifyYourself().
    // sSomeBaseObject objects[10];
    // objects[3] = sSomeSubObjectA();
    // for (int i = 0; i < 10; i++)
    //     cout << objects[i].IdentifyYourself() << endl;

    // EXAMPLE 2
    // Here we are declaring a pointer to an array of pointers.
    // In this case its an array of pointers that represent our sSomeBaseObject.
    // These pointers are empty because we get a segmention fault on the first for loop.
    sSomeBaseObject **pSomeArray = new sSomeBaseObject *[5];
    // for (int i = 0; i < 5; i++)
    //     cout << pSomeArray[i]->IdentifyYourself() << endl;
    // Here we can see this actually changes the object
    pSomeArray[0] = new sSomeSubObjectA();
    pSomeArray[1] = new sSomeSubObjectB();
    pSomeArray[2] = new sSomeSubObjectA();
    pSomeArray[3] = new sSomeBaseObject();
    pSomeArray[4] = new sSomeBaseObject();
    // for (int i = 0; i < 5; i++)
    //     cout << pSomeArray[i]->IdentifyYourself() << endl;
    for (int i = 0; i < 5; i++)
        delete pSomeArray[i];
    delete[] pSomeArray;

    // EXAMPLE 2
    // Lets use vectors from the same type of base and sub objects case in example 2
    vector<sSomeBaseObject *> vSomeVector;
    vSomeVector.push_back(new sSomeSubObjectA());
    vSomeVector.push_back(new sSomeSubObjectB());
    vSomeVector.push_back(new sSomeSubObjectA());
    vSomeVector.push_back(new sSomeBaseObject());
    vSomeVector.push_back(new sSomeBaseObject());
    // with this auto in the for loop it is saying pass by reference
    // otherwise normally it would give us a copy of the actual object
    // we don't want that. we want what is actually there.
    // Becasue that means less copies in memory.
    // for (auto &a : vSomeVector)
    //     cout << a->IdentifyYourself() << endl;
    for (auto &a : vSomeVector)
        delete a;
    vSomeVector.clear();


    // BAD BAD BAD - never create a pointer to the element of a vector because 
    // vecotrs may reallocate memory indexing and addressing causing the data
    // to sometimes be overwritten 
    // sSomeBaseObject *pPointerToVectorElement = &vSomeVector[3];




    // vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // for (int i : vi)
    //     cout << "i = " << i << endl;
    //     i 


    return 0;
}