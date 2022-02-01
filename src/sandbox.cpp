#include "appframework.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


class sandbox : public app {
public:
    sandbox(args_t args_f) {
        args = args_f; // save args so they can be used by get_arg() and find_arg()
        std::cout << get_executable_name() << "\n\n";
        std::cout << get_executable_path() << "\n\n";
        std::cout << "Sandbox " << sandbox_version << " build using appframework " << appframework_version << "\n\n";

        for (size_t i = 0; i < 4; i++) {
            terminal.logging_level = (terminal::loglevel)i;
            std::cout << "logging_level == " << (int)terminal.logging_level << "\n\n";

            terminal.fatal("Fatal error looks like this.");
            std::cout << "\n";

            terminal.error("Error looks like this.");
            std::cout << "\n";

            terminal.warn("Warn looks like this.");
            std::cout << "\n";

            terminal.info("Info looks like this.");
            std::cout << "\n";
            std::cout << "\n";

            std::this_thread::sleep_for(0.5s);
        }
        

        // Test RGB
        for (uint8_t color = 0; color < 255; color++) {
            terminal.set_color({color, 0, 0});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal.set_color({color, color, 0});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal.set_color({0, color, color});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal.set_color({0, 0, color});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal.set_color({color, 0, color});
            std::cout << "█";
        }
        
        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        // Test difrent terminal modes

        terminal.reset();
        std::cout << "\ndeafult - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

        terminal.reset();
        terminal.set_bold();
        std::cout << "\nbold - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal.reset();
        terminal.set_faint();
        std::cout << "\nfaint - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal.reset();
        terminal.set_italic();
        std::cout << "\nitalic - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal.reset();
        terminal.set_underline();
        std::cout << "\nunderline - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

        terminal.reset();
        terminal.set_blinking();
        std::cout << "\nblinking - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal.reset();
        terminal.set_inverse();
        std::cout << "\ninverse - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal.reset();
        terminal.set_invisible();
        std::cout << "\ninvisible - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal.reset();
        terminal.set_strikethrough();
        std::cout << "\nstrikethrough - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

    }

    void run() {

    }

    ~sandbox() {
        std::cout << "\n";
    }


private:
    version sandbox_version = {1,0,0};
};



int main(int argc, char const *argv[]) {
    app* app = new sandbox(create_args(argc, argv));
    app->run();
    delete app;
    return 0;
}
