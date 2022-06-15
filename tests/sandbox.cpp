#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



class sandbox : public apf::app {
public:
    void start() {
        apf::process p("./test.sh");
        std::this_thread::sleep_for(1s);
        std::cout << p.get() << std::endl;
        std::cout << "exit code: " << p.join() << std::endl;
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