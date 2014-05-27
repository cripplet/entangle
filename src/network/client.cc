#include "client.h"

ClientEngine::ClientEngine(const std::shared_ptr<GraphicsEngine>& graphics_engine) : graphics_engine(graphics_engine) {}
ClientEngine::~ClientEngine() {}

void ClientEngine::set_buffer(std::string buffer) {
	this->graphics_engine->get_buffer()->set_buffer(buffer);
}
