project('JustEnoughMod', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20',
                     'optimization=g'])

add_project_arguments('-D_GLIBCXX_USE_CXX11_ABI=0', language : 'cpp')

bgfx_dep = dependency('bgfx')
bimg_dep = dependency('bimg')
bx_dep = dependency('bx')
dylib_dep = dependency('dylib')
sdl2_dep = dependency('sdl2')

incdir = include_directories('include')

jem_lib = library('JustEnoughMod', 'src/core/Application.cpp',
  include_directories : incdir,
  dependencies: [
    sdl2_dep, 
    bgfx_dep,  
    bimg_dep,  
    bx_dep, 
    dylib_dep
  ])

jem_dep = declare_dependency(
  link_with : jem_lib,
  include_directories : incdir,
  dependencies: [
    sdl2_dep, 
    bgfx_dep,  
    bimg_dep,  
    bx_dep, 
    dylib_dep
  ])

executable('JustEnoughMod', 'src/main.cpp',
  win_subsystem: 'windows',
  dependencies: [
    jem_dep
  ])
