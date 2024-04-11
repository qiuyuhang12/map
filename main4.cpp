
#include <iostream>
#include "src/map.hpp"
#include <map>
#include "src/my_print.hpp"
#include <vector>

using namespace std;
int main() {
    cout << boolalpha;
    sjtu::map<int, int> map1;
    map<int, int> map2;
    vector<int> vec;
    for (int i = 0; i < 5; i++) {
        map1[i] = i;
        map2[i] = i;
        vec.push_back(i);
    }
//    sample();
    int a[5]={1,2,3,4,5};
    cout<<boolalpha;
    cout<<sjtu::is_container<map<int,int> >;
//    sjtu::print(map2);
//    auto b=std::begin(map1);
//    int *e=std::end(a)-1;

//    cout<<*e;
    return 0;
}
