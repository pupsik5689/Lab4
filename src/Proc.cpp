#include "Proc.h"
#include <cstdlib>
TProc::TProc(double rate, size_t maxJobs) : jobs(maxJobs)
{
	if ((rate < 0.0) || (rate > 1.0))
		throw "Error";

	procRate = rate;
	jobsDone = 0;
	overflowTimes = 0;
	noJobsTimes = 0;
}

double TProc::GetRate() const
{
	return procRate;
}

bool TProc::IsProcBusy() const
{
	if (jobs.IsEmpty())
		return false;
	else
		return true;
}

bool TProc::IsProcFull() const
{
	return jobs.IsFull();
}

size_t TProc::RunNewJob(size_t jobId)
{

	if (jobId > 0)
	{
		if (IsProcFull())
		{
			overflowTimes++;
			return 0;
		}
		else
		{
			jobs.Push(jobId);
			return jobId;
		}
	}
	else
		return 0;
}

size_t TProc::DoJob(void)
{
	if (!IsProcBusy())
	{
		noJobsTimes++;
		return 0;
	}
	else if (static_cast<double>(rand()) / static_cast<double>(RAND_MAX) <= procRate && IsProcBusy())
	{
		size_t LastJob = jobs.TopPop();
		jobsDone++;
		return LastJob;
	}
	else
		return jobs.Top();
}

size_t TProc::GetJobsDone() const 
{
	return jobsDone;
}

size_t TProc::GetOverflowTimes() const 
{
	return overflowTimes;
}

size_t TProc::GetNoJobsTimes() const 
{
	return noJobsTimes;
}