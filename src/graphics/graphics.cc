#include <ncurses.h>

#include "graphics.h"

GraphicsEngine::GraphicsEngine() : Engine() {}
GraphicsEngine::~GraphicsEngine() {}

void GraphicsEngine::set_buffer(std::string buffer) {
	this->buffer_lock.lock();
	this->buffer.append(buffer);
	this->buffer_lock.unlock();
 }

void GraphicsEngine::ignite() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	Engine::ignite();
}

void GraphicsEngine::cycle() {
	// clear();
	this->buffer_lock.lock();
	// printw("%s", this->buffer.c_str());
	this->buffer_lock.unlock();
}

void GraphicsEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
