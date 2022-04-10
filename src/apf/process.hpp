#include "common.hpp"


#ifdef APF_POSIX
    #include <unistd.h>
    #include <signal.h>
    #include <sys/wait.h>
#endif

#ifdef APF_LINUX
    #include <sys/prctl.h>
#endif



/////////////////////////////////////////////////////
// Class declaration.
/////////////////////////////////////////////////////

namespace apf {

    class process {
    public:
        // Default constructor and destructor
        process();
        ~process();

        // Constructors (Safe to call again after join() or terminate(), otherwise it can lead to some weird stuff)
        process(std::filesystem::path executable, std::vector<std::string> args);
        process(std::string command);

        // State
        bool running();
        bool finished();

        // Finish
        int join();
        void terminate();

        // Process communication
        void send(std::string str);
        std::string get();

    private:
        int exit_code = 0;

        bool state_started = false;
        bool state_running = false;
        bool state_ended   = false;
        void update_state();

        #ifdef APF_POSIX
            pid_t child_pid;
            //int output_pipe_fd, input_pipe_fd;
            void process_start(std::filesystem::path executable, std::vector<std::string> args);
        #endif
    };
}



/////////////////////////////////////////////////////
// Global function definitions.
/////////////////////////////////////////////////////

inline apf::process::process() {

}

inline apf::process::~process() {

}



/////////////////////////////////////////////////////
// Function definitions for POSIX.
/////////////////////////////////////////////////////

#ifdef APF_POSIX

inline apf::process::process(std::filesystem::path executable, std::vector<std::string> args) {
    process_start(executable, args);
}

inline apf::process::process(std::string command) {
    process_start(command, {command});
}


inline void apf::process::process_start(std::filesystem::path executable, std::vector<std::string> args) {
    state_started = false;
    state_running = false;
    state_ended   = false;

    child_pid = fork();
    if(child_pid == 0) {
        // Child process
        setpgid(0, 0);                      // Create new group id for child process

        #ifdef APF_LINUX
        prctl(PR_SET_PDEATHSIG, SIGTERM);   // Terminate child if parent dies
        #endif

        // Convert std::vector to char array that can be passed to execv()
        const char** temp_argv = new const char*[args.size() + 2];
        temp_argv[0] = executable.c_str();

        for (size_t i = 1; i <= args.size(); i++) {
            temp_argv[i] = args[i-1].c_str();
        }

        temp_argv[args.size()+1] = NULL;

        // Execute
        execvp(executable.c_str(), (char *const *)temp_argv);
        perror("execvp() failed");
        exit(-1);
    }

    state_started = true;
    update_state();
}



inline bool apf::process::running() {
    update_state();
    return state_running;
}

inline bool apf::process::finished() {
    update_state();
    return state_ended;
}



inline int apf::process::join() {
    update_state();
    if(!state_ended) {
        killpg(child_pid, SIGINT);
        waitpid(child_pid, &exit_code, WCONTINUED);
        return exit_code;
    }
    if(!state_started) {
        std::cerr << "You cannot call join() or terminate() when process is not even started yet!\n";
        abort();
    }
    return exit_code;
}

inline void apf::process::terminate() {
    update_state();
    if(!state_ended) {
        killpg(child_pid, SIGTERM);
        waitpid(child_pid, &exit_code, WCONTINUED);
    }
    if(!state_started) {
        std::cerr << "You cannot call join() or terminate() when process is not even started yet!\n";
        abort();
    }
}



void apf::process::send(std::string str) {
    
}

std::string apf::process::get() {
    return "";
}



inline void apf::process::update_state() {
    if(state_ended) {
        return;
    }

    int result = waitpid(child_pid, &exit_code, WCONTINUED || WNOHANG);

    if(result == child_pid) {
        state_running = false;
        state_ended = true;
    } 
    if(result == 0) {
        state_running = true;
        state_ended = false;
    }
}

#endif