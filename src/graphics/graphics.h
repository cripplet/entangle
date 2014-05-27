#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include <mutex>

#include "../../libs/spp/base/engine.h"

class GraphicsEngine : public Engine {
	public:
		GraphicsEngine();
		~GraphicsEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		void set_buffer(std::string buffer);

	private:
		std::string buffer;			// render onto the screen
		std::mutex buffer_lock;			// lock the buffer when reading and writing
};

#endif
