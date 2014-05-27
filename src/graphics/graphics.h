#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include <mutex>

#include "../../libs/spp/base/engine.h"

#include "../file/file.h"

class PosInfo {
	public:
		PosInfo();
		~PosInfo();

		int get_x();
		int get_y();

		void set_x(int x);
		void set_y(int y);

	private:
		int x;
		int y;
};

class GraphicsEngine : public Engine {
	public:
		GraphicsEngine(const std::shared_ptr<Line>& buffer);
		~GraphicsEngine();

		const std::shared_ptr<PosInfo>& get_pos();

		void ignite() override;
		void cycle() override;
		void shutdown() override;

		const std::shared_ptr<Line>& get_buffer();
	private:
		std::shared_ptr<Line> buffer;		// render onto the screen
		std::shared_ptr<PosInfo> pos;
};

#endif
