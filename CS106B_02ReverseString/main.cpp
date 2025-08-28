#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

class TrieNode {
public: 
    unordered_map<char, TrieNode*> children; 
    vector<pair<int, string>> words; 
    TrieNode() : children(unordered_map<char, TrieNode*>()), 
        words(vector<pair<int, string>>()) {}
};

class AutoComplete {
    TrieNode *root{nullptr};
    void addToTrie(string &inputWord, int relevance)  {
        auto curr = root; 
        for (auto ch : inputWord) {
            if (curr->children.find(ch) == curr->children.end()) {
                curr->children[ch] = new TrieNode();
            }
            curr = curr->children[ch]; 
            curr->words.push_back({relevance, inputWord}); 
        }
    }
public: 
    AutoComplete(vector<string> &dict) {
        root = new TrieNode(); 
        int relevance = 1; 
        for (auto &inputWord : dict) {
            addToTrie(inputWord, relevance);
            relevance++;
        }
    }
    ~AutoComplete() {
        // TODO: release all memory;
        // dfs
    }
    vector<string> complete(const string &prefix) {
        if (!root || prefix.empty())  {
            return vector<string>(); 
        }
        auto curr = root; 
        for (auto ch : prefix) {
            if (curr->children.find(ch) == curr->children.end()) {
                return vector<string>();
            }
            curr = curr->children[ch];
        }

        auto cmp = [&](auto lhs, auto rhs) {
            return lhs.first < rhs.first; 
        };
        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(cmp)> maxHeap(cmp); 
        for (auto & p : curr->words) {
            maxHeap.push(p); 
            if (maxHeap.size() > 5) {
                maxHeap.pop(); 
            }
        }
        
        vector<string> suggestions; 
        while (!maxHeap.empty()) {
            auto &p = maxHeap.top(); maxHeap.pop(); 
            auto str = p.second + " (" + to_string(p.first) + ")";
            suggestions.push_back(str);
        }
        reverse(begin(suggestions), end(suggestions)); 

        return suggestions; 
    }
};


int main(int argc, char** argv) {
    if (2 != argc) {
        cout << "wrong format" << endl; // TODO: make it better
        return 1;// an error
    }

    auto fileName = argv[1]; 

    ifstream inputFile(fileName); 
    vector<string> dict, prefixes; 
    int i = 0;
    int dictCount = 0, prefixCount = 0; 

    string line; 
    while (getline(inputFile, line)) {
        if (0 == i) {
            dictCount = stoi(line); 
        } else if (1 == i) {
            prefixCount = stoi(line); 
        } else if (2 <= i && i < 2 + dictCount) {
            dict.push_back(line);
        } else {
            prefixes.push_back(line); 
        }
        i++;
    }

    AutoComplete dictionary(dict); 
    for (auto &prefix : prefixes) {
        auto suggestions = dictionary.complete(prefix); 
        for (auto &line : suggestions) {
            cout << line << endl; 
        }
    }
    
}
