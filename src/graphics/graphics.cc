#include <ncurses.h>

#include "graphics.h"

PosInfo::PosInfo() : x(0), y(0) {}
PosInfo::~PosInfo() {}

int PosInfo::get_x() {
	this->pos_lock.lock();
	int x = this->x;
	this->pos_lock.unlock();
	return(x);
}
int PosInfo::get_y() {
	this->pos_lock.lock();
	int y = this->y;
	this->pos_lock.unlock();
	return(y);
}

void PosInfo::set_x(int x) {
	this->pos_lock.lock();
	this->x += x;
	if(this->x < 0) { this->x = 0; }
	this->pos_lock.unlock();
}
void PosInfo::set_y(int y) {
	this->pos_lock.lock();
	this->y += y;
	if(this->y < 0) { this->y = 0; }
	this->pos_lock.unlock();
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
	curs_set(0);
	keypad(stdscr, TRUE);
	refresh();
	Engine::ignite();
}

void GraphicsEngine::cycle() {
	clear();
	for(std::shared_ptr<Line> line = this->buffer; line != NULL; line = line->get_next()) {
		printw("%s", line->get_buffer().c_str());
	}
	mvaddch(this->pos->get_x(), this->pos->get_y(), '_');
}

void GraphicsEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
