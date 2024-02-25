project('JustEnoughMod', 'cpp',
  version : '0.0.1',
  default_options : ['cpp_std=c++23'])

add_project_arguments('-DVERSION="@0@"'.format(meson.project_version()), language : 'cpp')

bgfx_proj = subproject('bgfx', default_options: ['warning_level=0'])

bgfx_dep = bgfx_proj.get_variable('bgfx_dep')
bimg_dep = bgfx_proj.get_variable('bimg_dep')
bx_dep = bgfx_proj.get_variable('bx_dep')

dylib_dep = subproject('dylib', default_options: ['warning_level=0']).get_variable('dylib_dep')

sdl2_dep = dependency('sdl2', default_options: ['warning_level=0'])
spdlog_dep = dependency('spdlog', default_options: ['warning_level=0'])

incdir = include_directories('include')

core_dep = [
  bgfx_dep,  
  bimg_dep,  
  bx_dep, 
  dylib_dep,
  sdl2_dep, 
  spdlog_dep
]

jem_lib = library('JustEnoughMod', 
  'src/core/Application.cpp',
  'src/core/Logger.cpp',
  'src/core/Window.cpp',
  'src/plugin/PluginLoader.cpp',
  include_directories : incdir,
  dependencies: core_dep,
  cpp_pch : 'pch/pch.hpp'
)

jem_dep = declare_dependency(
  link_with : jem_lib,
  include_directories : incdir,
  dependencies: core_dep
)

executable('JustEnoughMod', 'src/main.cpp',
  win_subsystem: 'windows',
  dependencies: [
    jem_dep
  ])
