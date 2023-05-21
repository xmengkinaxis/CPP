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

ASSUMPTIONS
1. A handle is not shared among threads, but exclusively used by a single thread
2. There is no malicious thread which will guess or fabric a handle to use
3. A handle must be associated with some internal data object
4. Each created handle must be deleted accordingly
5. There is no independent thread of initializing during booting up and maintaining this system

POSSIBLE MITIGATION IF SOME ABOVE ASSUMPTIONS ARE CHANGED
1. Add the ownership for a handle to enforce the handle can be accessed by its creator, 
or to allow its ownership be transferred to another thread
2. Need an independent thread to do garbage-collection for the handle which is created without deletion
3. System could main a list of handles for each thread, so that it can delete all handles when 
   the thread crashes, to avoid wasting handles
4. Can allocate the handles randomly instead of sequentially, to make a thread harder 
    to guess or fabric a handle
5. Can encode and decode the handle instead of using an integer directly
6. If there is an independent thread, all handles can be initialized into the free list, 
   and there is no linear search anymore 

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

Tasks: 
1. (done) define handle, data, and context
2. (done) define APIs
3. (done) add usages into main and run; 
4. (done) define the internal functions; 
5. (done) add the management
6. (done) add singleThread and multiple thread demo
7. (done) implement the create api
8. (done) implement the delete api
9. (done) implement the get api
10. (done) add multiple thread tests
11. improve the free list: circular buffer and 
     and when to switch from linear to free list
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdatomic.h>

// define it to 11 in order to test a multiple case: 
// three threads, each requires 4 handles
#define HANDLE_MAX 100 

const int OK = 0; 
const int NON_EXIT = -1; 
typedef int HANDLE; 
const int INVALID_HANDLE = -1; 

// a complex data structure/object in the OS
typedef struct Data {
    // Can define something here
    int value; 
    /* e.g.
    uint64_t id; 
    HANDLE myHandle; 
    */
} DATA; 

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
// a circular queue of all handles
static DATA* systemHandle[HANDLE_MAX];

// use semaphore for its initialization does not need a special function call
static sem_t countSemaphore;  
static int usedCount = 0; 
static int freeCount = HANDLE_MAX; 
static atomic_int freeIndex = -1; 
static sem_t handleSemaphore; 

// use a queue to hold the free handles
// so that the access on a stale handle could be captured
typedef struct Item {
    struct Item *prev, *next; 
    HANDLE handle;
} ITEM;

static sem_t freeSemaphore; 
static ITEM* head = NULL; 
static ITEM* tail = NULL; 

static const DATA dummyData; 
static const ITEM dummyItem; 

static HANDLE getFreeHandle();
static HANDLE createHandleAndData(int input)
{    
    // get a free handle     
    HANDLE handle = getFreeHandle();
    if (INVALID_HANDLE == handle) {
        return INVALID_HANDLE; 
    }

    // create a data
    DATA *data = (DATA *) malloc(sizeof(DATA)); 
    data->value = input; 

    // associate the handle with the data
    systemHandle[handle] = data; 

    return handle; 
} 

static DATA fetchDataFromHandle(HANDLE handle)
{
    if (!isInUsedHandle(handle)) {
        return dummyData; 
    }
    return *(systemHandle[handle]);
}

static void addFreeHandle(HANDLE handle);
static int deleteHandleAndData(HANDLE handle)
{
    if (!isInUsedHandle(handle)) {
        return NON_EXIT; 
    }

    // Delete the data; 
    free(systemHandle[handle]); 
    // add into the free list
    addFreeHandle(handle);
    // Delete the handle; 
    systemHandle[handle] = NULL; 

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

static bool isFreeMajor()
{
    sem_wait(&countSemaphore);
    // return true if 75% handles are still free
    bool mostFree = usedCount <= (HANDLE_MAX >> 2); 
    sem_post(&countSemaphore);
    return mostFree; 
}

static void addOneUsed() 
{
    sem_wait(&countSemaphore);
    --freeCount;
    ++usedCount; 
    assert(HANDLE_MAX == freeCount + usedCount);
    sem_post(&countSemaphore);
}

static void addOneFree() 
{
    sem_wait(&countSemaphore);
    ++freeCount;
    --usedCount; 
    assert(HANDLE_MAX == freeCount + usedCount);
    sem_post(&countSemaphore);
}

static HANDLE oneLinearSearch();
static HANDLE getFreeHandle() 
{
    // first do a linear search when most are still free
    if (atomic_load(&freeIndex) < HANDLE_MAX && isFreeMajor()) {
        int linearHandle = oneLinearSearch();
        if (!isInRangeHandle(atomic_load(&freeIndex)) && isFreeMajor()) {
            // try again from the index 0
            atomic_store(&freeIndex, -1);
            linearHandle = oneLinearSearch(); 
        }
        if (isInRangeHandle(linearHandle)) {
            addOneUsed(); 
            return linearHandle;
        }
    }

    // second search the free queue 
    HANDLE freeHandle = INVALID_HANDLE;
    ITEM *first = NULL; 
    {
        sem_wait(&freeSemaphore);
        if (head && tail) {
            first = head; 
            if (head == tail) {
                head = tail = NULL; 
            } else {
                head = first->next; 
            }
            first->prev = first->next = NULL; 
            freeHandle = first->handle;
        }
        sem_post(&freeSemaphore);
        if (INVALID_HANDLE != freeHandle) {
            addOneUsed();  
            free(first); 
        }
    }

    return freeHandle; 
}

static HANDLE oneLinearSearch() 
{
    HANDLE handle = INVALID_HANDLE; 
    do {
        handle = atomic_fetch_add(&freeIndex, 1) + 1; 
    } while (isInUsedHandle(handle));
    return handle; 
}

static void addFreeHandle(HANDLE handle)
{
    if (isFreeMajor()) {
        systemHandle[handle] = NULL; 
        addOneFree();
        return; 
    }

    // add it to the free queue
    ITEM *item = (ITEM *) malloc(sizeof(ITEM));
    item->prev = item->next = NULL; 
    item->handle = handle; 
    {
        sem_wait(&freeSemaphore);
        if (NULL == head && NULL == tail) {
            head = tail = item; 
        }
        tail->next = item; 
        item->prev = tail; 
        tail = item; 
        sem_post(&freeSemaphore);
    }
    addOneFree(); 
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


void singleThreadDemo() {
    
    // assert the statistic is empty now 
    assertState(0, HANDLE_MAX);

    // create
    srand(time(NULL)); 
    int input = rand(); 
    HANDLE handle = handleCreate(input);   
    assert(handleIsValid(handle));
    assertState(1, HANDLE_MAX - 1);

    // look up
    DATA data = handleGetData(handle);     
    assert(data.value == input);
    // assert one is used now

    // delete
    handleDelete(handle); 
    // assert it is empty again  
    assertState(0, HANDLE_MAX); 
}

void* threadMultipleHandlesInorder(void* arg) {
    int id = (int) arg; 
    printf("Thread arg: %d\n", id); 
    HANDLE handle1 = handleCreate(100); 
    HANDLE handle2 = handleCreate(200); 
    HANDLE handle3 = handleCreate(300);
    assert(handleGetData(handle1).value == 100);
    assert(handleGetData(handle2).value == 200);
    assert(handleGetData(handle3).value == 300);
    handleDelete(handle1); 
    handleDelete(handle2);
    handleDelete(handle3);
    return NULL;
}

void* threadMultipleHandlesDisorder(void* arg) {
    int id = (int) arg; 
    printf("Thread arg: %d\n", id); 
    HANDLE handle1 = handleCreate(101); 
    HANDLE handle2 = handleCreate(201); 
    HANDLE handle3 = handleCreate(301); 
    assert(handleGetData(handle2).value == 201);
    assert(handleGetData(handle1).value == 101);
    assert(handleGetData(handle3).value == 301);
    handleDelete(handle2); 
    handleDelete(handle1);
    handleDelete(handle3);
    return NULL;
}

void* threadMultipleHandlesReversed(void* arg) {
    int id = (int) arg; 
    printf("Thread arg: %d\n", id);
    HANDLE handle1 = handleCreate(102); 
    HANDLE handle2 = handleCreate(202); 
    HANDLE handle3 = handleCreate(302); 
    assert(handleGetData(handle3).value == 302);
    assert(handleGetData(handle2).value == 202);
    assert(handleGetData(handle1).value == 102);
    handleDelete(handle3); 
    handleDelete(handle2);
    handleDelete(handle1);
    return NULL;
}

void* threadMultipleHandlesStress(void* arg) {
#define REQUEST_MAX 2 
    int id = (int) arg; 
    printf("Thread arg: %d\n", id);
    HANDLE handles[REQUEST_MAX];
    int values[REQUEST_MAX];    
    for (int i = 0; i < REQUEST_MAX; ++i) {
        handles[i] = handleCreate(100 + i); 
        printf("Thread arg: %d creates handle %d\n", id, handles[i]);
    }

    srand(time(NULL)); 
    for (int i = 0; i < REQUEST_MAX * 5; ++i) {
        int id = rand() % REQUEST_MAX; 
        assert(handleGetData(handles[id]).value == 100 + id);
        printf("Thread arg: %d access handle %d\n", id, handles[id]);
    }
    
    for (int count = REQUEST_MAX; 0 < count; ) {
        int id = rand() % REQUEST_MAX; 
        if (NULL == handles[id]) { continue; }
        printf("Thread arg: %d delete handle %d from %d counts \n", id, handles[id], count);
        handleDelete(handles[id]);
        handles[id] = NULL;
        --count; 
    }
    return NULL;
}


typedef void* (THREAD_FUNC)(void*); 

int multipleThreadsDemo(THREAD_FUNC func) {
#define THREAD_MAX 3 
    pthread_t threads[THREAD_MAX];
    int args[THREAD_MAX];
    int result = 0;
    for (int i = 0; i < THREAD_MAX; ++i) {
        args[i] = i + 1; 
        result = pthread_create(&threads[i], NULL, func, (void*)args[i]);
        if (OK != result) {
            return -1; 
        }
    }

    for (int i = 0; i < THREAD_MAX; ++i) {
        pthread_join(threads[i], NULL);
    }
    return OK; 
}

int main() {
    // assert it is empty again  
    assertState(0, HANDLE_MAX); 

    singleThreadDemo(); 

    multipleThreadsDemo(threadMultipleHandlesInorder);
    multipleThreadsDemo(threadMultipleHandlesDisorder);
    multipleThreadsDemo(threadMultipleHandlesReversed);
    multipleThreadsDemo(threadMultipleHandlesStress);
    
    // assert it is empty again  
    assertState(0, HANDLE_MAX); 

    printf("Hello, World!\n");
    return 0;
}
