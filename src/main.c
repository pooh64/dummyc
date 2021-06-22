#include <logger.h>

int main()
{
	logger("starting main");
	logger_fatal("quack!");
	return 0;
}