#include "JobStream.h"

TJobStream::TJobStream(double jIntens)
{
	if ((jIntens < 0.0) || (jIntens > 1.0))
		throw "Error";
	
	jobIntense = jIntens;
	lastJobId = 1;
}

double TJobStream::GetJobIntens() const
{
	return jobIntense;
}

size_t TJobStream::GetNewJob()
{
	if (static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX) <= jobIntense)
	{
		lastJobId++;
		return lastJobId - 1;
	}
	else
		return 0;
}

size_t TJobStream::GetLastJobId() const
{
	return lastJobId;
}