#include<iostream>
#include <ncurses.h>

#include "controller.h"

ControllerEngine::ControllerEngine() : Engine() {}
ControllerEngine::~ControllerEngine() {}

void ControllerEngine::ignite() {
	initscr();
	timeout(1);
	// noecho();
	Engine::ignite();
}

void ControllerEngine::cycle() {
	getch();
	refresh();
	Engine::cycle();
}

void ControllerEngine::shutdown() {
	endwin();
	Engine::shutdown();
}
