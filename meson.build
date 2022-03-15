project('appframework', 'cpp',
  version: '0.3.0',
  default_options: ['warning_level=3', 'cpp_std=c++17'],
  license: 'MIT')

apf_files     = files()
apf_includes  = include_directories('src')
apf_deps      = [dependency('threads')]

apf_dep = declare_dependency(
  dependencies          : apf_deps,
  include_directories   : apf_includes,
  sources               : apf_files
)

appframework_dep = apf_dep


if not meson.is_subproject()
  sandbox_exe = executable('sandbox', files('tests/sandbox.cpp'), dependencies: apf_dep)

  test('files', executable('test_files', files('tests/files/test.cpp'), dependencies: apf_dep))
endif