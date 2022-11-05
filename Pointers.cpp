#include <iostream>
using namespace std;

int main()
{

    // GOAL
    // UNDERSTAND BELOW
    // if ((bytesRecvd = recvfrom(globalSocketUDP, recvBuf, 1000 , 0,
    // 				(struct sockaddr*)&theirAddr, &theirAddrLen)) == -1)
    // 	{
    // 		perror("connectivity listener: recvfrom failed");
    // 		exit(1);
    // 	}

    // ------------------------- EXAMPLE 1 -------------------------

    // Below we are declaring an array of 10 integers.
    // Each integer is 4 bytes (32 bits).
    int SomeArray[10] = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30};

    // Assigning each pointer in the contigous block of memory.
    int *pLocation6 = &SomeArray[6];
    int *pLocation0 = &SomeArray[0];

    for (int i = 0; i < 10; i++)
    {
        // SomeArray + i    is the Memory location for each index in SomeArray.
        // *(SomeArray + i) using the value of operator to get the contents of
        //    each address of SomeArray in memory.
        cout << SomeArray + i << " = " << *(SomeArray + i) << endl;
    }
    // The memory address work on a per byte basis.
    // Print out the memory address of each pointer.
    // This will cause an error because the compiler with notify bad practice?
    // cout << "pLocation6 = " << (int)pLocation6 << endl;
    // cout << "pLocation0 = " << (int)pLocation0 << endl;

    // the pointers themselves refer to the type of object or data type a pointer is pointing to
    //    in this case an integer (32 bits).
    // This difference is 6 instead of 24 because the compiler looks at the contigous block size
    //    of the memory address sizes of a per byte basis data type size.
    cout << "Difference = " << pLocation6 - pLocation0 << endl;

    // ------------------------- EXAMPLE 2 -------------------------
    struct sSomeObject
    {
        int x = 0xA3A2A1A0;
        int y = 0xB3B2B1B0;
    };

    // Heap (run time)
    // A pointer that points to an array of pointer
    sSomeObject *pSomeObject = new sSomeObject[10];

    for (int i = 0; i < 10; i++)
        pSomeObject[i] = new sSomeObject();

    // delete the objects in the arrays
    for (int i = 0; i < 10; i++)
        delete pSomeObject[i];

    // delete the pointer array - does not delete each object inside the array
    //                            only deletes the array's data structure
    delete[] pSomeObject;

    cout << endl;
    return 0;
}