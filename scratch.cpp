// https://leetcode.com/explore/interview/card/cheatsheets/720/resources/4723/
// cheatsheet and code template
#include <vector>
#include <String> 
#include <unordered_map> 
#include <stack>

using namespace std; 

// two pointers with opposite directions
int fnTwoPointers(vector<int>& arr) {
	int left = 0, right = arr.size() - 1; 
	int ans = 0;
	while (left < right)  {
		if (CONDITION) {
			++left;
		} else {
			--right; 
		}
	}
	return ans; 
}

// two pointers for two arrays with the same direction
int fnTwoPointersTwoArrays(vector<int>& arr1, vector<int>& arr2) {
	int i = 0, j = 0, ans = 0; 

	while (i < arr1.size() && j < arr2.size()) {
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
int fnSlidingWindow(vector<int>& arr) {
	int ans = 0; 
	for (int left = 0, right = 0, curr = 0; right < arr.size(); ++right) {
		// add arr[right] into curr; 
		while (CONDITION && left <= right ) {
			// remove arr[left] from curr; 
			++left; 
		}
		// do something for this valid window
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

// fast and slow pointers
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

// ???? Find numbers of subarrays that fit an exact criteria
int fnFindSubarrays(vector<int>& arr, int k) {
	unordered_map<int, int> counts; 
	counts[0] = 1; 
	int ans = 0, curr = 0; 
	for (int num : arr) {
		ans += counts[curr -k]; 
		counts[curr]++; 
	}
	return ans; 
}

// ????
int fnMonotonicIncreasingStack(vector<int>& arr) {
	stack<int> stack; 
	int ans = 0;

	for (int n : arr) {
		while (!stack.empty() && stack.top() > num) {
			stack.pop(); 
		}
		stack.push(n); 
	}
}

// inorder, preorder, postorder;

int dfsTree(TreeNode *root) {
	// 1. deal withing the special base cases
	// leave is one of these cases
	// could be more base cases
	if (!root) { return 0; }
	int ans = 0; 
	// 2. do logic for this node
	// 3. iterate all branches/candidates/choices/
	// 4. might need to check if a branch should be visited with some conditions
	//  or depending on if other branches exist or not
	dfsTree(root->left); 
	dfsTree(root->right); 
	return ans; 	
}


int dfsTreeStack(TreeNode* root) {
	if (!root) { return 0; 	}

	stack<TreeNode*> stack; 
	stack.push(root); 
	int ans = 0; 
	// beside if the stack is empty, it might need to check if other conditions are met
	while (!stack.empty()) {
		auto node = stack.top(); 
		stack.pop(); 
		// do logic for this node
		if (node->left) {
			stack.push(node->left);
		}
		if (node->right) {
			stack.push(node->right);
		}

	}
	return ans; 
}

int bfsTree(TreeNode* root) {
	if (!root) { return 0; }

	queue<TreeNode*> queue; 
	queue.push(root); 
	int ans = 0; 
	// beside if the queue is empty, it might need to check if other conditions are met
	while (!queue.empty()) {
		// the following for loop can be eliminated if there is NO action for each layer
		for (int count = queue.size(); 0 < count; --count) {
			auto node = queue.front(); queue.pop(); 
			// do logic for node
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
// 2. check if the node is already visited, e.g. seen/visited already contains it
// 3. check if the node should be visited, e.g. the original value/attribute of this node makes it as a valid candidate. 
// 4. do something for this node; this is a real visit on this node
// 5. visit all its neighbors; 
// * these core actions is the core of DFS and the block of the BFS while loop
// * for BFS, the order might be 4, 5, 1, 2, 3
// * if changing the original value instead of using seen/visited, the 2 and 3 are merged into one of checking value


unordered_set<int> seen; 
int dfsGraph1(vector<vector<int>>& graph) {
	seen.insert(START_NODE); // #1. must do insert before visiting it in order to avoid the dead loop
							// #2. alternatively, immediately insert it when start visiting it, 
							// and check if the neighbor is already visited when iterating them 
	return dfsGraph(START_NODE, graph);
}

int dfsGraph1(int node, vector<vector<int>>& graph) {
	int ans = 0; 
	// do logic for node here
	for (int neighbor : graph[node]) { // might to validate if a neighbor is valid first		
		if (seen.find(neighbor) = seen.end()) { // prerequisite of the atomic action: ensure the node is not visited before
			// they are a pair of actions, inserting the node into seen and call dfs on this node.
			// an atomic action: add into seen, and then dfs ths node
			// AKA. the atomic action: want to visit (add into seen), and do visit (do dfs)
			seen.insert(neighbor); // this and the next steps are repeating the two steps in the above function
			dfsGraph(neighbor, graph); 
		}
	}
	return ans; 
}


// ????
unordered_set<int> seen2; 
int dfsGraph2(vector<vector<int>>& graph) {
	return dfsGraph(START_NODE, graph);
}

int dfsGraph2(int node, vector<vector<int>>& graph) {
	seen2.insert(START_NODE); // must do insert before visiting it in order to avoid the dead loop
	int ans = 0; 
	// do logic for node here
	// if the node value can be changed and the changed value can be used as the visited flag, 
	// then there is no need to create a separated seen/visited data structure
	for (int neighbor : graph[node]) { // might to validate if a neighbor is valid first		
		if (seen2.find(neighbor) = seen2.end()) { // prerequisite of the atomic action: ensure the node is not visited before
			// they are a pair of actions, inserting the node into seen and call dfs on this node.
			// an atomic action: add into seen, and then dfs ths node
			// AKA. the atomic action: want to visit (add into seen), and do visit (do dfs)
			dfsGraph2(neighbor, graph); 
		}
	}
	return ans; 
}

int dfsIterative(vector<vector<int>> & graph) {
	stack<int> stack; 
	unordered_set<int> seen; 
	seen.insert(Start_node);
	stack.push(Start_node);
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

int bfsGraph(vector<vector<int>>& graph) {
	queue<int> queue; 
	unordered_set<int> seen; 
	// they are a pair of actions, inserting the node into seen and adding the node into queen.
	// an atomic action: add into seen, and then add into queue
	// there might be a numbers of starting nodes and all these need to be added into the queue initially
	// there might be zero of starting nodes. This is an edge case. 
	// in summary, the number of starting nodes, could be 0, 1, N; 
	seen.insert(start_node); 
	queue.push(start_node); 
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

vector<int> fnTopK(vector<int>& arr, int k) {
	priority_queue<int, vector<int>, greater<int>> minHeap; // priority_queue<int> heap; 
	for (auto n : arr) {
		minHeap.push(n); 
		if (minHeap.size() > k) {
			minHeap.pop();
		}
	}

	vector<int> ans; 
	while (minHeap.size() > 0){
		ans.push_back(minHeap.top()); 
		minHeap.pop(); 
	}
	return ans; 
}

int binarySearch(vector<int>& arr, int target) {
	int left = 0, right = arr.size() - 1; 
	while (left <= right) {
		int mid = left + (right - left) / 2; 
		if (target == arr[mid])  {
			return mid; 
		} else if (target < arr[mid]) {
			right = mid - 1; 
		} else {
			left = mid + 1; 
		}
	}
	return left; 
}

int binaryLeftMost(vector<int>& arr, int target) {
	int left = 0;
	for (int right = arr.size(); left < right; )  {
		auto mid = left + (right - left) / 2; 
		if (arr[mid] >= target) {
			right = mid; 
		} else {
			left = mid + 1; 
		}
	}
	return left; 
}

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

// ????
int binaryMinimum(vector<int>& arr) {
	int left = MINIMUM_POSSIBLE_ANSWER; 
	int right = MAXIMUM_POSSIBLE_ANSWER; 
	while (left <= right) {
		auto mid = left + (right - left) / 2; 
		if (check(mid)) {
			right = mid - 1; 
		} else {
			left = mid + 1; 
		}
	}
	return left; 
}

int binaryMaximum(vector<int>& arr) {
	int left = MINIMUM_POSSIBLE_ANSWER; 
	int right = MAXIMUM_POSSIBLE_ANSWER;
	while (left <= right) {
		auto mid = left + (right - left) / 2; 
		if (check(mid)) {
			right = mid - 1; 
		} else {
			left = mid + 1; 
		}
	}
	return right; 
}

int backtrack(STATE curr, OTHERS) {
	if (BASE_CASE) {
		return 0; // modify the answer
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
}

// Input size VS time complexity
n <= 10 : O(n^2 * n!) or O(4^n), backtrack or brute-force 
n <= 20: O(2^n), backtrack or recursion 
n <= 100: O(n^3), brute-force
n <= 1,000: O(n * n)
n <= 100,000: O(n * log n) or O(n): sort or heap; 
hash map, two pointers, sliding windows, Monotonic stack, 
binary search, heap, or combination
n <= 1,000,000: O(n) or O(n * logh n): hash map
More: O(log n ) or O(1)