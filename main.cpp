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
        int tmp = int(rand()) % int(17117);
        mii.insert(sjtu::pair<int, int>(i, tmp));
        co[i] = tmp;
        mii.check();
        assert(same(co, mii));
    }
    for (int i = 0; i < n; ++i) {
        if ((i & -i) > (1 << 7))
            cout << 1 << ' ' << i << endl;
        int tmp = rand() % int(9721);
        mii.erase(tmp);
        mii.check();
        co.erase(tmp);
        assert(same(co, mii));
    }
}

void cccchhhheeeecccckkkk2() {
    sjtu::map<int, int> mii;
    map<int, int> co;
    for (int n = 0; n < 1000; ++n) {
        cout << n;
        for (int i = 0; i < n; ++i) {
            int tmp = i;
            mii.insert(sjtu::pair<int, int>(i, tmp));
            co[i] = tmp;
            mii.check();
            assert(same(co, mii));
        }
        for (int i = 0; i < n; ++i) {
            if ((i & -i) > (1 << 7))
                cout << 1 << ' ' << i << endl;
            int tmp = i;
            mii.erase(tmp);
            mii.check();
            co.erase(tmp);
            assert(same(co, mii));
        }
    }
}

void cccchhhheeeecccckkkk3() {
    sjtu::map<int, int> mii;
    map<int, int> co;
    int n = 5e3;
    for (int i = 0; i < n; ++i) {
        int tmp = int(rand()) % int(17117);
        mii.insert(sjtu::pair<int, int>(i, tmp));
        co[i] = tmp;
        mii.check();
        assert(same(co, mii));
    }
    for (int i = 0; i < n; ++i) {
        if ((i & -i) > (1 << 7))
            cout << 1 << ' ' << i << endl;
        int tmp = rand() % int(9721);
        mii.erase(tmp);
        mii.check();
        co.erase(tmp);
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
        sjtu::map<int, int> copy(mii);
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
    return 0;
}