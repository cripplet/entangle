#include "client.h"

ClientEngine::ClientEngine(const std::shared_ptr<GraphicsEngine>& graphics_engine) : graphics_engine(graphics_engine) {}
ClientEngine::~ClientEngine() {}

void ClientEngine::set_buffer(std::string buffer) {
	std::vector<int> delta = this->graphics_engine->get_buffer()->set_buffer(this->graphics_engine->get_pos()->get_x(), buffer);
	this->graphics_engine->get_pos()->set_x(delta.at(0));
	this->graphics_engine->get_pos()->set_y(delta.at(1));
}
