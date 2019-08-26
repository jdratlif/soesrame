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
 
// $Id: aboutdialog.cc,v 1.1 2008/01/23 21:30:18 technoplaza Exp $

#include "view/aboutdialog.hh"

using namespace soesrame;

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) {
    ui.setupUi(this);
    
    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(hide()));
}

