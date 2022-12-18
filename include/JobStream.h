#pragma once
#include <cstdlib>

class TJobStream
{
private:
	double jobIntense;
	size_t lastJobId;
public:
	TJobStream(double jIntens);
	double GetJobIntens() const;
	size_t GetNewJob();
	size_t GetLastJobId() const;
};
