#include "apf/all.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;



class sandbox : public apf::app {
public:
    void start() {
        apf::log::set_level(apf::log_level::error);
        auto start = std::chrono::system_clock::now();

        for (int i = 0; i < 10; i++) {
            apf::log::fatal("jrfdyhojkfgojhnflkjgnhlkdjfgnhljkdfnglkhjndflkgjhnldfknghlkdnfglkhndlfkgnhljdmfn vikbjnritgbiusrbfgiubvhdrfgiuhbirjfgbh");
            apf::log::error("jrfdyhojkfgojhnflkjgnhlkdjfgnhljkdfnglkhjndflkgjhnldfknghlkdnfglkhndlfkgnhljdmfn vikbjnritgbiusrbfgiubvhdrfgiuhbirjfgbh");
            apf::log::warn("jrfdyhojkfgojhnflkjgnhlkdjfgnhljkdfnglkhjndflkgjhnldfknghlkdnfglkhndlfkgnhljdmfn vikbjnritgbiusrbfgiubvhdrfgiuhbirjfgbh");
            apf::log::info("jrfdyhojkfgojhnflkjgnhlkdjfgnhljkdfnglkhjndflkgjhnldfknghlkdnfglkhndlfkgnhljdmfn vikbjnritgbiusrbfgiubvhdrfgiuhbirjfgbh");
            apf::log::note("jrfdyhojkfgojhnflkjgnhlkdjfgnhljkdfnglkhjndflkgjhnldfknghlkdnfglkhndlfkgnhljdmfn vikbjnritgbiusrbfgiubvhdrfgiuhbirjfgbh");
        }
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end - start;

        std::cout << "\n\nThis took " << diff.count() << "s\n";
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