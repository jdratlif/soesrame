################################################################################
# Secret of Evermore SRAM Editor
# Copyright (C) 2006,2008 emuWorks
# http://games.technoplaza.net/
#
# This file is part of Secret of Evermore SRAM Editor.
#
# Secret of Evermore SRAM Editor is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of the License,
# or (at your option) any later version.
#
# Secret of Evermore SRAM Editor is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Secret of Evermore SRAM Editor; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
################################################################################

TEMPLATE = app
TARGET += 
DEPENDPATH += .
INCLUDEPATH += .
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.3
CONFIG += x86 ppc

TRANSLATIONS = resources/soesrame_de.ts \
	resources/soesrame_es.ts \
	resources/soesrame_fr.ts

RESOURCES += resources/soesrame.qrc
RC_FILE = resources/windows.rc

SOURCES += soesrame.cc \
	exceptions/invalidsramfileexception.cc \
	model/sramfile.cc \
	view/aboutdialog.cc view/mainwindow.cc
	
HEADERS += exceptions/invalidsramfileexception.hh \
	model/sramfile.hh \
	view/aboutdialog.hh view/mainwindow.hh

FORMS += view/aboutdialog.ui view/mainwindow.ui
