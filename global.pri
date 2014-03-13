CONFIG       += c++11

ROOT = $$PWD

defineReplace(proFileSubdir) {
    # Find the immediate subdirectory of this directory which is an ancestor
    # of the current pro file.
    rel_path = $$relative_path($$_PRO_FILE_, $$ROOT)
    subdir = $$absolute_path($$section(rel_path, /, 0, 0), $$ROOT)
    return($$subdir)
}

INCLUDEPATH  += $${PWD}/include
VPATH        += $${PWD}/include

INCLUDEPATH  += $$proFileSubdir()/include
VPATH        += $$proFileSubdir()/include

defineTest(linkStaticlib) {
    isEmpty(2) {
        # e.g. linkStaticlib(pipeline)
        libname = $$1
        subdir = $$proFileSubdir()
    }
    !isEmpty(2) {
        # e.g. linkStaticlib(app, pipeline)
        libname = $$2
        subdir = $$ROOT/$$1
    }
    outdir = $$shadowed($$subdir)

    LIBS            += -L$$outdir/lib/$${libname}/ -l$${libname}
    INCLUDEPATH     += $$subdir/lib/$${libname}
    DEPENDPATH      += $$subdir/lib/$${libname}
    PRE_TARGETDEPS  += $$outdir/lib/$${libname}/lib$${libname}.a

    export(LIBS)
    export(INCLUDEPATH)
    export(DEPENDPATH)
    export(PRE_TARGETDEPS)
}
