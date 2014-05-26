#include <memory>
#include <ncurses.h>
#include <unistd.h>

#include "../libs/spp/scheduling/calendar.h"
#include "../libs/spp/scheduling/scheduling.h"

#include "controller/controller.h"

int main(int argc, const char **argv) {
	std::shared_ptr<ControllerEngine> controller (new ControllerEngine());
	std::shared_ptr<Calendar> cal_controller (new Calendar(0, controller));
	std::shared_ptr<SchedulingEngine> scheduler (new SchedulingEngine());
	scheduler->add_calendar(cal_controller);

	scheduler->ignite();
	scheduler->cycle();
	sleep(10);
	scheduler->shutdown();
	return(0);
}
