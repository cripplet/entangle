#include <ncurses.h>

#include "controller.h"

ControllerEngine::ControllerEngine(const std::shared_ptr<GraphicsEngine>& network_client_engine) : Engine(), network_client_engine(network_client_engine) {}
ControllerEngine::~ControllerEngine() {}

void ControllerEngine::ignite() {
	Engine::ignite();
}

void ControllerEngine::cycle() {
	nodelay(stdscr, TRUE);
	this->buffer = "";
	int next_char = getch();
	while(next_char != ERR) {
		switch(next_char) {
		}
		// test for char here for special commands
		// printw("%i", next_char);
		this->buffer.push_back((char) next_char);
		next_char = getch();
	}
	this->network_client_engine->set_buffer(this->buffer);
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	Engine::shutdown();
}
