project('appframework', 'cpp',
  version: '0.4.1',
  default_options: ['warning_level=3', 'cpp_std=c++17'],
  license: 'MIT')

files     = files()
includes  = include_directories('src')
deps      = [dependency('threads')]

apf_dep = declare_dependency(
  dependencies          : deps,
  include_directories   : includes,
  sources               : files
)

appframework_dep = apf_dep


if not meson.is_subproject()
  sandbox_exe = executable('sandbox', files('tests/sandbox.cpp'), dependencies: apf_dep)

  test('files', executable('test_files', files('tests/files/test.cpp'), dependencies: apf_dep))
  test('tree', executable('test_tree', files('tests/tree/test.cpp'), dependencies: apf_dep))
endif