#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



void create_join_process() {
    std::filesystem::current_path("test");
    apf::process p("./start.sh");
    std::this_thread::sleep_for(10s);
    std::cout << p.running() << std::endl;
    p.interrupt();
    std::cout << p.get() << std::endl;
    std::cout << p.join() << std::endl;
}



class sandbox : public apf::app {
public:
    void start() {
        std::thread t(&create_join_process);
        t.join();
    }

    int run() {
        return 1;
    }

    void end() {
        apf::term::reset();
        std::cout << "\n";
    }


private:
    version sandbox_version = {1,2,3};
};



APF_MAIN(sandbox)