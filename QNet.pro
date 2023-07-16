include($$PWD/QNET.pri)

QT = core network testlib
DESTDIR = $${IDE_BIN_PATH}

include($$PWD/QNet/QNetSrc.pri)
include($$PWD/test/test.pri)

INCLUDEPATH +=$$PWD/include



