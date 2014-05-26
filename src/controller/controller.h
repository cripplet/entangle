#ifndef _CONTROLLERENGINE_H
#define _CONTROLLERENGINE_H

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
