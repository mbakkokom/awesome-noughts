#include "NoughtsWindow.hpp"

#include <iostream>

NoughtsWindow::NoughtsWindow()
{
    set_title ("aweome-noughts");
    set_default_size(200, 200);
    set_titlebar(mHeader);

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

}

/*
bool NoughtsWindow::on_configure_event(GdkEventConfigure* evt) {
    std::cout << "Window resized!" << std::endl;
    return false;
}
*/

void NoughtsWindow::new_game() {
    std::cout << "New game called!" << std::endl;
}

void NoughtsWindow::grid_button_click(size_t id) {
    std::cout << "Clicked grid at " << id << std::endl;
}
