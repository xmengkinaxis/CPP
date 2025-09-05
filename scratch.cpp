#include <memory> 
#include <vector>
#include <algorithm>
#include <iostream> 
#include <mutex>

using namespace std; 

struct Node {
    int value; 
    unique_ptr<Node> left; 
    unique_ptr<Node> right; 

    Node(int v) : value(v) {}
};

mutex mut; 

struct Foo {
    Foo() { cout << "Foo Created\n"; }
    ~Foo() { cout << "Food Destroyed\n"; }
};

int main()
{
    lock_guard<mutex> lock(mut);

    unique_ptr<Foo> f1 = make_unique<Foo>(); 
    shared_ptr<Foo> f2 = make_shared<Foo>(); 
    
    vector<int> v = {5, 3, 8, 1}; 
    sort(v.begin(), v.end()); 
    for (auto n: v) cout << n << " ";

    auto root = make_unique<Node>(0);
    root->left = make_unique<Node>(1); 
    root->right = make_unique<Node>(2)
;
    return 0; 
}