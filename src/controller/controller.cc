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
	for(int next_char = getch(); next_char != ERR; next_char = getch()) {
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
				break;
			case KEY_RIGHT:
				this->client_engine->send_buffer(this->buffer);
				this->buffer = "";
				this->client_engine->send_move({ 0, 1 });
				break;
			case KEY_LEFT:
				this->client_engine->send_buffer(this->buffer);
				this->buffer = "";
				this->client_engine->send_move({ 0, -1 });
				break;
			case KEY_UP:
				this->client_engine->send_buffer(this->buffer);
				this->buffer = "";
				this->client_engine->send_move({ -1, 0 });
				break;
			case KEY_DOWN:
				// this->client_engine->send_buffer(this->buffer);
				// this->buffer = "";
				this->client_engine->send_move({ 1, 0 });
				break;
			default:
				break;
		}
		if(next_char < 0x80) {
			this->buffer.push_back((char) next_char);
		}
	}
	this->client_engine->send_buffer(this->buffer);
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	Engine::shutdown();
}
