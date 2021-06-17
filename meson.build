project('Discordbot', 'cpp', version: '0.1.0-a.1')

cpp_compiler = meson.get_compiler('cpp')
add_project_arguments('--std=c++2a', '-c', '-fcoroutines', '-ggdb', language: 'cpp')

add_project_link_arguments('-lssl', language: 'cpp')
add_project_link_arguments('-lcrypto', language: 'cpp')
add_project_link_arguments('-lpthread', language: 'cpp')
add_project_link_arguments('-lfmt', language: 'cpp')

add_project_arguments('-Wno-non-virtual-dtor', language : 'cpp')

subdir('src')
#subdir('include')
subdir('tests')
subdir('docs')