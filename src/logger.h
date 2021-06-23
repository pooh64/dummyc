#ifndef __LOGGER_H
#define __LOGGER_H

void _logger(char const *file, char const *func, int line, char const *fmt,
	     ...);
void _logger_fatal(char const *file, char const *func, int line,
		   char const *fmt, ...);

#define logger(fmt, ...)                                                       \
	_logger(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

#define logger_fatal(fmt, ...)                                                 \
	_logger_fatal(__FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

#endif