#include "appframework.hpp"
#include "apf/args.hpp"
#include "apf/term.hpp"
#include "apf/logs.hpp"
#include "apf/tree.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;




class sandbox : public apf::app {
public:
    void start() {
        tree.push_back(123);
        tree.push_back(456);
        tree.push_back(789);
        tree[2].push_back(1);
        tree[2][0].push_back(2);
        std::cout << tree.size() << "\n";
        std::cout << tree[0] << "\n";
        std::cout << tree[1].get() << "\n";
        std::cout << tree[2].get() << "\n";
        std::cout << tree[2][0].get() << "\n";
        std::cout << tree[2][0][0].get() << "\n";
    }

    void run() {

    }

    void end() {
        apf::term::reset();
        std::cout << "\n";
    }


private:
    apf::tree<int> tree;

    version sandbox_version = {1,2,3};
};



APF_MAIN(sandbox)