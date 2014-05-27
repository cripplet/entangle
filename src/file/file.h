#ifndef _FILEENGINE_H
#define _FILEENGINE_H

#include <memory>
#include <mutex>
#include <string>

/**
 * Abstraction for a line of text
 */
class Line {
	public:
		Line(int line, std::string buffer, const std::shared_ptr<Line>& prev, const std::shared_ptr<Line>& next);
		~Line();

		int get_line();
		std::string get_buffer();
		const std::shared_ptr<Line>& get_prev();
		const std::shared_ptr<Line>& get_next();

		void set_line(int line);
		void set_buffer(std::string buffer);
		void set_prev(const std::shared_ptr<Line>& prev);
		void set_next(const std::shared_ptr<Line>& next);

	private:
		int line;

		std::string buffer;

		std::shared_ptr<Line> prev;
		std::shared_ptr<Line> next;

		std::mutex buffer_lock;
};

#endif
