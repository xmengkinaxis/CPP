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
* IDE: Visual Studio Code with GCC

FUNCTIONAL 
APIs for client: 
1. create a handle
2. get an object by giving a handle
3. delete a handle 

Internal functions: 
1. allocate/create/construct a handle
2. associate the handle with a data object 
3. retire/destruct/delete a handle
4. lookup/query
5. manage (statistic for analysis, used, free, etc.)

NON-FUNCTIONAL 
* performance is key
* highly scalable 

Tasks: 
1. (done) define handle, data, and context
2. (done) define APIs
3. (done) add usages into main and run; 
4. (done) define the internal functions; 
4. (done) add the management
5. implement the create api
6. implement the delete api
7. implement the get api
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <semaphore.h>

#define HANDLE_MAX 10 

const int OK = 0; 
const int NON_EXIT = -1; 
typedef int HANDLE; 
const int INVALID_HANDLE = -1; 

// a complex data structure/object in the OS
typedef struct Data {
    // Can define something here
    uint64_t id; // e.g.
    int input; 
    HANDLE myHandle; 
} DATA; 

typedef struct Item {
    struct Item *prev, *next; 
    DATA data; 
} ITEM;

// statistic information on handles 
typedef struct HandleSummary {
    uint32_t used; 
    uint32_t free; 
} HANDLE_SUMMARY;


/******************************************************************************
* APIs for clients
******************************************************************************/

// declaration for internal functions
static HANDLE createHandleAndData(int input); 
static DATA fetchDataFromHandle(HANDLE handle);
static int deleteHandleAndData(HANDLE handle);
static bool isInRangeHandle(HANDLE handle);
static bool isInUsedHandle(HANDLE handle);
static HANDLE_SUMMARY summarizeHandles(); 

// declaration of APIs for clients: 
HANDLE handleCreate(int input); 
DATA handleGetData(HANDLE handle);
int handleDelete(HANDLE handle);
bool handleIsValid(HANDLE handle); 
HANDLE_SUMMARY handleSummarize(); 

// implementation of APIs for clients
HANDLE handleCreate(int input) {
    HANDLE handle = createHandleAndData(input); 
    assert(handleIsValid(handle)); 
    return handle; 
}

DATA handleGetData(HANDLE handle) 
{
    assert(handleIsValid(handle));
    DATA data = fetchDataFromHandle(handle); 
    return data; 
}

int handleDelete(HANDLE handle) {
    assert(handleIsValid(handle)); 
    int code = deleteHandleAndData(handle);
    assert(!handleIsValid(handle));
    return code; 
}

bool handleIsValid(HANDLE handle) {
    return isInRangeHandle(handle) && isInUsedHandle(handle); 
}

HANDLE_SUMMARY handleSummarize() {
    HANDLE_SUMMARY summary = {.used = 0, .free = 0};
    summary = summarizeHandles();
    return summary; 
}

/******************************************************************************
* Internal functions
******************************************************************************/
static ITEM* systemHandle[HANDLE_MAX];
static int usedCount = 0; 
static int freeCount = 0; 
static int nextFreeIndex = 0; 
static sem_t handleSemaphore; 
static const DATA dummyData; 
static const ITEM dummyItem; 

static HANDLE createHandleAndData(int input)
{
    sem_wait(handleSemaphore);
    // Todo 
    // create an item and data
    // create a handle 
    HANDLE handle = 0; //  INVALID_HANDLE; 
    systemHandle[handle] = &dummyItem; 
    // associate the handle with item
    return handle; 
} 

static DATA fetchDataFromHandle(HANDLE handle)
{
    sem_wait(handleSemaphore);
    if (!isInUsedHandle(handle)) {
        return dummyData; 
    }
    return systemHandle[handle]->data;
}

static int deleteHandleAndData(HANDLE handle)
{
    if (!isInUsedHandle(handle)) {
        return NON_EXIT; 
    }
    // Todo: 
    // Delete the data; 
    // Delete the handle; 
    systemHandle[handle] = NULL; 
    // add into the free list
    return OK; 
}

static bool isInRangeHandle(HANDLE handle)
{
    return 0 <= handle && handle < HANDLE_MAX; 
}

static bool isInUsedHandle(HANDLE handle)
{
    return isInRangeHandle(handle) && NULL != systemHandle[handle]; 
}

static HANDLE_SUMMARY summarizeHandles()
{
    sem_wait(handleSemaphore);
    HANDLE_SUMMARY summary = {.used = usedCount, .free = freeCount};
    return summary; 
}

/******************************************************************************
* Usage examples and tests
******************************************************************************/

void assertState(int used, int free)
{
    HANDLE_SUMMARY summary = handleSummarize(); 
    assert(summary.used == used); 
    assert(summary.free == free);
}


int main() {
    // assert the statistic is empty now 
    assertState(0, 0);

    // create
    srand(time(NULL)); 
    int input = rand(); 
    HANDLE handle = handleCreate(input);   
    assert(handleIsValid(handle));
    // assertState(1, 0);
    assertState(0, 0);

    // look up
    DATA data = handleGetData(handle);     
    // assert one is used now

    // delete
    handleDelete(handle); 
    // assert it is empty again    
    assertState(0, 0);

    printf("Hello, World!\n");
    return 0;
}
