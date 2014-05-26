#include<iostream>
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
	int a;
	do {
		a = getch();
		if(a != ERR) {
			// clear();
			// printw("the key pressed is ");
			attron(A_BOLD);
			printw("%c", a);
			attroff(A_BOLD);
		}
	} while(a != ERR);
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
