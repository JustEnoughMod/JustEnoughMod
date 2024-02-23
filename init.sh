git submodule update --init --recursive
meson subprojects download
meson setup build --buildtype=debugoptimized --optimization=g --cross-file toolchain.ini --reconfigure
