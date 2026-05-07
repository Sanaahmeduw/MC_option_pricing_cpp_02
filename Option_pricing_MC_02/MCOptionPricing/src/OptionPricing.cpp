// OptionPricing.cpp

#include <Rcpp.h>
#include "SimpleMC8.h"
#include "AntiThetic.h"
#include "ParkMiller.h"
#include "StatisticsMC.h"
#include "MCStatistics.h"
#include "Vanilla3.h"
#include "Parameters.h"

// [[Rcpp::export]]
double price_option(double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths, double alpha, char optionType, bool use_antithetic) {
  PayOff* thePayOff;
  if (optionType == 'c') {
    thePayOff = new PayOffCall(Strike);
  } else {
    thePayOff = new PayOffPut(Strike);
  }

  VanillaOption theOption(*thePayOff, Expiry);
  ParametersConstant VolParam(Vol);
  ParametersConstant rParam(r);

  StatisticsMCAlpha gatherer(alpha);
  RandomParkMiller generator(1);
  AntiThetic generator2(generator);

  if (use_antithetic) {
    SimpleMonteCarlo6(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer, generator2);
  } else {
    SimpleMonteCarlo6(theOption, Spot, VolParam, rParam, NumberOfPaths, gatherer, generator);
  }

  std::vector<std::vector<double>> results = gatherer.GetResultsSoFar();
  delete thePayOff;
  return results[0][0];  // Return the averaged discounted payoff
}
