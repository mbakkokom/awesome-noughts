/* main.cpp
 *
 * Copyright (C) 2018 Koo Tito Novelianto
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm.h>
#include <iostream>

#include "NoughtsGame.hpp"
#include "NoughtsWindow.hpp"

int main(int   argc,
         char *argv[])
{
    auto app =
      Gtk::Application::create(argc, argv,
                               "org.gnome.AweomeNoughts");

    NoughtsGame game;
    NoughtsWindow window;

    return app->run(window);
}
