#include <cstdlib>
#include <ctime>

#include "src/entangle_client.h"

entangle::EntangleClient::EntangleClient() {
	srand(time(NULL));
	this->is_blank = true;
}

entangle::EntangleClient::EntangleClient(std::string filename) : entangle::EntangleClient::EntangleClient() {
	this->node = entangle::OTNode<entangle::EntangleClient>(5000 + rand() % 1000, 0);
	this->node.up();
	this->node.bind(filename);
	this->is_blank = false;
}

entangle::EntangleClient::EntangleClient(std::string hostname, size_t port) : entangle::EntangleClient::EntangleClient() {
	this->node = entangle::OTNode<entangle::EntangleClient>(5000 + rand() % 1000, 0);
	this->node.up();
	this->node.join(hostname, port);
	this->is_blank = false;
}

entangle::EntangleClient::~EntangleClient() {
	if(!this->is_blank) {
		this->node.dn();
	}
}

size_t entangle::EntangleClient::get_port() { return(this->node.get_port()); }

void entangle::EntangleClient::i(size_t pos, char c) {}
void entangle::EntangleClient::e(size_t pos) {}
