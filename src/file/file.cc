#include "file.h"

Line::Line(int line, std::string buffer, const std::shared_ptr<Line>& prev, const std::shared_ptr<Line>& next) : line(line), buffer(buffer), prev(prev), next(next) {}
Line::~Line() {}

int Line::get_line() { return(this->line); }
std::string Line::get_buffer() { return(this->buffer); }
const std::shared_ptr<Line>& Line::get_prev() { return(this->prev); }
const std::shared_ptr<Line>& Line::get_next() { return(this->next); }

void Line::set_line(int line) { this->line = line; }
void Line::set_buffer(std::string buffer) {
	this->buffer_lock.lock();
	this->buffer.append(buffer);
	this->buffer_lock.unlock();
}
void Line::set_prev(const std::shared_ptr<Line>& prev) {
	this->prev = prev;
}
void Line::set_next(const std::shared_ptr<Line>& next) {
	this->next = next;
}
