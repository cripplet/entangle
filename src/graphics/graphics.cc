#include <ncurses.h>

#include "graphics.h"

PosInfo::PosInfo() : x(0), y(0) {}
PosInfo::~PosInfo() {}

int PosInfo::get_x() {
	getyx(stdscr, this->y, this->x);
	return(this->x);
}
int PosInfo::get_y() {
	getyx(stdscr, this->y, this->x);
	return(this->y);
}

void PosInfo::set_x(int x) {
	this->x += x;
	if(this->x < 0) { this->x = 0; }
}
void PosInfo::set_y(int y) {
	this->y += y;
	if(this->y < 0) { this->y = 0; }
}
GraphicsEngine::GraphicsEngine(const std::shared_ptr<Line>& buffer) : Engine(), buffer(buffer) {
	std::shared_ptr<PosInfo> new_pos (new PosInfo());
	this->pos = new_pos;
}
GraphicsEngine::~GraphicsEngine() {}

const std::shared_ptr<Line>& GraphicsEngine::get_buffer() { return(this->buffer); }
const std::shared_ptr<PosInfo>& GraphicsEngine::get_pos() { return(this->pos); }

void GraphicsEngine::ignite() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	this->get_pos()->set_y(0);
	this->get_pos()->set_x(0);
	refresh();
	Engine::ignite();
}

void GraphicsEngine::cycle() {
	clear();
	for(std::shared_ptr<Line> line = this->buffer; line != NULL; line = line->get_next()) {
		printw("%s", line->get_buffer().c_str());
	}
	// refresh();
	move(this->get_pos()->get_y(), this->get_pos()->get_x());
}

void GraphicsEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
