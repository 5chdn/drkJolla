/*
 * Copyright (C) 2014 Alexander Schoedon <schoedon@uni-potsdam.de>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtQuick>

#include "sailfishapp.h"
#include "tickerhandler.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<TickerHandler>("harbour.drkjolla.tickerHandler", 1, 7, "TickerHandler");

    return SailfishApp::main(argc, argv);
}

