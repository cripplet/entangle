#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>

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
	{
		std::stringstream buf;
		buf << "starting entangle server on " << this->get_port();
		this->enq(buf.str());
	}
	{
		std::stringstream buf;
		buf << "editing local file " << filename;
		this->enq(buf.str());
	}
}

entangle::EntangleClient::EntangleClient(std::string hostname, size_t port) : entangle::EntangleClient::EntangleClient() {
	this->node = entangle::OTNode<entangle::EntangleClient>(5000 + rand() % 1000, 0);
	this->node.up();
	this->node.join(hostname, port);
	this->is_blank = false;
	{
		std::stringstream buf;
		buf << "starting entangle server on " << this->get_port();
		this->enq(buf.str());
	}
	{
		std::stringstream buf;
		buf << "connected to remote server " << hostname << ":" << port;
		this->enq(buf.str());
	}
}

entangle::EntangleClient::~EntangleClient() {
	if(!this->is_blank) {
		this->node.dn();
	}
}

void entangle::EntangleClient::enq(std::string l) {
	char t_buf[256];
	time_t r_time;
	time(&r_time);
	struct tm *t_info = localtime(&r_time);
	strftime(t_buf, 256, "%T[%Z] ", t_info);

	std::stringstream buf;
	buf << t_buf << l;
	this->log.push_back(buf.str());
}
std::vector<std::string> entangle::EntangleClient::get_log() { return(this->log); }

size_t entangle::EntangleClient::get_port() { return(this->node.get_port()); }

void entangle::EntangleClient::i(size_t pos, char c) {}
void entangle::EntangleClient::e(size_t pos) {}
