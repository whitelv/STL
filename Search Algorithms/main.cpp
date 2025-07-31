#include <iostream>
#include <vector>
#include <forward_list>
#include "find.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <string>
#include <iterator>
#include <algorithm>


int main()
{

    std::vector<int> v{1,1,1,1,1,1,1,1,1,1,1,2,2,4,5,6,3,4,4,4,5,7,7,7,7,7};
    std::vector<int> v1{};
    auto p =  findLongestStreak(v.begin(), v.end());
    return 0;
}