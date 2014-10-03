#ifndef _ENTANGLE_NO_MAIN

#include <iostream>

#include "libs/tclap/CmdLine.h"

#include "src/entangle_client.h"

int main(int argc, char** argv) {
        entangle::EntangleClient client;
	try {
		TCLAP::CmdLine parser("entangle -- concurrent file editor", ' ', "0.0.1");
		TCLAP::ValueArg<std::string> fn("f", "filename", "file to edit", false, "", "string", parser);
		TCLAP::ValueArg<std::string> hn("n", "hostname", "host of the file", false, "", "string", parser);
		TCLAP::ValueArg<size_t> p("p", "port", "port of the hostname", false, 0, "size_t", parser);
		parser.parse(argc, argv);
		std::string _fn = fn.getValue();
		std::string _hn = hn.getValue();
		size_t _p = p.getValue();
		if(_fn.compare("") == 0) {
			client = entangle::EntangleClient(_hn, _p);
		} else {
			client = entangle::EntangleClient(_fn);
		}
		std::cout << "client port opened on " << client.get_port() << std::endl;
	} catch(TCLAP::ArgException &e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
        return(0);
}

#endif
