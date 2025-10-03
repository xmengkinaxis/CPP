
# Python3 Standard Library Modules

# For input and output
import sys

# For character manipulation
import string # .isalnum(), .isalpha(), .isdigit(), .lower(), .upper()

# For string manipulation and formatting
import io

# For working with collections, hash maps (Python dictionaries), stacks, double-ended queues (Python collections module provides deque)
import collections

# For working with vectors (Python lists)
import array # list or stack: append, pop, len, [-1]

# For working with sets
import set # in, add, remove, discard

# For working with queues (Python queue module provides Queue and PriorityQueue)
import queue

# For sorting, finding min and max, numeric operations like sum and max
import functools

from collections import deque # popleft, append
from collections import defaultdict # defaultdict is a subclass of the built-in dict class that provides a convenient way to create dictionaries with default values for keys that don't exist yet
from collections import Counter # count the occurrences of elements in a collection, typically in a list, tuple, or string. It returns a dictionary-like object where keys are the unique elements in the input collection, and values are the counts of each element.
from collections import most_common # returns a list of the n most common elements and their counts from the most common to the least; use as priority queue

import heapq # By default, heapq implements a min heap
'''
The heapq module in Python provides a collection of efficient heap queue algorithms. The name "heapq" is derived from "heap" (a data structure) and "queue" (a data structure). 
heappush(heap, item): This function adds the element item to the heap while maintaining the heap property. 
heappop(heap): This function removes and returns the smallest (or largest in the case of a max-heap) element from the heap. 
heappushpop(heap, item): This operation pushes item onto the heap and then immediately pops and returns the smallest element. It can be more efficient than performing separate heappush and heappop operations.
heapreplace(heap, item): This operation pops and returns the smallest element from the heap and then pushes item onto the heap
    def findKthLargest(self, nums: List[int], k: int) -> int:
        min_heap = []
        for n in nums: 
            heapq.heappush(min_heap, n)
            if len(min_heap) > k: 
                heapq.heappop(min_heap)
        return heapq.heappop(min_heap)
'''

CONDITION = True

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


def fn_two_pointers(arr):
    ans = 0
    left, right = 0, len(arr) - 1

    while left < right:
        # Do some logic here with left and right for ans
        if CONDITION:
            left += 1
        else:
            right -= 1
        # There might be a case that left += 1 and right -= 1 here
        # Anyway, you must update left, right, or both; otherwise, it would be a dead loop

    return ans

def fn_two_pointers_two_arrays(arr1, arr2):
    i = j = 0
    ans = 0

    while i < len(arr1) and j < len(arr2): #  might contain other conditions here like a carry in adding
        # You can add your condition here, e.g., if arr1[i] < arr2[j]:
        if CONDITION:
            i += 1
        else:
            j += 1

    while i < len(arr1):
        i += 1

    while j < len(arr2):
        j += 1

    return ans

def fn_sliding_window(arr:list, size):
    ans = 0
    start = 0
    curr = 0

    for end in len(arr):
        # Add arr[end] into curr (the window)
        # The curr might be a complex data structure like a deque or a dictionary
        # Depending on your use case, you might need some preprocessing before adding

        # Depending on whether the window size is fixed or not, 
        # if fixed, remove the start by moving it towards the end by one
        # if not fixed, depend on the loop condition to remove the start
        while CONDITION and start <= end:  # The condition "start <= end" ensures it's a valid window; it can be omitted if window size can be zero
            # Do something for the valid window here as the window is shrinking
            # Remove arr[start] from curr
            start += 1  # It would be a dead loop if start is not moved

        # Do something for this valid window
        # If the size is fixed, when "size - 1 <= end", do something
        # You can add your logic here to process the current window
        # For example, you can update ans based on the contents of the window

    return ans

def fn_prefix_sum(arr):
    prefix = [0] * len(arr)
    prefix[0] = arr[0]

    for i in range(1, len(arr)):
        prefix[i] = prefix[i - 1] + arr[i]

    return prefix

def fn_string(arr):
    return ''.join(arr)


def fn_fast_and_slow_pointers(head):
    ans = 0
    slow = fast = head

    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next

    return ans

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def fn_reverse(head):
    prev = None
    curr = head

    while curr:
        next_node = curr.next
        curr.next = prev
        prev = curr
        curr = next_node

    return prev

def fn_find_subarrays(arr, k):
    # Define a dictionary to store prefix sum frequencies.
    # It will serve as a memo/dp and is used to count the frequency of pre-sums.
    counts = {0: 1}  # Initialize with the base case counts[0] = 1
    # counts = defaultdict(int)
    # counts[0] = 1

    ans = 0
    curr = 0  # Current prefix sum

    for num in arr:
        # Update curr to include num (do any necessary logic here).
        # For example, you can update curr by adding num to it.
        curr += num

        # Check the dictionary for pre-sums.
        # Check if curr - k is in the dictionary to count subarrays.
        ans += counts.get(curr - k, 0)

        # Update the dictionary (counts).
        # Make sure to update the dictionary after checking, as adding curr first may affect the result.
        counts[curr] = counts.get(curr, 0) + 1

    return ans

def fn_find_subarrays2(arr, k):
    # Define a dictionary to store prefix sum frequencies.
    # It will serve as a memo/dp and is used to count the frequency of pre-sums.
    counts = defaultdict(int)
    counts[0] = 1

    ans = 0
    curr = 0  # Current prefix sum

    for num in arr:
        # Update curr to include num (do any necessary logic here).
        # For example, you can update curr by adding num to it.
        curr += num

        # Check the dictionary for pre-sums.
        # Check if curr - k is in the dictionary to count subarrays.
        ans += counts[curr - k]

        # Update the dictionary (counts).
        # Make sure to update the dictionary after checking, as adding curr first may affect the result.
        counts[curr] += 1

    return ans

def fn_monotonic_increasing_stack(arr):
    stack = []
    ans = 0

    for n in arr:
        # This is for monotonic increasing.
        # For monotonic decrease, change '>' to '<'.
        while stack and stack[-1] > n:
            # Do logic here.
            stack.pop()
        
        # You might do logic here too.
        stack.append(n)  # You can push the value (n) into the stack or the index if needed.

    # You might need to return something, like the 'stack' itself or the final 'ans'.
    return ans  # Currently, 'ans' is not modified in the function.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def dfs_tree(root):
    # 1. Deal with the special base cases
    if not root:
        return 0

    # 2. Do logic for this node (pre-order)
    # Replace this comment with your logic for pre-order traversal

    # 3. Recursively visit left subtree
    dfs_tree(root.left)

    # 4. Do logic for this node (in-order)
    # Replace this comment with your logic for in-order traversal

    # 5. Recursively visit right subtree
    dfs_tree(root.right)

    # 6. Do logic for this node (post-order)
    # Replace this comment with your logic for post-order traversal

    # 7. Return an appropriate value if needed
    return 0  # Modify this return statement as needed


def dfs_tree_stack(root):
    if not root:
        return 0

    stack = []
    stack.append(root)
    ans = 0

    while stack:
        node = stack.pop()

        # 1. Do logic for this node
        # Replace this comment with your logic for the current node

        # 2. Visit its branches
        if node.left:
            stack.append(node.left)
        if node.right:
            stack.append(node.right)

    return ans


from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def bfs_tree(root):
    if not root:
        return 0

    queue = deque()
    queue.append(root)
    ans = 0

    while queue:
        # The following for loop can be eliminated if there is no action for each layer
        for count in range(len(queue)):
            node = queue.popleft()

            # 1. Do logic for this node; might do some logic as post-Check
            # Replace this comment with your logic for the current node

            # 2. Visit its branches; might need to do pre-Check
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        # Do some actions for this layer
        # For example, calculating steps/time/sum for this layer
        # Or this action can be merged with the while loop and change it into a for loop

    return ans

seen = set()  # Initialize the set of seen nodes
def dfs_graph_2(node, graph, seen):
    seen.add(node)  # Add the current node to the set of seen nodes

    # 1. Do logic for node here
    # Replace this comment with your logic for the current node

    ans = 0  # Initialize ans, modify as needed

    for neighbor in graph[node]:
        # 2. Validate if a neighbor is valid first (if needed)
        # 3. Check if the neighbor is not visited before
        if neighbor not in seen:
            # Call dfs on this neighbor
            ans += dfs_graph_2(neighbor, graph, seen)  # Accumulate any result as needed

    return ans  # Return any accumulated result as needed

def dfs_graph_3(node, graph, seen):
    if node in seen:
        return False  # Already visited

    if CONDITION:  # Ending condition: node is the destination
        return True  # Found

    seen.add(node)  # Add the current node to the set of seen nodes

    # 1. Do logic for node here
    # Replace this comment with your logic for the current node

    for neighbor in graph[node]:
        if dfs_graph_3(neighbor, graph, seen):
            return True

    return False

def dfs_iterative(graph, start_node):
    stack = []
    seen = set()
    seen.add(start_node)
    stack.append(start_node)
    ans = 0

    while stack:
        node = stack.pop()

        # 1. Do logic for the node here
        # Replace this comment with your logic for the current node

        for neighbor in graph[node]:
            if neighbor not in seen:
                seen.add(neighbor)
                stack.append(neighbor)

    return ans

def bfs_graph(graph):
    queue = deque()
    seen = set()
    
    seen.add(START_NODES)
    queue.append(START_NODES)
    
    ans = 0

    while queue:
        node = queue.popleft()

        # 1. Do logic for the node here
        # Replace this comment with your logic for the current node

        for neighbor in graph[node]:
            if neighbor not in seen:
                seen.add(neighbor)
                queue.append(neighbor)

    return ans


def bfs_graph_steps(grid):
    N = len(grid)
   
    # Deal with special cases, e.g., grid[0][0] or/and grid[N - 1][N - 1]
    
    queue = deque()
    queue.append((0, 0))
    grid[0][0] = 2  # Mark it as visited by changing its value
    
    for step in range(1, N * N + 1):  # The step is initialized properly and increased level by level
        for _ in range(len(queue)):
            r, c = queue.popleft()
            
            # 1. Do logic for this node, e.g., check if it is finished
            if r == N - 1 and c == N - 1:
                return step
            
            dirs = [(-1, 0), (0, 1), (1, 0), (0, -1), (-1, -1), (-1, 1), (1, 1), (1, -1)]
            
            # Iterate all candidates
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                if (
                    nr < 0 or nr >= N or nc < 0 or nc >= N or  # Valid if it is a valid candidate
                    grid[nr][nc]  # Check if it was visited already
                ):
                    continue
                
                grid[nr][nc] = 2
                queue.append((nr, nc))
    
    return -1


def top_k(arr, k):
    min_heap = []

    for n in arr:
        heapq.heappush(min_heap, n)
        if len(min_heap) > k:
            heapq.heappop(min_heap)

    ans = []

    while min_heap:
        ans.append(heapq.heappop(min_heap))

    ans.reverse()  # Reverse the list to get the elements in descending order (from largest to smallest)

    return ans

def binary_search(arr, target):
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = low + (high - low) // 2

        if target == arr[mid]:
            return mid
        elif target < arr[mid]:
            high = mid - 1
        else:
            low = mid + 1

    return low

def binary_leftmost(arr, target):
    left = 0
    right = len(arr)

    while left < right:
        mid = left + (right - left) // 2

        if arr[mid] >= target:
            right = mid
        else:
            left = mid + 1

    return left

def binary_rightmost(arr, target):
    left = 0
    right = len(arr)

    while left < right:
        mid = left + (right - left) // 2

        if arr[mid] > target:
            right = mid
        else:
            left = mid + 1

    return left

def binary_search(arr, target, cmp):
    left = 0
    right = len(arr)

    while left < right:
        mid = left + (right - left) // 2

        if cmp(arr[mid], target):
            right = mid
        else:
            left = mid + 1

    return left

# Define lambda functions for leftmost and rightmost comparisons
cmp_leftmost = lambda lhs, rhs: lhs >= rhs
cmp_rightmost = lambda lhs, rhs: lhs > rhs

# Assuming you have a 'nums' list and a 'target' value
first = binary_search(nums, target, cmp_leftmost)
last = binary_search(nums, target, cmp_rightmost) - 1


def binary_minimum(arr):
    low = float("-inf")  # Set to the minimum possible answer
    high = float("inf")  # Set to the maximum possible answer

    while low <= high:
        mid = low + (high - low) // 2

        if check(mid):
            high = mid - 1
        else:
            low = mid + 1

    return low

def binary_maximum(arr):
    low = float("-inf")  # Set to the minimum possible answer
    high = float("inf")  # Set to the maximum possible answer

    while low <= high:
        mid = low + (high - low) // 2

        if check(mid):
            low = mid + 1
        else:
            high = mid - 1

    return high

def backtrack(curr, others):
    # Check the base condition of backtrack first, before checking the DFS conditions
    if BASE_CASE:  # Adjust your base case condition here
        # Modify the answer
        return 0

    ans = 0

    # Iterate over all candidates, similar to DFS
    # The difference is that you may need to modify the current state and undo the modification
    # If some changes are made on the current node in DFS, undo them after iterating its neighbors and before returning
    for candidate in ITERATE_OVER_INPUT:  # Adjust the iteration over candidates
        # DO modify curr, the current state
        ans += backtrack(curr, OTHERS)  # Recursive call with updated curr and other parameters
        # UNDO the modification of the current state

    return ans


class TrieNode:
    def __init__(self):
        self.data = 0
        self.children = {}

def build_trie(words):
    root = TrieNode()
    for word in words:
        curr = root
        for c in word:
            if c not in curr.children:
                curr.children[c] = TrieNode()
            curr = curr.children[c]
            # Perform something on the current TrieNode
    return root

class UnionFind:
    def __init__(self, elements):
        self.parent = {}
        for element in elements:
            self.parent[element] = element

    def find(self, a):
        if self.parent[a] != a:
            self.parent[a] = self.find(self.parent[a])  # Path compression
        return self.parent[a]

    def merge(self, a, b):
        self.parent[self.find(b)] = self.find(a)
