# C++ Re-entry

## Step 1: Environment Setup

### check C++ compiler version 

// check g++ version
g++ --version
// compile a file
g++ -std=c++20 -Wall -Wextra -O2 helloworld.cpp -o helloworld
// open a file
code helloworld.cpp 

## Terms

### RAII = Resource Acquisition Is Initialization (资源获取即初始化)

It means:

* Tie the lifetime of a resource to the lifetime of an object.
* The resource is acquired in the object’s constructor, and automatically released in its destructor.
So when the object goes out of scope, the destructor runs, and the resource is freed safely — no leaks, no dangling states.

Examples of Resources

* Memory (new/delete)
* File handles
* Mutex locks
* Network sockets
* Database connections
  
Why RAII Matters

* Prevents resource leaks (no forgotten delete or close)
* Provides exception safety (resources cleaned even if an exception is thrown)
* Encourages deterministic cleanup (resources released immediately at end of scope, unlike garbage-collected languages)

If asked “What is RAII?”:

RAII is a C++ idiom where resource management (like memory, file handles, locks) is bound to the lifetime of an object. The resource is acquired in the constructor and released in the destructor, ensuring automatic cleanup, exception safety, and no leaks.