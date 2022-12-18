#pragma once
#include "Queue.h"
#include "JobStream.h"
#include <cstdlib>

class TProc
{
private:
	double procRate;
	TQueue<size_t> jobs;
	size_t jobsDone;
	size_t overflowTimes;
	size_t noJobsTimes;
public:
	TProc(double rate, size_t maxJobs);
	double GetRate() const;
	bool IsProcBusy() const;
	bool IsProcFull() const;
	size_t RunNewJob(size_t jobId);
	size_t DoJob();
	size_t GetJobsDone() const;
	size_t GetOverflowTimes() const;
	size_t GetNoJobsTimes() const;
};

