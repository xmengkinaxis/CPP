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

NOTE: 
* Need to map a handle with the type HANDLE to a data with the type Data as its internal data structure
* The handle should be a unique key in the system which represents an association with the a specific data object
* The handle starts from zero, increases as more are allocated, and reuses to keep compact
* Ideally the file content should be divided into the following files
    - a header file which declares all APIs used by clients
    - a source file which implements these APIs
    - a header file which declares all internal functions and the internal data structures for the handles
    - a source file which implements these internal functions
* Use only C library in order to make the code portable
* IDE: Visual Studio Code with GCC


FURTHER IMPROVEMENT
* can use other light-weight synchronization mechanims, such mutex or spinlock instead of semaphore
* the performance can be achieved by implementing a lock-free queue
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>

// the limit for handles in the system
#define HANDLE_MAX 100 

typedef int HANDLE; 

const int OK = 0; 
const int NON_EXIT = -1; 
const int INVALID_HANDLE = -1; 

// a complex data structure/object in the OS
typedef struct Data {
    // Can define something here
    int value; 
    /* e.g.
    uint64_t id; 
    HANDLE myHandle; 
    pthread_t threadId; 
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
static HANDLE createHandleForData(int input); 
static DATA fetchDataFromHandle(HANDLE handle);
static int deleteHandleAndData(HANDLE handle);
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
    HANDLE handle = createHandleForData(input); 
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
    return isInUsedHandle(handle); 
}

HANDLE_SUMMARY handleSummarize() {
    HANDLE_SUMMARY summary = {.used = 0, .free = 0};
    summary = summarizeHandles();
    return summary; 
}

/******************************************************************************
* Internal functions
******************************************************************************/
typedef struct Item {
    HANDLE prev, next; 
    DATA* data; 
} ITEM;

// a queue of all handles
static ITEM systemHandles[HANDLE_MAX];

// use semaphore for its initialization does not need a special function call
static sem_t countSemaphore;  
static int usedCount = 0; 
static int freeCount = HANDLE_MAX; 

// use a queue to hold the free handles
// so that the access on a stale handle could be captured
static sem_t freeSemaphore; 
HANDLE head = INVALID_HANDLE; 
HANDLE tail = INVALID_HANDLE; 

static const DATA dummyData; 

static void initializeSystemHandles()
{
    head = 0; 
    tail = HANDLE_MAX - 1; 
    systemHandles[head].prev = INVALID_HANDLE; 
    systemHandles[tail].next = INVALID_HANDLE; 

    for (int i = 1; i < HANDLE_MAX; ++i) {
        systemHandles[i].prev = i - 1; 
    }
    for (int i = 0; i < HANDLE_MAX - 1; ++i) {
        systemHandles[i].next = i + 1; 
    }
    assert(INVALID_HANDLE == systemHandles[head].prev);
    assert(INVALID_HANDLE == systemHandles[tail].next);
}

static HANDLE fetchFreeHandle();
static HANDLE createHandleForData(int input)
{    
    // fetch a free handle
    HANDLE handle = fetchFreeHandle();
    if (INVALID_HANDLE == handle) {
        return INVALID_HANDLE; 
    }

    // create a data
    DATA *data = (DATA *) malloc(sizeof(DATA)); 
    data->value = input; 

    // associate the handle with the data
    systemHandles[handle].data = data; 

    return handle; 
} 

static DATA fetchDataFromHandle(HANDLE handle)
{
    if (!isInUsedHandle(handle)) {
        return dummyData; 
    }
    return *(systemHandles[handle].data);
}

static void returnFreeHandle(HANDLE handle);
static int deleteHandleAndData(HANDLE handle)
{
    if (!isInUsedHandle(handle)) {
        return NON_EXIT; 
    }

    // Delete the data; 
    free(systemHandles[handle].data); 
    systemHandles[handle].data = NULL; 
    // return the handle back into the free list
    returnFreeHandle(handle);

    return OK; 
}

static bool isInRangeHandle(HANDLE handle)
{
    return 0 <= handle && handle < HANDLE_MAX; 
}

static bool isInUsedHandle(HANDLE handle)
{
    return isInRangeHandle(handle) && NULL != systemHandles[handle].data; 
}

static HANDLE_SUMMARY summarizeHandles()
{
    sem_wait(countSemaphore);
    HANDLE_SUMMARY summary = {.used = usedCount, .free = freeCount};
    sem_post(&countSemaphore);
    return summary; 
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

static HANDLE fetchFreeHandle() 
{
    // get one from the free queue 
    HANDLE handle = INVALID_HANDLE;
    {
        sem_wait(&freeSemaphore);
        if (INVALID_HANDLE != head && INVALID_HANDLE != tail) {
            handle = head; 
            if (head == tail) {
                head = tail = INVALID_HANDLE; 
            } else {
                head = systemHandles[handle].next; 
                systemHandles[head].prev = INVALID_HANDLE; 
            }
            systemHandles[handle].prev = systemHandles[handle].next = INVALID_HANDLE; 
        }
        sem_post(&freeSemaphore);
    }

    if (INVALID_HANDLE != handle) {
        addOneUsed();  
    }

    return handle; 
}

static void returnFreeHandle(HANDLE handle)
{
    assert(INVALID_HANDLE == systemHandles[handle].prev);
    assert(INVALID_HANDLE == systemHandles[handle].next);
    // add it to the free queue
    {
        sem_wait(&freeSemaphore);
        if (INVALID_HANDLE == head && INVALID_HANDLE == tail) {
            head = tail = handle; 
        } else {
            systemHandles[tail].next = handle; 
            systemHandles[handle].prev = tail; 
            tail = handle; 
        }
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
#define REQUEST_MAX 20 
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
        if (INVALID_HANDLE == handles[id]) { continue; }
        printf("Thread arg: %d delete handle %d from %d counts \n", id, handles[id], count);
        handleDelete(handles[id]);
        handles[id] = INVALID_HANDLE;
        --count; 
    }
    return NULL;
}

typedef void* (THREAD_FUNC)(void*); 

int multipleThreadsDemo(THREAD_FUNC func) {
#define THREAD_MAX 5 
    pthread_t threads[THREAD_MAX];
    int args[THREAD_MAX];
    for (int i = 0; i < THREAD_MAX; ++i) {
        args[i] = i + 1; 
        int result = pthread_create(&threads[i], NULL, func, (void*)args[i]);
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
    initializeSystemHandles();

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
