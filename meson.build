project('appframework', 'c', 'cpp',
  version: '0.2.0',
  default_options: ['warning_level=3', 'c_std=c17', 'cpp_std=c++17'],
  license: 'MIT')

appframework_files = files('src/appframework.cpp', 'src/appframework/terminal.cpp', 'src/appframework/files.cpp', 'src/appframework/ini.cpp')
appframework_includes = include_directories('src', 'src/appframework')
appframework_depends = [dependency('threads')]

libappframework = static_library('appframework', appframework_files, include_directories: appframework_includes, dependencies: appframework_depends)

appframework_dep = declare_dependency(include_directories: appframework_includes, link_with: libappframework)

# build sandbox if not subproject
if not meson.is_subproject()
  sandbox_files = files('src/sandbox.cpp')
  sandbox_includes = include_directories('src')

  sandbox_exe = executable('sandbox', sandbox_files, include_directories: sandbox_includes, dependencies: [appframework_dep, dependency('threads')])
endif