tests_src = files('main_test.cpp', 'extern.cpp',
         'bot.cpp',
         'commandhandler.cpp',
         'modules/core.cpp',
         'commands/help.cpp',
         'commands/uptime.cpp',
         'commands/traceback.cpp',
         'commands/load.cpp',
         'commands/unload.cpp',
)

include_dirs = ['.', '../include']

gtestexe = executable(
  'gtest-all',
  tests_src,
  include_directories : include_dirs,
  dependencies : [
    dependency('gtest', method: 'pkg-config', required : true),
    dependency('gmock', method: 'pkg-config', required : true),
  ],
  cpp_args : ['--coverage' ],
  link_args : ['-lgcov', '--coverage' ],
)

# you can use ninja test in the build foler to run the testing
test('gtest tests', gtestexe)