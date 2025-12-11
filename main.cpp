#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>
#include <windows.h>

std::mutex mtx;
bool running = true;

void Test(bool &isRunning) {
    while (isRunning) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            std::lock_guard<std::mutex> l(mtx);
            isRunning = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int main() {
    std::thread t(Test, std::ref(running));

    while (running) {
        std::cout << "." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    t.join();
    std::cout << "Exited!" << std::endl;
    return 0;
}