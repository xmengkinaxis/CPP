#include <vector>
#include <String> 
#include <unorderd_map> 
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
int fnSlidingWindow(vector<int>& arr) {
	int ans = 0; 
	for (int left = 0, right = 0, curr = 0; right < arr.size(); ++right) {
		// add arr[right] into curr; 
		while (CoNDITION) {
			// remove arr[left] from curr; 
			++left; 
		}
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


int dfsTree(TreeNode *root) {
	// 1. deal withing the special base cases
	// leave is one of these cases
	// could be more base cases
	if (!root) { return 0; }
	int ans = 0; 
	// 2. do logic for this node
	// 3. iterate all branches/candidates/choices/
	dfsTree(root->left); 
	dfsTree(root->right); 
	return ans; 	
}


int dfsTreeStack(TreeNode* root) {
	if (!root) { return 0; 	}

	stack<TreeNode*> stack; 
	stack.push(root); 
	int ans = 0; 
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
	while (!queue.empty()) {
		for (int count = queue.size(); 0 < count; --count) {
			auto node = queue.front(); queue.pop(); 
			// do logic for node
			if (node->left) { queue.push(node->left); }
			if (node->right) { queue.push(node->right); }
		}
	}
	return ans; 
}

unordered_set<int> seen; 
int dfsGraph(vector<vector<int>>& graph) {
	seen.insert(START_NODE); 
	return dfsGraph(START_NODE, graph);
}

int dfsGraph(int node, vector<vector<int>>& graph) {
	int ans = 0; 
	// do logic for node here
	for (int neighbor : graph[node]) {
		if (seen.find(neighbor) = seen.end()) {
			seen.insert(neighbor); 
			dfsGraph(neighbor, graph); 
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


int bfsGraph(vector<vector<int>>& graph) {
	queue<int> queue; 
	unordered_set<int> seen; 
	// they are a pair of actions, inserting the node into seen and adding the node into queen.
	// an atomic action: add into seen, and then add into queue
	seen.insert(start_node); 
	queue.push(start_node); 
	int ans = 0; 
	while (!queue.empty()) {
		int node = queue.front(); 
		queue.pop(); 
		// do logic for the node; 
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
	priority_queue<int> heap; 
	for (auto n : arr) {
		heap.push(n); 
		if (heap.size() > k) {
			heap.pop();
		}
	}

	vector<int> ans; 
	while (heap.size() > 0){
		ans.push_back(heap.top()); 
		heap.pop(); 
	}
	return ans; 
}