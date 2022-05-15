Framework i made to help me with creating simple terminal apps.
If you want to use this, [here](https://github.com/kapigames/apf_template) you'll find a template with some comments explaining how some things work.
This framework should work with Windows and any posix os aka Linux, MacOS and other unix like OS'es.

Any modern C++17 compiler should work, but these were tested to work on github actions:
- MSVC  on Windows
- g++   on linux
- clang on MacOS

To compile you also need mesonbuild system, use these commands to compile:

```bash
$ meson bin
$ meson compile -C bin
```

Use this command to run tests:

```bash
$ meson test -C bin
```