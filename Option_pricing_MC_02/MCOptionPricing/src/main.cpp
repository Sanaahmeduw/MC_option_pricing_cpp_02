#include <iostream>
#include "SimpleMC8.h"
#include "ParkMiller.h"
#include "Vanilla3.h"
#include "MCStatistics.h"
#include "AntiThetic.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    srand(time(NULL));
    unsigned long baseSeed = rand();

    double Expiry;
    cout << "Enter expiry: ";
    cin >> Expiry;

    double Strike;
    cout << "Enter strike: ";
    cin >> Strike;

    double Spot;
    cout << "Enter spot: ";
    cin >> Spot;

    double Vol;
    cout << "Enter volatility: ";
    cin >> Vol;

    double r;
    cout << "Enter risk-free rate: ";
    cin >> r;

    unsigned long NumberOfPaths;
    cout << "Enter number of paths: ";
    cin >> NumberOfPaths;

    double alpha;
    cout << "Enter alpha (confidence level): ";
    cin >> alpha;

    char optionType;
    cout << "Enter option type (c for call, p for put): ";
    cin >> optionType;

    char useAntithetic;
    cout << "Use antithetic variates? (y/n): ";
    cin >> useAntithetic;

    PayOff* thePayOff;
    if (optionType == 'c' || optionType == 'C') {
        thePayOff = new PayOffCall(Strike);
    } else if (optionType == 'p' || optionType == 'P') {
        thePayOff = new PayOffPut(Strike);
    } else {
        cerr << "Invalid option type." << endl;
        return 1;
    }

    VanillaOption theOption(*thePayOff, Expiry);

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);

    StatisticsMeanWithConf gatherer(alpha);

    RandomParkMiller generator(1, baseSeed);

    if (useAntithetic == 'y' || useAntithetic == 'Y') {
        AntiThetic generator2(generator);
        SimpleMonteCarlo6(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer, generator2);
    } else {
        SimpleMonteCarlo6(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer, generator);
    }

    vector<vector<double>> results = gatherer.GetResultsSoFar();

    cout << "Results for the " << (optionType == 'c' || optionType == 'C' ? "call" : "put") << " option:" << endl;
    cout << "Averaged discounted payoff: " << results[0][0] << endl;
    cout << "Standard deviation of discounted payoffs: " << results[0][1] << endl;
    cout << "Standard deviation of averaged discounted payoffs: " << results[0][2] << endl;
    cout << "Lower " << alpha * 100 << "% confidence limit: " << results[0][3] << endl;
    cout << "Upper " << alpha * 100 << "% confidence limit: " << results[0][4] << endl;

    delete thePayOff;
    return 0;
}
