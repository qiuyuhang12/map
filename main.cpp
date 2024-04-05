//
// Created by qiuyuhang on 24-3-25.
//
#include <iostream>
#include <map>
#include "src/map.hpp"
using namespace std;
struct a{
    int _a;
    a(int a_){
        _a=a_;
    }
    bool operator<(const a& other)const{
        return _a<other._a;
    }
};
//struct
//using namespace sjtu;
int main(){
    sjtu::map<a,int>n;
    a aa(2);
//    n[aa]=2;
    sjtu::map<int ,int>m;
    for (int i = 0; i < 10; ++i) {
        m[i]=i;
    }
//    for (auto item:m) {
//        cout<<item.second;
//    }
//    auto item=m.begin();
//    for (int i = 0; i < 10; ++i) {
//        cout<<m[i];
//    }
//    std::map<int ,int >mm;
//    mm[1];
//    cout<<mm.size();

//    std::map<int ,int >m;
//    pair<int ,int > p(1,1);
//    pair<int ,int > p2(1,2);
//    std::map<int , a> mm;
////    cout<<mm.end()->first;
//    a* v= nullptr;
////    cout<<v->_a;
////    cout<<1009*1008;
//    m[1]=1;
//    m[1]=2;
//    m[1]=3;
//    m[2]=1000;
//    cout<<m.erase(1);
//    cout<<m.erase(1);
//    cout<<m.erase(2);
//    cout<<m[1];
////    cout<<m.count(1);
////    cout<<m[1];
////    m.insert(p);
////    m.insert(p2);
////    std::cout<<m[1];
    return 0;
}
