/*
REQUIREMENT cited from the assessment
As an exercise, you are to design a set of APIs and implement a subsystem that will allow for 
the creation, query and destruction of handles that can be used to reference the data objects bound to them.

Your subsystem should at a minimum include:
1. A method to allocate/retire handles
2. A method to associate a handle to a data object
3. A method to look up a data object given a handle
4. A method retire handles and disassociate them from a data object
5. Example usage demonstrating the operation

NOTE: 
* Need to map a handle with the type HANDLE to a data with the type Data as its internal data structure
* The handle should be a unique key in the system which represents an association with the a specific data object
* The handle starts from zero, increases as more are allocated, and reuses to keep compact
* Ideally the file content should be divided into the following files
    - a header file which declares all APIs used by clients and the handle
    - a source file which implements these APIs
    - a header file which declares all internal functions and the internal data structure for the handle
    - a source file which implements these internal functions

FUNCTIONAL 
APIs for client: 
1. create a handle
2. lookup an object by giving a handle
3. delete a handle 

Internal functions: 
1. allocate/create/construct a handle
2. associate the handle with a data object 
3. retire/destruct/delete a handle
4. lookup/query
5. manage (statistic for analysis, free, inused, total, maximum)

NON-FUNCTIONAL 
* performance is key
* highly scaleble 

*/

#include <stdio.h>

typedef int HANDLE; 

// a complex data structure/object in the OS
struct Data {
    // Can define something here
    int id; // e.g.
}; 

// the context for the data structure/object in the OS
struct Context {
    // Can define something here
    int threadId; // e.g.
}; 


/* 
Usage examples and tests
*/
int main() {
    printf("Hello, World!\n");
    // assert the statistic is empty now 
    // create
    // look up
    // assert one is inused now
    // delete
    // assert it is empty again
    return 0;
}
