project('JustEnoughMod', 'cpp',
  version : '0.0.1',
  default_options : ['cpp_std=c++23'])

add_project_arguments('-DVERSION="@0@"'.format(meson.project_version()), language : 'cpp')

bgfx_proj = subproject('bgfx', default_options: ['warning_level=0'])

bgfx_dep = bgfx_proj.get_variable('bgfx_dep')
bimg_dep = bgfx_proj.get_variable('bimg_dep')
bx_dep = bgfx_proj.get_variable('bx_dep')

dylib_dep = subproject('dylib', default_options: ['warning_level=0']).get_variable('dylib_dep')
spdlog_dep = subproject('spdlog', default_options: ['warning_level=0', 'compile_library=false', 'std_format=enabled']).get_variable('spdlog_dep')

sdl2_dep = dependency('sdl2', default_options: ['warning_level=0'])
wayland_dep = dependency('wayland-client', default_options: ['warning_level=0'])
wayland_egl_dep = dependency('wayland-egl', default_options: ['warning_level=0'])

incdir = include_directories('include')

core_dep = [
  bgfx_dep,
  bimg_dep,
  bx_dep,
  dylib_dep,
  sdl2_dep,
  spdlog_dep,
  wayland_dep,
  wayland_egl_dep
]

jem_src = files(
  'src/core/Application.cpp',
  'src/core/Logger.cpp',
  'src/core/Window.cpp',
  'src/plugin/PluginLoader.cpp',
  'src/render/Renderer.cpp'
)

jem_lib = library('JustEnoughMod',
  jem_src,
  include_directories : incdir,
  dependencies: core_dep,
  cpp_pch : 'pch/pch.hpp'
)

jem_dep = declare_dependency(
  link_with : jem_lib,
  include_directories : incdir,
  dependencies: core_dep
)

src_files = files('src/main.cpp')

executable('JustEnoughMod',
  src_files,
  win_subsystem: 'windows',
  dependencies: [
    jem_dep
  ])

# clangtidy = find_program('clang-tidy', required: false)
# if clangtidy.found()
#   run_target(
#     'clang-tidy',
#     command: [
#       clangtidy,
#       '--header-filter=\'../include/*\'',
#       '--config-file=../.clang-tidy',
#       '--checks=*',
#       '--fix-errors',
#       '-p', meson.build_root(),
#     ] + src_files + jem_src
#   )
# endif
