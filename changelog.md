## Changes since last release:
- Removed cross_linux_to_windows.ini cross file

## v0.4.0 Changelog:
- Added apf::process class, as name suggests it abstracts from you creating and controlling child processes using pipes.
- Added apf/all.hpp header, it includes every apf header.
- apf/logs.hpp refactor, apf::log is now a singleton.
- Added apf::log::set_level() and get_level() these functions can be used to set logging level globally if you want less garbage in your logs.
- Optimized apf::log it now uses std::printf and std::string_view. (this and optimization bellow give me ~3x performance boost when logging random stuff to console)
- Optimized apf::term::color() and back_color() it now uses std::printf.
- apf::app::run() now returns int, its now a "game loop" it will be ran infinitely until you return 1.