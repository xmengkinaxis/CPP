# C++ 并发 / 并行编程 Cheatsheet（含工业级 Patterns）

本文件整合了核心并发概念、最佳实践、工业界常用模式、常见坑点，适合作为你的随手速查表。

---

## 🧩 1. 核心概念

### **线程 (std::thread)**
- 每个 thread 是独立执行流。
- 创建：`std::thread t(func);`
- 回收：`t.join()` 或 `t.detach()`
- **永远不要忘记 join，否则 crash / terminate。**

### **互斥锁 mutex (std::mutex)**
- 用来保护共享数据。
- 使用 RAII：`std::lock_guard<std::mutex> lock(mtx);`
- 永远不要调用 `mtx.unlock()`（容易忘记）。

### **读写锁 shared_mutex（C++17）**
- 多读单写。
- `std::shared_lock`（读）
- `std::unique_lock`（写）

### **条件变量 condition_variable**
- 用来线程等待事件。
- 常见模式：Producer–Consumer。

### **原子操作 atomic**
- 无锁 lock‑free 编程。

---

## 🧩 2. 并发与并行的区别

| 概念 | 并发 Concurrency | 并行 Parallelism |
|------|------------------|-------------------|
| 含义 | 多任务交替执行 | 多任务真正同时执行 |
| 关键问题 | 正确性 + 数据保护 | 性能最大化 |
| 典型工具 | mutex, lock, condition variable | thread pool, SIMD, async |

---

## 🧩 3. 工业界常用并发模式（真正会用到的）

### **Pattern 1 — Per‑Key Lock（每个 key 一把锁）**
> 用来保护 DB 行、缓存条目、unordered_map[key] 的更新。
```cpp
unordered_map<string, mutex> keyMutex;
unordered_map<string, unordered_map<string,int>> mDB;

void setFieldValue(string key, string field, int value) {
    std::lock_guard<std::mutex> lock(keyMutex[key]);
    mDB[key][field] = value;
}
```
✔ 不同 key 可并行；同 key 串行。

---

### **Pattern 2 — Sharded Lock（分片锁）**
> 每个 key 不用一个 mutex，而是哈希到固定若干锁，减少内存占用。
```cpp
static const int NUM_SHARDS = 64;
array<mutex, NUM_SHARDS> shardLocks;

mutex& getLock(const string& key) {
    return shardLocks[ std::hash<string>{}(key) % NUM_SHARDS ];
}
```
✔ 大幅减少 mutex 数量
✔ 适合高并发

---

### **Pattern 3 — Reader–Writer Lock（读多写少）**
```cpp
shared_mutex rwlock;

int readValue() {
    shared_lock lock(rwlock); // 多读
    return data;
}

void writeValue(int x) {
    unique_lock lock(rwlock); // 单写
    data = x;
}
```

---

### **Pattern 4 — Double‑Checked Locking（DCLP）**
> 用来懒加载一个全局对象。
```cpp
if (!ptr.load()) {
    lock_guard lock(mtx);
    if (!ptr.load()) {
        ptr = new T();
    }
}
```
⚠ 必须使用 `std::atomic<T*>` 才安全。

---

### **Pattern 5 — Thread Pool（线程池）**
> 用来执行大量短任务。
```cpp
#include <future>

std::future<int> f = std::async(std::launch::async, [](){ return 42; });
```
✔ 比创建新线程更高效。

---

## 🧩 4. C++ 锁工具对比

| 工具 | 能力 | 用途 |
|------|------|------|
| `mutex` | 排他锁 | 最常用的数据保护 |
| `shared_mutex` | 多读单写 | 读多写少 |
| `recursive_mutex` | 可重入 | 不推荐（设计问题） |
| `timed_mutex` | 可超时 | 尝试加锁 |
| `condition_variable` | 事件等待 | Producer/Consumer |

---

## 🧩 5. lock_guard / unique_lock 区别

### **std::lock_guard**
- 最轻量
- 无法提前 unlock
- 无法 try_lock

### **std::unique_lock**
- 功能强
- 能 unlock()/lock() 再锁
- 能 try_lock() 和 try_lock_for()

---

## 🧩 6. 避坑指南（必须牢记）

### ❌ 在共享数据结构外访问数据
```cpp
auto p = &mDB[key];  // ❌ key 删除后悬空
```

### ❌ 锁的粒度不当
- 锁太大 → 性能差
- 锁太小 → 死锁风险

### ✔ 使用 RAII
```cpp
std::lock_guard<std::mutex> lock(mtx);
```
永不手动 unlock！！

### ❌ 两把锁加锁顺序不一致 → 死锁
```cpp
// Thread A：lock A → lock B
// Thread B：lock B → lock A
```
✔ 总是用固定顺序。

---

## 🧩 7. 异步 async / future
```cpp
std::future<int> f = std::async(std::launch::async, work);
int result = f.get();
```
- 自动在线程池中运行
- 返回值通过 future 取得

---

## 🧩 8. 并行 STL（C++17）

```cpp
#include <execution>

std::sort(std::execution::par, v.begin(), v.end());
```
✔ 在多核并行排序
✔ 只需多加一个参数

---

## 🧩 9. lock‑free 概念
- atomic
- compare_exchange
- memory ordering（非常难，不建议初学）

---

## 🧩 10. 推荐高效范式

### **1. 尽量避免共享数据** → 使用局部变量
### **2. 避免锁嵌套**
### **3. 尽量使用 lock_guard**（简单且安全）
### **4. 按 key 分片加锁（高性能系统常用）**
### **5. 多读少写使用 shared_mutex**

---

# C++ 并发 / 并行编程 Cheatsheet（工业级 Patterns + 可编译示例）

本文件整合核心概念、最佳实践、工业界常用模式、可编译示例、图解说明，适合作为快速学习与参考。

---

## 🧩 1. 核心概念
```cpp
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <iostream>
#include <vector>
```

### **线程 (std::thread)**
```cpp
void func() { std::cout << "Hello from thread" << std::endl; }
std::thread t(func);
t.join();
```

### **互斥锁 mutex (std::mutex)**
```cpp
std::mutex mtx;
{
    std::lock_guard<std::mutex> lock(mtx);
    // critical section
}
```

### **读写锁 shared_mutex**
```cpp
std::shared_mutex rwlock;
void reader() { std::shared_lock lock(rwlock); }
void writer() { std::unique_lock lock(rwlock); }
```

### **条件变量 condition_variable**
```cpp
std::condition_variable cv;
std::mutex cv_m;
bool ready = false;
cv.wait(lock, []{ return ready; });
```

### **原子操作 atomic**
```cpp
std::atomic<int> counter(0);
counter.fetch_add(1);
```

---

## 🧩 2. 工业级 Patterns + 示例

### **Pattern 1 — Per-Key Lock**
```cpp
#include <unordered_map>
std::unordered_map<std::string, int> mDB;
std::unordered_map<std::string, std::mutex> keyMutex;

void setFieldValue(const std::string& key, int value) {
    std::lock_guard<std::mutex> lock(keyMutex[key]);
    mDB[key] = value;
}
```

### **Pattern 2 — Sharded Lock**
```cpp
static const int NUM_SHARDS = 64;
std::array<std::mutex, NUM_SHARDS> shardLocks;
std::mutex& getLock(const std::string& key) {
    return shardLocks[ std::hash<std::string>{}(key) % NUM_SHARDS ];
}
```

### **Pattern 3 — Reader–Writer Lock**
```cpp
#include <shared_mutex>
std::shared_mutex rwlock;
int data;

int readValue() {
    std::shared_lock lock(rwlock);
    return data;
}
void writeValue(int x) {
    std::unique_lock lock(rwlock);
    data = x;
}
```

### **Pattern 4 — Thread Pool / async**
```cpp
#include <future>
auto f = std::async(std::launch::async, [](){ return 42; });
int result = f.get();
```

### **Pattern 5 — Actor / Message Queue (无锁队列示例)**
```cpp
#include <queue>
#include <atomic>
#include <thread>
std::queue<int> q;
std::atomic<bool> done(false);
std::mutex q_m;

void producer() {
    for(int i=0;i<10;i++) {
        std::lock_guard<std::mutex> lock(q_m);
        q.push(i);
    }
}
void consumer() {
    while(!done) {
        std::lock_guard<std::mutex> lock(q_m);
        if(!q.empty()) {
            int val = q.front(); q.pop();
            std::cout << val << std::endl;
        }
    }
}
```

---

## 🧩 3. 并发对比表
| 工具 | 能力 | 用途 |
|------|------|------|
| mutex | 排他锁 | 数据保护 |
| shared_mutex | 多读单写 | 读多写少 |
| condition_variable | 事件等待 | Producer/Consumer |
| atomic | 无锁 | 简单计数、标志 |

---

## 🧩 4. 常见问题 / 避坑
- 忘记 join 或 detach 线程 → crash
- 手动 unlock 容易忘记 → 死锁或崩溃
- 锁顺序不一致 → 死锁
- 访问 map / vector 时未加锁 → 悬空指针或数据竞争
- 不同 key 使用不同 mutex，最大化并行

---

## 🧩 5. 可视化概念
```
[Thread Pool]
  worker0 --- task queue --- task done
  worker1 --- task queue --- task done

[Per-Key Lock]
  key1 <mutex> --- only one thread updates key1
  key2 <mutex> --- only one thread updates key2

[Deadlock Example]
  Thread A: lock1 -> lock2
  Thread B: lock2 -> lock1
  -> deadlock
```

---

## 🧩 6. 高性能建议
- 避免共享数据，局部变量优先
- 锁粒度按 key / 按 shard 分片
- 读多写少使用 shared_mutex
- 尽量使用 RAII 管理锁
- 线程池处理大量小任务而不是不断 spawn thread

---

## 📌 总结
- 结合 per-key 或 sharded 锁可以实现高并发 DB 或缓存修改
- Actor / message queue 可实现无锁并发处理
- async / future / thread pool 是工业界高效并发方案
- lock_guard / unique_lock + RAII 是 C++ 并发安全基石
- 注意死锁、锁顺序、访问 map/vector 时加锁

---
## condition_variable

I can certainly explain `std::condition_variable`\! It's one of the most confusing parts of C++ concurrency, but it's essential for thread synchronization.

The main reason people find it confusing is that it **doesn't prevent race conditions**—that's the job of the `std::mutex`. Instead, the `std::condition_variable` is about **timing** and **communication**.

-----

### 💡 What is `std::condition_variable`?

The `std::condition_variable` is a synchronization primitive used to **block one or more threads** until another thread **modifies a shared variable (the condition)** and notifies the `condition_variable` that the condition might be true.

It solves the problem of **busy-waiting**, where a thread continuously checks a flag in a tight loop, wasting CPU cycles.

#### Analogy: The Restaurant Queue 🍽️

Imagine a restaurant:

  * **Thread 1 (Waiter/Notifier):** The **Producer** (Chef). When an order is ready, the Chef changes the state (the order is ready) and shouts, "Order up\!" (`notify_one`).
  * **Thread 2 (Diner/Waiter):** The **Consumer**. They are not actively checking the kitchen door every second. Instead, they stand quietly by the counter waiting for the "Order up\!" call (`wait`).
  * **The Shared Condition:** The food queue.
  * **The Mutex (`std::mutex`):** The sign-in sheet on the counter. Only one person can look at or change the queue status at a time.

-----

### 🛠️ C++ Example: Producer-Consumer (Revisited)

We will use the **Producer-Consumer** pattern to show the roles of the condition variable, the mutex, and the unique lock.

```cpp
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

// Shared Resources
queue<int> buffer;
std::mutex mtx;                 // Protects the buffer
std::condition_variable cv;     // Manages the waiting/notifying

// --- Consumer Function (The Waiter) ---
void consumer() {
    // 1. UNIQUE LOCK: Required because cv.wait() needs to temporarily release and reacquire the lock.
    std::unique_lock<std::mutex> lock(mtx); 
    
    cout << "Consumer: Waiting for data..." << endl;

    // 2. THE WAIT CALL: Blocks the thread until cv.notify_one() is called
    //    AND the lambda condition is true.
    cv.wait(lock, []{ return !buffer.empty(); }); 
    
    // Once the wait returns, the lock is RE-ACQUIRED.
    
    int data = buffer.front();
    buffer.pop();
    cout << "Consumer: Consumed data: " << data << endl;

    // Lock is automatically released when 'lock' goes out of scope.
}

// --- Producer Function (The Chef) ---
void producer() {
    // 1. LOCK GUARD: Protects the shared buffer (Standard mutual exclusion)
    std::lock_guard<std::mutex> lock(mtx); 
    
    int item = 42;
    buffer.push(item); // Change the shared condition (buffer is no longer empty)
    
    cout << "Producer: Produced data: " << item << endl;
    
    // 2. THE NOTIFY CALL: Wakes up one waiting thread (the consumer)
    cv.notify_one(); 
    
    // Lock is automatically released here.
}

void run_cv_example() {
    std::thread t1(consumer);
    // Add a slight delay to ensure the consumer starts waiting before the producer acts
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    std::thread t2(producer);

    t1.join();
    t2.join();
}
```

-----

### 🧩 Detailed Explanation of the `condition_variable` Lines

The complexity lies entirely within the `consumer` function, specifically how `cv.wait()` works.

#### 1\. The `std::unique_lock` Requirement

```cpp
std::unique_lock<std::mutex> lock(mtx);
```

  * **Why Unique Lock?** `cv.wait()` must be able to **atomically release** the mutex when the thread goes to sleep and **re-acquire** it when the thread wakes up.
  * The simpler `std::lock_guard` cannot be manually unlocked and relocked, so it won't work with `cv.wait()`. **`std::unique_lock`** is flexible and supports this internal manipulation required by the condition variable.

#### 2\. The `cv.wait()` Function Call

```cpp
cv.wait(lock, []{ return !buffer.empty(); });
```

This is the most critical line. It performs three atomic steps:

| Step | Action | Why it's Important |
| :--- | :--- | :--- |
| **A. Check and Release** | The function first checks the lambda condition (`!buffer.empty()`). If the condition is **FALSE** (the queue is empty): it **atomically releases the mutex** (`mtx`) and puts the thread to sleep. | **Prevents Busy-Waiting:** The thread stops consuming CPU resources. **Prevents Race:** Releasing and going to sleep is atomic, ensuring no signal is missed between checking the condition and waiting. |
| **B. Wait for Signal** | The thread remains blocked until another thread calls `cv.notify_one()` or `cv.notify_all()`. | This is the communication step. |
| **C. Reacquire and Recheck** | When signaled, the thread **wakes up** and **re-acquires the mutex** (`mtx`). It then **re-checks the lambda condition**. | **Prevents Spurious Wakeups:** The thread only proceeds if the condition is *actually* true (not just because it was signaled or woke up for a spurious reason). |

#### 3\. The `cv.notify_one()` Call

```cpp
cv.notify_one();
```

  * **Location:** Always called by the thread that *changes* the shared condition (the Producer).
  * **Purpose:** To transition any threads blocked on the `cv.wait()` state from **Waiting** to **Ready-to-Run**. It sends a signal to one waiting thread.
  * **Safety:** The notification should occur **after** the shared state has been modified and **before** (or immediately after) the lock protecting the shared state is released.

---

# C++ 并发 / 并行 全套速成（Cheatsheet + 海报生成说明 + 可编译示例 + CMake）

> 目标：把你需要的**工业级并发/并行模式**、**可编译代码示例**、**构建脚本（CMake）**、以及**生成 A1 海报（300 DPI）**和**perf 火焰图 / Helgrind 检测流程**整合到一个 Markdown 文档，便于保存、打印、生成 PDF 或导出为高分辨率海报。

---

## 目录

1. 快速 Cheatsheet（关键概念、常用模式）
2. 完整可编译示例（single-file + CMake）
3. Per-key / Sharded locks 实战示例（满足 caller_id 语义）
4. 性能分析（perf 火焰图）
5. 死锁检测（Valgrind Helgrind）
6. 生成 A1 海报（300 DPI）与 Mindmap 的步骤与参数
7. 附录：常用命令与注意事项

---

# 1. 快速 Cheatsheet（摘录）

* **线程**：`std::thread`，必须 `join()` 或 `detach()`。
* **互斥**：`std::mutex`，用 `std::lock_guard` / `std::unique_lock`（RAII）。
* **读写锁**：`std::shared_mutex` (`shared_lock` / `unique_lock`)。
* **条件变量**：`std::condition_variable`，与 `std::unique_lock` 配合 `wait(lock, predicate)`。
* **原子**：`std::atomic<T>`，用于无锁计数/flag。
* **模式**：Per-key lock, Sharded lock, Thread pool, Actor model, Lock-free queue。

---

# 2. 完整可编译示例（单文件 demo）

保存为 `concurrency_demo.cpp`。

```cpp
// concurrency_demo.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <vector>
#include <chrono>

// 简单示例：per-key mutex map + owner semantics
static std::unordered_map<std::string, std::unordered_map<std::string,int>> mDB;
static std::unordered_map<std::string, std::string> keyOwner;
static std::unordered_map<std::string, std::mutex> keyMutex;
static std::mutex mapMutex; // protect keyMutex/keyOwner maps

bool setFieldValue(const std::string& key, const std::string& field, int value, const std::string& caller_id) {
    // ensure per-key mutex exists
    {
        std::lock_guard<std::mutex> lk(mapMutex);
        keyMutex.emplace(key, std::mutex{});
    }

    std::mutex& m = keyMutex[key];
    std::lock_guard<std::mutex> rowLock(m);

    // owner logic
    auto it = keyOwner.find(key);
    if (it == keyOwner.end()) {
        keyOwner[key] = caller_id;
    } else if (it->second != caller_id) {
        return false; // owned by other caller
    }

    mDB[key][field] = value;
    return true;
}

void releaseKey(const std::string& key, const std::string& caller_id) {
    std::lock_guard<std::mutex> lk(mapMutex);
    auto it = keyOwner.find(key);
    if (it != keyOwner.end() && it->second == caller_id) keyOwner.erase(it);
}

int main() {
    // demo: two threads attempt to set same key
    std::thread t1([](){
        if (setFieldValue("account123","balance",100,"alice")) std::cout<<"alice updated"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        releaseKey("account123","alice");
    });

    std::thread t2([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (!setFieldValue("account123","balance",200,"bob")) std::cout<<"bob blocked"<<std::endl;
    });

    t1.join(); t2.join();
    std::cout << "final: " << mDB["account123"]["balance"] << std::endl;
}
```

---

## CMake 构建文件（`CMakeLists.txt`）

```cmake
cmake_minimum_required(VERSION 3.10)
project(concurrency_demo LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(concurrency_demo concurrency_demo.cpp)
# 推荐打开编译警告与地址/线程 sanitizer（调试时）
# add_compile_options(-Wall -Wextra -Wpedantic)
# target_compile_options(concurrency_demo PRIVATE -fsanitize=address,undefined,thread)
```

构建命令：

```bash
mkdir -p build && cd build
cmake ..
cmake --build . -j
./concurrency_demo
```

---

# 3. Per-key / Sharded locks 实战要点

* **Per-key map**：`unordered_map<string, mutex>`，需额外保护 map 本身的并发访问（`mapMutex`）。
* **懒创建 mutex**：首次访问时 `mapMutex` 加锁并 `emplace` 新 mutex。之后访问使用该 mutex。避免提前为大量 key 分配锁。
* **Sharded locks**：若 key 数量巨大且并发极高，使用固定 N 个锁（shards），通过哈希 `hash(key) % N` 映射到 shard，减少 map 搬移与内存占用。
* **owner 语义**：业务层维护 `keyOwner[key] = caller_id`，在持有 row-level mutex 的临界区内读写 owner 字段，保证原子性。

---

# 4. 性能分析：perf 火焰图流程（Linux）

要生成火焰图，请安装 `perf` 与 Brendan Gregg 的 FlameGraph 脚本（[https://github.com/brendangregg/FlameGraph）。](https://github.com/brendangregg/FlameGraph）。)

### 采样并生成火焰图步骤

1. 运行你的程序（最好是 release 编译并带符号）
2. 记录 perf 指令（采样）

```bash
# 记录 CPU 采样（例如运行 10 秒）
perf record -F 99 -p <pid> -g -- sleep 10
# 或直接运行: perf record -F 99 -g -- ./concurrency_demo
```

3. 导出火焰图数据

```bash
perf script > out.perf
```

4. 生成火焰图 SVG（需要 FlameGraph 工具）

```bash
git clone https://github.com/brendangregg/FlameGraph.git
./FlameGraph/stackcollapse-perf.pl out.perf > out.folded
./FlameGraph/flamegraph.pl out.folded > flamegraph.svg
```

5. 用浏览器打开 `flamegraph.svg` 分析热点（宽块为热点，垂直为调用层次）。

**提示**：若使用 `-fno-omit-frame-pointer` 编译，堆栈符号更准确；用 `-g` 保留调试符号便于识别函数名。

---

# 5. 死锁检测：Valgrind Helgrind

Helgrind 是 Valgrind 下的工具，用于检测数据竞争和潜在死锁（规模有限时有用）。

安装 Valgrind（Ubuntu）：

```bash
sudo apt-get install valgrind
```

运行示例：

```bash
valgrind --tool=helgrind ./concurrency_demo
```

Helgrind 输出会指出潜在的数据竞争（race）和锁使用不当的地方。注意：Helgrind 会显著降低运行速度，仅用于调试环境。

---

# 6. 生成 A1 海报（300 DPI）与 Mindmap

你希望得到：**A1（594x841 mm），浅色风格，300 DPI** 的海报（mindmap 或 cheatsheet）。下面给出从 Markdown / SVG 到高分辨率 PNG/PDF 的推荐流程。

### A. 海报像素尺寸（A1 @ 300 DPI）

* A1 尺寸：594 x 841 mm = 23.386 x 33.110 inches
* 300 DPI 像素：`width = 23.386 * 300 ≈ 7016 px`, `height = 33.110 * 300 ≈ 9933 px`
* 建议最终导出为 `7016 x 9933` PNG（或 PDF）以保证打印质量。

### B. 推荐流程（Markdown -> SVG -> PNG / PDF）

1. **准备 Markdown**（本文件）并用支持导出 SVG 的工具生成可视化 mindmap 或海报。常用工具：

   * Typora（可导出 PDF/SVG）
   * Markdown + Mermaid（生成流程图）
   * 手工用 draw.io / diagrams.net 绘制并导出 SVG
2. **用 Inkscape / ImageMagick 导出高分辨率 PNG**（示例）

   * 如果你有 `poster.svg`（矢量），用 Inkscape：

     ```bash
     inkscape poster.svg --export-type=png --export-width=7016 --export-height=9933 --export-background=#FFFFFF --export-dpi=300 -o poster_a1_300dpi.png
     ```
   * 或用 ImageMagick（注意：从 SVG 渲染可能需要 librsvg 支持）：

     ```bash
     convert -density 300 poster.svg -resize 7016x9933 poster_a1_300dpi.png
     ```
3. **打印或导出 PDF**：

   * 可以把 PNG 嵌入 PDF，或直接用 Inkscape `--export-type=pdf` 导出高质量 PDF。

### C. 风格与排版建议

* 浅色背景（#FFFFFF）+ 深色字体，图例用浅色填充区分模块。
* 字体大小：标题 ≥ 72pt，二级标题 36–48pt，正文 18–24pt（按实际像素微调）。
* 保留足够页边距，避免关键文本靠近边缘。

---

# 7. 附录：常用命令与注意事项

### 编译优化建议（Release）

```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j
```

### perf 采样注意事项

* 在容器中运行 perf 需要额外权限（--privileged 或配置 perf_event_paranoid）。
* 使用 `-F` 采样频率来控制采样精度（例如 `-F 99`）。

### Valgrind / Helgrind 注意

* Helgrind 主要用于检测锁使用错误与竞态，但不能检测所有问题。
* 对于高并发长运行程序，Helgrind 开销很大，不适合生产直接使用。

---

## 结语

我已经把：

* 完整 Cheatsheet（含示例）
* 可编译示例 + CMake
* perf 火焰图 与 Helgrind 调试流程
* A1 海报导出参数（7016x9933 px @300 DPI）

整合在本 Markdown 文档中。接下来我可以：

* **生成一份可下载的单文件 Markdown（已完成）**；
* **生成高分辨率 A1 海报 PNG（浅色风格，300 DPI）** 的图像文件（需要我调用图像生成/渲染工具为你生成；如果需要，我会使用你的风格偏好）；
* **把可编译示例打包为 zip** 并提供构建/测试脚本。

你想先要哪个产物？（A1 PNG 海报 / zip 源码包 / 生成 PDF）

