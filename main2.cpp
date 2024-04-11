#include <iostream>
#include "src/map.hpp"
#include <map>
#include <mutex>
#include <thread>
#include <unistd.h>
std::mutex m1;
std::mutex m2;

void f(char a, int s) {
    std::lock_guard<std::mutex> lock2(m2);
//    sleep(5); // sleep for 5 second
//    std::lock_guard<std::mutex> lock1(m1);
    std::cout << a << s << std::endl;
}
void f2(char a, int s) {
    std::cout << "f2" << std::endl;
    std::lock_guard<std::mutex> lock1(m1);
    std::lock_guard<std::mutex> lock2(m2);
    std::cout << a << s << std::endl;
}

int main() {
    std::lock_guard<std::mutex> lock1(m1);
    std::thread t1(f, 'a', 1);
    std::thread t2(f2, 'b', 2);
    std::cout << "Hello, World!" << std::endl;
    lock1.~lock_guard();
    t1.join();
    t2.join();
    return 0;
}
