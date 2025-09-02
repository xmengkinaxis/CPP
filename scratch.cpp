#include <memory> 
#include <vector>
#include <algorithm>
#include <iostream> 
#include <mutex>

using namespace std; 

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
    return 0; 
}