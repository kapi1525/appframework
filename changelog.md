## Changes since last release:
- None


## v0.4.1 Changelog:
- Removed cross_linux_to_windows.ini cross file.
- vec2_t, vec3_t, vec4_t have now new optional template argument modyfing type, by default its float.
- i_vec2_t, i_vec3_t, i_vec4_t is now vector<int>
- u_vec2_t, u_vec3_t, u_vec4_t is now vector<unsigned int>
- Added new vectors:
  - f_vec2_t
  - f_vec3_t
  - f_vec4_t
  - im_vec2_t
  - im_vec3_t
  - im_vec4_t
  - iz_vec2_t
  - iz_vec3_t
  - iz_vec4_t
  - um_vec2_t
  - um_vec3_t
  - um_vec4_t
  - uz_vec2_t
  - uz_vec3_t
  - uz_vec4_t
- Fixed: Dot was always added at the end of log messages, now its only added when dot is missing.


## v0.4.0 Changelog:
- Added apf::process class, as name suggests it abstracts from you creating and controlling child processes using pipes.
- Added apf/all.hpp header, it includes every apf header.
- apf/logs.hpp refactor, apf::log is now a singleton.
- Added apf::log::set_level() and get_level() these functions can be used to set logging level globally if you want less garbage in your logs.
- Optimized apf::log it now uses std::printf and std::string_view. (this and optimization bellow give me ~3x performance boost when logging random stuff to console)
- Optimized apf::term::color() and back_color() it now uses std::printf.
- apf::app::run() now returns int, its now a "game loop" it will be ran infinitely until you return 1.