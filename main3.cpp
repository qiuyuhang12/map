//
// Created by qiuyuhang on 24-4-10.
//
#include <iostream>
#include "src/map.hpp"
#include <map>
#include "src/my_sort.hpp"
#include <vector>

using namespace std;
struct a {
    struct my_itr {
    };
    my_itr myItr;
};

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
//    cout<<sjtu::is_my_itr<sjtu::map<int,int>::iterator>;
//    cout<<sjtu::is_my_itr<a>;
//    sjtu::map<int,int>::iterator::my_itr a;
//    a::my_itr b;
//    a c;
//    c.myItr;
    sjtu::my_sort(map1.begin(), map1.end()--);
//    sjtu::my_sort(map2.begin(),map2.end()--);
    sjtu::my_sort(vec.begin(), vec.end()--);
    int *a,*b;
    double * c,*d;
//    sjtu::my_sort(a,c);

//    cout<<sjtu::has_rand<sjtu::map<int,int >::iterator >;
//    cout<<sjtu::is_my_itr<sjtu::map<int,int >::iterator >;
//    cout<<sjtu::has_rand<vector<map<int,int> >::iterator >;
    return 0;
}
