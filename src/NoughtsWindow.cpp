#include "NoughtsWindow.hpp"

#include <iostream>
#include <string>

#ifdef WITH_RANDOM_AI
// RandomAI AI function declaration
#include "RandomAI"
#endif

NoughtsWindow::NoughtsWindow()
{
    GdkGeometry g;
    g.min_width = 300;
    g.min_height = 300;
    g.min_aspect = 1.0;
    g.max_aspect = 1.0;
    set_geometry_hints(mCanvas, g, (Gdk::WindowHints) Gdk::HINT_MIN_SIZE | Gdk::HINT_ASPECT);

    set_title ("awesome-noughts");
    set_default_size(200, 200);
    set_titlebar(mHeader);

    mHeader.set_subtitle ("Click 'New Game' first!");
    mHeader.pack_start(mNewGameButton);
    //add(mGrid);
    add(mCanvas);

    mHeader.set_show_close_button();
    mHeader.set_title("Noughts And Crosses");

    //mNewGameButton.set_label("New Game");
    mNewGameButton.set_image_from_icon_name("document-new");
    mNewGameButton.signal_clicked().connect( sigc::mem_fun(*this, &NoughtsWindow::new_game) );

    mHeader.show();
    mNewGameButton.show();
    mCanvas.show();
}

NoughtsWindow::~NoughtsWindow() {
    NoughtsGame *last = mCanvas.getGameEx();

    if (lastConnection.connected() == true) {
        lastConnection.disconnect();
    }

    if (last != nullptr) {
        delete last;
    }

    mCanvas.setGameEx(nullptr);
}

/*
bool NoughtsWindow::on_configure_event(GdkEventConfigure* evt) {
    std::cout << "Window resized!" << std::endl;
    return false;
}
*/

void NoughtsWindow::on_game_event(NoughtsGame *game, NoughtsGame::GameStatus status, NoughtsGame::PlayerTurn turn) {
    std::cout << "NoughtsWindow::on_game_event" << std::endl;

    std::string st;

    switch(status) {
    case NoughtsGame::GAME_RUNNING:
        st = (turn == NoughtsGame::PLAYER_CROSS) ? "X" : "O";
        st += "'s turn";
        break;
    case NoughtsGame::GAME_WON:
        st = (turn == NoughtsGame::PLAYER_CROSS) ? "X" : "O";
        st += " won!";
        break;
    case NoughtsGame::GAME_DRAW:
        st = "Draw!";
        break;
    }

    mHeader.set_subtitle(st);

#ifdef WITH_RANDOM_AI
    // TODO. check return value.
    if (!NoughtsAI(game))
        std::cout << "fixme::NoughtsWindow::on_game_event NoughtsAI(nw) returns false" << std::endl;
#endif

}

void NoughtsWindow::new_game() {
    std::cout << "NoughtsWindow::new_game" << std::endl;

    NoughtsGame *nw = new NoughtsGame(),
                *old = mCanvas.getGameEx();

    if (lastConnection.connected() == true) {
        lastConnection.disconnect();
    }

    if (old != nullptr) {
        delete old;
    }

    lastConnection = nw->signal_game_event().connect(sigc::mem_fun(*this, &NoughtsWindow::on_game_event));
    on_game_event(nw, (NoughtsGame::GameStatus) nw->getState(), nw->getTurn());

    mCanvas.setGameEx(nw);

}