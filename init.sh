git submodule update --init --recursive
meson setup build --cross-file toolchain.ini --reconfigure
meson subprojects download
