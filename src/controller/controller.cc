#include <ncurses.h>

#include "controller.h"

ControllerEngine::ControllerEngine(const std::shared_ptr<ClientEngine>& client_engine) : Engine(), client_engine(client_engine) {}
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
			// manually convert CR to LF
			case 0x0D:
				next_char = 0x0A;
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
	this->client_engine->set_buffer(this->buffer);
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	Engine::shutdown();
}
