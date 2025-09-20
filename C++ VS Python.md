
**C++ → Python containers cheat sheet** 

I’ll cover **vector, list, unordered\_map, unordered\_set, stack, queue, deque** in C++ and their closest **Python equivalents**, with **creation + common operations**.

- [🚀 C++ vs Python Containers Cheat Sheet](#-c-vs-python-containers-cheat-sheet)
  - [🔥 Examples Side by Side](#-examples-side-by-side)
    - [Vector vs List](#vector-vs-list)
    - [Unordered Map vs Dict](#unordered-map-vs-dict)
    - [Stack](#stack)
    - [Queue](#queue)
- [🚀 C++ vs Python Containers with Time Complexities](#-c-vs-python-containers-with-time-complexities)
  - [⚠️ Key Notes](#️-key-notes)
- [🚀 C++ vs Python Containers with Time Complexities](#-c-vs-python-containers-with-time-complexities-1)
  - [⚠️ Key Notes](#️-key-notes-1)
- [⚡ C++ STL vs Python Containers (with Time Complexities)](#-c-stl-vs-python-containers-with-time-complexities)
  - [1. **Vector → Python `list`**](#1-vector--python-list)
  - [2. **List → Python `deque`**](#2-list--python-deque)
  - [3. **Unordered Map → Python `dict`**](#3-unordered-map--python-dict)
  - [4. **Unordered Set → Python `set`**](#4-unordered-set--python-set)
  - [5. **Stack → Python `list` / `deque`**](#5-stack--python-list--deque)
  - [6. **Queue → Python `deque`**](#6-queue--python-deque)
  - [7. **Deque → Python `deque`**](#7-deque--python-deque)
- [📌 Summary Takeaways](#-summary-takeaways)
- [⚡ C++ STL vs Python Containers (with Time Complexities)](#-c-stl-vs-python-containers-with-time-complexities-1)
  - [1. **Vector → Python `list`**](#1-vector--python-list-1)
  - [2. **List → Python `deque`**](#2-list--python-deque-1)
  - [3. **Unordered Map → Python `dict`**](#3-unordered-map--python-dict-1)
  - [4. **Unordered Set → Python `set`**](#4-unordered-set--python-set-1)
  - [5. **Stack → Python `list` / `deque`**](#5-stack--python-list--deque-1)
  - [6. **Queue → Python `deque`**](#6-queue--python-deque-1)
  - [7. **Deque → Python `deque`**](#7-deque--python-deque-1)
- [📌 Summary Takeaways](#-summary-takeaways-1)
- [🚀 C++ vs Python Containers – Syntax Cheat Sheet](#-c-vs-python-containers--syntax-cheat-sheet)
  - [1. **Vector ↔ Python `list`**](#1-vector--python-list-2)
  - [2. **List ↔ Python `deque`**](#2-list--python-deque-2)
  - [3. **Unordered Map ↔ Python `dict`**](#3-unordered-map--python-dict-2)
  - [4. **Unordered Set ↔ Python `set`**](#4-unordered-set--python-set-2)
  - [5. **Stack ↔ Python `list`**](#5-stack--python-list)
  - [6. **Queue ↔ Python `deque`**](#6-queue--python-deque-2)
  - [7. **Deque ↔ Python `deque`**](#7-deque--python-deque-2)
- [🔑 Quick Memory Tips](#-quick-memory-tips)
- [🚀 C++ vs Python Containers – Extended Cheat Sheet](#-c-vs-python-containers--extended-cheat-sheet)
  - [8. **Priority Queue (Heap)**](#8-priority-queue-heap)
    - [✅ Example: Max-Heap in Python](#-example-max-heap-in-python)
    - [✅ Example: Min-Heap in Python](#-example-min-heap-in-python)
- [🚀 C++ vs Python Containers – Extended Cheat Sheet (with Ordered Containers)](#-c-vs-python-containers--extended-cheat-sheet-with-ordered-containers)
  - [9. **Ordered Map**](#9-ordered-map)
  - [10. **Ordered Set**](#10-ordered-set)
    - [✅ Example: Lower Bound with `bisect` in Python](#-example-lower-bound-with-bisect-in-python)
- [📝 C++ vs Python Containers – Quick Cheat Sheet](#-c-vs-python-containers--quick-cheat-sheet)
  - [⚡ Special Notes](#-special-notes)
- [🌟 BFS Example – C++ vs Python3](#-bfs-example--c-vs-python3)
    - [**C++ Implementation**](#c-implementation)
    - [**Python3 Implementation**](#python3-implementation)
- [🔑 Key Takeaways](#-key-takeaways)
- [🔑 Python Built-in Functions vs C++ STL](#-python-built-in-functions-vs-c-stl)
  - [1. **Length**](#1-length)
  - [2. **Sum**](#2-sum)
  - [3. **Min / Max**](#3-min--max)
  - [4. **Sorted**](#4-sorted)
  - [5. **Reversed**](#5-reversed)
  - [6. **Any / All**](#6-any--all)
  - [7. **Enumerate**](#7-enumerate)
  - [8. **Zip**](#8-zip)
  - [9. **Map / Filter**](#9-map--filter)
  - [10. **Set / Unique Elements**](#10-set--unique-elements)
- [📘 Python vs C++ Containers \& Functions Cheat Sheet](#-python-vs-c-containers--functions-cheat-sheet)
  - [🔎 Example Side-by-Side](#-example-side-by-side)
    - [Reverse a list/vector](#reverse-a-listvector)
    - [Filter evens](#filter-evens)
- [📘 Python vs C++ Built-in Functions \& STL – with Time Complexity](#-python-vs-c-built-in-functions--stl--with-time-complexity)
  - [🔎 Interview Highlights](#-interview-highlights)
    - [Example: Membership Test](#example-membership-test)
- [🌳 Greedy Algorithm Patterns with Python Templates](#-greedy-algorithm-patterns-with-python-templates)
  - [1️⃣ Interval Scheduling (Sort by Finish Time)](#1️⃣-interval-scheduling-sort-by-finish-time)
  - [2️⃣ Heap-based Choice (Drop Worst)](#2️⃣-heap-based-choice-drop-worst)
  - [3️⃣ Sort + Local Matching (Two Pointers)](#3️⃣-sort--local-matching-two-pointers)
  - [4️⃣ Monotonic Stack (Greedy Removal)](#4️⃣-monotonic-stack-greedy-removal)
  - [5️⃣ Prefix Greedy (Running Sum Reset)](#5️⃣-prefix-greedy-running-sum-reset)
  - [6️⃣ Two-pointer Shrink (From Both Ends)](#6️⃣-two-pointer-shrink-from-both-ends)
- [✅ Summary](#-summary)
- [📘 Python3 Competitive Programming Cheat Sheet (Built-in Functions)](#-python3-competitive-programming-cheat-sheet-built-in-functions)
    - [🔥 Specially useful in **LeetCode**:](#-specially-useful-in-leetcode)
- [🚀 C++ vs Python3 Competitive Programming Cheat Sheet](#-c-vs-python3-competitive-programming-cheat-sheet)
- [🚀 C++ vs Python3 Competitive Programming Cheat Sheet with Time Complexities](#-c-vs-python3-competitive-programming-cheat-sheet-with-time-complexities)
- [📌 String Operations in C++ vs Python3 (with Time Complexities)](#-string-operations-in-c-vs-python3-with-time-complexities)
    - [🔑 Competitive Programming Notes:](#-competitive-programming-notes)

---

# 🚀 C++ vs Python Containers Cheat Sheet

| C++ STL                            | Python Equivalent         | Creation                                                     | Common Operations                                                                                                                                                |
| ---------------------------------- | ------------------------- | ------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **`vector<T>`**                    | **`list`**                | `nums = [1, 2, 3]` <br> `nums = []`                          | `nums.append(x)` ← `push_back(x)` <br> `nums.pop()` ← `pop_back()` <br> `nums[i]` ← `nums[i]` <br> `len(nums)` ← `nums.size()`                                   |
| **`list<T>` (doubly-linked list)** | **`collections.deque`**   | `from collections import deque` <br> `dq = deque([1, 2, 3])` | `dq.append(x)` ← `push_back(x)` <br> `dq.appendleft(x)` ← `push_front(x)` <br> `dq.pop()` ← `pop_back()` <br> `dq.popleft()` ← `pop_front()`                     |
| **`unordered_map<K,V>`**           | **`dict`**                | `m = {"a": 1, "b": 2}` <br> `m = {}`                         | `m[k] = v` ← insert/update <br> `m.get(k, default)` ← lookup <br> `k in m` ← containsKey <br> `del m[k]` ← erase                                                 |
| **`unordered_set<T>`**             | **`set`**                 | `s = {1, 2, 3}` <br> `s = set()`                             | `s.add(x)` ← insert <br> `s.remove(x)` ← erase (KeyError if missing) <br> `s.discard(x)` ← erase safely <br> `x in s` ← contains                                 |
| **`stack<T>`**                     | **`list`** *(or `deque`)* | `st = []` <br> `st = deque()`                                | `st.append(x)` ← push <br> `st.pop()` ← pop <br> `st[-1]` ← top/peek <br> `len(st)` ← size                                                                       |
| **`queue<T>`**                     | **`collections.deque`**   | `q = deque()`                                                | `q.append(x)` ← enqueue <br> `q.popleft()` ← dequeue <br> `q[0]` ← front <br> `len(q)` ← size                                                                    |
| **`deque<T>`**                     | **`collections.deque`**   | `dq = deque([1, 2, 3])`                                      | `dq.append(x)` ← push\_back <br> `dq.appendleft(x)` ← push\_front <br> `dq.pop()` ← pop\_back <br> `dq.popleft()` ← pop\_front <br> `dq[0], dq[-1]` ← front/back |

---

## 🔥 Examples Side by Side

### Vector vs List

```cpp
// C++
vector<int> nums = {1,2,3};
nums.push_back(4);
nums.pop_back();
int x = nums[0];
```

```python
# Python
nums = [1,2,3]
nums.append(4)
nums.pop()
x = nums[0]
```

---

### Unordered Map vs Dict

```cpp
// C++
unordered_map<string,int> m;
m["apple"] = 2;
if (m.count("apple")) { int x = m["apple"]; }
```

```python
# Python
m = {}
m["apple"] = 2
if "apple" in m:
    x = m["apple"]
```

---

### Stack

```cpp
// C++
stack<int> st;
st.push(10);
int top = st.top();
st.pop();
```

```python
# Python
st = []
st.append(10)
top = st[-1]
st.pop()
```

---

### Queue

```cpp
// C++
queue<int> q;
q.push(1);
q.push(2);
int x = q.front();
q.pop();
```

```python
# Python
from collections import deque
q = deque()
q.append(1)
q.append(2)
x = q[0]
q.popleft()
```

---

✅ Rule of thumb:

* **C++ vector ↔ Python list**
* **C++ unordered\_map ↔ Python dict**
* **C++ unordered\_set ↔ Python set**
* **C++ stack/queue/deque ↔ Python deque (or list for stack)**

---

Perfect 👍 Let’s extend the cheat sheet with **time complexity comparisons** for the common operations, so you can see where **Python differs from C++ STL**.

---

# 🚀 C++ vs Python Containers with Time Complexities

| C++ STL                     | Python Equivalent       | Common Operations            | C++ Complexity           | Python Complexity                             |
| --------------------------- | ----------------------- | ---------------------------- | ------------------------ | --------------------------------------------- |
| **`vector<T>`**             | **`list`**              | `push_back(x)` / `append(x)` | **O(1) amortized**       | **O(1) amortized**                            |
|                             |                         | `pop_back()` / `pop()`       | **O(1)**                 | **O(1)**                                      |
|                             |                         | random access (`nums[i]`)    | **O(1)**                 | **O(1)**                                      |
|                             |                         | insert/erase at middle       | **O(n)**                 | **O(n)**                                      |
| **`list<T>` (linked list)** | **`deque`**             | `push_front` / `appendleft`  | **O(1)**                 | **O(1)**                                      |
|                             |                         | `push_back` / `append`       | **O(1)**                 | **O(1)**                                      |
|                             |                         | random access                | **O(n)**                 | **O(1)** for `deque[i]`, but slower than list |
| **`unordered_map<K,V>`**    | **`dict`**              | insert / lookup / erase      | **O(1) avg, O(n) worst** | **O(1) avg, O(n) worst**                      |
|                             |                         | iteration over keys/values   | **O(n)**                 | **O(n)**                                      |
| **`unordered_set<T>`**      | **`set`**               | insert / lookup / erase      | **O(1) avg, O(n) worst** | **O(1) avg, O(n) worst**                      |
| **`stack<T>`**              | **`list`** (or `deque`) | `push` / `append`            | **O(1)**                 | **O(1)**                                      |
|                             |                         | `pop`                        | **O(1)**                 | **O(1)**                                      |
|                             |                         | `top` / `[-1]`               | **O(1)**                 | **O(1)**                                      |
| **`queue<T>`**              | **`deque`**             | enqueue (`push` / `append`)  | **O(1)**                 | **O(1)**                                      |
|                             |                         | dequeue (`pop` / `popleft`)  | **O(1)**                 | **O(1)**                                      |
| **`deque<T>`**              | **`deque`**             | `push_front` / `appendleft`  | **O(1)**                 | **O(1)**                                      |
|                             |                         | `push_back` / `append`       | **O(1)**                 | **O(1)**                                      |
|                             |                         | `pop_front` / `popleft`      | **O(1)**                 | **O(1)**                                      |
|                             |                         | `pop_back` / `pop`           | **O(1)**                 | **O(1)**                                      |

---

## ⚠️ Key Notes

1. **Python list is a dynamic array** → works just like `std::vector` (good for append, pop\_back, random access; bad for insert/erase in the middle).

2. **Python deque is a doubly-linked list with blocks** (optimized for both ends). It’s the best choice for **queue** and **stack (if large)** operations.

3. **Python dict and set are hash-based** like `unordered_map` and `unordered_set`. Average **O(1)**, but worst case **O(n)** if hash collisions are bad (rare in practice).

4. Iterating through dict/set/list/deque is **O(n)** in both C++ and Python.

---

👉 So when porting algorithms from C++ to Python:

* Use **list** if you need random access and dynamic resizing.
* Use **deque** if you need **queue or stack** with efficient front operations.
* Use **dict/set** just like unordered\_map/unordered\_set.

---

Would you like me to also show you a **visual quick-reference code snippet (C++ vs Python side by side)** for each container so you can glance and remember quickly?

Perfect 👍 Let’s extend the cheat sheet with **time complexity comparisons** for the common operations, so you can see where **Python differs from C++ STL**.

---

# 🚀 C++ vs Python Containers with Time Complexities

| C++ STL                     | Python Equivalent       | Common Operations            | C++ Complexity           | Python Complexity                             |
| --------------------------- | ----------------------- | ---------------------------- | ------------------------ | --------------------------------------------- |
| **`vector<T>`**             | **`list`**              | `push_back(x)` / `append(x)` | **O(1) amortized**       | **O(1) amortized**                            |
|                             |                         | `pop_back()` / `pop()`       | **O(1)**                 | **O(1)**                                      |
|                             |                         | random access (`nums[i]`)    | **O(1)**                 | **O(1)**                                      |
|                             |                         | insert/erase at middle       | **O(n)**                 | **O(n)**                                      |
| **`list<T>` (linked list)** | **`deque`**             | `push_front` / `appendleft`  | **O(1)**                 | **O(1)**                                      |
|                             |                         | `push_back` / `append`       | **O(1)**                 | **O(1)**                                      |
|                             |                         | random access                | **O(n)**                 | **O(1)** for `deque[i]`, but slower than list |
| **`unordered_map<K,V>`**    | **`dict`**              | insert / lookup / erase      | **O(1) avg, O(n) worst** | **O(1) avg, O(n) worst**                      |
|                             |                         | iteration over keys/values   | **O(n)**                 | **O(n)**                                      |
| **`unordered_set<T>`**      | **`set`**               | insert / lookup / erase      | **O(1) avg, O(n) worst** | **O(1) avg, O(n) worst**                      |
| **`stack<T>`**              | **`list`** (or `deque`) | `push` / `append`            | **O(1)**                 | **O(1)**                                      |
|                             |                         | `pop`                        | **O(1)**                 | **O(1)**                                      |
|                             |                         | `top` / `[-1]`               | **O(1)**                 | **O(1)**                                      |
| **`queue<T>`**              | **`deque`**             | enqueue (`push` / `append`)  | **O(1)**                 | **O(1)**                                      |
|                             |                         | dequeue (`pop` / `popleft`)  | **O(1)**                 | **O(1)**                                      |
| **`deque<T>`**              | **`deque`**             | `push_front` / `appendleft`  | **O(1)**                 | **O(1)**                                      |
|                             |                         | `push_back` / `append`       | **O(1)**                 | **O(1)**                                      |
|                             |                         | `pop_front` / `popleft`      | **O(1)**                 | **O(1)**                                      |
|                             |                         | `pop_back` / `pop`           | **O(1)**                 | **O(1)**                                      |

---

## ⚠️ Key Notes

1. **Python list is a dynamic array** → works just like `std::vector` (good for append, pop\_back, random access; bad for insert/erase in the middle).

2. **Python deque is a doubly-linked list with blocks** (optimized for both ends). It’s the best choice for **queue** and **stack (if large)** operations.

3. **Python dict and set are hash-based** like `unordered_map` and `unordered_set`. Average **O(1)**, but worst case **O(n)** if hash collisions are bad (rare in practice).

4. Iterating through dict/set/list/deque is **O(n)** in both C++ and Python.

---

👉 So when porting algorithms from C++ to Python:

* Use **list** if you need random access and dynamic resizing.
* Use **deque** if you need **queue or stack** with efficient front operations.
* Use **dict/set** just like unordered\_map/unordered\_set.

---

Would you like me to also show you a **visual quick-reference code snippet (C++ vs Python side by side)** for each container so you can glance and remember quickly?

Great 👍 Let’s extend the **C++ vs Python Containers Cheat Sheet** with **time complexity comparisons** for common operations.

---

# ⚡ C++ STL vs Python Containers (with Time Complexities)

---

## 1. **Vector → Python `list`**

✅ Dynamic array

| Operation                  | C++ `vector`       | Python `list`      |
| -------------------------- | ------------------ | ------------------ |
| `push_back()` / `append()` | **O(1)** amortized | **O(1)** amortized |
| `pop_back()` / `pop()`     | **O(1)**           | **O(1)**           |
| Random access `v[i]`       | **O(1)**           | **O(1)**           |
| Insert/erase in middle     | **O(n)**           | **O(n)**           |
| Sort                       | **O(n log n)**     | **O(n log n)**     |

---

## 2. **List → Python `deque`**

✅ Doubly linked list (C++) vs Double-ended queue (Python)

| Operation                  | C++ `list` | Python `deque`                               |
| -------------------------- | ---------- | -------------------------------------------- |
| Push/pop front             | **O(1)**   | **O(1)**                                     |
| Push/pop back              | **O(1)**   | **O(1)**                                     |
| Random access              | **O(n)**   | **O(1)** for ends, **O(n)** for index lookup |
| Insert/erase with iterator | **O(1)**   | **O(n)** (must shift)                        |

👉 Python `deque` is not a linked list but a **block-based structure**, so random insertions are slower than C++ `list`.

---

## 3. **Unordered Map → Python `dict`**

✅ Hash map

| Operation     | C++ `unordered_map` | Python `dict`    |
| ------------- | ------------------- | ---------------- |
| Insert        | **O(1)** average    | **O(1)** average |
| Erase         | **O(1)** average    | **O(1)** average |
| Find / lookup | **O(1)** average    | **O(1)** average |
| Iteration     | **O(n)**            | **O(n)**         |

---

## 4. **Unordered Set → Python `set`**

✅ Hash set

| Operation               | C++ `unordered_set` | Python `set`     |
| ----------------------- | ------------------- | ---------------- |
| Insert                  | **O(1)** average    | **O(1)** average |
| Erase                   | **O(1)** average    | **O(1)** average |
| Lookup (`count` / `in`) | **O(1)** average    | **O(1)** average |
| Iteration               | **O(n)**            | **O(n)**         |

---

## 5. **Stack → Python `list` / `deque`**

✅ LIFO

| Operation | C++ `stack` | Python `list` | Python `deque` |
| --------- | ----------- | ------------- | -------------- |
| Push      | **O(1)**    | **O(1)**      | **O(1)**       |
| Pop       | **O(1)**    | **O(1)**      | **O(1)**       |
| Top/peek  | **O(1)**    | **O(1)**      | **O(1)**       |

---

## 6. **Queue → Python `deque`**

✅ FIFO

| Operation  | C++ `queue` | Python `deque` |
| ---------- | ----------- | -------------- |
| Push       | **O(1)**    | **O(1)**       |
| Pop        | **O(1)**    | **O(1)**       |
| Front/peek | **O(1)**    | **O(1)**       |

---

## 7. **Deque → Python `deque`**

✅ Double-ended queue

| Operation           | C++ `deque` | Python `deque` |
| ------------------- | ----------- | -------------- |
| Push/pop front      | **O(1)**    | **O(1)**       |
| Push/pop back       | **O(1)**    | **O(1)**       |
| Random access       | **O(1)**    | **O(1)**       |
| Insert/erase middle | **O(n)**    | **O(n)**       |

---

# 📌 Summary Takeaways

* **Python `list` ≈ C++ `vector`** (dynamic array, O(1) amortized append, O(n) insert in middle).
* **Python `deque` is closer to C++ `deque` than `list`**, but differs from `std::list` (not linked).
* **Python `dict` & `set` ≈ C++ `unordered_map` & `unordered_set`** (hash-based, O(1) average lookup).
* **Stacks & queues** in Python are typically built on `list` (for stack) and `deque` (for queue).

---

Would you like me to also add a **side-by-side syntax summary table** (like `push_back` vs `append`, `count` vs `in`, etc.) so you can quickly translate C++ → Python during LeetCode practice?

Great 👍 Let’s extend the **C++ vs Python Containers Cheat Sheet** with **time complexity comparisons** for common operations.

---

# ⚡ C++ STL vs Python Containers (with Time Complexities)

---

## 1. **Vector → Python `list`**

✅ Dynamic array

| Operation                  | C++ `vector`       | Python `list`      |
| -------------------------- | ------------------ | ------------------ |
| `push_back()` / `append()` | **O(1)** amortized | **O(1)** amortized |
| `pop_back()` / `pop()`     | **O(1)**           | **O(1)**           |
| Random access `v[i]`       | **O(1)**           | **O(1)**           |
| Insert/erase in middle     | **O(n)**           | **O(n)**           |
| Sort                       | **O(n log n)**     | **O(n log n)**     |

---

## 2. **List → Python `deque`**

✅ Doubly linked list (C++) vs Double-ended queue (Python)

| Operation                  | C++ `list` | Python `deque`                               |
| -------------------------- | ---------- | -------------------------------------------- |
| Push/pop front             | **O(1)**   | **O(1)**                                     |
| Push/pop back              | **O(1)**   | **O(1)**                                     |
| Random access              | **O(n)**   | **O(1)** for ends, **O(n)** for index lookup |
| Insert/erase with iterator | **O(1)**   | **O(n)** (must shift)                        |

👉 Python `deque` is not a linked list but a **block-based structure**, so random insertions are slower than C++ `list`.

---

## 3. **Unordered Map → Python `dict`**

✅ Hash map

| Operation     | C++ `unordered_map` | Python `dict`    |
| ------------- | ------------------- | ---------------- |
| Insert        | **O(1)** average    | **O(1)** average |
| Erase         | **O(1)** average    | **O(1)** average |
| Find / lookup | **O(1)** average    | **O(1)** average |
| Iteration     | **O(n)**            | **O(n)**         |

---

## 4. **Unordered Set → Python `set`**

✅ Hash set

| Operation               | C++ `unordered_set` | Python `set`     |
| ----------------------- | ------------------- | ---------------- |
| Insert                  | **O(1)** average    | **O(1)** average |
| Erase                   | **O(1)** average    | **O(1)** average |
| Lookup (`count` / `in`) | **O(1)** average    | **O(1)** average |
| Iteration               | **O(n)**            | **O(n)**         |

---

## 5. **Stack → Python `list` / `deque`**

✅ LIFO

| Operation | C++ `stack` | Python `list` | Python `deque` |
| --------- | ----------- | ------------- | -------------- |
| Push      | **O(1)**    | **O(1)**      | **O(1)**       |
| Pop       | **O(1)**    | **O(1)**      | **O(1)**       |
| Top/peek  | **O(1)**    | **O(1)**      | **O(1)**       |

---

## 6. **Queue → Python `deque`**

✅ FIFO

| Operation  | C++ `queue` | Python `deque` |
| ---------- | ----------- | -------------- |
| Push       | **O(1)**    | **O(1)**       |
| Pop        | **O(1)**    | **O(1)**       |
| Front/peek | **O(1)**    | **O(1)**       |

---

## 7. **Deque → Python `deque`**

✅ Double-ended queue

| Operation           | C++ `deque` | Python `deque` |
| ------------------- | ----------- | -------------- |
| Push/pop front      | **O(1)**    | **O(1)**       |
| Push/pop back       | **O(1)**    | **O(1)**       |
| Random access       | **O(1)**    | **O(1)**       |
| Insert/erase middle | **O(n)**    | **O(n)**       |

---

# 📌 Summary Takeaways

* **Python `list` ≈ C++ `vector`** (dynamic array, O(1) amortized append, O(n) insert in middle).
* **Python `deque` is closer to C++ `deque` than `list`**, but differs from `std::list` (not linked).
* **Python `dict` & `set` ≈ C++ `unordered_map` & `unordered_set`** (hash-based, O(1) average lookup).
* **Stacks & queues** in Python are typically built on `list` (for stack) and `deque` (for queue).

---

Would you like me to also add a **side-by-side syntax summary table** (like `push_back` vs `append`, `count` vs `in`, etc.) so you can quickly translate C++ → Python during LeetCode practice?

Perfect 👍 Let’s make a **side-by-side syntax translation table** between **C++ STL containers** and their **Python counterparts**.

This will let you quickly translate code while practicing LeetCode.

---

# 🚀 C++ vs Python Containers – Syntax Cheat Sheet

---

## 1. **Vector ↔ Python `list`**

| Operation   | C++ `vector<int> v;`        | Python `v = []`          |
| ----------- | --------------------------- | ------------------------ |
| Create      | `vector<int> v;`            | `v = []`                 |
| Append      | `v.push_back(x);`           | `v.append(x)`            |
| Access      | `v[i]`                      | `v[i]`                   |
| Size        | `v.size()`                  | `len(v)`                 |
| Remove last | `v.pop_back();`             | `v.pop()`                |
| Insert      | `v.insert(v.begin()+i, x);` | `v.insert(i, x)`         |
| Erase       | `v.erase(v.begin()+i);`     | `v.pop(i)`               |
| Iterate     | `for (auto x : v)`          | `for x in v:`            |
| Sort        | `sort(v.begin(), v.end());` | `v.sort()` / `sorted(v)` |

---

## 2. **List ↔ Python `deque`**

(C++ doubly linked list vs Python double-ended queue)

| Operation  | C++ `list<int> l;` | Python `from collections import deque; l = deque()` |
| ---------- | ------------------ | --------------------------------------------------- |
| Push front | `l.push_front(x);` | `l.appendleft(x)`                                   |
| Push back  | `l.push_back(x);`  | `l.append(x)`                                       |
| Pop front  | `l.pop_front();`   | `l.popleft()`                                       |
| Pop back   | `l.pop_back();`    | `l.pop()`                                           |
| Iterate    | `for (auto x : l)` | `for x in l:`                                       |

---

## 3. **Unordered Map ↔ Python `dict`**

| Operation | C++ `unordered_map<string,int> m;` | Python `m = {}`         |
| --------- | ---------------------------------- | ----------------------- |
| Insert    | `m["a"] = 1;`                      | `m["a"] = 1`            |
| Access    | `m["a"]`                           | `m["a"]`                |
| Find      | `if (m.count("a"))`                | `if "a" in m:`          |
| Erase     | `m.erase("a");`                    | `del m["a"]`            |
| Iterate   | `for (auto &p : m)`                | `for k,v in m.items():` |

---

## 4. **Unordered Set ↔ Python `set`**

| Operation | C++ `unordered_set<int> s;` | Python `s = set()`             |
| --------- | --------------------------- | ------------------------------ |
| Insert    | `s.insert(x);`              | `s.add(x)`                     |
| Erase     | `s.erase(x);`               | `s.remove(x)` / `s.discard(x)` |
| Find      | `if (s.count(x))`           | `if x in s:`                   |
| Iterate   | `for (auto x : s)`          | `for x in s:`                  |

---

## 5. **Stack ↔ Python `list`**

| Operation | C++ `stack<int> st;` | Python `st = []` |
| --------- | -------------------- | ---------------- |
| Push      | `st.push(x);`        | `st.append(x)`   |
| Pop       | `st.pop();`          | `st.pop()`       |
| Top       | `st.top()`           | `st[-1]`         |
| Empty?    | `st.empty()`         | `len(st) == 0`   |

---

## 6. **Queue ↔ Python `deque`**

| Operation | C++ `queue<int> q;` | Python `from collections import deque; q = deque()` |
| --------- | ------------------- | --------------------------------------------------- |
| Push      | `q.push(x);`        | `q.append(x)`                                       |
| Pop       | `q.pop();`          | `q.popleft()`                                       |
| Front     | `q.front()`         | `q[0]`                                              |
| Empty?    | `q.empty()`         | `len(q) == 0`                                       |

---

## 7. **Deque ↔ Python `deque`**

| Operation  | C++ `deque<int> d;` | Python `from collections import deque; d = deque()` |
| ---------- | ------------------- | --------------------------------------------------- |
| Push front | `d.push_front(x);`  | `d.appendleft(x)`                                   |
| Push back  | `d.push_back(x);`   | `d.append(x)`                                       |
| Pop front  | `d.pop_front();`    | `d.popleft()`                                       |
| Pop back   | `d.pop_back();`     | `d.pop()`                                           |
| Access     | `d[i]`              | `d[i]`                                              |

---

# 🔑 Quick Memory Tips

* **C++ `vector` ↔ Python `list`** (dynamic array).
* **C++ `list` ↔ Python `deque`** (but Python `deque` ≠ linked list, just block deque).
* **C++ `unordered_map` ↔ Python `dict`**.
* **C++ `unordered_set` ↔ Python `set`**.
* **C++ `stack` / `queue`** → Built using `list` / `deque` in Python.

---

👉 Do you also want me to include **priority queue / heap** (`std::priority_queue` vs `heapq` in Python)? That’s another very common one for LeetCode.
Great 👍 Let’s extend the cheat sheet with **Priority Queue / Heap** — this is one of the most important for LeetCode problems (like Dijkstra, K-th Largest, etc.).

---

# 🚀 C++ vs Python Containers – Extended Cheat Sheet

---

## 8. **Priority Queue (Heap)**

C++’s `priority_queue` is a **max-heap by default**.
Python’s `heapq` is a **min-heap by default**.

| Operation       | C++                                                  | Python                                                         |
| --------------- | ---------------------------------------------------- | -------------------------------------------------------------- |
| Create max-heap | `priority_queue<int> pq;`                            | `import heapq; pq = []` (store as `-val` to simulate max-heap) |
| Create min-heap | `priority_queue<int, vector<int>, greater<int>> pq;` | `heapq.heapify(pq)` (default)                                  |
| Push            | `pq.push(x);`                                        | `heapq.heappush(pq, x)`                                        |
| Pop top         | `pq.pop();`                                          | `heapq.heappop(pq)`                                            |
| Peek top        | `pq.top();`                                          | `pq[0]`                                                        |
| Size            | `pq.size()`                                          | `len(pq)`                                                      |
| Empty?          | `pq.empty()`                                         | `len(pq) == 0`                                                 |

---

### ✅ Example: Max-Heap in Python

```python
import heapq

pq = []
heapq.heappush(pq, -5)   # push 5
heapq.heappush(pq, -2)   # push 2
heapq.heappush(pq, -10)  # push 10

print(-pq[0])  # peek max -> 10
print(-heapq.heappop(pq))  # pop max -> 10
```

---

### ✅ Example: Min-Heap in Python

```python
import heapq

pq = []
heapq.heappush(pq, 5)
heapq.heappush(pq, 2)
heapq.heappush(pq, 10)

print(pq[0])  # peek min -> 2
print(heapq.heappop(pq))  # pop min -> 2
```

---

⚡ **Quick Mapping Reminder**:

* **C++ max-heap** = `priority_queue<int>`
* **C++ min-heap** = `priority_queue<int, vector<int>, greater<int>>`
* **Python** always uses `heapq` (min-heap). For max-heap → push `-x`, pop and negate.

---

👉 Do you want me to also include **ordered containers** like C++ `map` and `set` (which are tree-based, unlike unordered ones) and their closest Python equivalents?

Perfect 👍 Let's add **ordered containers** (`map`, `set`) in C++ and their **Python counterparts**.

---

# 🚀 C++ vs Python Containers – Extended Cheat Sheet (with Ordered Containers)

---

## 9. **Ordered Map**

* **C++**: `std::map` (implemented as balanced BST, keys are sorted).
* **Python**: Built-in `dict` (in **Python 3.7+**, insertion order is preserved, but not sorted).
  For a **sorted map**, use **`collections.OrderedDict`** or **`sortedcontainers.SortedDict`** (3rd-party library).

| Operation                    | C++                      | Python                                                               |
| ---------------------------- | ------------------------ | -------------------------------------------------------------------- |
| Create                       | `map<int, string> m;`    | `m = {}` or `from collections import OrderedDict; m = OrderedDict()` |
| Insert                       | `m[1] = "a";`            | `m[1] = "a"`                                                         |
| Access                       | `m[1]`                   | `m[1]`                                                               |
| Erase                        | `m.erase(1);`            | `del m[1]`                                                           |
| Find key                     | `m.find(1)`              | `1 in m`                                                             |
| Iterate keys (sorted in C++) | `for (auto &[k, v] : m)` | `for k, v in m.items():`                                             |
| Lower bound                  | `m.lower_bound(3)`       | `use bisect module on sorted(m.keys())`                              |

---

## 10. **Ordered Set**

* **C++**: `std::set` (balanced BST, sorted unique keys).
* **Python**: Built-in `set` is **hash-based (unordered)**.
  For a **sorted set**, use `sortedcontainers.SortedSet` (3rd-party).

| Operation               | C++                | Python                    |
| ----------------------- | ------------------ | ------------------------- |
| Create                  | `set<int> s;`      | `s = set()`               |
| Insert                  | `s.insert(5);`     | `s.add(5)`                |
| Erase                   | `s.erase(5);`      | `s.discard(5)`            |
| Find                    | `s.find(5)`        | `5 in s`                  |
| Iterate (sorted in C++) | `for (auto x : s)` | `for x in sorted(s):`     |
| Lower bound             | `s.lower_bound(3)` | `use bisect on sorted(s)` |

---

### ✅ Example: Lower Bound with `bisect` in Python

```python
import bisect

nums = [1, 3, 5, 7]
x = 4
pos = bisect.bisect_left(nums, x)  # lower_bound
print(pos)  # index where 4 can be inserted -> 2
```

---

⚡ **Quick Mapping Reminder**:

* `std::map` (C++) ≈ Python `dict` (insertion order preserved, but not sorted).
* `std::set` (C++) ≈ Python `set` (unordered).
* For **sorted behavior**, Python needs `bisect` or `sortedcontainers`.

---

👉 Would you like me to also add a **summary table of all containers (C++ ↔ Python)** in one place, so you have a quick "at-a-glance" reference?

Great 👍 Let’s wrap everything up into a **single summary table** so you can glance at C++ containers and their Python counterparts quickly.

---

# 📝 C++ vs Python Containers – Quick Cheat Sheet

| **C++ Container**        | **Python Counterpart**               | **Create**                                    | **Insert / Push**                   | **Access / Top**  | **Remove / Pop**               | **Iterate**             |
| ------------------------ | ------------------------------------ | --------------------------------------------- | ----------------------------------- | ----------------- | ------------------------------ | ----------------------- |
| **`vector<int>`**        | `list`                               | `nums = []`                                   | `nums.append(5)`                    | `nums[i]`         | `nums.pop()`                   | `for x in nums:`        |
| **`list` (linked list)** | `collections.deque`                  | `from collections import deque; dq = deque()` | `dq.append(x)` / `dq.appendleft(x)` | `dq[0]`, `dq[-1]` | `dq.pop()`, `dq.popleft()`     | `for x in dq:`          |
| **`unordered_map<K,V>`** | `dict`                               | `m = {}`                                      | `m[k] = v`                          | `m[k]`            | `del m[k]`                     | `for k,v in m.items():` |
| **`unordered_set`**      | `set`                                | `s = set()`                                   | `s.add(x)`                          | —                 | `s.remove(x)` / `s.discard(x)` | `for x in s:`           |
| **`stack<int>`**         | `list` (or `deque`)                  | `st = []`                                     | `st.append(x)`                      | `st[-1]`          | `st.pop()`                     | `while st:`             |
| **`queue<int>`**         | `collections.deque`                  | `q = deque()`                                 | `q.append(x)`                       | `q[0]`            | `q.popleft()`                  | `for x in q:`           |
| **`deque<int>`**         | `collections.deque`                  | `dq = deque()`                                | `dq.append(x)` / `dq.appendleft(x)` | `dq[0]`, `dq[-1]` | `dq.pop()`, `dq.popleft()`     | `for x in dq:`          |
| **`map<K,V>` (ordered)** | `dict` (insertion ordered in Py3.7+) | `m = {}`                                      | `m[k] = v`                          | `m[k]`            | `del m[k]`                     | `for k,v in m.items():` |
| **`set` (ordered)**      | `set` (unordered)                    | `s = set()`                                   | `s.add(x)`                          | —                 | `s.remove(x)`                  | `for x in sorted(s):`   |

---

## ⚡ Special Notes

* In **C++**:

  * `map` and `set` are **ordered (sorted)** by default.
  * `unordered_map` and `unordered_set` are **hash-based** (no order).

* In **Python**:

  * `dict` and `set` are **hash-based** (unordered by value).
  * From Python 3.7+, `dict` preserves **insertion order**.
  * Use `bisect` (or `sortedcontainers` library) if you need **sorted map/set** functionality.

---

✅ This table now covers **all containers you mentioned** (`vector`, `list`, `unordered_map`, `unordered_set`, `stack`, `queue`, `deque`, `map`, `set`) and their **Python equivalents** with basic operations.

---

Would you like me to also prepare a **side-by-side code example** (same algorithm in C++ vs Python, e.g. BFS with `queue`) to make the container usage differences crystal clear?

Perfect 👍 Let’s do a **side-by-side BFS example** (since it touches `queue`, `unordered_set`, `unordered_map`) to clearly see the **syntax difference** between **C++** and **Python**.

---

# 🌟 BFS Example – C++ vs Python3

We’ll implement BFS on a graph to check if a path exists between two nodes.

---

### **C++ Implementation**

```cpp
#include <bits/stdc++.h>
using namespace std;

bool bfs(int start, int target, unordered_map<int, vector<int>>& graph) {
    unordered_set<int> visited; 
    queue<int> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int node = q.front(); 
        q.pop();

        if (node == target) return true; 

        for (auto nei : graph[node]) {
            if (!visited.count(nei)) {
                visited.insert(nei);
                q.push(nei);
            }
        }
    }
    return false;
}

int main() {
    unordered_map<int, vector<int>> graph;
    graph[1] = {2, 3};
    graph[2] = {4};
    graph[3] = {5};
    graph[4] = {};
    graph[5] = {4};

    cout << bfs(1, 4, graph) << endl; // Output: 1 (true)
}
```

---

### **Python3 Implementation**

```python
from collections import deque

def bfs(start: int, target: int, graph: dict[int, list[int]]) -> bool:
    visited = set()
    q = deque([start])
    visited.add(start)

    while q:
        node = q.popleft()
        if node == target:
            return True
        for nei in graph.get(node, []):
            if nei not in visited:
                visited.add(nei)
                q.append(nei)
    return False


if __name__ == "__main__":
    graph = {
        1: [2, 3],
        2: [4],
        3: [5],
        4: [],
        5: [4]
    }
    print(bfs(1, 4, graph))  # Output: True
```

---

# 🔑 Key Takeaways

| Concept                 | **C++**                                                            | **Python3**                                                               |
| ----------------------- | ------------------------------------------------------------------ | ------------------------------------------------------------------------- |
| **Queue**               | `queue<int> q; q.push(x); q.front(); q.pop();`                     | `from collections import deque; q = deque([x]); q.append(x); q.popleft()` |
| **Set**                 | `unordered_set<int> visited; visited.insert(x); visited.count(x)`  | `visited = set(); visited.add(x); x in visited`                           |
| **Map**                 | `unordered_map<int, vector<int>> graph; graph[key].push_back(val)` | `graph = {}; graph[key] = [val1, val2]`                                   |
| **Loop over neighbors** | `for (auto nei : graph[node])`                                     | `for nei in graph[node]:`                                                 |

---

👉 Would you like me to also prepare a **DFS example (recursion)** in **C++ vs Python**, so you can see the difference for **stack usage** (explicit vs implicit recursion)?

Great question 👍 — this is one of the best ways to bridge **C++ STL** knowledge with **Python built-ins**.
Let’s make a **cheat sheet of common built-in functions** in Python, show examples, and compare with **C++ counterparts** (often in `<algorithm>` or STL).

---

# 🔑 Python Built-in Functions vs C++ STL

---

## 1. **Length**

* **Python:** `len(container)`
* **C++:** `.size()`

```python
nums = [1, 2, 3, 4]
print(len(nums))   # 4
```

```cpp
vector<int> nums = {1, 2, 3, 4};
cout << nums.size();  // 4
```

---

## 2. **Sum**

* **Python:** `sum(container)`
* **C++:** `accumulate(begin, end, init)` from `<numeric>`

```python
nums = [1, 2, 3, 4]
print(sum(nums))   # 10
```

```cpp
#include <numeric>
vector<int> nums = {1, 2, 3, 4};
cout << accumulate(nums.begin(), nums.end(), 0);  // 10
```

---

## 3. **Min / Max**

* **Python:** `min(container)`, `max(container)`
* **C++:** `*min_element(...)`, `*max_element(...)`

```python
nums = [3, 1, 7, 5]
print(min(nums))   # 1
print(max(nums))   # 7
```

```cpp
#include <algorithm>
vector<int> nums = {3, 1, 7, 5};
cout << *min_element(nums.begin(), nums.end());  // 1
cout << *max_element(nums.begin(), nums.end());  // 7
```

---

## 4. **Sorted**

* **Python:** `sorted(container)` → returns new list
* **C++:** `sort(begin, end)` → sorts in place

```python
nums = [3, 1, 7, 5]
print(sorted(nums))    # [1, 3, 5, 7]
```

```cpp
#include <algorithm>
vector<int> nums = {3, 1, 7, 5};
sort(nums.begin(), nums.end());  // nums = {1, 3, 5, 7}
```

---

## 5. **Reversed**

* **Python:** `reversed(container)`
* **C++:** `reverse(begin, end)`

```python
nums = [1, 2, 3]
print(list(reversed(nums)))  # [3, 2, 1]
```

```cpp
#include <algorithm>
vector<int> nums = {1, 2, 3};
reverse(nums.begin(), nums.end());  // {3, 2, 1}
```

---

## 6. **Any / All**

* **Python:** `any(iterable)`, `all(iterable)`
* **C++:** `any_of(begin, end, pred)`, `all_of(begin, end, pred)`

```python
nums = [0, 1, 0]
print(any(nums))   # True
print(all(nums))   # False
```

```cpp
#include <algorithm>
vector<int> nums = {0, 1, 0};
cout << any_of(nums.begin(), nums.end(), [](int x){ return x != 0; }); // true
cout << all_of(nums.begin(), nums.end(), [](int x){ return x != 0; }); // false
```

---

## 7. **Enumerate**

* **Python:** `enumerate(container)` → gives `(index, value)`
* **C++:** use `for (int i = 0; i < v.size(); i++)`

```python
nums = [10, 20, 30]
for i, val in enumerate(nums):
    print(i, val)
# 0 10
# 1 20
# 2 30
```

```cpp
vector<int> nums = {10, 20, 30};
for (int i = 0; i < nums.size(); i++) {
    cout << i << " " << nums[i] << endl;
}
```

---

## 8. **Zip**

* **Python:** `zip(list1, list2)`
* **C++:** no direct built-in → iterate manually or use `std::tuple`

```python
a = [1, 2, 3]
b = ['a', 'b', 'c']
for x, y in zip(a, b):
    print(x, y)
# 1 a
# 2 b
# 3 c
```

```cpp
vector<int> a = {1, 2, 3};
vector<char> b = {'a', 'b', 'c'};
for (int i = 0; i < a.size(); i++) {
    cout << a[i] << " " << b[i] << endl;
}
```

---

## 9. **Map / Filter**

* **Python:** `map(func, iterable)`, `filter(func, iterable)`
* **C++:** use `transform`, `copy_if`

```python
nums = [1, 2, 3]
print(list(map(lambda x: x*2, nums)))   # [2, 4, 6]
print(list(filter(lambda x: x%2==0, nums)))  # [2]
```

```cpp
#include <algorithm>
vector<int> nums = {1, 2, 3};
vector<int> doubled(nums.size());
transform(nums.begin(), nums.end(), doubled.begin(), [](int x){ return x*2; });
// doubled = {2, 4, 6}

vector<int> even;
copy_if(nums.begin(), nums.end(), back_inserter(even), [](int x){ return x % 2 == 0; });
// even = {2}
```

---

## 10. **Set / Unique Elements**

* **Python:** `set(container)`
* **C++:** `unordered_set` or `set`

```python
nums = [1, 2, 2, 3]
print(set(nums))  # {1, 2, 3}
```

```cpp
unordered_set<int> s = {1, 2, 2, 3}; 
// s = {1, 2, 3}
```

---

✅ These cover the **most common Python built-ins** and their **C++ STL equivalents**.

👉 Do you want me to extend this into a **reference table (one-liner mapping)** that you can use as a **quick lookup cheat sheet** for interviews?

Perfect 👍 Let’s make a **quick lookup reference table** — Python built-ins vs. C++ STL equivalents, with one-liner examples.

---

# 📘 Python vs C++ Containers & Functions Cheat Sheet

| **Concept**         | **Python (Built-in)**                       | **C++ (STL)**                                     | **Example**                                                                                 |
| ------------------- | ------------------------------------------- | ------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| **Length**          | `len(lst)`                                  | `vec.size()`                                      | Python: `len([1,2,3]) → 3` <br> C++: `vec.size();`                                          |
| **Sum**             | `sum(lst)`                                  | `accumulate(vec.begin(), vec.end(), 0)`           |                                                                                             |
| **Min / Max**       | `min(lst)`, `max(lst)`                      | `*min_element(...)`, `*max_element(...)`          |                                                                                             |
| **Sort**            | `sorted(lst)` (returns new)                 | `sort(vec.begin(), vec.end())` (in-place)         |                                                                                             |
| **Reverse**         | `list(reversed(lst))`                       | `reverse(vec.begin(), vec.end())`                 |                                                                                             |
| **Any / All**       | `any(lst)`, `all(lst)`                      | `any_of(...)`, `all_of(...)`                      |                                                                                             |
| **Index + Value**   | `enumerate(lst)`                            | `for (int i=0; i<vec.size(); i++)`                |                                                                                             |
| **Zip**             | `zip(a, b)`                                 | Manual loop over `for (int i=0; i<a.size(); i++)` |                                                                                             |
| **Map**             | `map(func, lst)`                            | `transform(begin, end, out, func)`                |                                                                                             |
| **Filter**          | `filter(pred, lst)`                         | `copy_if(begin, end, out, pred)`                  |                                                                                             |
| **Unique Elements** | `set(lst)`                                  | `unordered_set<int> s(lst.begin(), lst.end())`    |                                                                                             |
| **Membership**      | `x in lst`, `x in s`                        | `find(...) != end`, `s.count(x)`                  |                                                                                             |
| **Max Index**       | `max(range(len(lst)), key=lst.__getitem__)` | `distance(begin, max_element(...))`               |                                                                                             |
| **Min Index**       | `min(range(len(lst)), key=lst.__getitem__)` | `distance(begin, min_element(...))`               |                                                                                             |
| **Slicing**         | `lst[1:4]`                                  | Use iterators & `vector` constructor              | Python: `[1,2,3,4][1:3] → [2,3]` <br> C++: `vector<int> sub(vec.begin()+1, vec.begin()+3);` |

---

## 🔎 Example Side-by-Side

### Reverse a list/vector

```python
nums = [1, 2, 3]
print(list(reversed(nums)))   # [3, 2, 1]
```

```cpp
vector<int> nums = {1, 2, 3};
reverse(nums.begin(), nums.end()); // {3, 2, 1}
```

---

### Filter evens

```python
nums = [1, 2, 3, 4]
print(list(filter(lambda x: x%2==0, nums)))  # [2, 4]
```

```cpp
vector<int> nums = {1, 2, 3, 4}, evens;
copy_if(nums.begin(), nums.end(), back_inserter(evens), [](int x){ return x%2==0; });
// evens = {2, 4}
```

---

✅ This table gives you **fast equivalence mapping** between Python and C++.
Would you like me to also include **time complexity comparisons** (e.g., `len()` is O(1) vs `size()` is O(1), but `sum()` in Python is O(n), etc.) so you can use it in **interview prep**?

Awesome 🚀 Let’s extend the cheat sheet with **time complexity analysis** for Python built-ins vs. C++ STL equivalents.
This way you’ll know **which operations are safe in interviews and competitive coding**.

---

# 📘 Python vs C++ Built-in Functions & STL – with Time Complexity

| **Operation**       | **Python Built-in**                                        | **C++ STL Equivalent**                          | **Time Complexity**                             |
| ------------------- | ---------------------------------------------------------- | ----------------------------------------------- | ----------------------------------------------- |
| **Length**          | `len(lst)`                                                 | `vec.size()`                                    | **O(1)** both                                   |
| **Sum**             | `sum(lst)`                                                 | `accumulate(vec.begin(), vec.end(), 0)`         | **O(n)** both                                   |
| **Min / Max**       | `min(lst)`, `max(lst)`                                     | `*min_element(...)`, `*max_element(...)`        | **O(n)** both                                   |
| **Sort**            | `sorted(lst)` (new list) <br> `lst.sort()` (in-place)      | `sort(vec.begin(), vec.end())`                  | **O(n log n)** both                             |
| **Reverse**         | `reversed(lst)` (iterator) <br> `lst.reverse()` (in-place) | `reverse(vec.begin(), vec.end())`               | **O(n)** both                                   |
| **Any / All**       | `any(lst)`, `all(lst)`                                     | `any_of(...)`, `all_of(...)`                    | **O(n)** worst case                             |
| **Index + Value**   | `enumerate(lst)`                                           | `for (int i=0; i<vec.size(); i++)`              | **O(1)** per step                               |
| **Zip**             | `zip(a, b)`                                                | Manual loop with index                          | **O(n)** to iterate                             |
| **Map**             | `map(func, lst)`                                           | `transform(begin, end, out, func)`              | **O(n)** both                                   |
| **Filter**          | `filter(pred, lst)`                                        | `copy_if(begin, end, out, pred)`                | **O(n)** both                                   |
| **Unique Elements** | `set(lst)`                                                 | `unordered_set<int> s(lst.begin(), lst.end())`  | **O(n)** average                                |
| **Membership**      | `x in lst`                                                 | `find(...) != end`                              | Python list: **O(n)** <br> C++ vector: **O(n)** |
|                     | `x in s` (set/dict)                                        | `s.count(x)` (unordered\_set)                   | **O(1)** average                                |
| **Max Index**       | `max(range(len(lst)), key=lst.__getitem__)`                | `distance(begin, max_element(...))`             | **O(n)** both                                   |
| **Min Index**       | `min(range(len(lst)), key=lst.__getitem__)`                | `distance(begin, min_element(...))`             | **O(n)** both                                   |
| **Slicing**         | `lst[1:4]`                                                 | `vector<int> sub(vec.begin()+1, vec.begin()+4)` | **O(k)**, where k = slice length                |

---

## 🔎 Interview Highlights

* ✅ **len() vs size()** → both O(1).
* ⚠️ **Membership test** → `x in list` is O(n) in Python (like searching in `vector` in C++). Use `set` / `unordered_set` for O(1).
* ✅ **Sorting** → O(n log n) both.
* ✅ **Reversing** → O(n).
* ✅ **Map/Filter/Comprehension** in Python = O(n), same as `transform` or `copy_if` in C++.

---

### Example: Membership Test

```python
nums = [1, 2, 3, 4]
print(3 in nums)   # O(n)

s = {1, 2, 3, 4}
print(3 in s)     # O(1) average
```

```cpp
vector<int> nums = {1, 2, 3, 4};
cout << (find(nums.begin(), nums.end(), 3) != nums.end()); // O(n)

unordered_set<int> s = {1, 2, 3, 4};
cout << (s.count(3) > 0); // O(1) average
```

---

👉 This cheat sheet now shows **syntax + complexity** so you can confidently compare **Python vs C++** in interviews.

Do you want me to also prepare a **separate table for stack/queue/deque/priority\_queue** operations (push, pop, peek, etc.) in both Python and C++ with complexity?


Great 👍 Let’s expand the **Greedy Algorithm Decision Tree** into **Python templates** so you have both recognition patterns + code skeletons.

---

# 🌳 Greedy Algorithm Patterns with Python Templates

---

## 1️⃣ Interval Scheduling (Sort by Finish Time)

**Signal**: Problem involves **intervals with start & end** (meeting rooms, non-overlapping, arrows, etc.).
**Template**:

```python
def interval_scheduling(intervals):
    # Sort by end time
    intervals.sort(key=lambda x: x[1])
    count, end = 0, float("-inf")
    for s, e in intervals:
        if s >= end:
            count += 1
            end = e
    return count
```

🔹 Example: **435. Non-overlapping Intervals**, **452. Minimum Arrows to Burst Balloons**

---

## 2️⃣ Heap-based Choice (Drop Worst)

**Signal**: Problem involves **choosing items with deadlines/capacities** (courses, IPO, projects).
**Template**:

```python
import heapq

def resource_allocation(tasks):
    # Sort tasks by deadline (or end time)
    tasks.sort(key=lambda x: x[1])
    heap, total = [], 0
    for duration, deadline in tasks:
        total += duration
        heapq.heappush(heap, -duration)   # max-heap via negative
        if total > deadline:              # too many tasks → drop worst
            total += heapq.heappop(heap)  # remove largest duration
    return len(heap)
```

🔹 Example: **630. Course Schedule III**, **502. IPO**

---

## 3️⃣ Sort + Local Matching (Two Pointers)

**Signal**: Two groups (children & cookies, people & boats).
**Template**:

```python
def assign_resources(A, B):
    A.sort()
    B.sort()
    i = j = 0
    count = 0
    while i < len(A) and j < len(B):
        if A[i] <= B[j]:
            count += 1
            i += 1
        j += 1
    return count
```

🔹 Example: **455. Assign Cookies**, **1029. Two City Scheduling**

---

## 4️⃣ Monotonic Stack (Greedy Removal)

**Signal**: Optimize string/number by removing chars/digits.
**Template**:

```python
def greedy_stack(s, k):
    stack = []
    for ch in s:
        while stack and k > 0 and stack[-1] > ch:
            stack.pop()
            k -= 1
        stack.append(ch)
    return "".join(stack[:len(stack)-k])
```

🔹 Example: **402. Remove K Digits**, **316. Remove Duplicate Letters**

---

## 5️⃣ Prefix Greedy (Running Sum Reset)

**Signal**: Circular/linear array, must "reset" when failing (gas station, max subarray in greedy sense).
**Template**:

```python
def gas_station(gas, cost):
    total, tank, start = 0, 0, 0
    for i in range(len(gas)):
        total += gas[i] - cost[i]
        tank += gas[i] - cost[i]
        if tank < 0:  # fail → reset start
            start = i + 1
            tank = 0
    return start if total >= 0 else -1
```

🔹 Example: **134. Gas Station**

---

## 6️⃣ Two-pointer Shrink (From Both Ends)

**Signal**: Max/min optimization by moving **left & right pointers**.
**Template**:

```python
def container_most_water(height):
    left, right = 0, len(height) - 1
    best = 0
    while left < right:
        best = max(best, (right - left) * min(height[left], height[right]))
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1
    return best
```

🔹 Example: **11. Container With Most Water**, **881. Boats to Save People**

---

# ✅ Summary

* **Intervals → Sort by end**
* **Deadlines/resources → Heap drop worst**
* **Matching groups → Sort + two pointers**
* **Remove chars/digits → Monotonic stack**
* **Circular sum reset → Prefix greedy**
* **Shrink from ends → Two pointers**

---

👉  do you want me to **make a consolidated PDF cheat sheet** with these **patterns + code templates + LeetCode examples** so you can keep it as quick reference when practicing?


Absolutely! 🚀
Here’s a **cheat sheet of popular Python3 built-in functions** that are **commonly used in competitive programming / LeetCode**, with examples for each.

---

# 📘 Python3 Competitive Programming Cheat Sheet (Built-in Functions)

| Function                                 | Purpose                               | Example                                       | Output           |
| ---------------------------------------- | ------------------------------------- | --------------------------------------------- | ---------------- |
| **`ord(ch)`**                            | Convert char → Unicode integer        | `ord('a')`                                    | `97`             |
| **`chr(num)`**                           | Convert Unicode integer → char        | `chr(97)`                                     | `'a'`            |
| **`len(obj)`**                           | Get length of string/list/etc.        | `len("leetcode")`                             | `8`              |
| **`min(iterable)` / `max(iterable)`**    | Find smallest/largest element         | `min([3,1,4])`                                | `1`              |
| **`sum(iterable)`**                      | Sum of numbers                        | `sum([1,2,3])`                                | `6`              |
| **`sorted(iterable)`**                   | Return a sorted list                  | `sorted([3,1,2])`                             | `[1,2,3]`        |
| **`reversed(iterable)`**                 | Reverse an iterable                   | `list(reversed([1,2,3]))`                     | `[3,2,1]`        |
| **`enumerate(iterable)`**                | Get index + value while iterating     | `for i,x in enumerate(['a','b']): print(i,x)` | `0 a` <br> `1 b` |
| **`zip(a,b)`**                           | Pair elements from multiple iterables | `list(zip([1,2],[3,4]))`                      | `[(1,3),(2,4)]`  |
| **`map(func, iterable)`**                | Apply function to all elements        | `list(map(str, [1,2,3]))`                     | `['1','2','3']`  |
| **`filter(func, iterable)`**             | Keep elements where func returns True | `list(filter(lambda x: x%2==0, [1,2,3,4]))`   | `[2,4]`          |
| **`any(iterable)`**                      | True if *any* element is True         | `any([0,0,1])`                                | `True`           |
| **`all(iterable)`**                      | True if *all* elements are True       | `all([1,1,1])`                                | `True`           |
| **`divmod(a,b)`**                        | Returns `(quotient, remainder)`       | `divmod(7,3)`                                 | `(2,1)`          |
| **`pow(a,b,mod)`**                       | Fast power (with modulo)              | `pow(2,10,1000)`                              | `24`             |
| **`bin(num)` / `hex(num)` / `oct(num)`** | Convert int to binary/hex/oct string  | `bin(5)`                                      | `'0b101'`        |
| **`int(str, base)`**                     | Parse string in given base            | `int("101",2)`                                | `5`              |
| **`str(obj)`**                           | Convert object to string              | `str(123)`                                    | `'123'`          |
| **`set(iterable)`**                      | Unique elements as a set              | `set([1,2,2,3])`                              | `{1,2,3}`        |
| **`list(iterable)`**                     | Convert to list                       | `list("abc")`                                 | `['a','b','c']`  |
| **`dict(zip(keys,values))`**             | Build dictionary                      | `dict(zip(['a','b'],[1,2]))`                  | `{'a':1,'b':2}`  |

---

### 🔥 Specially useful in **LeetCode**:

* `ord` + `chr` → For char ↔ int conversion (`a-z`, `A-Z`, `0-9`).
* `divmod` → For digit/bitwise problems (`Add Binary`, `Multiply Strings`).
* `enumerate` → For 2-pointer / sliding window.
* `zip` → For pairing arrays (`Two Sum`, matrix problems).
* `pow(a,b,mod)` → For modular arithmetic in number theory problems.
* `any` / `all` → For quick checks on conditions (like monotonic arrays).

---

⚡ Would you like me to also create a **"C++ vs Python equivalents" version of this table** (like you asked earlier for containers) so you can directly map them one-to-one?

Perfect 👍 Let’s build a **C++ vs Python Cheat Sheet for Competitive Programming**.
This will help you quickly map **C++ STL functions** to their **Python built-ins** (very handy for LeetCode).

---

# 🚀 C++ vs Python3 Competitive Programming Cheat Sheet

| Concept                            | C++ (STL)                                                                      | Python3                                        | Example (Python3)                                            | Output             |
| ---------------------------------- | ------------------------------------------------------------------------------ | ---------------------------------------------- | ------------------------------------------------------------ | ------------------ |
| **Length of container**            | `vec.size()`                                                                   | `len(obj)`                                     | `len([1,2,3])`                                               | `3`                |
| **Min / Max**                      | `min_element(vec.begin(),vec.end())` <br> `max_element(vec.begin(),vec.end())` | `min(iterable)` <br> `max(iterable)`           | `min([3,1,4])`                                               | `1`                |
| **Sum**                            | `accumulate(vec.begin(), vec.end(), 0)`                                        | `sum(iterable)`                                | `sum([1,2,3])`                                               | `6`                |
| **Sort**                           | `sort(vec.begin(), vec.end())`                                                 | `sorted(iterable)`                             | `sorted([3,1,2])`                                            | `[1,2,3]`          |
| **Reverse**                        | `reverse(vec.begin(), vec.end())`                                              | `reversed(iterable)` or `list[::-1]`           | `list(reversed([1,2,3]))`                                    | `[3,2,1]`          |
| **Iteration with index**           | `for (int i=0;i<n;++i)`                                                        | `enumerate(iterable)`                          | `for i,x in enumerate(['a','b']): print(i,x)`                | `0 a` <br> `1 b`   |
| **Pair iteration**                 | `for (int i=0;i<n;++i) pair(a[i],b[i])`                                        | `zip(a,b)`                                     | `list(zip([1,2],[3,4]))`                                     | `[(1,3),(2,4)]`    |
| **Apply function to all elements** | `transform(vec.begin(),vec.end(),...)`                                         | `map(func, iterable)`                          | `list(map(str,[1,2,3]))`                                     | `['1','2','3']`    |
| **Filter elements**                | `copy_if(...)`                                                                 | `filter(func, iterable)`                       | `list(filter(lambda x:x%2==0,[1,2,3,4]))`                    | `[2,4]`            |
| **Check any / all true**           | Custom loop                                                                    | `any(iterable)` <br> `all(iterable)`           | `any([0,0,1])` / `all([1,1,1])`                              | `True` / `True`    |
| **Char to int / int to char**      | `'a' - 'a'` <br> `char(97)`                                                    | `ord(ch)` <br> `chr(num)`                      | `ord('a')` / `chr(97)`                                       | `97` / `'a'`       |
| **Power / Mod Power**              | `pow(a,b)%m` or `modpow(a,b,m)`                                                | `pow(a,b,mod)`                                 | `pow(2,10,1000)`                                             | `24`               |
| **Binary / Hex / Octal**           | `bitset` or manual                                                             | `bin(num)` / `hex(num)` / `oct(num)`           | `bin(5)`                                                     | `'0b101'`          |
| **String to int with base**        | `stoi(str,nullptr,2)`                                                          | `int(str, base)`                               | `int("101",2)`                                               | `5`                |
| **Int to string**                  | `to_string(num)`                                                               | `str(obj)`                                     | `str(123)`                                                   | `'123'`            |
| **Set (unique elements)**          | `unordered_set<int> s`                                                         | `set(iterable)`                                | `set([1,2,2,3])`                                             | `{1,2,3}`          |
| **Dict / HashMap**                 | `unordered_map<string,int> m`                                                  | `dict()` or `{}`                               | `{'a':1,'b':2}`                                              | `{'a': 1, 'b': 2}` |
| **Stack**                          | `stack<int> st; st.push(); st.top(); st.pop();`                                | `list` or `collections.deque`                  | `st=[]; st.append(1); st.pop()`                              |                    |
| **Queue**                          | `queue<int> q; q.push(); q.front(); q.pop();`                                  | `collections.deque`                            | `from collections import deque; q=deque([1,2]); q.popleft()` | `1`                |
| **Deque**                          | `deque<int> dq; dq.push_front(); dq.push_back();`                              | `collections.deque`                            | `dq=deque(); dq.appendleft(1); dq.append(2)`                 | `deque([1,2])`     |
| **Priority Queue (min/max heap)**  | `priority_queue<int>`                                                          | `heapq` (min-heap only, use `-x` for max-heap) | `import heapq; heapq.heappush(hq,3)`                         |                    |

---

✅ With this table, you can quickly **translate C++ logic into Python** for LeetCode/contests.

👉 Do you want me to also add **time complexities (C++ vs Python)** for these operations? That would help decide which container to use in coding interviews.

Great 👍 Let’s extend the **C++ vs Python Competitive Programming Cheat Sheet** by adding **time complexity** for each operation. This way, you’ll know whether Python behaves similarly to C++ STL or if there’s a hidden cost.

---

# 🚀 C++ vs Python3 Competitive Programming Cheat Sheet with Time Complexities

| Concept                       | C++ (STL)                                                    | Python3                             | Example                                       | Time Complexity              |
| ----------------------------- | ------------------------------------------------------------ | ----------------------------------- | --------------------------------------------- | ---------------------------- |
| **Length of container**       | `vec.size()`                                                 | `len(obj)`                          | `len([1,2,3])`                                | **O(1)**                     |
| **Min / Max**                 | `min_element(vec.begin(),vec.end())` <br> `max_element(...)` | `min(iterable)` / `max(iterable)`   | `min([3,1,4])`                                | **O(n)**                     |
| **Sum**                       | `accumulate(vec.begin(),vec.end(),0)`                        | `sum(iterable)`                     | `sum([1,2,3])`                                | **O(n)**                     |
| **Sort**                      | `sort(vec.begin(),vec.end())`                                | `sorted(iterable)`                  | `sorted([3,1,2])`                             | **O(n log n)**               |
| **Reverse**                   | `reverse(vec.begin(),vec.end())`                             | `list[::-1]` / `reversed(iterable)` | `[1,2,3][::-1]`                               | **O(n)**                     |
| **Iteration with index**      | `for (int i=0;i<n;++i)`                                      | `enumerate(iterable)`               | `for i,x in enumerate(['a','b']): print(i,x)` | **O(n)**                     |
| **Pair iteration**            | `zip(a,b)`                                                   | `zip(a,b)`                          | `list(zip([1,2],[3,4]))`                      | **O(min(len(a),len(b)))**    |
| **Apply function**            | `transform(...)`                                             | `map(func,iterable)`                | `list(map(str,[1,2,3]))`                      | **O(n)**                     |
| **Filter**                    | `copy_if(...)`                                               | `filter(func,iterable)`             | `list(filter(lambda x:x%2==0,[1,2,3,4]))`     | **O(n)**                     |
| **Any / All**                 | Custom loop                                                  | `any(iterable)` / `all(iterable)`   | `any([0,0,1])`                                | **O(n)** worst case          |
| **Char to int / int to char** | `'a'-'a'`, `char(97)`                                        | `ord(ch)`, `chr(num)`               | `ord('a') → 97`                               | **O(1)**                     |
| **Power / Mod Power**         | `pow(a,b)%m`                                                 | `pow(a,b,m)`                        | `pow(2,10,1000)`                              | **O(log b)**                 |
| **Binary / Hex / Octal**      | `bitset`                                                     | `bin(num)` / `hex(num)`             | `bin(5)` → `'0b101'`                          | **O(log n)**                 |
| **String to int (base)**      | `stoi(str,nullptr,2)`                                        | `int(str,base)`                     | `int("101",2)` → `5`                          | **O(n)**                     |
| **Int to string**             | `to_string(num)`                                             | `str(num)`                          | `str(123)` → `'123'`                          | **O(n)**                     |
| **Set (unique)**              | `unordered_set` insert/erase                                 | `set()`                             | `set([1,2,2,3])`                              | **O(1) avg**, **O(n)** worst |
| **Dict / HashMap**            | `unordered_map`                                              | `dict()`                            | `d={'a':1}`                                   | **O(1) avg**, **O(n)** worst |
| **Stack (push/pop)**          | `stack.push(), stack.pop()`                                  | `list.append(), list.pop()`         | `st=[]; st.append(1); st.pop()`               | **O(1) amortized**           |
| **Queue (FIFO)**              | `queue.push(), queue.pop()`                                  | `collections.deque`                 | `q=deque([1]); q.popleft()`                   | **O(1)**                     |
| **Deque (double-ended)**      | `deque.push_front()`                                         | `collections.deque`                 | `dq.appendleft(1); dq.append(2)`              | **O(1)**                     |
| **Priority Queue (heap)**     | `priority_queue` (max-heap)                                  | `heapq` (min-heap)                  | `heappush(h,3)`                               | **O(log n)**                 |

---

✅ Key Notes for Interviews / LeetCode:

* `len()`, `ord()`, `chr()`, `dict`, `set` are **O(1)** on average — very efficient.
* `sum()`, `min()`, `max()`, `sorted()`, `reversed()` are **linear or worse**, so avoid calling them repeatedly inside loops.
* `pow(a,b,m)` is **fast modular exponentiation** in Python (same as C++ `modpow`).
* `heapq` is **min-heap only**, so for max-heap use `heappush(h, -x)` and invert sign.

---

👉 Would you like me to also add **String operations** (like `find`, `startswith`, `split`, `join`) with their complexities? They’re heavily used in LeetCode string problems.

Perfect 👍 Let’s extend the cheat sheet to include **String operations** since they’re extremely common in LeetCode / competitive programming.

---

# 📌 String Operations in C++ vs Python3 (with Time Complexities)

| Operation                   | C++ (STL)                    | Python3                  | Example                              | Time Complexity                          |
| --------------------------- | ---------------------------- | ------------------------ | ------------------------------------ | ---------------------------------------- |
| **Length**                  | `s.size()`                   | `len(s)`                 | `len("hello") → 5`                   | **O(1)**                                 |
| **Access char**             | `s[i]`                       | `s[i]`                   | `"abc"[1] → 'b'`                     | **O(1)**                                 |
| **Substring**               | `s.substr(pos,len)`          | `s[start:end]`           | `"abcdef"[1:4] → 'bcd'`              | **O(k)** (k = substring length)          |
| **Concatenation**           | `s1 + s2`                    | `s1 + s2`                | `"a" + "b" → "ab"`                   | **O(n+m)**                               |
| **Repeat string**           | `N/A`                        | `s * k`                  | `"ab" * 3 → "ababab"`                | **O(n·k)**                               |
| **Find (first occurrence)** | `s.find("sub")`              | `s.find("sub")`          | `"abcabc".find("bc") → 1`            | **O(n·m)** worst (n = text, m = pattern) |
| **Check prefix**            | `s.rfind("pre",0)==0`        | `s.startswith("pre")`    | `"prefix".startswith("pre")`         | **O(m)**                                 |
| **Check suffix**            | Compare end substr           | `s.endswith("fix")`      | `"suffix".endswith("fix")`           | **O(m)**                                 |
| **Count substring**         | manual loop                  | `s.count("a")`           | `"banana".count("a") → 3`            | **O(n·m)**                               |
| **Replace substring**       | `std::regex_replace`         | `s.replace("old","new")` | `"abc".replace("a","z") → "zbc"`     | **O(n·m)**                               |
| **Split**                   | `stringstream`               | `s.split(delim)`         | `"a,b,c".split(",") → ['a','b','c']` | **O(n)**                                 |
| **Join**                    | manual loop                  | `sep.join(list)`         | `".".join(["a","b"]) → "a.b"`        | **O(n)**                                 |
| **Strip (trim)**            | custom code                  | `s.strip()`              | `"  hi  ".strip() → "hi"`            | **O(n)**                                 |
| **Reverse string**          | `reverse(s.begin(),s.end())` | `s[::-1]`                | `"abc"[::-1] → "cba"`                | **O(n)**                                 |
| **Check palindrome**        | manual loop                  | `s == s[::-1]`           | `"aba" == "aba" → True`              | **O(n)**                                 |
| **Convert to int**          | `stoi(s)`                    | `int(s)`                 | `int("123") → 123`                   | **O(n)**                                 |
| **Convert to string**       | `to_string(x)`               | `str(x)`                 | `str(123) → "123"`                   | **O(n)**                                 |

---

### 🔑 Competitive Programming Notes:

* `startswith()` / `endswith()` are **much faster** and more readable than slicing for prefix/suffix checks.
* `split()` and `join()` are heavily used in parsing and building strings (like CSV, paths).
* Be careful with concatenation in loops — in Python it’s **O(n²)** if done repeatedly. Use `''.join(list)` instead.
* `s[::-1]` is the idiomatic Pythonic way to reverse, similar to `reverse()` in C++.
* Pattern matching (like substring search) in Python’s `find` is **not KMP**; worst case is **O(n·m)**. For efficiency, use `re` (regex) or algorithms like KMP/Rabin-Karp if needed.

---

👉 Do you want me to **combine this String section** into the earlier **C++ vs Python Cheat Sheet** (containers + built-ins + strings) into one **big reference table** for you?
