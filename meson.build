project('sandbox', 'c', 'cpp',
  version: '1.0.0',
  default_options: ['warning_level=3', 'c_std=c17', 'cpp_std=c++17'],
  license: 'MIT')

appframework_files = files('src/appframework.cpp')
appframework_includes = include_directories('src')

libappframework = shared_library('appframework', appframework_files, dependencies: dependency('threads'))

appframework_dep = declare_dependency(include_directories: appframework_includes, link_with: libappframework)

# build sandbox if not subproject
if not meson.is_subproject()
  sandbox_files = files('src/sandbox.cpp')
  sandbox_includes = include_directories('src')

  sandbox_exe = executable('sandbox', sandbox_files, include_directories: sandbox_includes, dependencies: [appframework_dep, dependency('threads')])
endif