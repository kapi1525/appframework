#include "appframework.hpp"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;


class sandbox : public app {
public:
    sandbox(::args args) {
        if(args.has("v") || args.has("version")) {
            std::cout << "sandbox " << sandbox_version << "\n";
            exit(0);
        }

        terminal::inverse();
        terminal::cursor::set_pos({10,3});
        std::cout << " ";
        terminal::cursor::set_pos({15,3});
        std::cout << " ";
        terminal::cursor::set_pos({8,5});
        std::cout << " ";
        terminal::cursor::set_pos({17,5});
        std::cout << " ";
        terminal::cursor::set_pos({9,6});
        std::cout << "        ";
        terminal::reset();
        std::cout << "\n\n";
        
        std::this_thread::sleep_for(0.5s);

        std::cout << files::user::desktop() << "\n\n";
        std::cout << files::user::documents() << "\n";
        std::cout << files::user::music() << "\n";
        std::cout << files::user::videos() << "\n";
        std::cout << files::user::photos() << "\n";
        std::cout << files::user::downloads() << "\n";

        std::cout << files::user::home() << "\n\n";
        std::cout << files::user::appdata("sandbox") << "\n\n";
        std::cout << "Sandbox " << sandbox_version << " build using appframework " << appframework_version << "\n\n";

        std::this_thread::sleep_for(0.5s);

        for (size_t i = 0; i < 4; i++) {
            log.loging_level = (logs::loglevel)i;
            std::cout << "loging_level == " << (int)log.loging_level << "\n\n";

            log.fatal("Fatal error looks like this.");
            std::cout << "\n";

            log.error("Error looks like this.");
            std::cout << "\n";

            log.warn("Warn looks like this.");
            std::cout << "\n";

            log.info("Info looks like this.");
            std::cout << "\n";
            std::cout << "\n";

            std::this_thread::sleep_for(0.5s);
        }
        

        // Test RGB
        for (uint8_t color = 0; color < 255; color++) {
            terminal::color({color, 0, 0});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal::color({color, color, 0});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal::color({0, color, color});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal::color({0, 0, color});
            std::cout << "█";
        }

        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        for (uint8_t color = 0; color < 255; color++) {
            terminal::color({color, 0, color});
            std::cout << "█";
        }
        
        std::cout << "\n";
        std::this_thread::sleep_for(0.5s);

        // Test difrent terminal modes

        terminal::reset();
        std::cout << "\ndeafult - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

        terminal::reset();
        terminal::bold();
        std::cout << "\nbold - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal::reset();
        terminal::faint();
        std::cout << "\nfaint - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal::reset();
        terminal::italic();
        std::cout << "\nitalic - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal::reset();
        terminal::underline();
        std::cout << "\nunderline - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

        terminal::reset();
        terminal::blinking();
        std::cout << "\nblinking - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal::reset();
        terminal::inverse();
        std::cout << "\ninverse - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal::reset();
        terminal::invisible();
        std::cout << "\ninvisible - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);


        terminal::reset();
        terminal::strikethrough();
        std::cout << "\nstrikethrough - The quick brown fox jumps over the lazy dog\n";
        std::this_thread::sleep_for(0.5s);

    }

    void run() {

    }

    ~sandbox() {
        std::cout << "\n";
    }


private:
    version sandbox_version = {1,2,3};
};



int main(int argc, char const *argv[]) {
    run_app(new sandbox(args(argc, argv)));
    return 0;
}
