#include "client.h"

ClientEngine::ClientEngine(const std::shared_ptr<GraphicsEngine>& graphics_engine) : graphics_engine(graphics_engine) {}
ClientEngine::~ClientEngine() {}


/**
 * client is currently acting as server -- need to put these as PACKETS to the server
 */
void ClientEngine::send_move(std::vector<int> delta) {
	this->graphics_engine->get_pos()->set_x(delta.at(0));
	this->graphics_engine->get_pos()->set_y(delta.at(1));
}

void ClientEngine::send_buffer(std::string buffer) {
	if(buffer.compare("")) {
		this->send_move(this->graphics_engine->get_buffer()->set_buffer(this->graphics_engine->get_pos()->get_x(), buffer));
	}
}
