project('appframework', 'cpp',
  version: '0.3.0',
  default_options: ['warning_level=3', 'cpp_std=c++17'],
  license: 'MIT')

appframework_files = files()
appframework_includes = include_directories('src')
appframework_depends = [dependency('threads')]

# libappframework = static_library('appframework', appframework_files, include_directories: appframework_includes, dependencies: appframework_depends)

# appframework_dep = declare_dependency(include_directories: appframework_includes, link_with: libappframework)
appframework_dep = declare_dependency(include_directories: appframework_includes)

# build sandbox if not subproject
if not meson.is_subproject()
  test_depends = [appframework_dep, dependency('threads')]

  sandbox_exe = executable('sandbox', files('tests/sandbox.cpp'), dependencies: test_depends)

  test_args_exe = executable('test_args', files('tests/test_args.cpp'), dependencies: test_depends)

  test('args', test_args_exe, args: ['-posix', '-a', 'argument', '-b', 'very long option', '--long-option', '--long-option-with-arg=argument', '/windows', '/windows-with-arg:argument'])
endif