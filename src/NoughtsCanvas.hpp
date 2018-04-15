#pragma once

#include "NoughtsGame.hpp"

#include <gtkmm.h>

class NoughtsCanvas : public Gtk::DrawingArea
{
public:
 	NoughtsCanvas(NoughtsGame *game = nullptr);
  	//virtual ~NoughtsCanvas();

 	NoughtsGame *getGame();
  	void setGame(NoughtsGame *game);

protected:
	//Override default signal handler:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	bool on_button_press_event(GdkEventButton *event) override;

	//bool on_timeout();

	NoughtsGame *mData;
};
