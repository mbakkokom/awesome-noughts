#include "NoughtsCanvas.hpp"

#include <iostream>

NoughtsCanvas::NoughtsCanvas(NoughtsGame *game) {
	mData = game;

	// allow click handler
    add_events(Gdk::BUTTON_PRESS_MASK);
	//Glib::signal_timeout().connect( sigc::mem_fun(*this, &NoughtsCanvas::on_timeout), 1000 );
}

void drawCross(const Cairo::RefPtr<Cairo::Context>& cr, size_t x, size_t y) {
	double bx = (double)x * 0.33,
		   by = (double)y * 0.33,
		   sx = bx + 0.066, // 0.2
		   lx = bx + 0.281,	// 0.85
		   sy = by + 0.066,
		   ly = by + 0.281;

	cr->save();

	cr->set_source_rgb(0.898, 0.316, 0.0); // #E65100

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_line_width(0.025);

	cr->begin_new_path();
	cr->move_to(sx, sy);
	cr->line_to(lx, ly);
	cr->close_path();
	cr->stroke();

	cr->begin_new_path();
	cr->move_to(lx, sy);
	cr->line_to(sx, ly);
	cr->close_path();
	cr->stroke();

	cr->restore();
}

void drawNought(const Cairo::RefPtr<Cairo::Context>& cr, size_t x, size_t y) {
	double bx = (double)x * 0.33,
		   by = (double)y * 0.33,
		   sx = bx + 0.165, // half the tile
		   sy = by + 0.165;

	cr->save();

	cr->set_source_rgb(0.898, 0.316, 0.0); // #E65100

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_line_width(0.025);

	cr->begin_new_path();
	cr->arc(sx, sy, 0.1155, 0, 2 * M_PI);
	cr->close_path();
	cr->stroke();

	cr->restore();
}

void drawStrokeHorizontal(const Cairo::RefPtr<Cairo::Context>& cr, size_t y) {
	double qw = 0.25 * 0.33,
		   pw = 2.75 * 0.33;

	cr->save();

	cr->set_source_rgb(1.0, 0.2196, 0.0); // #FF9800

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_line_width(0.15);

	cr->begin_new_path();
	cr->move_to(qw, (y + 0.5) * 0.33);
	cr->line_to(pw, (y + 0.5) * 0.33);
	cr->close_path();

	cr->stroke();

	cr->restore();
}

void drawStrokeVertical(const Cairo::RefPtr<Cairo::Context>& cr, size_t x) {
	double qh = 0.25 * 0.33,
		   ph = 2.75 * 0.33;

	cr->save();

	cr->set_source_rgb(1.0, 0.2196, 0.0); // #FF9800

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_line_width(0.15);

	cr->begin_new_path();
	cr->move_to((x + 0.5) * 0.33, qh);
	cr->line_to((x + 0.5) * 0.33, ph);
	cr->close_path();

	cr->stroke();

	cr->restore();
}


void drawStrokeDiagonal(const Cairo::RefPtr<Cairo::Context>& cr, size_t x) {
	double qh = 0.25 * 0.33,
		   qw = 0.25 * 0.33,
		   ph = 2.75 * 0.33,
		   pw = 2.75 * 0.33;

	cr->save();

	cr->set_source_rgb(1.0, 0.2196, 0.0); // #FF9800

	cr->set_line_cap(Cairo::LINE_CAP_ROUND);
	cr->set_line_width(0.15);
	
	cr->begin_new_path();
	if (x == 2) {
		cr->move_to(qw, ph);
		cr->line_to(pw, qh);
	} else {
		cr->move_to(qw, qh);
		cr->line_to(pw, ph);
	}
	cr->close_path();

	cr->stroke();

	cr->restore();
}

bool NoughtsCanvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	const int width = get_allocated_width(),
			  height = get_allocated_height();

	// scale to width and height so we can get 0.0 to 1.0 coordinates
	cr->scale(width, height);

	cr->save();

	// background fill
	cr->set_source_rgb(1.0, 0.925, 0.117); // #FFECB3
	cr->paint();

	if (mData == nullptr)
		return true;

	// background border
	cr->set_source_rgb(1.0, 0.754, 0.027); // #FFC107
	cr->set_line_width(0.05);
	cr->begin_new_path();
	cr->rectangle(0.0, 0.0, 1.0, 1.0);
	cr->close_path();
	cr->stroke();

	cr->set_line_width(0.025);

	cr->restore();

	for (size_t y=0; y<3; y++) {
		for (size_t x=0; x<3; x++) {
			cr->save();

			cr->begin_new_path();
			cr->rectangle(x * 0.33, y * 0.33, 0.33, 0.33);
			cr->close_path();
			cr->stroke();

			cr->restore();

			switch(mData->getTile(x, y)) {
			case NoughtsGame::PLAYER_CROSS:
				drawCross(cr, x, y);
				break;
			case NoughtsGame::PLAYER_NOUGHT:
				drawCross(cr, x, y);
				break;
			}
		}
	}

	if (mData->getState() > NoughtsGame::GAME_RUNNING) {
		// something happen.
		auto stroke = mData->getStroke();

		switch(stroke.direction) {
		case NoughtsGame::STROKE_HORIZONTAL:
			drawStrokeHorizontal(cr, stroke.y);
			break;
		case NoughtsGame::STROKE_VERTICAL:
			drawStrokeVertical(cr, stroke.x);
			break;
		case NoughtsGame::STROKE_DIAGONAL:
			drawStrokeDiagonal(cr, stroke.x);
			break;
		}
	}

	return true;
}

bool NoughtsCanvas::on_button_press_event(GdkEventButton *event) {
	const int width = get_allocated_width() / 3,
			  height = get_allocated_height() / 3,
			  x = event->x / width,
        	  y = event->y / height;

    std::cout << "Clicked at " << x << ", " << y << std::endl;

    if (x < 0 || x >= 3 || y < 0 || y >= 3)
    	return true;

    //..

    return true;
}

/*
bool NoughtsCanvas::on_timeout() {
	// force our program to redraw the entire clock.
    auto win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}
*/