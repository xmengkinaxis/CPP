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
    - a source file which demonstrates the usages and run some tests
* Use only C library in order to make the code portable
* IDE: Visual Studio Code with GCC

FURTHER IMPROVEMENT
* can use other light-weight synchronization mechanims, such as spinlock instead of semaphore
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

void initializeSystemHandles()
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
        }
        sem_post(&freeSemaphore);
    }

    if (INVALID_HANDLE != handle) {
        systemHandles[handle].prev = systemHandles[handle].next = INVALID_HANDLE; 
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
* Usage examples and tests for handles
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

void* threadMultipleHandlesForward(void* arg) {
    intptr_t id = (intptr_t) arg; 
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

void* threadMultipleHandlesRandom(void* arg) {
    intptr_t id = (intptr_t) arg; 
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

void* threadMultipleHandlesBackward(void* arg) {
    intptr_t id = (intptr_t) arg; 
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
#define REQUEST_MAX 22 
    intptr_t id = (intptr_t) arg; 
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

typedef void (THREAD_FUNC)(void*); 

int multipleThreadsDemo(THREAD_FUNC func) {
#define THREAD_MAX 6 
    pthread_t threads[THREAD_MAX];
    int args[THREAD_MAX];
    for (int i = 0; i < THREAD_MAX; ++i) {
        args[i] = i + 1; 
        int result = pthread_create(&threads[i], NULL, func, (void*)(intptr_t)args[i]);
        if (OK != result) {
            return -1; 
        }
    }

    for (int i = 0; i < THREAD_MAX; ++i) {
        pthread_join(threads[i], NULL);
    }
    return OK; 
}

int handleTest() {
    initializeSystemHandles();

    // assert it is empty again  
    assertState(0, HANDLE_MAX); 

    singleThreadDemo(); 

    multipleThreadsDemo(threadMultipleHandlesForward);
    multipleThreadsDemo(threadMultipleHandlesRandom);
    multipleThreadsDemo(threadMultipleHandlesBackward);
    multipleThreadsDemo(threadMultipleHandlesStress);
    
    // assert it is empty again  
    assertState(0, HANDLE_MAX);
    
    return 0;
}


/******************************************************************************
Timers

REQUIREMENT
use this (handle) framework to manage timers – so the use cases are going to be 
    creating/destroying timers, updating existing timers and firing timers.  

The twist is that as an OS we need to fire timers by _value_ not by descriptor 
so you’ll need to come up with a solution that 
    allows the normal name/value key mapping ????
    but also allows for effective searching by value as an OS needs to fire the ‘next’ timer as time moves forward

ASSUMPTION
    the granularity of timer is 1 second; 
******************************************************************************/

#include <time.h>
#include <unistd.h>

typedef void (TIMER_CALLBACK_FUNC)(int); 

struct timer_queue_type;

typedef struct timer_type {
    struct timer_type *prev, *next; 
    struct timer_queue_type *queue; 
    TIMER_CALLBACK_FUNC *callBackFunc; 
    time_t expiration; 
    int duration; 
    bool isPeriodic; 
} TIMER_TYPE; 

typedef struct timer_queue_type {
    TIMER_TYPE *head; 
    sem_t semaphore; 
} TIMER_QUEUE_TYPE;

void timer_default_handler(int timerId) {
    printf("Timer #%d expired\n", timerId);
}

#define TIMER_VECTOR_MAX 10
TIMER_QUEUE_TYPE timerVector[TIMER_VECTOR_MAX]; 

// declaration for timer functions
void initAllTimerQueues();
TIMER_TYPE* timerCreate(int duration, TIMER_CALLBACK_FUNC *callBackFunc, bool isPeriodic); 
TIMER_CALLBACK_FUNC *timerSetCallBack(TIMER_TYPE *timer, TIMER_CALLBACK_FUNC *callBackFunc);
void timerSetDuration(TIMER_TYPE *timer, int duration); 
void timerSetPeriodic(TIMER_TYPE *timer, bool isPeriodic);  
bool timerIsExpired(TIMER_TYPE *timer); 
bool timerIsPeriodic(TIMER_TYPE *timer); 
int timerGetTime(TIMER_TYPE *timer);
int timerGetDuration(TIMER_TYPE *timer);
void timerDelete(TIMER_TYPE *timer); 
void timerStart(TIMER_TYPE *timer); 
void timerStop(TIMER_TYPE *timer); 
void timerReset(TIMER_TYPE *timer);

void timerFire(); 

// declaration for timer internal functions
static void initTimerQueue(TIMER_QUEUE_TYPE* queue);
static void timerEnqueue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer);
static void timerDequeue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer);

void initAllTimerQueues()
{
    for (int i = 0; i < TIMER_VECTOR_MAX; ++i) {
        initTimerQueue(&timerVector[i]); 
    }
}

static void timerAssertInactive(TIMER_TYPE *timer) {
    assert(NULL != timer);
    assert(NULL == timer->prev);
    assert(NULL == timer->next);
    assert(NULL == timer->queue);
}

TIMER_TYPE* timerCreate(int duration, TIMER_CALLBACK_FUNC* callBackFunc, bool isPeriodic) {
    TIMER_TYPE *timer = malloc(sizeof(TIMER_TYPE)); 
    assert(NULL != timer);
    timer->prev = timer->next = timer->queue = NULL;
    timerAssertInactive(timer); 

    timer->callBackFunc = callBackFunc;
    assert(NULL != timer->callBackFunc);
    timer->expiration = 0; // set in timerStart
    timer->isPeriodic = isPeriodic; 
    timer->duration = duration; 
    assert(0 < timer->duration); 

    return timer; 
}

TIMER_CALLBACK_FUNC *timerSetCallBack(TIMER_TYPE *timer, TIMER_CALLBACK_FUNC *callBackFunc)
{
    timerAssertInactive(timer); 
    assert(NULL != callBackFunc);
    timer->callBackFunc = callBackFunc;
}

void timerSetDuration(TIMER_TYPE *timer, int duration)
{
    timerAssertInactive(timer); 
    assert(0 < duration);
    timer->duration = duration; 
}

void timerSetPeriodic(TIMER_TYPE *timer, bool isPeriodic)
{
    timerAssertInactive(timer); 
    timer->isPeriodic = isPeriodic; 
}
  
bool timerIsExpired(TIMER_TYPE *timer)
{
    assert(NULL != timer); 
    return timer->expiration == 0;
}

bool timerIsPeriodic(TIMER_TYPE *timer)
{
    assert(NULL != timer); 
    return timer->isPeriodic;
}

int timerGetTime(TIMER_TYPE *timer)
{
    assert(NULL != timer); 
    return timer->expiration;
}

int timerGetDuration(TIMER_TYPE *timer)
{
    assert(NULL != timer); 
    return timer->duration;
}

void timerDelete(TIMER_TYPE *timer)
{
    timerAssertInactive(timer); 
    free(timer); 
}

void timerStart(TIMER_TYPE *timer)
{
    timerAssertInactive(timer);
    timer->expiration = time(NULL) + timer->duration; 
    // TODO
    // find the proper queue
    TIMER_QUEUE_TYPE * queue = NULL; 
    // enqueue
    sem_wait(queue->semaphore);
    timerEnqueue(queue, timer); 
    sem_post(queue->semaphore);
}

void timerStop(TIMER_TYPE *timer)
{
    assert(timer);
    
    TIMER_QUEUE_TYPE * queue = timer->queue; 
    if (!timer->queue) { 
        timerAssertInactive(timer);
        return; 
    }

    // dequeue
    sem_wait(queue->semaphore);
    timerDequeue(queue, timer); 
    sem_post(queue->semaphore);
    timerAssertInactive(timer); 
}

void timerReset(TIMER_TYPE *timer)
{
    // TODO
    timerStop(timer);
    timerAssertInactive(timer); 
    timer->expiration = time(NULL) + timer->expiration; 
    timerStart(timer); 
}

void timerFire()
{
    while(true) {
        sleep(1); // assume the resolution of the system time is one second
        for (int i = 0; i < TIMER_VECTOR_MAX; ++i) {
            // TODO
            //
        }
    }
}

static void initTimerQueue(TIMER_QUEUE_TYPE* queue) {
    assert(NULL != queue); 
    queue->head = NULL; 
}

// ensure the timers in the queue are sorted based on their expirations in the ascending order
static void timerEnqueue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer) {
    assert(queue && timer); 
    assert(!timer->prev && !timer->next && !timer->queue);
    
    TIMER_TYPE *prev = NULL; 
    for (TIMER_TYPE *curr = queue->head; curr && curr->expiration <= timer->expiration; curr = curr->next) {
        prev = curr; 
    }
    if (!prev) {
        // add as the new front
        timer->next = queue->head;
        queue->head->prev = timer; 
        queue->head = timer; 
    } else {
        // add in the middle
        timer->next = prev->next; 
        timer->prev = prev;
        if (prev->next) {
            prev->next->prev = timer; 
            prev->next = timer; 
        } 
    }
    timer->queue = queue;
    assert(timer->prev || timer->next);
    assert(queue->head);
}

static void timerDequeue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer) {
    assert(!queue || !timer);
    assert(queue->head); 
    assert(timer->prev || timer->next); 

    if (timer->prev) {
        timer->prev->next = timer->next; 
    } else {
        assert(queue->head == timer);
        queue->head = timer->next;
    }
    if (timer->next) {
        timer->next->prev = timer->prev; 
    }
        
    timer->prev = timer->next = timer->queue = NULL; 
    assert(!queue->head || !queue->head->prev);
}



/******************************************************************************
* Usage examples and tests for timers
******************************************************************************/
void oneTimerDemo() {
    return; 

    TIMER_TYPE *timer = timerCreate(1000, timer_default_handler, false); 
    timerStart(timer); 
    int remains = timerGetTime(timer); 
    timerStop(timer); 
    timerSetCallBack(timer, timer_default_handler); 
    timerSetPeriodic(timer, true); 
    assert(timerIsPeriodic(timer)); 
    timerSetDuration(timer, 2000); 
    assert(!timerIsPeriodic(timer)); 
    assert(!timerIsExpired(timer)); 
    timerStart(timer); 
    //wait
    assert(timerIsExpired(timer)); 
}

void timerTest() {
    oneTimerDemo(); 
} 

int main() {
    handleTest(); 
    timerTest(); 
    
    printf("Hello, World!\n");
    return 0;
}
