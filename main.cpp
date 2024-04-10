//
// Created by qiuyuhang on 24-3-25.
//
#include <iostream>
#include "src/map.hpp"
#include <map>

using namespace std;

template<typename t1, typename t2>
bool same(map<t1, t2> &m1, sjtu::map<t1, t2> &m2) {
    if (m1.size() != m2.size()) {
        cerr << "size! m1:" << m1.size() << "m2:" << m2.size() << endl;
        return false;
    }
    for (auto i: m2) {
        if (m1.count(i.first) == 0 || m1[i.first] != i.second) {
            cerr << "node! count:" << m2.count(i.first) << endl;
            return false;
        }
    }
    return true;
}

void cccchhhheeeecccckkkk() {
    sjtu::map<int, int> mii;
    map<int, int> co;
//    1e3 1e2 3e1 25 2e1
//rand()%2 ct 2e3 2e2 3e1 25
    int n = 5e3;
// n=5e3,17117,9721 vvvvv
    for (int i = 0; i < n; ++i) {
//        if ((i&-i)>(1<<7))
//            cout<<0<<i<<endl;
        int tmp = int(rand()) % int(17117);
//        if (rand() % 7)continue;
//        mii[i] = tmp;
        mii.insert(sjtu::pair<int, int>(i, tmp));
//        else mii[i]=i;
        co[i] = tmp;
        mii.check();
        assert(same(co, mii));
    }
    for (int i = 0; i < n; ++i) {
        if ((i & -i) > (1 << 7))
            cout << 1 << ' ' << i << endl;
        int tmp = rand() % int(9721);
//        cout<<tmp<<endl;
//        if (rand() == 0)continue;
//        cout << i << endl;
//        mii.print();

        mii.erase(tmp);
//        cout<<"after er:"<<endl;
//        mii.print();
        mii.check();
//        cout<<1e4<<endl;
        co.erase(tmp);
//        co[i]=i;
        assert(same(co, mii));
    }
}

void cccchhhheeeecccckkkk2() {
    sjtu::map<int, int> mii;
    map<int, int> co;
//    1e3 1e2 3e1 25 2e1
//rand()%2 ct 2e3 2e2 3e1 25
    for (int n = 0; n < 1000; ++n) {
        cout << n;

// n=5e3,17117,9721
        for (int i = 0; i < n; ++i) {
//        if ((i&-i)>(1<<7))
//            cout<<0<<i<<endl;
            int tmp = i;
//        if (rand() % 7)continue;
//        mii[i] = tmp;
            mii.insert(sjtu::pair<int, int>(i, tmp));
//        else mii[i]=i;
            co[i] = tmp;
            mii.check();
            assert(same(co, mii));
        }
        for (int i = 0; i < n; ++i) {
            if ((i & -i) > (1 << 7))
                cout << 1 << ' ' << i << endl;
            int tmp = i;
//        cout<<tmp<<endl;
//        if (rand() == 0)continue;
//        cout << i << endl;
//        mii.print();

            mii.erase(tmp);
//        cout<<"after er:"<<endl;
//        mii.print();
            mii.check();
//        cout<<1e4<<endl;
            co.erase(tmp);
//        co[i]=i;
            assert(same(co, mii));
        }
    }
}

void cccchhhheeeecccckkkk3() {
    sjtu::map<int, int> mii;
    map<int, int> co;
//    1e3 1e2 3e1 25 2e1
//rand()%2 ct 2e3 2e2 3e1 25
    int n = 5e3;
// n=5e3,17117,9721 vvvvv
    for (int i = 0; i < n; ++i) {
//        if ((i&-i)>(1<<7))
//            cout<<0<<i<<endl;
        int tmp = int(rand()) % int(17117);
//        if (rand() % 7)continue;
//        mii[i] = tmp;
        mii.insert(sjtu::pair<int, int>(i, tmp));
//        else mii[i]=i;
        co[i] = tmp;
        mii.check();
        assert(same(co, mii));
    }
    for (int i = 0; i < n; ++i) {
        if ((i & -i) > (1 << 7))
            cout << 1 << ' ' << i << endl;
        int tmp = rand() % int(9721);
//        cout<<tmp<<endl;
//        if (rand() == 0)continue;
//        cout << i << endl;
//        mii.print();

        mii.erase(tmp);
//        cout<<"after er:"<<endl;
//        mii.print();
        mii.check();
//        cout<<1e4<<endl;
        co.erase(tmp);
//        co[i]=i;
        assert(same(co, mii));
    }
}

void test() {
    char type;
    sjtu::map<int, int> mii;
    map<int, int> co;
    while (cin >> type) {
        int key;
        cin >> key;
        if (type == 'i') {
            mii[key] = key;
            mii.check();
            co[key] = key;
            assert(same(co, mii));
        } else {
            mii.erase(key);
            mii.check();
            co.erase(key);
            assert(same(co, mii));
        }
    }
}

void test2() {
    sjtu::map<int, int> mii;
    for (int i = 0; i < 1e5; ++i) {
        mii[i] = i;
    }
    for (int i = 0; i < 1e5; ++i) {
        if (i > 1896 && i <= 2016) {
            continue;
        }
        mii.erase(mii.find(i));
    }
    for (int i = 0; i < 1; ++i) {
		sjtu::map<int,int> copy(mii);
		mii.clear();
		std::cout << mii.size() << " " << copy.size() << " ";
		mii = copy;
		copy.clear();
		std::cout << mii.size() << " " << copy.size() << " ";
		copy = mii;
		mii.clear();
		std::cout << mii.size() << " " << copy.size() << " ";
		mii = copy;
		copy.clear();
		std::cout << mii.size() << " " << copy.size() << " ";
	}
    while (mii.begin() != mii.end()) {
        mii.erase(mii.begin());
    }
}

int main() {
    test2();
//    cccchhhheeeecccckkkk();
    return 0;
}
//    pii(1,2);
//        correct.erase(i);
//        cout<<"check..."<<endl;
//        m.check();
//        check(m,correct);
//        m.print();
//        cout<<endl;
//    }
//    cout << endl;
//    m.print();
//    cout << endl;
//    m.erase(m.find(9));
//    srand(time(0));

//    for (int i = 0; i < 100000; ++i) {
//        if (i > 1896 && i <= 2016) {
//            continue;
//        }
////        std::cout<<map.count(Integer(i));
//        assert(map.count(Integer(i)) == 1);
//        assert(map.find(Integer(i)) != map.end());
//        map.erase(map.find(Integer(i)));
//    }
//    for (int i = 0; i < 100000; ++i) {
//        if (i > 1896 && i <= 2016) {
//            continue;
//        }
//        cout << i << endl;
////        m.pt(m.find(2019));
////        cout<<"ssss"<<endl;
////        m.pt(m.find(i));
////        cout<<endl;
////        assert(m.count(i)==1);
//        m.erase(m.find(i));
////        m.print();
////        cout<<endl;
//    }
//    m.erase(m.find(199));
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

////Stack-overflow on address 0x7ffec0c23fd8 (pc 0x6020c7bb9497 bp 0x7ffec0c24020 sp 0x7ffec0c23fc0 T0)

// i 100
//
// i 50
// i 103
//
// i 25
// i 75
// i 101
// i 105
//
// i 80
// i 102
// i 104
// i 106
//
// i 107

// d 50
