project('JustEnoughMod', 'cpp',
  version : '0.0.1',
  default_options : ['cpp_std=c++23'])

add_project_arguments('-DVERSION="@0@"'.format(meson.project_version()), language : 'cpp')

dylib_dep = subproject('dylib', default_options: ['warning_level=0']).get_variable('dylib_dep')

spdlog_dep = dependency('spdlog', default_options: ['warning_level=0', 'compile_library=false', 'std_format=enabled'])
glfw_dep = dependency('glfw3', default_options: ['warning_level=0'])

vulkan_dep = dependency('vulkan', default_options: ['warning_level=0'])

incdir = include_directories('include')

core_dep = [
  dylib_dep,
  glfw_dep,
  spdlog_dep,
  vulkan_dep
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
  dependencies: core_dep
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

doxygen = find_program('doxygen', required : false)
if doxygen.found()
  message('Doxygen found')
  run_target('docs', command : 'scripts/doxygen.sh')
else
  warning('Documentation disabled without doxygen')
endif
