#pragma once

#include "NoughtsGame.hpp"
#include "NoughtsCanvas.hpp"

#include <gtkmm.h>

class NoughtsWindow : public Gtk::Window {
public:
    NoughtsWindow();
    ~NoughtsWindow();

    virtual void new_game() final;
protected:
	//bool on_configure_event(GdkEventConfigure* evt);

    Gtk::HeaderBar mHeader;
    Gtk::Button mNewGameButton;
    NoughtsCanvas mCanvas;


    void on_game_event(NoughtsGame::GameStatus status, NoughtsGame::PlayerTurn turn);
private:
	sigc::connection lastConnection;
};
