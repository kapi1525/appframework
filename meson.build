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
  test_depends = [appframework_dep, dependency('threads')]

  sandbox_exe = executable('sandbox', files('tests/sandbox.cpp'), dependencies: test_depends)

  test_args_exe = executable('test_args', files('tests/test_args.cpp'), dependencies: test_depends)
  test_ini_exe = executable('test_ini', files('tests/test_ini.cpp'), dependencies: test_depends)

  test('args', test_args_exe, args: ['-posix', '-a', 'argument', '-b', 'very long option', '--long-option', '--long-option-with-arg=argument', '/windows', '/windows-with-arg:argument'])
  test('ini', test_ini_exe)
endif