#include "control.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include "unique_ptr.h"

#include <memory>


int main(){
    // std::shared_ptr<int> e = std::make_shared<int>(7);
    // std::weak_ptr<int> l = e;
    // std::weak_ptr<int> t = l;


    Shared_ptr<int> a = make_shared<int>(8);
    Shared_ptr<int> b = make_shared<int>(10);
    Weak_ptr<int> w = a;
    Weak_ptr<int> w3 = a;
    Weak_ptr<int> w1;
    w1 = b;
    w1.swap(w);
    a.reset();
    std::cout << w1.expired() << std::endl;
    Shared_ptr<int> c = w1.lock();
    
    return 0;
}