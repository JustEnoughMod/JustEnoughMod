project('JustEnoughMod', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20',
                     'optimization=g'])

cmake = import('cmake')
opt_var = cmake.subproject_options()

opt_var.add_cmake_defines({'CMAKE_POLICY_DEFAULT_CMP0112': 'NEW', 'CMAKE_POLICY_DEFAULT_CMP0126': 'NEW'})
opt_var.set_override_option('warning_level', '1')
opt_var.append_compile_args('cpp', '-w', '-Wno-everything')

bgfx_proj = cmake.subproject('bgfx', options: opt_var)
bgfx_dep = bgfx_proj.dependency('bgfx')
bimg_dep = bgfx_proj.dependency('bimg')
bx_dep = bgfx_proj.dependency('bx')

dylib_proj = cmake.subproject('dylib', options: opt_var)
dylib_dep = dylib_proj.dependency('dylib')

sdl2_dep = dependency('sdl2')

incdir = include_directories('include')

jem_lib = library('JustEnoughMod', 
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
