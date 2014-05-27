#ifndef _FILEENGINE_H
#define _FILEENGINE_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

/**
 * Abstraction for a line of text
 *
 * Inspiration from the GNU nano source code
 *	cf. http://bit.ly/SI0z25
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

		std::mutex line_lock;
		std::mutex buffer_lock;
};

enum file_status { UNLOADED, LOADED };

class File {
	public:
		File(std::string filename);
		~File();

		void set_line(const std::shared_ptr<Line>& line);

		// load the filename and return a pointer to the nth line
		const std::shared_ptr<Line>& read(int index);

		// write the entirety of .line into the file
		void write();

	private:
		int status;
		std::string filename;
		std::shared_ptr<Line> line;
};

#endif
