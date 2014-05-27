#include <memory>
#include <ncurses.h>
#include <unistd.h>

#include "../libs/spp/scheduling/calendar.h"
#include "../libs/spp/scheduling/scheduling.h"

#include "controller/controller.h"
#include "file/file.h"
#include "graphics/graphics.h"

int main(int argc, const char **argv) {
	std::shared_ptr<SchedulingEngine> scheduler (new SchedulingEngine());

	// file initialization
	std::shared_ptr<File> file (new File("example.txt"));

	std::shared_ptr<GraphicsEngine> graphics_engine (new GraphicsEngine(file->read(0)));
	std::shared_ptr<ControllerEngine> controller_engine (new ControllerEngine(graphics_engine));

	std::shared_ptr<Calendar> cal_graphics (new Calendar(30, graphics_engine));
	std::shared_ptr<Calendar> cal_controller (new Calendar(60, controller_engine));

	scheduler->add_calendar(cal_controller);
	scheduler->add_calendar(cal_graphics);

	scheduler->ignite();
	scheduler->cycle();

	sleep(5);

	scheduler->shutdown();
	file->write();
	return(0);
}
