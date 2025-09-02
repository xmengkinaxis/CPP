#include <memory> 
#include <vector>
#include <algorithm>
#include <iostream> 

using namespace std; 

struct Foo {
    Foo() { cout << "Foo Created\n"; }
    ~Foo() { cout << "Food Destroyed\n"; }
};

int main()
{
    unique_ptr<Foo> f1 = make_unique<Foo>(); 
    shared_ptr<Foo> f2 = make_shared<Foo>(); 
    
    vector<int> v = {5, 3, 8, 1}; 
    sort(v.begin(), v.end()); 
    for (auto n: v) cout << n << " ";
    return 0; 
}