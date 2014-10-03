#ifndef _ENTANGLE_NO_MAIN

#define VERSION "0.0.1"
#define SOURCE "https://github.com/cripplet/entangle"

#include <iostream>
#include <memory>
#include <sstream>

#include "libs/tclap/CmdLine.h"

#include "src/entangle_client.h"

int main(int argc, char** argv) {
	std::shared_ptr<entangle::EntangleClient> client;
	try {
		std::stringstream buf;
		buf << "Entangle is a concurrent file editor. Contact information and source code can be found in the repository at " << SOURCE << ".";
		TCLAP::CmdLine parser(buf.str(), ' ', VERSION);
		TCLAP::ValueArg<std::string> fn("", "filename", "file to edit", false, "", "string");
		TCLAP::ValueArg<std::string> hn("", "hostname", "host of the file", false, "", "string");
		TCLAP::ValueArg<size_t> p("", "port", "port of the hostname", false, 0, "size_t");
		parser.xorAdd(fn, hn);
		parser.add(p);
		parser.parse(argc, argv);
		std::string _fn = fn.getValue();
		std::string _hn = hn.getValue();
		size_t _p = p.getValue();
		if(_fn.compare("") == 0) {
			client = std::shared_ptr<entangle::EntangleClient> (new entangle::EntangleClient(_hn, _p));
		} else {
			client = std::shared_ptr<entangle::EntangleClient> (new entangle::EntangleClient(_fn));
		}

		client->start();

		// delete this later
		auto l = client->get_log();
		for(auto i = l.begin(); i != l.end(); ++i) {
			std::cout << *i << std::endl;
		}
	} catch(TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
        return(0);
}

#endif
