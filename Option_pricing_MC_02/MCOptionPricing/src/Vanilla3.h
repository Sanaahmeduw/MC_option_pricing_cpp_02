#ifndef VANILLA_3_H
#define VANILLA_3_H

#include "PayOff3.h"

class VanillaOption {
public:
    VanillaOption(const PayOff& ThePayOff_, double Expiry_);
    double GetExpiry() const;
    double OptionPayOff(double Spot) const;

private:
    double Expiry;
    PayOff* ThePayOff;
};

#endif
