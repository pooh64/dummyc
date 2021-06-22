#include <logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void _vlogger(char const *file, char const *func, int line, char const *fmt, va_list ap)
{
	static char msg[1024];
	char *msgi = msg;

	msgi += snprintf(msgi, 256, "[%s:%s:%d]: ", file, func, line);
	msgi += vsnprintf(msgi, 256, fmt, ap);
	msgi += sprintf(msgi, "\n");

	fwrite(msg, 1, msgi - msg, stderr);
}

void _logger(char const *file, char const *func, int line, char const *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_vlogger(file, func, line, fmt, ap);
	va_end(ap);
}

void _logger_fatal(char const *file, char const *func, int line, char const *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	_vlogger(file, func, line, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}