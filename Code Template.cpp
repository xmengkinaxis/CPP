// https://leetcode.com/explore/interview/card/cheatsheets/720/resources/4723/
// cheat sheet and code template
#include <iostream> // cout, cin
#include <cctype> // isalnum, isalpha, isdigit, islower, isupper, isspace; toupper, tolower
#include <sstream> // stringstream
#include <String> // substr, getline, strlen, string(n, char), append(n, char), find(str, pos), strcpy, strncpy, strcmp, stryncmp
#include <vector>
#include <unordered_map> 
#include <unordered_set>
#include <set> // multiset
#include <stack>
#include <queue> // riority_queue
#include <deque> // deque
#include <algorithm> // sort, min, max, 

using namespace std; 

#define CONDITION true
#define START_NODE 0

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
O(n log n) - Linearithmic Time: Common for efficient sorting and searching algorithms.
O(n^2), O(n^3), ... - Polynomial Time: Performance grows with the square, cube, etc. of the input size.
O(2^n), O(n!) - Exponential and Factorial Time: Extremely inefficient algorithms.

Common space complexity notations include:
O(1) - Constant Space: The algorithm uses a fixed amount of memory regardless of the input size.
O(n) - Linear Space: The algorithm's memory usage scales linearly with the input size.
O(n^2), O(n^3), ... - Polynomial Space: Memory usage grows with the square, cube, etc. of the input size.
*/

/*
Two Pointers Technique: left and right, or slow and fast 
Sliding Window Technique: start and end
Binary Search: low and high if the array is strictly increased, or use left and right if there are some duplications
*/

// ??? sort all problems of meta once a week into different algorithms, whose numbers are less than 23 and after 29

// two pointers with opposite directions
// e.g. Palindrome problems (odd or even, two pointers with the opposite directions): 
// 647. Palindromic Substrings https://leetcode.com/problems/palindromic-substrings/?envType=list&envId=9kpcif56
// 15. 3Sum; https://leetcode.com/problems/3sum/description/
// 125. Valid Palindrome; https://leetcode.com/problems/valid-palindrome/description/
// 557. Reverse Words in a String III; https://leetcode.com/problems/reverse-words-in-a-string-iii/
int fnTwoPointers(vector<int>& arr) {
	int left = 0, right = arr.size() - 1; 
	int ans = 0;
	while (left < right)  {
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


// two pointers for two arrays with the same direction; to merge rather to to intersect 
// 408. Valid Word Abbreviation https://leetcode.com/problems/valid-word-abbreviation/?envType=list&envId=9kpcif56
// 21. Merge Two Sorted Lists; https://leetcode.com/problems/merge-two-sorted-lists/
// 234. Palindrome Linked List; https://leetcode.com/problems/palindrome-linked-list/description/
// 1570. Dot Product of Two Sparse Vectors; https://leetcode.com/problems/dot-product-of-two-sparse-vectors/
// 1650. Lowest Common Ancestor of a Binary Tree III; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/description/
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


// sliding window
// for the window with the various size, need two pointers to indicate the start and the end of the window
// for the window with the fixed size, only need a single pointer to point to the end of the window
// for the window with the fixed size, remove the start since the end >= the window size
// must ensure the start is moved, otherwise, the inner loop would become a dead one.
// 239. Sliding Window Maximum;  https://leetcode.com/problems/sliding-window-maximum/?envType=list&envId=9kpcif56
// 1004. Max Consecutive Ones III; https://leetcode.com/problems/max-consecutive-ones-iii/?envType=list&envId=9kpcif56
// 76. Minimum Window Substring; https://leetcode.com/problems/minimum-window-substring/description/
int fnSlidingWindow(vector<int>& arr) {
	int ans = 0; 
	for (int start = 0, end = 0, curr = 0; end < arr.size(); ++end) {
		// add arr[end] into curr; 
		// the curr might be a complex one, 
		// 	such as a monotonic deque, and need some preprocess before adding
		// 	or a unordered_map to represent the frequency of characters in the window

		// depend on if the window size is fixed or not, 
		// if fixed, when end >= size, remove the start by moving it towards end by one
		// if not fixed, depend on the loop condition to remove the start
		while (CONDITION && start <= end ) { // the condition "start <= end" is critical to ensure it is still a valid window
			// can do something for the valid window here as the window is shrinking
			// remove arr[start] from curr; 
			++start;  // it would be a dead loop if start is not moved
		}
		// do something for this valid window
		// if the size is fixed, when end >= size - 1, do something
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

// fast and slow pointers; a case of two pointers with the same direction
// odd number of items: fast is valid, but fast->next is nullptr, slow points to the exact middle node of list
// even number of items: fast is nullptr, and slow points to the second middle (right-middle) node 
// 283. Move Zeroes; https://leetcode.com/problems/move-zeroes/description/
// 234. Palindrome Linked List; https://leetcode.com/problems/palindrome-linked-list/description/
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
// 234. Palindrome Linked List; https://leetcode.com/problems/palindrome-linked-list/description/
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

// Find numbers of subarrays that fit an exact criteria
// this like a fixed-left-side sliding window and process as a length-increasing-forever window, sharing the similar code template
// 325. Maximum Size Subarray Sum Equals k; https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/description/?envType=list&envId=9kpcif56
// 523. Continuous Subarray Sum; https://leetcode.com/problems/continuous-subarray-sum/description/?envType=list&envId=9kpcif56 
// 560. Subarray Sum Equals K; https://leetcode.com/problems/subarray-sum-equals-k/description/
// similar e.g. 219. Contains Duplicate II; https://leetcode.com/problems/contains-duplicate-ii/description/
int fnFindSubarrays(vector<int>& arr, int k) {
	// 0. define the map and initialize it properly
	// using a map to look up quickly; and it serves as a memo/dp, so it needs the initialization
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
		counts[curr]++; // there might be a condition to check before adding into the map
	}
	return ans; 
}

// the monotonic stack might contain values or some index; 
// if the stack contains index, the while condition should be changed accordingly
// < and > is opposite to the order decreasing and increasing
// 	increase: >
// 	decrease: <
// 1944. Number of Visible People in a Queue https://leetcode.com/problems/number-of-visible-people-in-a-queue/description/?envType=list&envId=9kpcif56
// 1762. Buildings With an Ocean View https://leetcode.com/problems/buildings-with-an-ocean-view/description/ 
// 316. Remove Duplicate Letters; https://leetcode.com/problems/remove-duplicate-letters/?envType=list&envId=9kpcif56
int fnMonotonicIncreasingStack(vector<int>& arr) {
	stack<int> stack; 
	int ans = 0;

	for (int n : arr) {
		// this is monotonic increasing
		// for monotonic decrease, change > to < 
		while (!stack.empty() && stack.top() > n) {
			// do logic here
			stack.pop(); 
		}
		// might do logic here too
		stack.push(n); // might be index pushed into the stack
	}
}

// inorder, preorder, postorder;
// 987. Vertical Order Traversal of a Binary Tree; https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/?envType=list&envId=9kpcif56
// 543. Diameter of Binary Tree; https://leetcode.com/problems/diameter-of-binary-tree/description/
// 1382. Balance a Binary Search Tree; https://leetcode.com/problems/balance-a-binary-search-tree/?envType=list&envId=9kpcif56
// 536. Construct Binary Tree from String; https://leetcode.com/problems/construct-binary-tree-from-string/?envType=list&envId=9kpcif56
// 938. Range Sum of BST; https://leetcode.com/problems/range-sum-of-bst/description/
// 236. Lowest Common Ancestor of a Binary Tree; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
// 1644. Lowest Common Ancestor of a Binary Tree II; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/description/
// 1676. Lowest Common Ancestor of a Binary Tree IV; https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/description/
// 426. Convert Binary Search Tree to Sorted Doubly Linked List; https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/description/
// 95. Unique Binary Search Trees II; https://leetcode.com/problems/unique-binary-search-trees-ii/description/
// 129. Sum Root to Leaf Numbers; https://leetcode.com/problems/sum-root-to-leaf-numbers/description/; // leave is one of the base cases 
// 623. Add One Row to Tree; https://leetcode.com/problems/add-one-row-to-tree/description/; do logic for the node at the certain level
// 1110. Delete Nodes And Return Forest; https://leetcode.com/problems/delete-nodes-and-return-forest/description/
// 865. Smallest Subtree with all the Deepest Nodes; https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
// 1123. Lowest Common Ancestor of Deepest Leaves; https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/description/
int dfsTree(TreeNode *root) { // could return a tuple of a node and the depth
	// 1. deal withing the special base cases;  could be more base cases
	// when calculating the depth, it is 0 for nullptr and 1 for a leave; so the base case is still nullptr; 
	if (!root) { return 0; }

	int ans = 0; 
	// 2. do logic for this node
	// sometime check if the root is the special target, such as a leave, do the logic for leaf and then return; 

	// 3. iterate all branches/candidates/choices/;
	// 4. might need to check if a branch should be visited with some conditions, e.g. value in the special range
	//  or depending on if other branches exist or not
	dfsTree(root->left); 
	dfsTree(root->right); 
	return ans; 	
}

// 173. Binary Search Tree Iterator; https://leetcode.com/problems/binary-search-tree-iterator/description/
// dfsTreeStack is much similar to bfsTree; the only difference is stack vs queue
int dfsTreeStack(TreeNode* root) {
	if (!root) { return 0; 	}

	stack<TreeNode*> stack; 
	stack.push(root); 
	int ans = 0; 
	// beside if the stack is empty, it might need to check if other conditions are met
	while (!stack.empty()) {
		auto node = stack.top(); 
		stack.pop(); 
		// 1. do logic for this node
		// 2. visit its branches
		if (node->left) { stack.push(node->left); }
		if (node->right) { stack.push(node->right); }

	}
	return ans; 
}


// 314. Binary Tree Vertical Order Traversal, https://leetcode.com/problems/binary-tree-vertical-order-traversal/
// 199. Binary Tree Right Side View; https://leetcode.com/problems/binary-tree-right-side-view/description/
int bfsTree(TreeNode* root) {
	if (!root) { return 0; }

	queue<TreeNode*> queue; 
	queue.push(root); 
	int ans = 0; 
	// beside if the queue is empty, it might need to check if other conditions are met, e.g. reaching the target level
	while (!queue.empty()) {
		// the following for loop can be eliminated if there is NO action for each layer
		for (int count = queue.size(); 0 < count; --count) {
			auto node = queue.front(); queue.pop(); 
			// 1. do logic for this node
			// 2. visit its branches
			if (node->left) { queue.push(node->left); }
			if (node->right) { queue.push(node->right); }
		}
		// do some actions for this layer, e.g. calculating steps/time
		// or this action can be merged with the while loop and change it into a for loop
	}
	return ans; 
}

// for DFS, the core actions are: 
// 1. check if the node is valid, e.g. it must be in the grid when the problem is a grid,
// 2. check if the node should be visited, e.g. the original value/attribute of this node makes it as a valid candidate. 
// 3. check if the node is already visited, e.g. seen/visited already contains it 
// 4. do something for this node; this is a real visit on this node
// 5. visit all its neighbors; 
// * these core actions is the core of DFS and the block of the BFS while loop
// * for BFS, the order might be 4, 5, 1, 2, 3
// * if changing the original value instead of using seen/visited, the 2 and 3 are merged into one of checking value

// 317. Shortest Distance from All Buildings;  https://leetcode.com/problems/shortest-distance-from-all-buildings/description/?envType=list&envId=9kpcif56
// 339. Nested List Weight Sum; https://leetcode.com/problems/nested-list-weight-sum/description/
// 529. Minesweeper; https://leetcode.com/problems/minesweeper/description/; acton 2 and 3 are separated
unordered_set<int> seen; 
int dfsGraph1(vector<vector<int>>& graph) {
	seen.insert(START_NODE); // #1. must do insert before visiting it in order to avoid the dead loop
							// #2. alternatively, immediately insert it when start visiting it, 
							// and check if the neighbor is already visited when iterating them 
	return dfsGraph1(START_NODE, graph);
}

int dfsGraph1(int node, vector<vector<int>>& graph) {
	int ans = 0; 
	// do logic for node here
	for (int neighbor : graph[node]) { // might to validate if a neighbor is valid first		
		if (seen.find(neighbor) == seen.end()) { // prerequisite of the atomic action: ensure the node is not visited before
			// they are a pair of actions, inserting the node into seen and call dfs on this node.
			// an atomic action: add into seen, and then dfs ths node
			// AKA. the atomic action: want to visit (add into seen), and do visit (do dfs)
			seen.insert(neighbor); // this and the next steps are repeating the two steps in the above function
			dfsGraph1(neighbor, graph); 
		}
	}
	return ans; 
}


// 490. The Maze; https://leetcode.com/problems/the-maze/description/
unordered_set<int> seen2; 
int dfsGraph2(vector<vector<int>>& graph) {
	return dfsGraph2(START_NODE, graph);
}

int dfsGraph2(int node, vector<vector<int>>& graph) {
	seen2.insert(START_NODE); // must do insert before visiting it in order to avoid the dead loop
	int ans = 0; 
	// do logic for node here
	// if the node value can be changed and the changed value can be used as the visited flag, 
	// then there is no need to create a separated seen/visited data structure
	for (int neighbor : graph[node]) { // might to validate if a neighbor is valid first		
		if (seen2.find(neighbor) == seen2.end()) { // prerequisite of the atomic action: ensure the node is not visited before
			// they are a pair of actions, inserting the node into seen and call dfs on this node.
			// an atomic action: add into seen, and then dfs ths node
			// AKA. the atomic action: want to visit (add into seen), and do visit (do dfs)
			dfsGraph2(neighbor, graph); 
		}
	}
	return ans; 
}

// 490. The Maze; https://leetcode.com/problems/the-maze/description/
// 778. Swim in Rising Water; https://leetcode.com/problems/swim-in-rising-water/description/?envType=list&envId=9kpcif56
// 79. Word Search; https://leetcode.com/problems/word-search/
bool dfsGraph3(int node, vector<vector<int>>& graph) {	
	if (seen2.find(node) == seen2.end()) {
		return false; 
	} else if (CONDITION) { // CONDITION: node is the destination
		return true; // found
	}
	seen2.insert(START_NODE); // must do insert before visiting it in order to avoid the dead loop
	// do logic for node here
	for (int neighbor : graph[node]) { 
		if (dfsGraph3(neighbor, graph)) {
			return true; 
		} 
	}
	return false; 
}


int dfsIterative(vector<vector<int>> & graph) {
	stack<int> stack; 
	unordered_set<int> seen; 
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

// when do Topological Sort, no need to keep the seen set, 
// for it is DAG, and a node is added into queue only when only its in/out degree reach zero
// 317. Shortest Distance from All Buildings; https://leetcode.com/problems/shortest-distance-from-all-buildings/?envType=list&envId=9kpcif56
// 1091. Shortest Path in Binary Matrix; https://leetcode.com/problems/shortest-path-in-binary-matrix/description/
// 286. Walls and Gates; https://leetcode.com/problems/walls-and-gates/description/
// 863. All Nodes Distance K in Binary Tree; https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/; reach a certain level
// 200. Number of Islands; https://leetcode.com/problems/number-of-islands/description/
int bfsGraph(vector<vector<int>>& graph) {
	queue<int> queue; 
	unordered_set<int> seen; 
	// they are a pair of actions, inserting the node into seen and adding the node into queen.
	// an atomic action: add into seen, and then add into queue
	// there might be a numbers of starting nodes and all these need to be added into the queue initially
	// there might be zero of starting nodes. This is an edge case. 
	// in summary, the number of starting nodes, could be 0, 1, N; 
	seen.insert(START_NODE); 
	queue.push(START_NODE); 
	int ans = 0; 
	while (!queue.empty()) {
		int node = queue.front(); 
		queue.pop(); 
		// do logic for the node; e.g. set the distance or time for this node, or check if reach the destination and then exit
		for (auto neighbor : graph[node]) {
			// iterate candidates or validate if it is a valid candidate
			if (seen.find(neighbor) == seen.end()) {
				// ensure if it is NOT seen yet
				// atomic action: add it into both seen and queue
				seen.insert(neighbor); 
				queue.push(neighbor); 
			}
		}
	}
	return ans; 
}

int bfsGraphSteps(vector<vector<int>>& grid) {
	const int N = grid.size(); 
	// deal with the special case, e.g. grid[0][0] or/and grid[N - 1][N - 1]

	queue<pair<int, int>> queue; 
	queue.push({0, 0}); 
	grid[0][0] = 2; // mark it as visited by changing its value
	for (int step = 1; !queue.empty(); step++) { // the step must be initialized properly, and is increased level by level
		for (int count = queue.size(); 0 < count; --count) {
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
				if (nr < 0 || nr >= N || nc < 0 || nc >= N // valid if it is a valid candidate
					|| grid[nr][nc]) { // check if it was visited
					continue; 
				}
				grid[nr][nc] = 2; 
				queue.push({nr, nc});
			}
		}
	}
	return -1; 
}

// 973. K Closest Points to Origin; https://leetcode.com/problems/k-closest-points-to-origin/description/
// 347. Top K Frequent Elements; https://leetcode.com/problems/top-k-frequent-elements/
vector<int> fnTopK(vector<int>& arr, int k) {
	priority_queue<int, vector<int>, greater<int>> minHeap; // priority_queue<int> heap; 
	for (auto n : arr) {
		minHeap.push(n); 
		if (minHeap.size() > k) {
			minHeap.pop();
		}
	}

	vector<int> ans; 
	while (!minHeap.empty()){
		ans.push_back(minHeap.top()); 
		minHeap.pop(); 
	}
	return ans; 
}

int binarySearch(vector<int>& arr, int target) {
	int low = 0, high = arr.size() - 1; 
	while (low <= high) {
		int mid = low + (high - low) / 2; 
		if (target == arr[mid])  {
			return mid; 
		} else if (target < arr[mid]) {
			high = mid - 1; 
		} else {
			low = mid + 1; 
		}
	}
	return low; 
}

// e.g. 852. Peak Index in a Mountain Array, https://leetcode.com/problems/peak-index-in-a-mountain-array/description/
// 1870. Minimum Speed to Arrive on Time; https://leetcode.com/problems/minimum-speed-to-arrive-on-time/description/
// 1539. Kth Missing Positive Number; https://leetcode.com/problems/kth-missing-positive-number/?envType=list&envId=9kpcif56
// 778. Swim in Rising Water; https://leetcode.com/problems/swim-in-rising-water/description/?envType=list&envId=9kpcif56
// Binary search: duplicate elements, left-most insertion point
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
/*
int minSpeedOnTime(vector<int>& dist, double hour) {
	int left = 1;
	int right = 1e7;
	int minSpeed = -1;
	
	while (left <= right) {
		int mid = (left + right) / 2;
		
		// Move to the left half.
		if (timeRequired(dist, mid) <= hour) {
			minSpeed = mid;
			right = mid - 1;
		} else {
			// Move to the right half.
			left = mid + 1;
		}
	}
	return minSpeed;
}
*/
// Binary search: duplicate elements, right-most insertion point
// 1060. Missing Element in Sorted Array; https://leetcode.com/problems/missing-element-in-sorted-array/?envType=list&envId=9kpcif56
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
// e.g. 1060. Missing Element in Sorted Array https://leetcode.com/problems/missing-element-in-sorted-array/description/?envType=list&envId=9kpcif56 
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
In C++, when using binary search, the initialization of the right pointer in the search range can be done in two ways:

1. When considering the entire array:
   - If the binary search needs to consider all elements of the array, the right pointer is initialized to `array.size()`. For example:
*/

vector<int> nums; 
{
     int left = 0;
     int right = nums.size(); // Right pointer initialized to array.size()
     while (left < right) {
         // Binary search logic
     }
}
/*
2. When excluding the last element:
   - In some scenarios, the binary search may need to exclude the last element from the search range. 
   This is commonly seen when searching for a specific target or finding an element that is just greater or equal to a given value. 
   In such cases, the right pointer is initialized to `array.size() - 1`. For example:
*/
{
     int left = 0;
     int right = nums.size() - 1; // Right pointer initialized to array.size() - 1
     while (left <= right) {
         // Binary search logic
     }
}
	 
/*
3. Adjusting indexing convention:
   - In C++, arrays are 0-indexed, which means that the valid indices of elements range from 0 to `array.size() - 1`. 
   If the binary search uses this indexing convention, then the right pointer is typically initialized to `array.size() - 1` to prevent accessing an element beyond the valid index range. For example:
*/
{
     int left = 0;
     int right = nums.size() - 1; // Right pointer initialized to array.size() - 1
     while (left <= right) {
         // Binary search logic
     }
}
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
}

// Binary search: for greedy problems
// If looking for a minimum:
// e.g. 1011. Capacity To Ship Packages Within D Days; https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
int binaryMinimum(vector<int>& arr) {
	int low = MINIMUM_POSSIBLE_ANSWER; 
	int high = MAXIMUM_POSSIBLE_ANSWER; 
	// must use <= here; this is different from the above binary search
	while (low <= high) {
		auto mid = low + (high - low) / 2; 
		if (check(mid)) {
			high = mid - 1; 
		} else {
			low = mid + 1;  // when exit, low will be the first/smallest/minimum to meet the check function
		}
	}
	return low; 
}

// 1891. Cutting Ribbons https://leetcode.com/problems/cutting-ribbons/description/?envType=list&envId=9kpcif56 
// Binary search: for greedy problems
// If looking for a maximum:
int binaryMaximum(vector<int>& arr) {
	int low = MINIMUM_POSSIBLE_ANSWER; 
	int high = MAXIMUM_POSSIBLE_ANSWER;
	// must use <= here
	while (low <= high) {
		auto mid = low + (high - low) / 2; 
		if (check(mid)) {
			low = mid + 1; 
		} else {
			high = mid - 1; // when exit, high will be the last/largest/maximum to meet the check function
		}
	}
	return high; 
}

// 17. Letter Combinations of a Phone Number; https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
// 78. Subsets https://leetcode.com/problems/subsets/description/
// 301. Remove Invalid Parentheses; https://leetcode.com/problems/remove-invalid-parentheses/?envType=list&envId=9kpcif56
// 46. Permutations; https://leetcode.com/problems/permutations/
// 77. Combinations; https://leetcode.com/problems/combinations/
// 140. Word Break II; https://leetcode.com/problems/word-break-ii/description/?envType=list&envId=9kpcif56 
// 282. Expression Add Operators; https://leetcode.com/problems/expression-add-operators/?envType=list&envId=9kpcif56
int backtrack(STATE curr, OTHERS) {
	if (BASE_CASE) { // startId, or curr state size, or both
		// modify the answer
		return 0; 
	}

	int ans = 0; 
	// like dfs, iterate all candidates
	// the other difference is to modify the current state
	// and to undo the modification
	for (INTERATE_OVER_INPUT) {
		// modify curr, the current state
		ans += backtrack(curr, OTHERS); 
		// undo the modification of the current state
	}
	return ans; 
}

// 212. Word Search II; https://leetcode.com/problems/word-search-ii/description/
struct TrieNode {
	int data; 
	unordered_map<char, TrieNode*> children; 
	TrieNode(): data(0), children(unordered_map<char, TrieNode*>()) {}
};

TrieNode* buildTrie(vector<string> words) {
	TrieNode* root = new TrieNode(); 
	for (auto word : words) {
		auto curr = root; 
		for (auto c : word) {
			if (curr->children.find(c) == curr->children.end()) {
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


/* Parentheses
921. Minimum Add to Make Parentheses Valid; https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/?envType=list&envId=9kpcif56
1249. Minimum Remove to Make Valid Parentheses; https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
301. Remove Invalid Parentheses; https://leetcode.com/problems/remove-invalid-parentheses/
*/

/* intervals 
sort by start or end; when merging, newEnd = max(newEnd, end); when overlapping, newEnd = min(minEnd, end); 
56. Merge Intervals; https://leetcode.com/problems/merge-intervals/
253. Meeting Rooms II; https://leetcode.com/problems/meeting-rooms-ii/
163. Missing Ranges; https://leetcode.com/problems/missing-ranges/
986. Interval List Intersections; https://leetcode.com/problems/interval-list-intersections/
*/

// combine data structures

// sell and buy stocks

/* Calculator 
224. Basic Calculator; https://leetcode.com/problems/basic-calculator/
227. Basic Calculator II; https://leetcode.com/problems/basic-calculator-ii/
772. Basic Calculator III; https://leetcode.com/problems/basic-calculator-iii/
282. Expression Add Operators; https://leetcode.com/problems/expression-add-operators/ 
*/

/* dp
1216. Valid Palindrome III https://leetcode.com/problems/valid-palindrome-iii/?envType=list&envId=9kpcif56
91. Decode Ways; https://leetcode.com/problems/decode-ways/description/
139. Word Break; https://leetcode.com/problems/word-break/

1D dp 
2369. Check if There is a Valid Partition For The Array; https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/description/

2D dp
63. Unique Paths II; https://leetcode.com/problems/unique-paths-ii/description/
*/

/* Palindrome
680. Valid Palindrome II; https://leetcode.com/problems/valid-palindrome-ii/
1216. Valid Palindrome III https://leetcode.com/problems/valid-palindrome-iii/?envType=list&envId=9kpcif56 ; 2D DP
*/

/* Heap
215. Kth Largest Element in an Array; https://leetcode.com/problems/kth-largest-element-in-an-array/
253. Meeting Rooms II; https://leetcode.com/problems/meeting-rooms-ii/
*/

/* unordered_map and map
249. Group Shifted Strings; https://leetcode.com/problems/group-shifted-strings/
*/

/* stack
71. Simplify Path; https://leetcode.com/problems/simplify-path/description/
1209. Remove All Adjacent Duplicates in String II; https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
*/

/* Divide and conquer
779. K-th Symbol in Grammar; https://leetcode.com/problems/k-th-symbol-in-grammar/description/
50. Pow(x, n); https://leetcode.com/problems/powx-n/
*/

/* Multiset
218. The Skyline Problem; https://leetcode.com/problems/the-skyline-problem/description/
*/