Changes since last release:
- Added apf::process class wich allows for easy starting and controlling child processes.
- apf::app::run() is now "game" loop, it will run infinetly until you return 1.
- Added apf/all.hpp, it includes every apf header.
- Refactored apf/logs.hpp, apf::log is now a singleton class with support for logging levels and more controll over custom logging.