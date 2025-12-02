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

## 结束
如需，我可以：
- 给你生成 PDF 版本
- 把每个 pattern 添加实际案例
- 给你生成可编译 C++ 示例项目
- 加上图解（锁竞争、死锁、线程池模型）

