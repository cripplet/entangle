#include <ncurses.h>

#include "graphics.h"

GraphicsEngine::GraphicsEngine(const std::shared_ptr<Line>& buffer) : Engine(), buffer(buffer) {}
GraphicsEngine::~GraphicsEngine() {}

const std::shared_ptr<Line>& GraphicsEngine::get_buffer() { return(this->buffer); }

void GraphicsEngine::ignite() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	Engine::ignite();
}

void GraphicsEngine::cycle() {
	clear();
	printw("%s", this->buffer->get_buffer().c_str());
}

void GraphicsEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
