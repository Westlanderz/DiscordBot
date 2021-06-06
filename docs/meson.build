cdata = configuration_data()
cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())
cdata.set('OUTPUT_DIR', join_paths(meson.build_root(),'docs'))
cdata.set('README_PATH', join_paths(meson.source_root(),'README.md'))
cdata.set('VERSION', meson.project_version())
cdata.set('PROJECT_NAME', meson.project_name())

doxyfile = configure_file(input: 'Doxyfile.in',
                          output: 'Doxyfile',
                          configuration: cdata,
                          install: false)

doxygen = find_program('doxygen')

sphinxexe = find_program('sphinx-build')

sdata = '-Dbreathe_projects.Discordbot=' + join_paths(meson.build_root(),'docs')

doc_target = run_target('doc',command: [doxygen, doxyfile])
sphinx_target = run_target('docs', command: [sphinxexe, '-bhtml', sdata, join_paths(meson.source_root(),'docs'), join_paths(meson.build_root(),'docs/sphinx')])