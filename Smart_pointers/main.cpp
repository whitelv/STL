#include "control.h"
#include "shared_ptr.h"
#include "weak_ptr.h"

int main()
{
    // std::shared_ptr<int> e = std::make_shared<int>(7);
    // std::weak_ptr<int> l = e;
    // std::weak_ptr<int> t = l;
    Shared_ptr<int> ptr = make_shared<int>(5);
    ptr.reset(new int{4});

    return 0;
}