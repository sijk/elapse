CONFIG       += c++11

INCLUDEPATH  += $${PWD}/include
VPATH        += $${PWD}/include

# Find the immediate subdirectory of this directory which is an ancestor
# of the current pro file.
rel_path = $$relative_path($$_PRO_FILE_)
subdir = $$absolute_path($$section(rel_path, /, 0, 0))

INCLUDEPATH  += $${subdir}/include
VPATH        += $${subdir}/include

defineTest(linkStaticlib) {
    libname = $$1
    prodir = $$_PRO_FILE_PWD_
    outdir = $$shadowed($$_PRO_FILE_PWD_)

    LIBS            += -L$$outdir/../lib/$${libname}/ -l$${libname}
    INCLUDEPATH     += $$prodir/../lib/$${libname}
    DEPENDPATH      += $$prodir/../lib/$${libname}
    PRE_TARGETDEPS  += $$outdir/../lib/$${libname}/lib$${libname}.a

    export(LIBS)
    export(INCLUDEPATH)
    export(DEPENDPATH)
    export(PRE_TARGETDEPS)
}
