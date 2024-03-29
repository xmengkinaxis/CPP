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
#include <unistd.h>

// the limit for handles in the system
#define HANDLE_MAX 100 

typedef int HANDLE; 

const int OK = 0; 
const int NON_EXIT = -1; 
const int INVALID_HANDLE = -1; 

typedef void (*TIMER_CALLBACK_FUNC)(void*, int);

struct timer_queue_type;

typedef struct timer_type {
    struct timer_type *prev, *next; 
    struct timer_queue_type *queue; 
    TIMER_CALLBACK_FUNC callBackFunc; 
    time_t expiration; 
    int duration; 
    bool isPeriodic; 
} TIMER_TYPE; 

typedef struct timer_queue_type {
    TIMER_TYPE *head; 
    sem_t semaphore; 
    int scan; 
    int magnitude; 
} TIMER_QUEUE_TYPE;

// a complex data structure/object in the OS
typedef struct Data {
    // Can define something here
    int value; 
    TIMER_TYPE *timer; 
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
static TIMER_TYPE *fetchTimerFromHandle(HANDLE handle);
static int deleteHandleAndData(HANDLE handle);
static bool isInUsedHandle(HANDLE handle);
static HANDLE_SUMMARY summarizeHandles(); 

TIMER_TYPE* timerCreate(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic); 
void timerStart(TIMER_TYPE *timer); 
void timerStop(TIMER_TYPE *timer); 
static HANDLE createHandleForTimer(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic);

// declaration of APIs for clients: 
HANDLE handleCreate(int input); 
DATA handleGetData(HANDLE handle);
TIMER_TYPE *handleGetTimer(HANDLE handle);
int handleDelete(HANDLE handle);
bool handleIsValid(HANDLE handle); 
HANDLE_SUMMARY handleSummarize(); 


HANDLE handleTimerCreate(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic);
void handleTimerStart(HANDLE timerHandle);
void handleTimerStop(HANDLE timerHandle);

// implementation of APIs for clients
HANDLE handleCreate(int input) {
    HANDLE handle = createHandleForData(input); 
    assert(handleIsValid(handle)); 
    return handle; 
}

HANDLE handleTimerCreate(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic) {
    HANDLE handle = createHandleForTimer(duration, callBackFunc, isPeriodic); 
    assert(handleIsValid(handle)); 
    return handle; 
}


void handleTimerStart(HANDLE timerHandle)
{
    TIMER_TYPE *timer = handleGetTimer(timerHandle);
    timerStart(timer); 
}

void handleTimerStop(HANDLE timerHandle)
{
    TIMER_TYPE *timer = handleGetTimer(timerHandle);
    timerStop(timer);
}


DATA handleGetData(HANDLE handle) 
{
    assert(handleIsValid(handle));
    DATA data = fetchDataFromHandle(handle); 
    return data; 
}

TIMER_TYPE *handleGetTimer(HANDLE handle)
{
    assert(handleIsValid(handle));
    TIMER_TYPE *timer = fetchTimerFromHandle(handle); 
    return timer; 
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

    sem_init(&countSemaphore, 0, 1); 
    sem_init(&freeSemaphore, 0, 1);
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
    data->timer = NULL;

    // associate the handle with the data
    systemHandles[handle].data = data; 

    return handle; 
} 

static HANDLE createHandleForTimer(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic) 
{ 
    // fetch a free handle
    HANDLE handle = fetchFreeHandle();
    if (INVALID_HANDLE == handle) {
        return INVALID_HANDLE; 
    }

    // create a data for a timer
    DATA *data = (DATA *) malloc(sizeof(DATA)); 
    TIMER_TYPE *timer = timerCreate(duration, callBackFunc, isPeriodic);
    data->timer = timer; 
    data->value = 0; 

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

static TIMER_TYPE *fetchTimerFromHandle(HANDLE handle)
{
    if (!isInUsedHandle(handle)) {
        return NULL; 
    }
    return systemHandles[handle].data->timer;
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
    sem_wait(&countSemaphore);
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

void singleThreadHandleDemo() {
    
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
    printf("Thread arg: %d creates handles\n", id); 
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

typedef void* (THREAD_FUNC)(void*); 

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
    // assert it is empty again  
    assertState(0, HANDLE_MAX); 

    singleThreadHandleDemo(); 

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
    a. allows the normal name/value key mapping ????
    b. but also allows for effective searching by value as an OS needs to fire the ‘next’ timer as time moves forward

QUESTIONS 
1. the requirement a "name/value key mapping" is unclear;
    Does it mean each timer is created with a name and searched by name?
    Why needs such a mapping? How to use it?
2. an email is sent to Huawei recruiter about it, but there is no rely.
3. the requirement a is NOT implemented. 

ASSUMPTION
    the granularity of timer is 1 second; 

IMPLEMENTATION
0. There are two types of timers implemented: the normal timer and the periodic timer; 
    the normal timer expires only one, while the periodic timer repeats expiring, until it is stopped
1. The time resolution is 1 second in this time subsytem
2. All timers are organized in an array of queues
3. Each queue hold all the timers which will expire in a certain range from now on and which 
    are sorted according to their expirations
4. The order of magnitudes of timer duration is creased by 10 between the queue in the array
5. In the current implementation, the ranges for queues are
    queue #0: < 10; 0 - 9 seconds;
    queue #1: < 100; 1 minute 40 seconds; 
    queue #2: < 1,000; 16 minutes 40 seconds; 
    queue #3: < 10,000; 2 hours 46 minutes 40 seconds; 
    queue #4: < 100,000; 
    queue #5: < 1000,000;  
6. Anytime, the queue #0 holds all timers which are going to expired in 10 seconds, 
    the queue #1 contains all timers which are going to expired between 10 and 100 seconds; 
7. During each scan, the timers might be moved from high to low in the queues according 
    their remained time to expired

FURTHER IMPROVEMENT
1. User more level timer vectors to scale with more timers
2. the CPU core count can be used as a dimension in the timer vectors, 
    so that there is a thread of firing the timers on each core and that
    the timeout timers could be fired concurrently and in time
3. Could use heap or tree to hold the timers and sort them according to their expiration, 
    so that it would be easy to get the very timer which is going to expired very soon

******************************************************************************/

void timer_default_handler(void* expiration, int duration) {
    printf("Timer expired after %d seconds at %s", duration, ctime(expiration));
}

#define MAGNITUDE 10

// the timers are organized into an array according to their expirations
// according to the different order of magnitudes
#define TIMER_VECTOR_MAX 7
TIMER_QUEUE_TYPE timerVector[TIMER_VECTOR_MAX]; 

// declaration for timer functions
void initAllTimerQueues();
TIMER_TYPE* timerCreate(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic); 
TIMER_CALLBACK_FUNC *timerSetCallBack(TIMER_TYPE *timer, TIMER_CALLBACK_FUNC callBackFunc);
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

void* timerFire(void *arg); 

// declaration for timer internal functions
static int initTimerQueue(TIMER_QUEUE_TYPE* queue, int magnitude);
static void timerEnqueue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer);
static void timerDequeue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer);
static TIMER_QUEUE_TYPE *timerGetTargetQueue(TIMER_TYPE *timer); 

void initAllTimerQueues()
{
    for (int i = 0, magnitude = 1; i < TIMER_VECTOR_MAX; ++i, magnitude *= MAGNITUDE) {
        initTimerQueue(&timerVector[i], magnitude); 
    }
}

static void timerAssertInactive(TIMER_TYPE *timer) {
    assert(timer);
    if (timer->prev || timer->next) {
        printf("something wrong here");
    }
    assert(!timer->prev && !timer->next);
    assert(!timer->queue);
}

static void timerAssertActive(TIMER_TYPE *timer) {
    assert(timer);
    assert(timer->prev || timer->next);
    assert(timer->queue);
}

TIMER_TYPE* timerCreate(int duration, TIMER_CALLBACK_FUNC callBackFunc, bool isPeriodic) {
    TIMER_TYPE *timer = malloc(sizeof(TIMER_TYPE)); 
    assert(timer);

    timer->prev = timer->next = NULL;
    timer->queue = NULL;
    timerAssertInactive(timer); 

    timer->callBackFunc = callBackFunc;
    assert(timer->callBackFunc);
    timer->expiration = 0; // set in timerStart
    timer->isPeriodic = isPeriodic; 
    timer->duration = duration; 
    assert(0 < timer->duration); 

    return timer; 
}

TIMER_CALLBACK_FUNC *timerSetCallBack(TIMER_TYPE *timer, TIMER_CALLBACK_FUNC callBackFunc)
{
    timerAssertInactive(timer); 
    assert(callBackFunc);
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
    assert(timer); 
    return timer->expiration <= time(NULL);
}

bool timerIsPeriodic(TIMER_TYPE *timer)
{
    assert(timer); 
    return timer->isPeriodic;
}

int timerGetTime(TIMER_TYPE *timer)
{
    assert(timer); 
    return timer->expiration;
}

int timerGetDuration(TIMER_TYPE *timer)
{
    assert(timer); 
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
    TIMER_QUEUE_TYPE *queue = timerGetTargetQueue(timer); 
    timer->expiration = time(NULL) + timer->duration; 
    timerEnqueue(queue, timer); 
}

void timerStop(TIMER_TYPE *timer)
{
    assert(timer);    
    TIMER_QUEUE_TYPE *queue = timer->queue; 
    if (timer->queue) { 
        timerDequeue(queue, timer); 
    }
    timerAssertInactive(timer); 
}

void timerReset(TIMER_TYPE *timer)
{
    assert(timer);
    timerStop(timer);
    timerAssertInactive(timer); 
    timer->expiration = time(NULL) + timer->duration; 
    timerStart(timer); 
}


static void timerScanExpirations(TIMER_QUEUE_TYPE *sourceQueue, TIMER_QUEUE_TYPE *targetQueue, time_t current); 
static void timerMigrateQueue(TIMER_QUEUE_TYPE *sourceQueue, TIMER_QUEUE_TYPE *targetQueue); 
static void timerFireQueue(TIMER_QUEUE_TYPE *queue); 

static TIMER_QUEUE_TYPE tempQueue; 
static TIMER_QUEUE_TYPE fireQueue; 
void* timerFire(void *arg)
{
    initTimerQueue(&tempQueue, 1); 
    initTimerQueue(&fireQueue, 1);

    while(true) {
        sleep(1); // assume the resolution of the system time is one second

        assert(!fireQueue.head);
        // scan the timers' expiration and move down along the vector 
        time_t current = time(NULL); 
        for (int i = 0; i < TIMER_VECTOR_MAX; i++) {
            assert(!tempQueue.head); // ensure it is empty

            TIMER_QUEUE_TYPE *sourceQueue = &timerVector[i];
            TIMER_QUEUE_TYPE *moveQueue = 0 == i ? &fireQueue : &tempQueue;
            // scan expirations of all timers in the queue, and 
            // add it into tempQueue if the expiration is less than 
            // than the magnitude of this level 
            // or into fireQueue to fire later
            timerScanExpirations(sourceQueue, moveQueue, current); 
            if (0 < i && moveQueue->head) {
                // migrate all timers from tempQueue to the lower level
                timerMigrateQueue(moveQueue, &timerVector[i - 1]); 
            }

            // continue scanning the next level queue only when 
            // the count of scanning the current queue reaches MAGNITUDE
            sourceQueue->scan++; 
            if (sourceQueue->scan < MAGNITUDE) {
                break; 
            } else {
                sourceQueue->scan = 0; 
            }
        }
        timerFireQueue(&fireQueue); 
    }
    return NULL; 
}


static void timerScanExpirations(TIMER_QUEUE_TYPE *sourceQueue, TIMER_QUEUE_TYPE *targetQueue, time_t current)
{
    assert(sourceQueue && targetQueue); 
    assert(!targetQueue->head);
    for (TIMER_TYPE *timer = sourceQueue->head, *next = NULL; timer; timer = next) {
        next = timer->next; 
        if (timer->expiration - current < sourceQueue->magnitude) {
            timerDequeue(sourceQueue, timer); 
            timerEnqueue(targetQueue, timer);
        }
    }
}

static void timerMigrateQueue(TIMER_QUEUE_TYPE *sourceQueue, TIMER_QUEUE_TYPE *targetQueue)
{
    assert(sourceQueue && targetQueue); 
    assert(sourceQueue->head);
    for (TIMER_TYPE *timer = sourceQueue->head, *next = NULL; timer; timer = next) {
        next = timer->next;
        timerDequeue(sourceQueue, timer); 
        timerEnqueue(targetQueue, timer);
    }
    assert(!sourceQueue->head);
}

static void timerFireQueue(TIMER_QUEUE_TYPE *queue)
{
    assert(queue); 
    // fire each timer in the queue
    for (TIMER_TYPE *timer = queue->head; timer; timer = timer->next) {
        TIMER_CALLBACK_FUNC func = timer->callBackFunc; 
        func(&timer->expiration, timer->duration); 
    }
    // clean the queue and put the periodic timer back 
    for (TIMER_TYPE *timer = queue->head, *next = NULL; timer; timer = next) {
        next = timer->next; 
        if (timer->isPeriodic) {
            timerReset(timer); 
        } else {
            timerStop(timer); 
        }
    }
}

static int initTimerQueue(TIMER_QUEUE_TYPE* queue, int magnitude) {
    assert(queue); 
    assert(0 < magnitude);
    queue->head = NULL; 
    int result = sem_init(&(queue->semaphore), 0, 1);
    if (result != 0) {
        return -1; 
    }
    queue->scan = 0; 
    queue->magnitude = magnitude; 
    return OK; 
}

void timerAssertQueue(TIMER_QUEUE_TYPE *queue) {
    assert(queue); 
    TIMER_TYPE *prev = NULL; 
    for (TIMER_TYPE *curr = queue->head; curr; curr = curr->next) {
        if (curr->queue != queue || curr->prev != prev) {
            printf("something wrong here");
        }
        assert(curr->queue == queue); 
        assert(curr->prev == prev); 
        prev = curr; 
    }
    if (prev && !prev->next) {
        printf("something wrong here");
    }
    assert(!prev || !prev->next);
}

// ensure the timers in the queue are sorted based on their expirations in the ascending order
static void timerEnqueue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer) {
    assert(queue); 
    timerAssertInactive(timer);
    
    sem_wait(&(queue->semaphore));
    timerAssertQueue(queue);
    
    TIMER_TYPE *prev = NULL; 
    for (TIMER_TYPE *curr = queue->head; curr && curr->expiration <= timer->expiration; curr = curr->next) {
        prev = curr; 
    }
    if (!prev) {
        // add as the new front
        timer->next = queue->head;
        queue->head = timer; 
    } else {
        // add in the middle after prev
        timer->next = prev->next; 
        timer->prev = prev;
        if (prev->next) {
            prev->next->prev = timer; 
        } 
        prev->next = timer; 
    }
    timer->queue = queue;

    timerAssertQueue(queue);
    sem_post(&(queue->semaphore));

    assert(timer->queue);
    assert(queue->head);
}

static void timerDequeue(TIMER_QUEUE_TYPE *queue, TIMER_TYPE *timer) {
    assert(queue && timer);
    assert(queue->head); 
    assert(queue == timer->queue);
    
    sem_wait(&(queue->semaphore));
    timerAssertQueue(queue);

    if (timer->prev) {
        timer->prev->next = timer->next; 
    } else {
        if (queue->head != timer) {
            printf("something wrong here.");
        }
        assert(queue->head == timer);
        queue->head = timer->next;
    }
    if (timer->next) {
        timer->next->prev = timer->prev; 
    }        
    timer->prev = timer->next = NULL; 
    timer->queue = NULL; 

    timerAssertQueue(queue);
    sem_post(&(queue->semaphore));

    assert(!queue->head || !queue->head->prev);
}

// find the target queue according to the timer duration
static TIMER_QUEUE_TYPE *timerGetTargetQueue(TIMER_TYPE *timer)
{
    timerAssertInactive(timer);
    int count = 0; 
    for (int duration = timer->duration; duration; duration /= MAGNITUDE) {
        count++;
    }
    int id = count >= TIMER_VECTOR_MAX ? TIMER_VECTOR_MAX - 1 : count - 1; 
    assert(0 <= id && id < TIMER_VECTOR_MAX);
    return &timerVector[id]; 
}

/******************************************************************************
* Usage examples and tests for timers
******************************************************************************/
void durationTimerDemo(int duration ) {
    printf("test the normal timer with duration: %d\n", duration);
    TIMER_TYPE *timer = timerCreate(duration, timer_default_handler, false); 
    timerStart(timer); 
    int remains = timerGetTime(timer); 
    timerStop(timer); 
    timerSetCallBack(timer, timer_default_handler); 
    timerSetPeriodic(timer, true); 
    assert(timerIsPeriodic(timer)); 
    timerSetDuration(timer, 30); 
    timerSetPeriodic(timer, false); 
    assert(!timerIsPeriodic(timer)); 
    timerStart(timer); 
    assert(!timerIsExpired(timer)); 
    sleep(duration * 4);
    assert(timerIsExpired(timer)); 
}

void periodicTimerDemo(int duration) {
    printf("test the periodic timer with duration: %d\n", duration);
    TIMER_TYPE *timer = timerCreate(duration, timer_default_handler, true); 
    assert(timerIsPeriodic(timer));  
    timerStart(timer); 
    assert(!timerIsExpired(timer)); 
    sleep(duration * 8);
    timerStop(timer); 
}

void* threadMultipleTimer(void *arg) {
#define CREATE_MAX 5
    intptr_t id = (intptr_t) arg; 
    printf("Thread arg: %d creates timers\n", id); 
    int maxDuration = id * MAGNITUDE; 
    TIMER_TYPE *timers[CREATE_MAX];
    for (int i = 0; i < CREATE_MAX; ++i){
        int duration = rand() % maxDuration + 1; 
        bool isPeriodic = (MAGNITUDE < duration) && (duration & 3); 
        timers[i] = timerCreate(duration, timer_default_handler, isPeriodic); 
        timerStart(timers[i]); 
    }
    sleep(maxDuration * 8); 
    for (int i = 0; i < CREATE_MAX; ++i){
        timerStop(timers[i]); 
    }
}

void singleThreadTimerDemo() {    
#define CASE_MAX 4
    int durations[CASE_MAX] = {8, 18, 30, 101};
    for (int i = 0; i < CASE_MAX; ++i) {
        durationTimerDemo(durations[i]); 
        periodicTimerDemo(durations[i]); 
    }
}

void pureTimerTest() {
    multipleThreadsDemo(threadMultipleTimer);
    singleThreadTimerDemo(); 
} 

int startThreadTimerFire() {
    pthread_t fireThread; 
    int result = pthread_create(&fireThread, NULL, timerFire, NULL); 
    if (OK != result) {
        return -1; 
    }
    pthread_detach(fireThread);
}

void handleTimerDemo() {
    int duration = 8; 
    HANDLE timerHandle = handleTimerCreate(duration, timer_default_handler, false);
    handleTimerStart(timerHandle); 
    sleep(duration * 4);
    handleTimerStop(timerHandle); 
}

int main() {    
    initializeSystemHandles();

    initAllTimerQueues();
    startThreadTimerFire(); 
    
    handleTest(); 
    
    pureTimerTest(); 

    handleTimerDemo(); 
    
    printf("Hello, World!\n");
    return 0;
}
