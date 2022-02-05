#include "appframework.hpp"


app::app() {
    #ifdef _WIN32
    // Configure windows terminal to handle ANSI escape sequences
    // I put it here cause i dont hava a better place for it since removal of terminal class.

    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    assert(hOut != INVALID_HANDLE_VALUE);
    assert(hIn != INVALID_HANDLE_VALUE);

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    assert(GetConsoleMode(hOut, &dwOriginalOutMode));
    assert(GetConsoleMode(hIn, &dwOriginalInMode));

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    // DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    DWORD dwInMode = dwOriginalInMode | ENABLE_VIRTUAL_TERMINAL_INPUT;

    if (!SetConsoleMode(hOut, dwOutMode)) {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if(!SetConsoleMode(hOut, dwOutMode)) {
            std::cerr << "Failed to set console mode, without it colors and other fancy terminal stuff wont be available.\n";
        }
    }

    if(!SetConsoleMode(hIn, dwInMode)) {
        std::cerr << "Failed to set console mode, without it colors and other fancy terminal stuff wont be available.\n";
    }
    #endif // _WIN32
    terminal::reset();
}

app::app(::args args) {
    if(args.has("v")) {
        std::cout << "appframework " << appframework_version << "\nIdk why but you compiled default app class isntead of actualy using it.\n";
    }
}

app::~app() {
    // Reset terminal to default settings
    terminal::reset();
}

void app::exit(int status) {
    delete this;        // Delete app to call destructor on everything
    ::exit(status);     // Exit
}



void run_app(app* app_ptr) {
    app_ptr->run();
    delete app_ptr;
}