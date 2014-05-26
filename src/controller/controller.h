#ifndef _ICONTROLLER_H
#define _ICONTROLLER_H

#include <mutex>
#include <string>

#include "../../libs/spp/base/engine.h"

class ControllerEngine : public Engine {
	public:
		ControllerEngine();
		~ControllerEngine();

		void ignite() override;
		void cycle() override;
		void shutdown() override;
};

#endif
