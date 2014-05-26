#include <ncurses.h>

#include "controller.h"

ControllerEngine::ControllerEngine() : Engine() {}
ControllerEngine::~ControllerEngine() {}

void ControllerEngine::ignite() {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	Engine::ignite();
}

void ControllerEngine::cycle() {
	nodelay(stdscr, TRUE);
	int next_char = getch();
	while(next_char != ERR) {
		printw("%c", next_char);
		next_char = getch();
	}
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
