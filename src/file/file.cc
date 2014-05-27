#include <fstream>
#include <ncurses.h>

#include "file.h"

Line::Line(int line, std::string buffer, const std::shared_ptr<Line>& prev, const std::shared_ptr<Line>& next) : line(line), buffer(buffer), prev(prev), next(next) {}
Line::~Line() {}

int Line::get_line() {
	this->line_lock.lock();
	int line = this->line;
	this->line_lock.unlock();
	return(line);
}
std::string Line::get_buffer() { return(this->buffer); }
const std::shared_ptr<Line>& Line::get_prev() { return(this->prev); }
const std::shared_ptr<Line>& Line::get_next() { return(this->next); }

void Line::set_line(int line) {
	this->line_lock.lock();
	this->line = line;
	this->line_lock.unlock();
}
std::vector<int> Line::set_buffer(int start, std::string buffer) {
	std::vector<int> delta = { 0, 0 };
	// this->buffer_lock.lock();

	start = (std::size_t) start > this->buffer.size() ? this->buffer.size() : start;
	this->buffer.insert(start, buffer);

	std::string::iterator i = this->buffer.begin();
	while(i < this->buffer.end()) {
		char ch = *i;
		// std::size_t index = std::distance(this->buffer.begin(), i);
		switch(ch) {
			case 0x08:
				delta.at(0)--;
				break;
			case 0x7F:
				this->buffer.erase(i++);
				if(i != this->buffer.end()) {
					this->buffer.erase(i++);
				} else if(this->next != NULL) {
					this->buffer.append(this->next->get_buffer());
					this->next = this->next->next;
				}
				break;
//			case 0x0A:
				// delta.at(1)++;
				/**
				{
					std::shared_ptr<Line> _this (this);
					std::shared_ptr<Line> line (new Line(this->line + 1, this->buffer.substr(index), _this, this->next));
					if(this->next != NULL) { this->next->set_prev(line); }
					this->next = line;
					this->buffer.erase(index);
				}
				*/
//				break;
			default:
				delta.at(0)++;
				break;
		}
		++i;
	}
	// this->buffer_lock.unlock();
	return(delta);
}

void Line::set_prev(const std::shared_ptr<Line>& prev) {
	this->prev = prev;
}
void Line::set_next(const std::shared_ptr<Line>& next) {
	this->next = next;
}


File::File(std::string filename) : status(file_status::UNLOADED), filename(filename) {
	std::shared_ptr<Line> line (new Line(0, "", NULL, NULL));
	this->line = line;
}
File::~File() {};

void File::set_line(const std::shared_ptr<Line>& line) {
	this->status = file_status::LOADED;
	this->line = line;
}

/**
 * Read from the file indicated
 *
 * cf. http://bit.ly/1kGaeAG
 */
const std::shared_ptr<Line>& File::read(int index) {
	if(this->status == file_status::UNLOADED) {
		std::ifstream file (this->filename);
		for(std::string buffer; getline(file, buffer);) {
			std::shared_ptr<Line> line (new Line(this->line->get_line() + 1, buffer, this->line, NULL));
			this->line = line;
		}
		this->status = file_status::LOADED;
		file.close();
	}
	// return the first line whose line number is greater than or equal to index
	for(std::shared_ptr<Line> line = this->line; line->get_line() < index; line = line->get_next());
	return(this->line);
}

void File::write() {
	if(this->status == file_status::UNLOADED) {
		return;
	}
	std::ofstream file (this->filename);
	for(std::shared_ptr<Line> line = this->line; line != NULL; line = line->get_next()) {
		file << line->get_buffer() << std::endl;
	}
	file.close();
}
