#pragma once

#include "NoughtsGame.hpp"

#include <gtkmm.h>
#include <mutex>

class NoughtsCanvas : public Gtk::DrawingArea
{
public:
 	NoughtsCanvas(NoughtsGame *game = nullptr);
  	//virtual ~NoughtsCanvas();

 	virtual NoughtsGame *getGame() final;
 	virtual NoughtsGame *getGameEx() final;
  	virtual void setGame(NoughtsGame *game) final;
  	virtual void setGameEx(NoughtsGame *game) final;
protected:
	//Override default signal handler:
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	virtual bool on_button_press_event(GdkEventButton *event) override;

	virtual void drawCross(const Cairo::RefPtr<Cairo::Context>& cr, size_t x, size_t y);
	virtual void drawNought(const Cairo::RefPtr<Cairo::Context>& cr, size_t x, size_t y);

	virtual void lockData() final;
	virtual void unlockData() final;

	virtual bool force_refresh() final;
private:
	std::mutex mDataMutex;
	NoughtsGame *mData;
};
