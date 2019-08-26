/*
 * Secret of Evermore SRAM Editor
 * Copyright (C) 2006,2008 emuWorks
 * http://games.technoplaza.net/
 *
 * This file is part of Secret of Evermore SRAM Editor.
 *
 * Secret of Evermore SRAM Editor is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * Secret of Evermore SRAM Editor is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Secret of Evermore SRAM Editor; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
 
// $Id: soesrame.cc,v 1.22 2008/01/24 15:14:20 technoplaza Exp $

#include <QApplication>
#include <QTranslator>

#include "view/mainwindow.hh"

using namespace soesrame;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QTranslator appTranslator, qtTranslator;
    
    appTranslator.load("soesrame_" + QLocale::system().name(), ":/translations");
    qtTranslator.load("qt_" + QLocale::system().name(), ":/translations");
    
    app.installTranslator(&appTranslator);
    app.installTranslator(&qtTranslator);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}

