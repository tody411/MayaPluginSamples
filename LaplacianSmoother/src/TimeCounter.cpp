#include "TimeCounter.h"

//! Set the name of the counter.
void TimeCounter::setName(const std::string& newname)
{
	name = newname;
}

//! Return the name of the counter.
const std::string& TimeCounter::getName() const
{
	return name;
}

//! Get elapsed time.
double TimeCounter::getElapsedTime()
{
	double res = elapsed;
	if (isRunning())
	{
		long currentTime = clock();
		res += (currentTime - last_start) / ((double)CLOCKS_PER_SEC);
	}
	return res;
}

//! Return if the counter is running or not.
bool TimeCounter::isRunning()
{
	return running;
}

//! Start the counter.
void TimeCounter::start()
{
	last_start = clock();
	running = true;
}

//! Stop without reseting
double TimeCounter::pause()
{
	if (isRunning())
	{
		long currentTime = clock();
		elapsed += (currentTime - last_start) / ((double)CLOCKS_PER_SEC);
	}
	running = false;

	return elapsed;
}

//! Rest the counter.
double TimeCounter::reset()
{
	double res = pause();
	elapsed = 0;
	running = false;
	return res;
}

//! Output string for the counter.
std::ostream& operator<< (std::ostream &out, TimeCounter &counter)
{
	out<< counter.name << ": " << counter.getElapsedTime() << "[sec]";
	return out;
}