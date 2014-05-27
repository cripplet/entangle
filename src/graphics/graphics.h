#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include <mutex>

#include "../../libs/spp/base/engine.h"

#include "../file/file.h"

class GraphicsEngine : public Engine {
	public:
		GraphicsEngine(const std::shared_ptr<Line>& buffer);
		~GraphicsEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		const std::shared_ptr<Line>& get_buffer();
	private:
		std::shared_ptr<Line> buffer;		// render onto the screen
};

#endif
