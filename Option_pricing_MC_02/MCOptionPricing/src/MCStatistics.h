#ifndef MCSTATISTICS_H
#define MCSTATISTICS_H

#include <vector>

class StatisticsMC {
public:
    StatisticsMC() {}
    virtual void DumpOneResult(double result) = 0;
    virtual std::vector<std::vector<double>> GetResultsSoFar() const = 0;
    virtual StatisticsMC* clone() const = 0;
    virtual ~StatisticsMC() {};
    virtual void reset() = 0;
};

class StatisticsMeanWithConf : public StatisticsMC {
public:
    StatisticsMeanWithConf(double alpha);
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double>> GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;
    virtual void reset();

private:
    double RunningSum;
    double RunningSum2;
    unsigned long PathsDone;
    double alpha;
};

#endif
