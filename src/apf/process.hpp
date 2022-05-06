#pragma once
#include "common.hpp"
#include <cstdio>
#include <cstring>


#ifdef APF_POSIX
    #include <fcntl.h>
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

    /**
     * @brief Create and manage child processes.
     * @note Maybe thread safe?
     */
    class process {
    public:
        // Default constructor and destructor, they do nothing.
        process() = default;
        ~process() = default;

        // Constructors (Safe to call again after join() or terminate(), otherwise it can lead to some weird stuff)
        process(std::filesystem::path executable, std::vector<std::string> args);
        process(std::string command);

        // State
        bool running();
        bool finished();

        // Finish
        int join();         // Wait for a process to finish (To avoid endless waiting use interrupt or other function before)
        void kill();        // Kill a child                          (process)


        #ifdef APF_POSIX
            void send_signal(int sig);  // Send signal to process (only LINUX and other posix OS'es)
        #else
            void send_signal(int sig) = delete;  // posix and linux exclusive :)
        #endif

        // Process communication
        void send(std::string str);
        std::string get();

    private:
        int exit_code = 0;

        bool state_started = false;
        bool state_running = false;
        bool state_ended   = false;
        void update_state();            // Updates state booleans and exit_code.

        void process_start(std::filesystem::path executable, std::vector<std::string> args);


        #ifdef APF_WINDOWS
            HANDLE process_handle = NULL;
            HANDLE thread_handle = NULL;
            
            HANDLE output_pipe_handle = NULL;   // Child STDIN
            HANDLE input_pipe_handle = NULL;    // Child STDOUT
        #endif

        #ifdef APF_POSIX
            pid_t child_pid;
            int output_pipe_fd;                 // Child STDIN
            int input_pipe_fd;                  // Child STDOUT
        #endif
    };
}



/////////////////////////////////////////////////////
// Function definitions for Windows.
/////////////////////////////////////////////////////

#ifdef APF_WINDOWS

#define WERR std::stringstream ss; ss << __FUNCTION__ << "() inside: " << __FILE__ << ":" << __LINE__ << ". Something went wrong, error: " << GetLastError() << ".\n"; std::cerr << ss.str(); abort();
#define WTRY(x) if(x == FALSE) { WERR }


inline apf::process::process(std::filesystem::path executable, std::vector<std::string> args) {
    process_start(executable, args);
}

inline apf::process::process(std::string command) {
    process_start(command, {});
}


inline void apf::process::process_start(std::filesystem::path executable, std::vector<std::string> args) {
    state_started = false;
    state_running = false;
    state_ended   = false;

    SECURITY_ATTRIBUTES security_attributes;    // Required to allow child process to inherit pipe handles
    STARTUPINFOA startup_info;
    PROCESS_INFORMATION process_info;           // Holds process and thread handle

    // Pipe ends that will be inherited by child process
    HANDLE output_pipe_handle_rd;
    HANDLE input_pipe_handle_wr;


    // Init security_attributes
    std::memset(&security_attributes, 0, sizeof(security_attributes));
    security_attributes.nLength = sizeof(security_attributes);
    security_attributes.bInheritHandle = true;  // Allow child to inherit pipe handles. 
    security_attributes.lpSecurityDescriptor = NULL;


    // Create pipes for childs STDIN and STDOUT.
    WTRY(CreatePipe(&output_pipe_handle_rd, &output_pipe_handle, &security_attributes, 0))
    WTRY(CreatePipe(&input_pipe_handle, &input_pipe_handle_wr, &security_attributes, 0))

    // Ensure the right pipe ends are not inherited.
    WTRY(SetHandleInformation(output_pipe_handle, HANDLE_FLAG_INHERIT, 0))
    WTRY(SetHandleInformation(input_pipe_handle, HANDLE_FLAG_INHERIT, 0))


    // Setup startup_info
    std::memset(&startup_info, 0, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    startup_info.hStdError = input_pipe_handle_wr;
    startup_info.hStdOutput = input_pipe_handle_wr;
    startup_info.hStdInput = output_pipe_handle_rd;
    startup_info.dwFlags |= STARTF_USESTDHANDLES;


    // Setup process_info
    std::memset(&process_info, 0, sizeof(process_info));


    // Convert cmd + args to entire command.
    std::string cmd = "\"" + executable.string() + "\"";
    for (size_t i = 0; i < args.size(); i++) {
        cmd = cmd + " " + args[i].c_str();
    }

    WTRY(CreateProcessA(
        NULL,                       // No module name (use command line)
        (char*)cmd.c_str(),         // Command line
        NULL,                       // Process security attributes 
        NULL,                       // Primary thread security attributes 
        TRUE,                       // Handles are inherited 
        0,                          // Creation flags 
        NULL,                       // Use parent's environment 
        NULL,                       // Use parent's current directory 
        &startup_info,              // Pointer to STARTUPINFO structure
        &process_info               // Pointer to PROCESS_INFORMATION structure
    ))


    // Copy process handles
    process_handle = process_info.hProcess;
    thread_handle = process_info.hThread;


    // Close unused pipe ends.
    WTRY(CloseHandle(output_pipe_handle_rd));
    WTRY(CloseHandle(input_pipe_handle_wr));


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
        {
            DWORD ret = WaitForSingleObject(process_handle, INFINITE);

            if(ret == WAIT_OBJECT_0) {
                state_running = false;
                state_ended = true;
                
                DWORD a;
                WTRY(GetExitCodeProcess(process_handle, &a))
                exit_code = a;
            }

            else {
                WERR
            }
        }

        state_ended = true;
        state_running = false;

        WTRY(CloseHandle(process_handle));
        WTRY(CloseHandle(thread_handle));

        WTRY(CloseHandle(output_pipe_handle));
        WTRY(CloseHandle(input_pipe_handle));

        return exit_code;
    }
    if(!state_started) {
        std::cerr << "You cannot call " << __FUNCTION__ << " when process is not even started yet!\n";
        abort();
    }
    return exit_code;
}

inline void apf::process::kill() {
    update_state();
    if(!state_ended) {
        WTRY(TerminateProcess(process_handle, 0));
    }
    if(!state_started) {
        std::cerr << "You cannot call " << __FUNCTION__ << " when process is not even started yet!\n";
        abort();
    }
}



inline void apf::process::send(std::string str) {
    if(running()) {
        WTRY(WriteFile(output_pipe_handle, str.c_str(), (DWORD)str.size(), NULL, NULL));
    }
}

inline std::string apf::process::get() {
    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    std::string str;
    DWORD read;

    while (true) {
        if(ReadFile(input_pipe_handle, buffer, buffer_size, &read, NULL) == -1 || read == 0) {
            break;
        }
        str.append(buffer);
    }
        
    return str;
}



inline void apf::process::update_state() {
    if(state_ended || !state_started) {
        return;
    }
    

    {
        DWORD ret = WaitForSingleObject(process_handle, 0);

        if(ret == WAIT_TIMEOUT) {
            state_running = true;
            state_ended = false;
        }

        else if(ret == WAIT_OBJECT_0) {
            state_running = false;
            state_ended = true;
            
            DWORD a;
            WTRY(GetExitCodeProcess(process_handle, &a))
            exit_code = a;
        }

        else {
            WERR
        }
    }
}

#undef WERR
#undef WTRY

#endif





/////////////////////////////////////////////////////
// Function definitions for POSIX.
/////////////////////////////////////////////////////

#ifdef APF_POSIX

// Macro to automaticaly call perror() when posix functions fail
#define PTRY(x) if(x == -1) { std::stringstream ss; ss << __FUNCTION__ << "() inside: " << __FILE__ << ":" << __LINE__; perror(ss.str().c_str()); abort(); }



inline apf::process::process(std::filesystem::path executable, std::vector<std::string> args) {
    process_start(executable, args);
}

inline apf::process::process(std::string command) {
    process_start("/bin/sh", {"-c", command});
}


inline void apf::process::process_start(std::filesystem::path executable, std::vector<std::string> args) {
    state_started = false;
    state_running = false;
    state_ended   = false;

    int in_pipe[2];
    int out_pipe[2];

    // I honestly dont know how but randomly pipes started to magicaly work...
    // I hate pipes... never again.
    PTRY(pipe(in_pipe));
    PTRY(pipe(out_pipe));

    child_pid = fork();
    if(child_pid == 0) {
        PTRY(dup2(out_pipe[0], STDIN_FILENO));
        PTRY(dup2(in_pipe[1], STDOUT_FILENO));
        PTRY(dup2(in_pipe[1], STDERR_FILENO));

        PTRY(close(out_pipe[1]));
        PTRY(close(in_pipe[0]));

        // Child process
        PTRY(setpgid(0, 0));                      // Create new group id for child process

        #ifdef APF_LINUX
        PTRY(prctl(PR_SET_PDEATHSIG, SIGTERM));   // Terminate child if parent dies
        #endif

        // Convert std::vector to char array that can be passed to execv()
        const char** temp_argv = new const char*[args.size() + 2];
        temp_argv[0] = executable.c_str();

        for (size_t i = 1; i <= args.size(); i++) {
            temp_argv[i] = args[i-1].c_str();
        }

        temp_argv[args.size()+1] = NULL;

        // Execute
        PTRY(execv(executable.c_str(), (char *const *)temp_argv));
    }

    PTRY(close(out_pipe[0]));
    PTRY(close(in_pipe[1]));

    output_pipe_fd = out_pipe[1];
    input_pipe_fd = in_pipe[0];

    PTRY(fcntl(output_pipe_fd, F_SETFL, O_NONBLOCK));
    PTRY(fcntl(input_pipe_fd, F_SETFL, O_NONBLOCK));

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
        PTRY(waitpid(child_pid, &exit_code, WCONTINUED));
        PTRY(close(output_pipe_fd));
        PTRY(close(input_pipe_fd));
        state_ended = true;
        state_running = false;
        return exit_code;
    }
    if(!state_started) {
        std::cerr << "You cannot call " << __FUNCTION__ << " when process is not even started yet!\n";
        abort();
    }
    return exit_code;
}

inline void apf::process::kill() {
    update_state();
    if(!state_ended) {
        PTRY(killpg(child_pid, SIGKILL));
    }
    if(!state_started) {
        std::cerr << "You cannot call " << __FUNCTION__ << " when process is not even started yet!\n";
        abort();
    }
}



inline void apf::process::send(std::string str) {
    if(running()) {
        PTRY(write(output_pipe_fd, str.c_str(), str.size()));
    }
}

inline std::string apf::process::get() {
    const size_t buffer_size = 1000000;     // FIXME: Dont create ~1MB buffer for read(), btw 10MB buffer segfaults lol.
    char buffer[buffer_size];
    std::string str;


    while (true) {
        memset(buffer, 0, buffer_size);
        int result = read(input_pipe_fd, buffer, buffer_size);

        if (result == -1 && errno != EAGAIN) {
            PTRY(-1);
        }

        if (result == 0) {
            break;
        }

        str.append(buffer);
    }

    return str;
}



inline void apf::process::send_signal(int sig) {
    update_state();
    if(!state_ended) {
        PTRY(killpg(child_pid, sig));
    }
    if(!state_started) {
        std::cerr << "You cannot call " << __FUNCTION__ << " when process is not even started yet!\n";
        abort();
    }
}



inline void apf::process::update_state() {
    if(state_ended || !state_started) {
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
    if(result == -1) {
        perror("waitpid() failed");
        abort();
    }
}

#undef PTRY

#endif