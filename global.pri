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

defineTest(linkLibrary) {
    linkage = $$1
    isEmpty(3) {
        # e.g. linkLibrary("static", pipeline)
        libname = $$2
        subdir = $$proFileSubdir()
    }
    !isEmpty(3) {
        # e.g. linkLibrary("static", app, pipeline)
        libname = $$3
        subdir = $$ROOT/$$2
    }
    outdir = $$shadowed($$subdir)

    LIBS            += -L$$outdir/lib/$${libname}/ -l$${libname}
    INCLUDEPATH     += $$subdir/lib/$${libname}
    DEPENDPATH      += $$subdir/lib/$${libname}

    export(LIBS)
    export(INCLUDEPATH)
    export(DEPENDPATH)

    equals(linkage, static) {
        PRE_TARGETDEPS  += $$outdir/lib/$${libname}/lib$${libname}.a
        export(PRE_TARGETDEPS)
    }

    equals(linkage, shared) {
        !isEmpty(4) {
            QMAKE_RPATHDIR += $$outdir/lib/$$libname
            export(QMAKE_RPATHDIR)
        }
    }
}

defineTest(linkStaticlib) {
    # linkStaticlib(libname)             link libname from current subdir
    # linkStaticlib(app, libname)        link libname from app subdir
    linkLibrary("static", $$1, $$2)
}

defineTest(linkSharedlib) {
    # linkSharedlib(libname)             link libname from current subdir
    # linkSharedlib(app, libname)        link libname from app subdir
    # linkSharedlib(app, libname, true)  link libname from app subdir and set rpath
    linkLibrary("shared", $$1, $$2, $$3)
}
