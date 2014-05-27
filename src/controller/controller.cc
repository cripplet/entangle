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
		// test for char here for special commands
		switch(next_char) {
			case KEY_BACKSPACE:
				next_char = 0x08;
				break;
			case KEY_DC:
				next_char = 0x7F;
				break;
			/**
			 * consider arrow keys & page_up / page_down here
			 * call server->move()
			 */
			default:
				break;
		}
		if(next_char < 0x80) {
			this->buffer.push_back((char) next_char);
		}
		next_char = getch();
	}
	this->network_client_engine->set_buffer(this->buffer);
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	Engine::shutdown();
}
