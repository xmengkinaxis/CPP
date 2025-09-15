// https://leetcode.com/explore/interview/card/cheatsheets/720/resources/4723/
// cheat sheet and code template
// https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed
// 14 Patterns to Ace Any Coding Interview Question

#include <iostream> // cout, cin
#include <cctype> // isalnum, isalpha, isdigit, islower, isupper, isspace; toupper, tolower
#include <sstream> // stringstream
#include <string> // substr, getline, strlen, stoi, string(n, char), append(n, char), find(str, pos), erase(first, last), strcpy, strncpy, strcmp, stryncmp
#include <vector>
#include <unordered_map> 
#include <unordered_set>
#include <set> // multiset
#include <stack>
#include <queue> // priority_queue
#include <deque> // deque
#include <algorithm> // sort, min, max, remove(first, last, value), reverse
#include <numeric> // accumulate(begin, end, 0) to calculate the sum in a range, max_element, partial_sum(begin, end, begin) to calculate the partial sum in a range, 
					// iota(begin, end, initial) to fill a range with the consecutive increasing values

using namespace std; 

#define CONDITION true
#define START_NODE 0

#define MINIMUM_POSSIBLE_ANSWER 1 
#define MAXIMUM_POSSIBLE_ANSWER 1000 
#define BASE_CASE true
#define ITERATE_OVER_INPUT 1 : 1

struct ListNode {
	int val; 
	ListNode *next; 
};

struct TreeNode {
	int val; 
	TreeNode *left, *right; 
};

// Input size VS time complexity
/*
n <= 10 : O(n^2 * n!) or O(4^n), backtrack or brute-force 
n <= 20: O(2^n), backtrack or recursion 
n <= 100: O(n^3), brute-force
(brute-force or backtrack can be used for the above input sizes)
--------------------------------------------
n <= 1,000: O(n * n)
n <= 100,000: O(n * log n) or O(n): sort or heap; 
hash map, two pointers, sliding windows, Monotonic stack, 
binary search, heap, or combination
n <= 1,000,000: O(n) or O(n * logh n): hash map
More: O(log n ) or O(1)
*/

/* Common time complexity notations: 
O(1) - Constant Time: The algorithm's performance does not change with input size.
O(log n) - Logarithmic Time: The algorithm's performance increases logarithmically with the input size.
O(n) - Linear Time: The algorithm's performance scales linearly with the input size.
O(n log n) - Linearithmic time: Common for efficient sorting algorithms (e.g., merge sort, heapsort, quicksort average case).
O(n^2), O(n^3), ... - Polynomial Time: Performance grows with the square, cube, etc. of the input size.
O(2^n), O(n!) - Exponential and Factorial Time: Extremely inefficient algorithms.

Common space complexity notations include:
O(1) - Constant Space: The algorithm uses a fixed amount of memory regardless of the input size.
O(n) - Linear Space: The algorithm's memory usage scales linearly with the input size.
O(n^2), O(n^3), ... - Polynomial Space: Memory usage grows with the square, cube, etc. of the input size.
------------

Time Complexity Pronunciation Cheat Sheet
| Complexity     | How to Say It           | Common Name      | Example Algorithms                                          |
| -------------- | ----------------------- | ---------------- | ----------------------------------------------------------- |
| **O(1)**       | “big O of one”          | Constant time    | Array access by index, push/pop in stack                    |
| **O(log n)**   | “big O of log n”        | Logarithmic time | Binary search                                               |
| **O(n)**       | “big O of n”            | Linear time      | Scanning an array                                           |
| **O(n log n)** | “big O of n log n”      | *n log n time*   | Merge sort, quicksort (average), heapsort                   |
| **O(n²)**      | “big O of n squared”    | Quadratic time   | Bubble sort, insertion sort, selection sort                 |
| **O(n³)**      | “big O of n cubed”      | Cubic time       | Floyd–Warshall algorithm                                    |
| **O(2ⁿ)**      | “big O of two to the n” | Exponential time | Recursive subset generation, brute-force traveling salesman |
| **O(n!)**      | “big O of n factorial”  | Factorial time   | Generating all permutations                                 |

---
**Interview Tip**:
Don’t just say the notation — give the **intuition**:

* *“O(1), meaning constant time.”*
* *“O(n log n), meaning linearithmic time, common in efficient sorting algorithms.”*

Space Complexities
| Complexity   | How to Say It        | Common Name       | Example Usage                                                    |
| ------------ | -------------------- | ----------------- | ---------------------------------------------------------------- |
| **O(1)**     | “big O of one”       | Constant space    | Iterative Fibonacci, two-pointer algorithms                      |
| **O(log n)** | “big O of log n”     | Logarithmic space | Recursive binary search, divide & conquer recursion depth        |
| **O(n)**     | “big O of n”         | Linear space      | Storing input array, recursion stack in DFS                      |
| **O(n²)**    | “big O of n squared” | Quadratic space   | Dynamic programming tables (e.g., edit distance, Floyd–Warshall) |
Interview Tip:
When asked about complexity, answer both time and space if relevant. For example:
“Merge sort runs in O(n log n) time and requires O(n) space.”
*/

/*
Two Pointers Technique: find a pair of index/positions on an array or list, or lock-steps on two arrays/lists
	left and right, or slow and fast, or async depending on conditions, or two arrays/lists;
	opposite directions toward the center, or against the center; 
	same directions, but with the different speeds, e.g. slow and fast; 
Sliding Window Technique: find a continuous sub array in an array, or a continuous substr in a string; 
	start and end with the variable window size, or end for the fixed window size;
Binary Search: use left / right when searching array indices or intervals; using low / high when searching numeric range 
	(emphasizing numeric bounds rather than spatial position); 
	Default: use left / right (most people are familiar with this from LeetCode/education); 
	When search space is numeric and not array indices: low / high might make more sense; 
	Old: low and high if the array is strictly increased, or use left and right if there are some duplications
*/

/* useful coding skills
1. Use unordered_set to speed up the lookup if the input is an array
2. Change the grid value in place as used as seen/visit
3. Can use unordered_set or vector<bool> as seen/visit
4. Use a local variable to store and restore a value before and after recursively invoking backtrack
5. Use a value instead of a reference in recursively invoking backtrack; passing by value will act as if do and undo for the original value is unchanged
6. Start with top-right toward bottom-left for a sorted matrix (2D vector). e.g. 378. Kth Smallest Element in a Sorted Matrix
7. If the first character is '0' in a string of presenting a number, this string is invalid
8. When paring a sting as a number, n = n * 10 + (ch - '0') by iterating each char in the string; always check if isdigit(ch) and reaching the string length
9. When verifying if two adjacent words are ordered, 
	if the length of the first word is larger than that of the second one, this is invalid (not ordered);
	if these two characters are different, reach the comparison result and break the loop;
	if two characters at the same index are same, move to compare the next one; 
10. Use -1 and 1 in counting two different things/numbers and judge if their occurrences are same; e.g. 525. Contiguous Array; 348. Design Tic-Tac-Toe
11. If more than one data structures are used in the algorithm, any action must update all data structures at the same time in order to keep them synchronized and consistent;
	The updates, such as pop and erase, must be done after all adjustments among these data structures, such as swap; 
	e.g. 316. Remove Duplicate Letters; 146. LRU Cache; 380. Insert Delete GetRandom O(1); https://leetcode.com/problems/insert-delete-getrandom-o1/
12. In matching a string, can set up an unordered_map to count the frequencies of characters in the string and the total, and use them as a budget to decrease both; 
	When the total is zero, it means that the whole string is matched. e.g. 76. Minimum Window Substring
13. It is not easy to define unordered_set<pair<int, int>>, instead, can use unordered_set<string> by encoding a pair as a string
	e.g. 489. Robot Room Cleaner
14. The short cut might be needed and dealt in the normal DFS/BFS on a tree/graph or backtrack, for it is unnecessary to browse all, when the answer is already found. 
	As a result, DFS/BFS/backtrack can end earlier than the normal cases
	e.g.  236. Lowest Common Ancestor of a Binary Tree, 285. Inorder Successor in BST
15. DFS problem's indicator: 
	Nested data structure, e.g. 339. Nested List Weight Sum
	Recursively process, e.g. 529. Minesweeper
	Repeated step, 490. The Maze
16. Add and then process vs process than then add; each item will be added once and only once
	Add and then process/calculate : sliding windows, topK
	Process/calculate and add : monotonic stack/queue (maintain monotonic), sub-array (avoid count the duplicates) (might not be added, if wanting to keep the small index) 
17. Converting an integer into a string is the quicker way of getting the digits from a number
18. can use minus to convert a maxHeap to minHeap, instead of creating a special comparison function
19. Need to pay attention to or skip the same items when processing an array to avoid the duplicate result, e.g. 15. 3Sum
*/

// ??? sort all problems of meta once a week into different algorithms, whose numbers are less than 23 and after 29

/* two pointers on the same data structure with opposite directions
e.g. Palindrome problems (odd or even, two pointers with the opposite directions): 
647. Palindromic Substrings https://leetcode.com/problems/palindromic-substrings/
15. 3Sum; https://leetcode.com/problems/3sum/
16. 3Sum Closest; https://leetcode.com/problems/3sum-closest/
125. Valid Palindrome; https://leetcode.com/problems/valid-palindrome/
557. Reverse Words in a String III; https://leetcode.com/problems/reverse-words-in-a-string-iii/
11. Container With Most Water; https://leetcode.com/problems/container-with-most-water/ 
*/
int fnTwoPointers(vector<int>& arr) {
	int ans = 0;
	for (int left = 0, right = arr.size() - 1; left < right; )  {
		// do some logic here with left and right for ans
		if (CONDITION) {
			++left;
		} else {
			--right; 
		}
		// there might be a case that left++ and right-- here
		// Anyway, must update left, or right, or both. Otherwise, it would be a dead loop
	}
	return ans; 
}


/* two pointers for two arrays with the same direction; to merge rather to intersect; lockstep to sync them 
Can start from front to back or from back to front
408. Valid Word Abbreviation https://leetcode.com/problems/valid-word-abbreviation/
21. Merge Two Sorted Lists; https://leetcode.com/problems/merge-two-sorted-lists/
234. Palindrome Linked List; https://leetcode.com/problems/palindrome-linked-list/
1570. Dot Product of Two Sparse Vectors; https://leetcode.com/problems/dot-product-of-two-sparse-vectors/
1650. Lowest Common Ancestor of a Binary Tree III; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/
88. Merge Sorted Array; https://leetcode.com/problems/merge-sorted-array/ 3 pointers in fact
67. Add Binary; https://leetcode.com/problems/add-binary/
--------
392. Is Subsequence; https://leetcode.com/problems/is-subsequence/
*/
int fnTwoPointersTwoArrays(vector<int>& arr1, vector<int>& arr2) {
	int i = 0, j = 0, ans = 0; 

	while (i < arr1.size() && j < arr2.size()) { // might contain other conditions here like a carry in adding
		if (CONDITION) {
			++i;
		} else {
			++j;
		}
	}

	while (i < arr1.size()) {
		++i; 
	}
	while (j < arr2.size()) {
		++j; 
	}
	return ans; 
}


/* sliding window
	for the window with the various size, need two pointers to indicate the start and the end of the window
	for the window with the fixed size, only need a single pointer to point to the end of the window
	for the window with the fixed size, remove the start since the end >= the window size
	must ensure the start is moved, otherwise, the inner loop would become a dead one.
239. Sliding Window Maximum;  https://leetcode.com/problems/sliding-window-maximum/; a very typical one; need a deque to maintain the values within the window
1004. Max Consecutive Ones III; https://leetcode.com/problems/max-consecutive-ones-iii/; the window size can be zero
76. Minimum Window Substring; https://leetcode.com/problems/minimum-window-substring/; use a frequency map
713. Subarray Product Less Than K; https://leetcode.com/problems/subarray-product-less-than-k/
-----------
1208. Get Equal Substrings Within Budget; https://leetcode.com/problems/get-equal-substrings-within-budget/
*/
int fnSlidingWindow(vector<int>& arr, int size) {
	int ans = 0; 
	for (int start = 0, end = 0, curr = 0; end < arr.size(); ++end) {
		// add arr[end] into curr (the window); 
		// the curr might be a complex one, 
		// 	such as a monotonic deque, and need some preprocess before adding
		// 	or a unordered_map to represent the frequency of characters in the window

		// depend on if the window size is fixed or not, 
		// if fixed, when size <= end, remove the start by moving it towards end by one
		// if not fixed, depend on the loop condition to remove the start
		while (CONDITION && start <= end ) { // the condition "start <= end" is critical to ensure it is still a valid window; it can be omitted if window size can be zero
			// can do something for this window if it is valid here when the window is shrinking
			// remove arr[start] from curr; 
			++start;  // it would be a dead loop if start is not moved
		}
		// do something for this window if it is valid
		// if the size is fixed, when "size - 1 <= end", do something
	}
	return ans; 
}

// prefix sum
vector<int> fnPrefixSum(vector<int>& arr) {
	vector<int> prefix(arr.size()); 
	prefix[0] = arr[0]; 
	
	for (int i = 1; i < arr.size(); ++i) {
		prefix[i] = prefix[i - 1] + arr[i]; 
	}
	return prefix; 
}

// string building 
string fnString(vector<char>& arr) {
	return string(arr.begin(), arr.end()); 
}

/* fast and slow pointers; a case of two pointers on the same data structure with the same direction, but moving speeds are different
while-loop condition: fast && fast->next (1st and 2nd conditions: odd => 2nd is false; even => 1st is false) 
odd number of items: fast is valid, but fast->next is nullptr, slow points to the exact middle node of list
even number of items: fast is nullptr, and slow points to the second middle (right-middle) node 
283. Move Zeroes; https://leetcode.com/problems/move-zeroes/
234. Palindrome Linked List; https://leetcode.com/problems/palindrome-linked-list/; need to distinguish odd or even numbers
287. Find the Duplicate Number; https://leetcode.com/problems/find-the-duplicate-number/
----------------------
905. Sort Array By Parity; https://leetcode.com/problems/sort-array-by-parity/
2486. Append Characters to String to Make Subsequence; https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/
*/
int fnFastAndSlowPointers(ListNode* head) {
	int ans = 0;
	ListNode *slow = head, *fast = head; 
	while (fast && fast->next) {
		slow = slow->next; 
		fast = fast->next->next; 
	}
	return ans; 
}

// reverse a linked list 
// 234. Palindrome Linked List; https://leetcode.com/problems/palindrome-linked-list/
ListNode* fnReverse(ListNode* head) {
	ListNode *prev = nullptr; 
	for (auto curr = head; curr; ) {
		auto next = curr->next; 
		curr->next = prev; 
		prev = curr; 
		curr = next; 
	}
	return prev; 
}

/* Find numbers of subarrays that fit an exact criteria
	this like a fixed-left-side sliding window and process as a length-increasing-forever window, sharing the similar code template
	this also looks like pre-sum; 
325. Maximum Size Subarray Sum Equals k; https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/
523. Continuous Subarray Sum; https://leetcode.com/problems/continuous-subarray-sum/ 
560. Subarray Sum Equals K; https://leetcode.com/problems/subarray-sum-equals-k/
525. Contiguous Array; https://leetcode.com/problems/contiguous-array/
similar e.g. 219. Contains Duplicate II; https://leetcode.com/problems/contains-duplicate-ii/
---------------------
1512. Number of Good Pairs; https://leetcode.com/problems/number-of-good-pairs/
*/
int fnFindSubarrays(vector<int>& arr, int k) {
	// 0. define the map and initialize it properly
	// using a map to look up quickly; and it serves as a memo/dp, so it needs the initialization
	// mapping a pre-sum to the index (for maximum size or longest), or counting the frequency of a pre-sum (for how many / total)
	unordered_map<int, int> counts;  // choose the proper name for this map according to the problem; the map serves as a dp array too
	counts[0] = 1; // must initialize counts[0], but its value will depend on the problem; dp array needs a base case
					// might be memo[0] = -1, if the value is the index of the array
	int ans = 0, curr = 0; // curr might be the current pre sum; 

	for (int num : arr) { // in this loop, search the map first and then add the curr into map later
        // 1. Update curr to include num; 
		// do logic here to change curr based on num

		// 2. Check the map
		// might need to check if the key in the unordered_map to avoid adding one mistakenly
		// might need to check some conditions before updating ans;
		ans += counts[curr - k]; 

		// 3. Update the map
		// NOTE: cannot add curr into map first; otherwise, ans might be counted incorrectly
		counts[curr]++; // there might be a condition to check before adding into the map, e.g. if curr is NOT in map
	}
	return ans; 
}

/* the monotonic stack might contain values or some index; 
	if the stack contains index, the while condition should be changed accordingly
	when the top the stack is at left and the current value is at right, < and > is opposite to the order decreasing and increasing
		increase: > (remove all items in the stack whose values are larger than the current value, to make the current value largest in the stack)
		decrease: < (remove all items in the stack whose values are less than the current value, to make the current value smallest in the stack)
	Each item will be eventually pushed into the stack after the stack is updated accordingly
1944. Number of Visible People in a Queue https://leetcode.com/problems/number-of-visible-people-in-a-queue/
1762. Buildings With an Ocean View https://leetcode.com/problems/buildings-with-an-ocean-view/ 
316. Remove Duplicate Letters; https://leetcode.com/problems/remove-duplicate-letters/
similar: 896. Monotonic Array; https://leetcode.com/problems/monotonic-array/
--------------
456. 132 Pattern; https://leetcode.com/problems/132-pattern/
739. Daily Temperatures; https://leetcode.com/problems/daily-temperatures/
402. Remove K Digits; https://leetcode.com/problems/remove-k-digits
*/
int fnMonotonicIncreasingStack(vector<int>& arr) {
	stack<int> stack; 
	int ans = 0;

	for (int n : arr) {
		// this is monotonic increasing
		// for monotonic decrease, change > to < 
		while (!stack.empty() && stack.top() > n) { // it is while-loop here
			// do logic here
			stack.pop(); 
		}
		// might do logic here too
		stack.push(n); // might be index pushed into the stack
	}
}

/* dfs on a Tree: preOrder, inOrder, postorder;
preOrder
623. Add One Row to Tree; https://leetcode.com/problems/add-one-row-to-tree/; do logic for the node at the certain level
inOrder
426. Convert Binary Search Tree to Sorted Doubly Linked List; https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/
987. Vertical Order Traversal of a Binary Tree; https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
1161. Maximum Level Sum of a Binary Tree; https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/; must be preOrder; crash if inOrder, for it is similar to bfs by layer
285. Inorder Successor in BST; https://leetcode.com/problems/inorder-successor-in-bst/; it needs a short cut when the answer is found; no need to browse all
postOrder
543. Diameter of Binary Tree; https://leetcode.com/problems/diameter-of-binary-tree/
536. Construct Binary Tree from String; https://leetcode.com/problems/construct-binary-tree-from-string/
938. Range Sum of BST; https://leetcode.com/problems/range-sum-of-bst/
236. Lowest Common Ancestor of a Binary Tree; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
1644. Lowest Common Ancestor of a Binary Tree II; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/
1676. Lowest Common Ancestor of a Binary Tree IV; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/
95. Unique Binary Search Trees II; https://leetcode.com/problems/unique-binary-search-trees-ii/
129. Sum Root to Leaf Numbers; https://leetcode.com/problems/sum-root-to-leaf-numbers/; // leave is one of the base cases 
1123. Lowest Common Ancestor of Deepest Leaves; https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
865. Smallest Subtree with all the Deepest Nodes; https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
1110. Delete Nodes And Return Forest; https://leetcode.com/problems/delete-nodes-and-return-forest/; must update root and add it if still valid
inOrder + postOrder
1382. Balance a Binary Search Tree; https://leetcode.com/problems/balance-a-binary-search-tree/
545. Boundary of Binary Tree; https://leetcode.com/problems/boundary-of-binary-tree/
--------------
postOrder: 
1325. Delete Leaves With a Given Value; https://leetcode.com/problems/delete-leaves-with-a-given-value
*/
int dfsTree(TreeNode *root) { // could return a tuple of a node and the depth
	// 1. deal with the special base cases;  could be more base cases
	// when calculating the depth, it is 0 for nullptr and 1 for a leave; so the base case is still nullptr; 
	if (!root) { return 0; }

	int ans = 0; 
	// 2. do logic for this node if it is preOrder
	// sometime check if the root is the special target, such as a leave, do the logic for leaf and then return; 
	// sometime check if the root at the certain layer, or if the root is some special input node

	// 3. iterate all branches/candidates/choices/;
	// 3.1. Pre-Check: might need to check if a branch should be visited with some conditions, e.g. value in the special range
	//  or depending on if other branches exist or not
	// 3.2. Post-Check might need to check the return value from a branch and then determine if it should return earlier or continue with other branch
	// 3.3 these two checks can be applied to DFS/BFS on Tree/Graph/Backtrack

	// must pay attention the parameters in invoking the recursive function call
	//	pass all parameters accordingly
	//	update some parameters properly, e.g. increase depth, increase or decrease row and column, 
	// the results from the branches might be required and combined in order to do the logic for this node
	//	the branches might be changes and should be updated accordingly
	//	the return might be complex as a tuple, e.g. Diameter and depth
	dfsTree(root->left); 

	// 4 do logic for this node if it is inOrder

	dfsTree(root->right); 
	
	// 5. do logic for this node if it is postOrder
	return ans; 	
}

/* dfsTreeStack is much similar to bfsTree; the only difference is stack vs queue
Normally, nullptr will not be pushed into the stack and the queue; 
173. Binary Search Tree Iterator; https://leetcode.com/problems/binary-search-tree-iterator/
270. Closest Binary Search Tree Value; https://leetcode.com/problems/closest-binary-search-tree-value
*/
int dfsTreeStack(TreeNode* root) {
	if (!root) { return 0; 	}

	stack<TreeNode*> stack; // contains the valid tree nodes which are going to be visited; the top is the next to visit
	stack.push(root); 
	int ans = 0; 
	// beside if the stack is empty, it might need to check if other conditions are met
	while (!stack.empty()) {
		auto node = stack.top(); 
		stack.pop(); 
		// 1. do logic for this node
		// 2. visit its branches; must check if the branch is valid, for nullptr should NOT be pushed onto the stack
		if (node->left) { stack.push(node->left); }
		if (node->right) { stack.push(node->right); }

	}
	return ans; 
}


/* bfsTree is much similar to dfsTree; 
	both are similar to preOrder
	use a queue in bfs instead of a stack in dfs; 
	usually pop all items in the queue and process one by one for bfs, while popping and process the top of the stack for dfs;
314. Binary Tree Vertical Order Traversal, https://leetcode.com/problems/binary-tree-vertical-order-traversal/
199. Binary Tree Right Side View; https://leetcode.com/problems/binary-tree-right-side-view/
1161. Maximum Level Sum of a Binary Tree; https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/; do some logic for each layer
-----------------
958. Check Completeness of a Binary Tree; https://leetcode.com/problems/check-completeness-of-a-binary-tree/
513. Find Bottom Left Tree Value; https://leetcode.com/problems/find-bottom-left-tree-value
*/
// BFS: level-order traversal with separate layers, vs flat (no level distinction)
int bfsTree(TreeNode* root) {
	if (!root) { return 0; } // this step is critical for BFS, for no nullptr can be pushed into queue any time

	queue<TreeNode*> queue; 
	queue.push(root); 
	int ans = 0; 
	// beside if the queue is empty, it might need to check if other conditions are met, e.g. reaching the target level
	while (!queue.empty()) {
		// the following for loop can be eliminated if there is NO action for each layer
		for (auto count = queue.size(); 0 < count; --count) {
			auto node = queue.front(); queue.pop(); 
			// 1. do logic for this node; might do some logic as post-Check
			// 2. visit its branches; might need to do pre-Check
			if (node->left) { queue.push(node->left); }
			if (node->right) { queue.push(node->right); }
		}
		// do some actions for this layer, e.g. calculating steps/time/sum for this layer
		// or this action can be merged with the while loop and change it into a for loop
	}
	return ans; 
}

/* In DFS, for a node, the core actions are: 
1. [valid] check if the node is a valid node, e.g. it must be within the grid when the problem is a grid,
2. [eligible] check if the node is a valid candidate and should be visited, e.g. the original value/attribute of this node makes it as a valid candidate. 
3. [unvisited] check if the node is already visited, e.g. seen/visited already contains it 
4. do something for this node; this is a real visit on this node; it might check if the condition of ending this DFS is met
	4.1 add this node into seen/visit; this step must be done before visiting its neighbors, otherwise, it would be a dead loop
	4.2 do logic for this node; 
	4.3 might need to check if it should be a short cut to end the whole DFS there, e.g. meet the certain condition/target
5. visit all its neighbors which are not seen/visit yet; need a pre-Check here; might need to add them into seen/visited
* all of these core actions form the core logic of DFS and the block of the BFS while loop
* the core logic of processing a node includes 1, 2, 3, 4; 
* For BFS, these actions in the core logic are done before the node is pushed into the queue, in order to avoid pushing an invalid node into the queue; 
* For some abnormal case, an invalid node like nullptr is pushed into the queue on purpose
* for BFS, the order might be 4, 5, 1, 2, 3
* if changing the original value instead of using seen/visited, the 2 and 3 are merged into one of checking value
* for DFS, the seen/visit must be set/inserted before visiting its neighbors; and it could be the first step checking if the current is seen or visited already

339. Nested List Weight Sum; https://leetcode.com/problems/nested-list-weight-sum/
529. Minesweeper; https://leetcode.com/problems/minesweeper/; acton 2 and 3 are separated
*/
unordered_set<int> seen; 
// if the node value can be changed and the changed value can be used as the visited flag, 
// then there is no need to create a separated seen/visited data structure

// NOT good, for actions are separated into two methods
int dfsGraph1(vector<vector<int>>& graph) {
	seen.insert(START_NODE); // #1. must do insert before visiting its neighbors in order to avoid the dead loop
							// #2. alternatively, immediately insert it when start visiting it as dfsGraph2, 
							// and check if the neighbor is already visited when iterating them 
	return dfsGraph1(START_NODE, graph);
}

int dfsGraph1(int node, vector<vector<int>>& graph) {
	int ans = 0; 
	// do logic for node here
	for (int neighbor : graph[node]) { // might to validate if a neighbor is valid first		
		if (seen.find(neighbor) == seen.end()) { // prerequisite of the atomic action: ensure the node is not visited before; otherwise, cause a dead loop
			// they are a pair of actions, inserting the node into seen and call dfs on this node.
			// an atomic action: add into seen, and then dfs ths node
			// AKA. the atomic action: want or label to visit (add into seen), and do visit (do dfs)
			seen.insert(neighbor); // this and the next steps are repeating the two steps in the outer function
			dfsGraph1(neighbor, graph); 
		}
	}
	return ans; 
}

// Good, for all actions are in a method
// pre-assumption: the node is a valid and unseen node in the graph; this pre-assumption must be preserved during the recursive calls later
int dfsGraph2(int node, vector<vector<int>>& graph) {
	seen.insert(START_NODE); // must do insert before visiting its neighbors in order to avoid the dead loop
	int ans = 0; 
	// do logic for node here
	for (int neighbor : graph[node]) { // might to validate if a neighbor is valid first		
		if (seen.find(neighbor) == seen.end()) { // prerequisite of the atomic action: ensure the node is not visited before; otherwise, cause a dead loop
			// they are a pair of actions, inserting the node into seen and call dfs on this node.
			// an atomic action: add into seen, and then dfs ths node
			// AKA. the atomic action: want or label to visit (add into seen), and do visit (do dfs)
			dfsGraph2(neighbor, graph); 
		}
	}
	return ans; 
}

/*
490. The Maze; https://leetcode.com/problems/the-maze/; not use the direct neighbor, but keep going
778. Swim in Rising Water; https://leetcode.com/problems/swim-in-rising-water/; Binary Search + DFS
721. Accounts Merge; https://leetcode.com/problems/accounts-merge/
200. Number of Islands; https://leetcode.com/problems/number-of-islands/
694. Number of Distinct Islands; https://leetcode.com/problems/number-of-distinct-islands/
827. Making A Large Island; https://leetcode.com/problems/making-a-large-island/
489. Robot Room Cleaner; https://leetcode.com/problems/robot-room-cleaner/description/
*/
bool dfsGraph3(int node, vector<vector<int>>& graph) {	
	if (seen.find(node) != seen.end()) { 
		return false; // already visited
	} else if (CONDITION) { // ending condition: node is the destination
		return true; // found
	}
	seen.insert(START_NODE); // must do insert before visiting its neighbor in order to avoid the dead loop
	// do logic for node here
	for (int neighbor : graph[node]) { 
		if (dfsGraph3(neighbor, graph)) {
			return true; 
		} 
	}
	return false; 
}

// to keep the definition and usage consistent, seen is defined before stack
int dfsIterative(vector<vector<int>> & graph) {
	unordered_set<int> seen; 
	stack<int> stack; // only contain these unseen nodes
	seen.insert(START_NODE);
	stack.push(START_NODE);
	int ans = 0;
	while (!stack.empty())  {
		auto node = stack.top(); stack.pop(); 
		// do logic for the node
		for (auto neighbor : graph[node]) {
			if (seen.find(neighbor) == seen.end()) {
				seen.insert(neighbor); 
				stack.push(neighbor);
			}
		}
	}
	return ans; 
}

/* when do Topological Sort, no need to keep the seen set, 
	for it is DAG, and a node is added into queue only when only its in/out degree reach zero
---------------
Meta
317. Shortest Distance from All Buildings; https://leetcode.com/problems/shortest-distance-from-all-buildings/
1091. Shortest Path in Binary Matrix; https://leetcode.com/problems/shortest-path-in-binary-matrix/
286. Walls and Gates; https://leetcode.com/problems/walls-and-gates/; min() for shortest
863. All Nodes Distance K in Binary Tree; https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/; reach a certain level
1293. Shortest Path in a Grid with Obstacles Elimination; https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/; visit[r][c] is an integer 
785. Is Graph Bipartite? https://leetcode.com/problems/is-graph-bipartite/; bfs return a bool; can have a short cut
127. Word Ladder; https://leetcode.com/problems/word-ladder/
--------------
994. Rotting Oranges; https://leetcode.com/problems/rotting-oranges/; there is an additional condition in the outer loop
365. Water and Jug Problem; https://leetcode.com/problems/water-and-jug-problem/
787. Cheapest Flights Within K Stops; https://leetcode.com/problems/cheapest-flights-within-k-stops/; can revisit, but only update when less
*/

// bfsGraph uses a queue, but dfsIterative uses a stack; others are the exactly same for iterative implementations
// In other words, BFS and DFS are essentially same, and their difference of browsing nodes 
// in different orders can be achieved by using queue(FIFO) and stack(LIFO/FILO) 
/* 
Both BFS (Breadth-First Search) and DFS (Depth-First Search) are graph/tree traversal algorithms.
The core mechanism is indeed similar:
	You start from a node, mark it as visited, then explore its neighbors.
	The main difference lies in how you manage the "frontier" (the next nodes to visit).
The main difference is in how the "frontier" (next nodes to visit) is managed:
	BFS uses a queue (FIFO), exploring level by level.
	DFS uses a stack (LIFO/FILO)(explicit or recursion), exploring as deep as possible first.
The choice of BFS vs DFS affects algorithmic properties:
	BFS is used for shortest path, level-order traversal, bipartite check, etc.
	DFS is used for cycle detection, topological sort, connected components, etc.
*/
int bfsGraph(vector<vector<int>>& graph) {
	unordered_set<int> seen; 
	queue<int> queue; 
	// they are a pair of actions, inserting the node into seen and adding the node into the queue.
	// an atomic action: add into seen, and then add into queue
	// Initialization:
	// 	there might be a numbers of starting nodes and all these need to be added into the queue initially
	// 	there might be zero of starting nodes. This is an edge case. 
	// 	in summary, the number of starting nodes, could be 0, 1, N; 
	seen.insert(START_NODE); 
	queue.push(START_NODE); 
	int ans = 0; 
	while (!queue.empty()) { // for (int step = 1; !queue.empty(); ++step)
		int node = queue.front(); queue.pop(); 
		// do logic for the node; e.g. set the distance or time for this node, or check if reach the destination and then exit
		for (auto neighbor : graph[node]) {
			// iterate candidates or validate if it is a valid candidate
			if (seen.find(neighbor) == seen.end()) { // ensure if it is NOT seen yet
				// atomic action: add it into both seen and queue
				seen.insert(neighbor); 
				queue.push(neighbor); 
			}
		}
	}
	return ans; 
}

int bfsGraphSteps(vector<vector<int>>& grid) {
	const auto N = grid.size(); 
	// deal with the special case, e.g. grid[0][0] or/and grid[N - 1][N - 1]

	queue<pair<int, int>> queue; 
	queue.push({0, 0}); 
	grid[0][0] = 2; // mark it as visited by changing its value
	for (int step = 1; !queue.empty(); step++) { // the step must be initialized properly, and is increased level by level
		for (auto count = queue.size(); 0 < count; --count) {
			auto [r, c] = queue.front(); queue.pop(); 
			// do logic for this node, e.g. check if it is finished
			if (N - 1 == r && N - 1 == c) {
				return step; 
			}
			constexpr int dirs[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, 
				{-1, -1}, {-1, 1}, {1, 1}, {1, -1}}; 
			// iterate all candidates
			for (auto [dr, dc] : dirs) {
				auto nr = r + dr, nc = c + dc; 
				if (nr < 0 || nr >= N || nc < 0 || nc >= N // validate if it is a valid location in the grid
					|| grid[nr][nc]) { // check if it was visited already
					continue; 
				}
				grid[nr][nc] = 2; 
				queue.push({nr, nc});
			}
		}
	}
	return -1; 
}

/*
Heap is a complete binary tree (the root is the heap top):
	Max Heap: the root is always the maximum value; keeps k minimum values
	Min Heap: the root is always the minimum value; keeps k maximum values 
Rule for Top K problems:
	To find Top K largest (remove smallest) → use a Min Heap (the root is the smallest; remove it to keep only the largest K elements)
	To find Top K smallest (remove largest) → use a Max Heap (the root is the largest; remove it to keep only the smallest K elements)
Reason: keep the heap size = K, and always remove the "least useful" element.
This is similar in spirit to a monotonic queue, but the order is opposite.

minHeap vs maxHeap;  similar to monotonic queue/stack, using minHeap and maxHeap is opposite to the order of decreasing and increasing
	using minHeap, in order to get the top K largest, must remove the current (K + 1)th minimum ; cmp is greater, > 
	using maxHeap, in order to get the top K smallest, must remove the current (K + 1)th maximum; the default cmp is lesser, < 

973. K Closest Points to Origin; https://leetcode.com/problems/k-closest-points-to-origin/
347. Top K Frequent Elements; https://leetcode.com/problems/top-k-frequent-elements/
215. Kth Largest Element in an Array; https://leetcode.com/problems/kth-largest-element-in-an-array/ use minus to create a minHeap;
1337. The K Weakest Rows in a Matrix；https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/
*/
vector<int> fnTopK(vector<int>& arr, int k) {
	priority_queue<int, vector<int>, greater<int>> minHeap; // priority_queue<int> maxHeap; 
	for (auto n : arr) {
		if (minHeap.size() < k || minHeap.top() > n) {
			minHeap.push(n); 
		}
		if (minHeap.size() > k) {
			minHeap.pop();
		}
	}

	vector<int> ans; 
	while (!minHeap.empty()){
		ans.push_back(minHeap.top()); 
		minHeap.pop(); 
	}
	// must reverse the array ans, in order to get the descendent order (from largest to smallest)
	reverse(begin(ans), end(ans));
	return ans; 
}


vector<int> fnTopKEnhanced(vector<int>& arr, int k) {
	priority_queue<int, vector<int>, greater<int>> minHeap; // priority_queue<int> maxHeap; 
	for (auto n : arr) {
		if (minHeap.size() < k) {
			minHeap.push(n); 
		} else if (n > minHeap.top()) {
			minHeap.pop();
			minHeap.push(n); 
		}
	}

	vector<int> ans; 
	while (!minHeap.empty()){
		ans.push_back(minHeap.top()); 
		minHeap.pop(); 
	}
	// must reverse the array ans, in order to get the descendent order (from largest to smallest)
	reverse(begin(ans), end(ans));
	return ans; 
}

/*
81. Search in Rotated Sorted Array II; https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
4. Median of Two Sorted Arrays; https://leetcode.com/problems/median-of-two-sorted-arrays/; for (int low = 0, high = M; low <= high; )
*/
// arr[mid] op target in conditions, the same order as the input parameters
int binarySearch(vector<int>& arr, int target) {
	int left = 0, right = arr.size() - 1; 
	while (left <= right) {
		int mid = left + (right - left) / 2; 
		if (arr[mid] == target)  {
			// do something;
			return mid; 
		} else if (arr[mid] > target) {
			right = mid - 1; 
		} else {
			left = mid + 1; 
		}
	}
	// left is the insertion point
	return left; 
}

/* Binary search: duplicate elements, left-most insertion point
852. Peak Index in a Mountain Array, https://leetcode.com/problems/peak-index-in-a-mountain-array/
1870. Minimum Speed to Arrive on Time; https://leetcode.com/problems/minimum-speed-to-arrive-on-time/
1539. Kth Missing Positive Number; https://leetcode.com/problems/kth-missing-positive-number/
778. Swim in Rising Water; https://leetcode.com/problems/swim-in-rising-water/; why not binaryMinimum ???
658. Find K Closest Elements; https://leetcode.com/problems/find-k-closest-elements/
*/
int binaryLeftMost(vector<int>& arr, int target) {
	int left = 0;
	for (int right = arr.size(); left < right; )  {
		auto mid = left + (right - left) / 2; 
		// it could be a condition to calculated here and then checked in the next if statement
		if (arr[mid] >= target) {
			right = mid; // right make the above condition always true, and right become smaller and smaller
		} else {
			left = mid + 1; // when for-loop is break-out, left would make the above condition become true for the first time; 
							// therefore, left becomes the smallest right which can make the condition true
		}
	}
	return left; 
}
/* Binary search on a spatial range
int minSpeedOnTime(vector<int>& dist, double hour) {
	int low = 1;
	int high = 1e7;
	int minSpeed = -1;
	
	while (low <= high) {
		int mid = (low + high) / 2;
		
		// Move to the left half.
		if (timeRequired(dist, mid) <= hour) {
			minSpeed = mid;
			high = mid - 1;
		} else {
			// Move to the right half.
			low = mid + 1;
		}
	}
	return minSpeed;
}
*/

/* Binary search: duplicate elements, right-most insertion point
1060. Missing Element in Sorted Array; https://leetcode.com/problems/missing-element-in-sorted-array/
similar : 162. Find Peak Element; https://leetcode.com/problems/find-peak-element/; right = nums.size() - 1 and if (nums[mid] > nums[mid + 1])
*/
int binaryRightMost(vector<int>& arr, int target) {
	int left = 0;
	for (int right = arr.size(); left < right; )  {
		int mid = left + (right - left) / 2; 
		if (arr[mid] > target) {
			right = mid; 
		} else {
			left = mid + 1; 
		}
	}
	return left; 
}
// e.g. 1060. Missing Element in Sorted Array https://leetcode.com/problems/missing-element-in-sorted-array/ 
/* in this example, its right and left are similar to the normal left and right; in other words, these two pointers are swapped
int missingElement(vector<int>& nums, int k) {
	int left = 0; 
	for (int right = nums.size() - 1; left < right; ) {
		auto mid = right - (right - left) / 2; 
		auto gap = nums[mid] - nums[0] - mid; 
		if (gap < k) {
			left = mid;
		} else {
			right = mid - 1; 
		}
	}
	return nums[0] + k + left; 
}
*/

/*
In summary, the choice of initializing the right pointer to `array.size()` or `array.size() - 1` in a binary search 
depends on the specific problem's requirements and the indexing convention used (0-indexed or 1-indexed). 
Careful consideration of the search range and the desired behavior will determine the appropriate initialization of the right pointer.
*/

/*
In binary search, if "left" is 0, "right" is the array size, the loop condition is "left < right". 
However, if "right" is  the array size minus 1, the loop condition is "left <= right".
For "left < right", the loop condition is that there are two items in the array, and the exit condition is only one item left (left == right); 
For "left <= right", the loop condition is that there is at least one item in the array, and the exit condition is the empty array (left > right);
NOTE: 
Exception #1 is 4. Median of Two Sorted Arrays; https://leetcode.com/problems/median-of-two-sorted-arrays/
for (int low = 0, high = M; low <= high; ) // high is size, but the loop condition is "low <= high"
Exception #2 is 162. Find Peak Element; https://leetcode.com/problems/find-peak-element/ 
for (int right = nums.size() - 1; left < right; ) // high is size - 1, but the loop condition is "left < right"
Exception #2 is similar to 852. Peak Index in a Mountain Array; https://leetcode.com/problems/peak-index-in-a-mountain-array/

Yes, the above statement is correct. The choice of loop condition in binary search depends on how you initialize the `right` pointer.

When the `right` pointer is initialized to the array size, the loop condition is typically `left < right`. 
This is because you want to keep searching until the pointers narrow down to a single element. 
When `left` and `right` point to the same element, the search space contains only one element, and at that point, the search is complete.

On the other hand, when the `right` pointer is initialized to the array size minus 1, the loop condition is typically `left <= right`. 
This is because you want to keep searching until the pointers narrow down to an empty subarray. 
When `left` and `right` cross each other, the search space becomes empty, and that is when the search is complete.

To summarize:
- If `right` is initialized to the array size: use `left < right` as the loop condition.
- If `right` is initialized to the array size minus 1: use `left <= right` as the loop condition.

Both approaches are valid, and you can choose the one that suits your preference or the specific problem you are solving. 
Just make sure to be consistent with the loop condition and handle boundary cases correctly to avoid any off-by-one errors.
*/

/*
34. Find First and Last Position of Element in Sorted Array; https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
*/
vector<int> binaryFirstLast(vector<int> &nums, int target)
{
	auto cmpLeftMost = [](auto lhs, auto rhs) -> bool {
		return lhs >= rhs; 
	};
	auto cmpRightMost = [](auto lhs, auto rhs) -> bool {
		return lhs > rhs; 
	};
	auto binarySearch = [&nums, target](auto cmp) -> int {
		int left = 0, right = nums.size(); 
		while (left < right) {
			auto mid = left + (right - left) / 2; 
			if (cmp(nums[mid], target)) {
				right = mid; 
			} else {
				left = mid + 1; 
			}
		}
		return left; // left finally becomes the first index which makes the lambda cmp true
	};

	auto first = binarySearch(cmpLeftMost); 
	auto last = binarySearch(cmpRightMost) - 1; 
	return {first, last};
}

/* Binary search: for greedy problems
If looking for a minimum:
1011. Capacity To Ship Packages Within D Days; https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
378. Kth Smallest Element in a Sorted Matrix; https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
*/
bool check(int x) { return true; }
int binaryMinimum(vector<int>& arr) {
	int low = MINIMUM_POSSIBLE_ANSWER; 
	int high = MAXIMUM_POSSIBLE_ANSWER; 
	// must use "<="" here; this is different from the above binary search, for both min and max are valid and should be included
	while (low <= high) {
		auto mid = low + (high - low) / 2; 
		if (check(mid)) {
			high = mid - 1; // different from the normal binary search here, "high = mid - 1" rather than high = "mid"; 
		} else {
			low = mid + 1;  // when exit, low will be the minimum (first/smallest) to meet the check function
		}
	}
	return low; // return the minimum
}

/* Binary search: for greedy problems
If looking for a maximum:
1891. Cutting Ribbons https://leetcode.com/problems/cutting-ribbons/
*/
int binaryMaximum(vector<int>& arr) {
	int low = MINIMUM_POSSIBLE_ANSWER; 
	int high = MAXIMUM_POSSIBLE_ANSWER;
	// must use "<="" here
	while (low <= high) {
		auto mid = low + (high - low) / 2; 
		if (check(mid)) {
			low = mid + 1; 
		} else {
			high = mid - 1; // when exit, high will be the maximum (last/largest) to meet the check function
		}
	}
	return high; // return the maximum
}

/* Backtrack vs DFS
Same: backtrack uses the similar code template as DFS
Diff: backtrack uses the short cut by trimming the candidates or solution space, while DFS will generally browses all 
	backtrack must check the ending condition to trim, before checking the normal conditions used in DFS; it is the base case 
	in backtrack which might be not valid condition in DFS anymore
		e.g. if the current index == word.length() or nums.size(); 
		if such a check is delayed in checking DFS conditions, it might cause an access violation
	backtrack do and then undo the current state before and after the recursive call 
	backtrack might do and undo the modification (adding into seen/visit) on the current node too
17. Letter Combinations of a Phone Number; https://leetcode.com/problems/letter-combinations-of-a-phone-number/
78. Subsets https://leetcode.com/problems/subsets/
301. Remove Invalid Parentheses; https://leetcode.com/problems/remove-invalid-parentheses/
46. Permutations; https://leetcode.com/problems/permutations/
77. Combinations; https://leetcode.com/problems/combinations/
140. Word Break II; https://leetcode.com/problems/word-break-ii/ 
282. Expression Add Operators; https://leetcode.com/problems/expression-add-operators/
490. The Maze; https://leetcode.com/problems/the-maze/; return bool; keep going on one direction
79. Word Search; https://leetcode.com/problems/word-search/
*/
int backtrack(STATE curr, OTHERS) {
	// might check if the current state is till valid, as 301. Remove Invalid Parentheses
	// check the base condition (the ending condition) of backtrack first, before check the DFS normal conditions
	if (BASE_CASE) { // startId, or curr state size, or both
		// modify the answer
		return 0; 
	}

	int ans = 0; 
	// like dfs, iterate all candidates
	// the other difference is to modify the current state and to undo the modification
	// if some change is done on the current node in DFS, then undo it after iterating its neighbors, and before return
	for (ITERATE_OVER_INPUT) {
		// DO modify curr, the current state
		ans += backtrack(curr, OTHERS); 
		// UNDO the modification of the current state
	}
	return ans; 
} 

/*
212. Word Search II; https://leetcode.com/problems/word-search-ii/
----------
642. Design Search Autocomplete System; https://leetcode.com/problems/design-search-autocomplete-system/
*/
struct TrieNode {
	int data; 
	unordered_map<char, TrieNode*> children; 
	TrieNode(): data(0), children(unordered_map<char, TrieNode*>()) {}
};

TrieNode* buildTrie(vector<string> words) {
	TrieNode* root = new TrieNode(); 
	for (auto &word : words) {
		auto curr = root; 
		for (auto c : word) {
			if (curr->children.find(c) == curr->children.end()) { // C++ 20: if (curr->contains(c))
				curr->children[c] = new TrieNode(); 
			}
			curr = curr->children[c]; 
			// perform something on the current TrieNode; 
		}
	}
	return root; 
}

// Union-Find
class UnionFind {
public:
    unordered_map<int, int> parent;
    
    // Constructor: Initialize each element as its own parent
    UnionFind(vector<int>& elements) {
        for (int element : elements) {
            parent[element] = element;
        }
    }
    
    // Find the representative parent of a component (with path compression)
    int find(int a) {
        if (parent[a] != a) {
            parent[a] = find(parent[a]); // Path compression
        }
        return parent[a];
    }
    
    // Merge two components by updating their parent pointers
    void merge(int a, int b) {
        parent[find(b)] = find(a);
    }
};

// or 
class UnionFind {
public:
    unordered_map<int, int> parent;

    int find(int a) {
        if(!parent.count(a))
            parent[a] = a;
        if(parent[a] != a)
            parent[a] = find(parent[a]);
        return parent[a];
    }
    void merge(int a, int b) {
        parent[find(b)] = find(a);
    }
};

/* or  Disjoint Set Union (DSU)
721. Accounts Merge; https://leetcode.com/problems/accounts-merge/
1584. Min Cost to Connect All Points; https://leetcode.com/problems/min-cost-to-connect-all-points/
*/
class DSU {
public:
    vector<int> representative;
    vector<int> size;
    
    DSU(int sz) : representative(sz), size(sz) {
        for (int i = 0; i < sz; ++i) {
            // Initially each group is its own representative
            representative[i] = i;
            // Initialize the size of all groups to 1
            size[i] = 1;
        }
    }
    
    // Finds the representative of group x
    int findRepresentative(int x) {
        if (x == representative[x]) {
            return x;
        }
        
        // This is path compression
        return representative[x] = findRepresentative(representative[x]);
    }
    
    // Unite the group that contains "a" with the group that contains "b"
    void unionBySize(int a, int b) {
        int representativeA = findRepresentative(a);
        int representativeB = findRepresentative(b);
        
        // If nodes a and b already belong to the same group, do nothing.
        if (representativeA == representativeB) {
            return;
        }
        
        // Union by size: point the representative of the smaller
        // group to the representative of the larger group.
        if (size[representativeA] >= size[representativeB]) {
            size[representativeA] += size[representativeB];
            representative[representativeB] = representativeA;
        } else {
            size[representativeB] += size[representativeA];
            representative[representativeA] = representativeB;
        }
    }
};

class UnionFind {
public: 
    vector<int> group; 
    vector<int> rank; 
    UnionFind(int size) {
        group  = vector<int>(size); 
        rank = vector<int>(size);
        for (int i = 0; i < size; ++i) {
            group[i] = i; 
        }
    }

    int find(int node) {
        if (group[node] != node) {
            group[node] = find(group[node]);
        }
        return group[node];
    }

    bool join(int node1, int node2) {
        int group1 = find(node1);
        int group2 = find(node2); 
        if (group1 == group2) {
            return false; 
        }
        if (rank[group1] > rank[group2]) {
            group[group2] = group1;
        } else if (rank[group1] < rank[group2]) {
            group[group1] = group2;
        } else {
            group[group1] = group2; 
            rank[group2]++;
        }
        return true; 
    }
};

// Dijkstra's algorithm
/* Dijkstra’s algorithm is not the same as BFS, but it can be seen as a generalization of BFS to weighted graphs.
At the framework level, Dijkstra looks almost identical to BFS — the only essential difference is the data structure that drives the traversal:
	BFS: expands nodes in first-in-first-out (FIFO) order → level by level.
	Dijkstra: expands nodes in smallest-distance-first order → controlled by a min-heap.
*/
#include <vector>
#include <queue>
#include <limits>

using namespace std;

using Edge = pair<int, int>;   // (neighbor, weight)
using HeapNode = pair<int, int>; // (distance, node)

vector<int> dijkstra(int n, int source, const vector<vector<Edge>>& graph) {
    vector<int> distances(n, numeric_limits<int>::max());
    distances[source] = 0;

    using MinHeap = priority_queue<HeapNode, vector<HeapNode>, greater<>>;
    MinHeap heap;
    heap.push({0, source});

    while (!heap.empty()) {
        auto [currDist, node] = heap.top();
        heap.pop();

        if (currDist > distances[node]) continue; // outdated entry

        for (const auto& [neighbor, weight] : graph[node]) {
            int newDist = currDist + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                heap.push({newDist, neighbor});
            }
        }
    }
    return distances;
}


/* Parentheses
921. Minimum Add to Make Parentheses Valid; https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
301. Remove Invalid Parentheses; https://leetcode.com/problems/remove-invalid-parentheses/
two rounds; first from left to right, second from right to left; in order to find the balance
1249. Minimum Remove to Make Valid Parentheses; https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
32. Longest Valid Parentheses; https://leetcode.com/problems/longest-valid-parentheses/
20. Valid Parentheses; https://leetcode.com/problems/valid-parentheses/
*/

/* Intervals 
sort by start or end; when merging, newEnd = max(newEnd, end); when overlapping, newEnd = min(minEnd, end); 
56. Merge Intervals; https://leetcode.com/problems/merge-intervals/
253. Meeting Rooms II; https://leetcode.com/problems/meeting-rooms-ii/
163. Missing Ranges; https://leetcode.com/problems/missing-ranges/
986. Interval List Intersections; https://leetcode.com/problems/interval-list-intersections/
435. Non-overlapping Intervals; https://leetcode.com/problems/non-overlapping-intervals/
*/

/* combine data structures
1. The critical and essential parts are to keep these combined data structures consistent, esp. when they refers each other
2. The quick lookup demands unordered_map
3. The random access needs a vector
4. LRU needs a list
unordered_map + list
146. LRU Cache; https://leetcode.com/problems/lru-cache/
unordered_map + vector
380. Insert Delete GetRandom O(1); https://leetcode.com/problems/insert-delete-getrandom-o1/
stack + vector
895. Maximum Frequency Stack; https://leetcode.com/problems/maximum-frequency-stack/; stack of stack; 2D stack; 
--------------------
1. Two set as stacks. 
716. Max Stack; https://leetcode.com/problems/max-stack/
*/

// sell and buy stocks

/* Parsing string 
String into integer: 
8. String to Integer (atoi); https://leetcode.com/problems/string-to-integer-atoi/
65. Valid Number; https://leetcode.com/problems/valid-number/; use four flags; 

Calculator 
224. Basic Calculator; https://leetcode.com/problems/basic-calculator/
227. Basic Calculator II; https://leetcode.com/problems/basic-calculator-ii/
772. Basic Calculator III; https://leetcode.com/problems/basic-calculator-iii/
282. Expression Add Operators; https://leetcode.com/problems/expression-add-operators/ 
*/

/* dp
91. Decode Ways; https://leetcode.com/problems/decode-ways/
53. Maximum Subarray; https://leetcode.com/problems/maximum-subarray
sliding
1D dp 
139. Word Break; https://leetcode.com/problems/word-break/
2369. Check if There is a Valid Partition For The Array; https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/
646. Maximum Length of Pair Chain; https://leetcode.com/problems/maximum-length-of-pair-chain/
377. Combination Sum IV; https://leetcode.com/problems/combination-sum-iv
746. Min Cost Climbing Stairs; https://leetcode.com/problems/min-cost-climbing-stairs/; from right to left
279. Perfect Squares; https://leetcode.com/problems/perfect-squares

2D dp
63. Unique Paths II; https://leetcode.com/problems/unique-paths-ii/ ; grid, up or left
518. Coin Change II; https://leetcode.com/problems/coin-change-ii/ ; not adjacent 
1216. Valid Palindrome III https://leetcode.com/problems/valid-palindrome-iii/; upper triangular matrix; -/|
97. Interleaving String; https://leetcode.com/problems/interleaving-string/
*/

/* Palindrome
680. Valid Palindrome II; https://leetcode.com/problems/valid-palindrome-ii/
1216. Valid Palindrome III https://leetcode.com/problems/valid-palindrome-iii/ ; 2D DP
*/

/* Heap
215. Kth Largest Element in an Array; https://leetcode.com/problems/kth-largest-element-in-an-array/
253. Meeting Rooms II; https://leetcode.com/problems/meeting-rooms-ii/
767. Reorganize String; https://leetcode.com/problems/reorganize-string/
*/

/* unordered_map and map
249. Group Shifted Strings; https://leetcode.com/problems/group-shifted-strings/
146. LRU Cache; https://leetcode.com/problems/lru-cache/
13. Roman to Integer; https://leetcode.com/problems/roman-to-integer/
953. Verifying an Alien Dictionary; https://leetcode.com/problems/verifying-an-alien-dictionary/
*/

/* stack
71. Simplify Path; https://leetcode.com/problems/simplify-path/
1209. Remove All Adjacent Duplicates in String II; https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
1047. Remove All Adjacent Duplicates In String; https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
20. Valid Parentheses; https://leetcode.com/problems/valid-parentheses/
1963. Minimum Number of Swaps to Make the String Balanced; https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/
*/

/* Divide and conquer
779. K-th Symbol in Grammar; https://leetcode.com/problems/k-th-symbol-in-grammar/
50. Pow(x, n); https://leetcode.com/problems/powx-n/
*/

/* Multiset
218. The Skyline Problem; https://leetcode.com/problems/the-skyline-problem/
*/

/* Greedy
135. Candy; https://leetcode.com/problems/candy/
435. Non-overlapping Intervals; https://leetcode.com/problems/non-overlapping-intervals/
605. Can Place Flowers; https://leetcode.com/problems/can-place-flowers/
670. Maximum Swap; https://leetcode.com/problems/maximum-swap/
767. Reorganize String; https://leetcode.com/problems/reorganize-string/
1647. Minimum Deletions to Make Character Frequencies Unique; https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/
1996. The Number of Weak Characters in the Game; https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/
*/


/* Cyclic Sorting
41. First Missing Positive; https://leetcode.com/problems/first-missing-positive/
	nums[i] - 1 == i || nums[nums[i] - 1] == nums[i]
287. Find the Duplicate Number; https://leetcode.com/problems/find-the-duplicate-number/
*/


/* 2D array
498. Diagonal Traverse; https://leetcode.com/problems/diagonal-traverse/
*/

/* Linked list
708. Insert into a Sorted Circular Linked List; https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/
*/