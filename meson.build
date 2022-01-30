project('sandbox', 'c', 'cpp',
  version : '1.0.0',
  default_options : ['warning_level=3', 'c_std=c17', 'cpp_std=c++17'],
  license : 'MIT')

files = files('src/appframework.cpp', 'src/sandbox.cpp')

dependencies = [dependency('threads')] 

extinstall = executable('sandbox', files)