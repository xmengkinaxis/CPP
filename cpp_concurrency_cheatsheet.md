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