TEMPLATE = app
TARGET = soesrame
QT += widgets
DEPENDPATH += . exceptions model resources view
INCLUDEPATH += .

HEADERS += exceptions/invalidsramfileexception.hh \
	model/sramfile.hh \
	view/aboutdialog.hh view/mainwindow.hh

SOURCES += soesrame.cc \
	exceptions/invalidsramfileexception.cc \
	model/sramfile.cc \
	view/aboutdialog.cc view/mainwindow.cc

FORMS += view/aboutdialog.ui view/mainwindow.ui
RESOURCES += resources/soesrame.qrc

TRANSLATIONS += resources/soesrame_de.ts \
	resources/soesrame_es.ts \
	resources/soesrame_fr.ts

win32 {
	RC_FILE = resources/windows.rc
}

macx {
	RC_FILE = resources/soesrame.icns
}
