#ifndef _CONTROLLERENGINE_H
#define _CONTROLLERENGINE_H

#include <memory>
#include <string>

#include "../../libs/spp/base/engine.h"
#include "../network/client.h"

class ControllerEngine : public Engine {
	public:
		ControllerEngine(const std::shared_ptr<ClientEngine>& client_engine);
		~ControllerEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

	private:
		std::shared_ptr<ClientEngine> client_engine;

		std::string buffer;
};

#endif
