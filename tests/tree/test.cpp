#include "appframework.hpp"
#include "apf/logs.hpp"
#include "apf/tree.hpp"
#include <cassert>


class test : public apf::app {
public:
    void start() {
        tree.push_back(123);
        assert(tree.size() == 1 && tree[0] == 123 && tree[0].get() == 123 && tree.at(0) == 123 && tree.at(0).get() == 123);
        tree.clear();
        assert(tree.size() == 0);
        tree.set(675);
        assert(tree == 675 && tree.get() == 675);
    }

    void run() {
    }

    void end() {
    }

private:
    apf::tree<int> tree;
};



APF_TEST_MAIN(test)