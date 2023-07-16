!isEmpty(QNET_PRI_INCLUDED) {
    error("QNET.pri already included")
}
QNET_PRI_INCLUDED = 1

QNET_VERSION_STR = 0.0.1
QNET_VERSION = 0x000001
VERSION = $$QNET_VERSION_STR
QNET_COPYRIGHT_YEAR = 2023

CONFIG += c++14

# Avoid automatically appending version numbers to generated libraries
CONFIG += skip_target_version_ext

# Config Para
CONFIG(debug, debug|release):{
    FILE_POSTFIX = d
    DIR_COMPILEMODE = Debug
}
else:CONFIG(release, debug|release):{
    FILE_POSTFIX =
    DIR_COMPILEMODE = Release
}

msvc {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS_WARN_ON *= -w44996
    # Speed up startup time when debugging with cdb
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
}


equals(TEST, 1) {
    QT +=testlib
    DEFINES += WITH_TESTS
}

IDE_APP_NAME = QNET
IDE_APP_PATH = $$PWD/bin
QNET_PREFIX = $$IDE_APP_PATH/$$DIR_COMPILEMODE
IDE_BIN_PATH     = $$QNET_PREFIX
IDE_LIBRARY_PATH = $$QNET_PREFIX
IDE_PLUGIN_PATH  = $$QNET_PREFIX/plugins
IDE_DOC_PATH     = $$QNET_PREFIX/share/doc
IDE_DATA_PATH    = $$QNET_PREFIX/share/$$IDE_APP_NAME

DEFINES += $$shell_quote(IDE_BIN_PATH=\"$$IDE_BIN_PATH\")
DEFINES += $$shell_quote(IDE_LIBRARY_PATH=\"$$IDE_LIBRARY_PATH\")
DEFINES += $$shell_quote(IDE_PLUGIN_PATH=\"$$IDE_PLUGIN_PATH\")

QNET_PATH_INFO = 0
equals(QNET_PATH_INFO, 1) {
message("=================PATH info =============================")
message("IDE_LIBRARY_PATH:       " $$IDE_LIBRARY_PATH)
message("IDE_PLUGIN_PATH:        " $$IDE_PLUGIN_PATH)
message("IDE_DATA_PATH:          " $$IDE_DATA_PATH)
message("IDE_DOC_PATH:           " $$IDE_DOC_PATH)
message("IDE_BIN_PATH:           " $$IDE_BIN_PATH)
message("INSTALL_LIBRARY_PATH:   " $$INSTALL_LIBRARY_PATH)
message("INSTALL_PLUGIN_PATH:    " $$INSTALL_PLUGIN_PATH)
message("INSTALL_LIBEXEC_PATH:   " $$INSTALL_LIBEXEC_PATH)
message("INSTALL_BIN_PATH:       " $$INSTALL_BIN_PATH)
message("INSTALL_APP_PATH:       " $$INSTALL_APP_PATH)
message("==============================================")
}

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}
