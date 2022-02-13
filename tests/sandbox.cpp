#include "appframework.hpp"
#include "apf/args.hpp"
#include "apf/term.hpp"
#include "apf/logs.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


class sandbox : public apf::app {
public:
    sandbox(apf::args args) {
        if(args.has("v") || args.has("version")) {
            std::cout << "sandbox " << sandbox_version << "\n";
            exit(0);
        }

        apf::term::erase();

        apf::term::inverse();
        apf::term::cursor::set_pos({10,3});
        std::cout << " ";
        apf::term::cursor::set_pos({15,3});
        std::cout << " ";
        apf::term::cursor::set_pos({8,5});
        std::cout << " ";
        apf::term::cursor::set_pos({17,5});
        std::cout << " ";
        apf::term::cursor::set_pos({9,6});
        std::cout << "        ";
        apf::term::reset();
        std::cout << "\n\n";
        
        std::this_thread::sleep_for(0.5s);

        std::cout << "Sandbox " << sandbox_version << " build using appframework " << appframework_version << "\n\n";

        std::this_thread::sleep_for(0.5s);


        apf::log::fatal("Fatal error looks like this.");
        std::cout << "\n";

        apf::log::error("Error looks like this.");
        std::cout << "\n";

        apf::log::warn("Warn looks like this.");
        std::cout << "\n";

        apf::log::info("Info looks like this.");
        std::cout << "\n";
        std::cout << "\n";
        
        std::this_thread::sleep_for(0.5s);

        // Test RGB
        for (uint8_t color = 0; color < 255; color++) {
            apf::term::color({color, 0, 0});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            apf::term::color({color, color, 0});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            apf::term::color({0, color, color});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            apf::term::color({0, 0, color});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            apf::term::color({color, 0, color});
            std::cout << "█";
        }
        
        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        // Test difrent apf::term modes

        apf::term::reset();
        std::cout << "\ndeafult - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

        apf::term::reset();
        apf::term::bold();
        std::cout << "\nbold - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        apf::term::reset();
        apf::term::faint();
        std::cout << "\nfaint - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        apf::term::reset();
        apf::term::italic();
        std::cout << "\nitalic - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        apf::term::reset();
        apf::term::underline();
        std::cout << "\nunderline - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

        apf::term::reset();
        apf::term::blinking();
        std::cout << "\nblinking - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        apf::term::reset();
        apf::term::inverse();
        std::cout << "\ninverse - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        apf::term::reset();
        apf::term::invisible();
        std::cout << "\ninvisible - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        apf::term::reset();
        apf::term::strikethrough();
        std::cout << "\nstrikethrough - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

    }

    void run() {

    }

    ~sandbox() {
        apf::term::reset();
        std::cout << "\n";
    }


private:
    version sandbox_version = {1,2,3};
};



int main(int argc, char const *argv[]) {
    apf::run_app(new sandbox(apf::args(argc, argv)));
    return 0;
}
