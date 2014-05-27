#ifndef _CONTROLLERENGINE_H
#define _CONTROLLERENGINE_H

#include <memory>
#include <string>

#include "../../libs/spp/base/engine.h"
#include "../graphics/graphics.h"

class ControllerEngine : public Engine {
	public:
		ControllerEngine(const std::shared_ptr<GraphicsEngine>& network_client_engine);
		~ControllerEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

	private:
		// TODO -- interface with the CLIENT instead
		std::shared_ptr<GraphicsEngine> network_client_engine;

		std::string buffer;
};

#endif
