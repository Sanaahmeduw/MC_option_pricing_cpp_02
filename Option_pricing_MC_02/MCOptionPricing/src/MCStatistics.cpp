#include "MCStatistics.h"
#include <cmath>

using namespace std;

StatisticsMeanWithConf::StatisticsMeanWithConf(double alpha)
    : RunningSum(0.0), RunningSum2(0.0), PathsDone(0UL), alpha(alpha) {}

void StatisticsMeanWithConf::DumpOneResult(double result) {
    PathsDone++;
    RunningSum += result;
    RunningSum2 += result * result;
}

vector<vector<double>> StatisticsMeanWithConf::GetResultsSoFar() const {
    vector<vector<double>> Results(1);

    Results[0].resize(5);
    double mean = RunningSum / PathsDone;
    double mean2 = RunningSum2 / PathsDone;
    double variance = mean2 - mean * mean;
    double stdDev = sqrt(variance);
    double stdDevMean = stdDev / sqrt(PathsDone);

    double z = 1.96; // for 95% confidence interval
    Results[0][0] = mean;
    Results[0][1] = stdDev;
    Results[0][2] = stdDevMean;
    Results[0][3] = mean - z * stdDevMean;
    Results[0][4] = mean + z * stdDevMean;

    return Results;
}

StatisticsMC* StatisticsMeanWithConf::clone() const {
    return new StatisticsMeanWithConf(*this);
}

void StatisticsMeanWithConf::reset() {
    PathsDone = 0UL;
    RunningSum = 0.0;
    RunningSum2 = 0.0;
}
