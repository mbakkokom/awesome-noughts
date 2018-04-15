#pragma once

#include "NoughtsGame.hpp"
#include "NoughtsCanvas.hpp"

#include <gtkmm.h>

class NoughtsWindow : public Gtk::Window {
public:
    NoughtsWindow();
    ~NoughtsWindow();

    void new_game();
    void grid_button_click(size_t id);
protected:
	//bool on_configure_event(GdkEventConfigure* evt);

    Gtk::HeaderBar mHeader;
    Gtk::Button mNewGameButton;
    NoughtsCanvas mCanvas;
};
