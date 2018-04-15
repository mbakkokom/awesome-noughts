project('awesome-noughts', 'cpp')

dependencies = [dependency('gtkmm-3.0')]

sources = ['src/main.cpp', 'src/NoughtsGame.cpp', 'src/NoughtsWindow.cpp', 'src/NoughtsCanvas.cpp']

if get_option('buildtype').startswith('debug')
  add_project_arguments('-g', language : 'cpp')
endif

executable('awesome-noughts', sources: sources, dependencies: dependencies)