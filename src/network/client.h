#ifndef _CLIENTENGINE_H
#define _CLIENTENGINE_H

#include <memory>
#include <string>
#include <vector>

#include "../../libs/spp/base/engine.h"

#include "../graphics/graphics.h"

class ClientEngine : public Engine {
	public:
		ClientEngine(const std::shared_ptr<GraphicsEngine>& graphics_engine);
		~ClientEngine();

		void set_buffer(std::string buffer);

	private:
		std::shared_ptr<GraphicsEngine> graphics_engine;
};

#endif
