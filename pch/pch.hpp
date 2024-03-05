#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include <SDL.h>
#include <SDL_syswm.h>

#include <dylib.hpp>

#include <any>
#include <chrono>
#include <condition_variable>
#include <filesystem>
#include <future>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// fix vscode intellisense
#ifdef __INTELLISENSE__
#pragma diag_suppress 1696
#endif

#include <wayland-egl.h>
