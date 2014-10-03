#include "src/entangle_client.h"

entangle::EntangleClient::EntangleClient(std::string filename) {
	this->node = entangle::OTNode<entangle::EntangleClient>(5000 + rand() % 1000, 0);
	this->node.up();
	this->node.bind(filename);
}

entangle::EntangleClient::EntangleClient(std::string hostname, size_t port) {
	this->node = entangle::OTNode<entangle::EntangleClient>(5000 + rand() % 1000, 0);
	this->node.up();
	this->node.join(hostname, port);
}

entangle::EntangleClient::~EntangleClient() {
	this->node.dn();
}

void entangle::EntangleClient::i(size_t pos, char c) {}
void entangle::EntangleClient::e(size_t pos) {}
