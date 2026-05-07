#include "Vanilla3.h"

VanillaOption::VanillaOption(const PayOff& ThePayOff_, double Expiry_)
    : Expiry(Expiry_) {
    ThePayOff = ThePayOff_.clone();
}

double VanillaOption::GetExpiry() const {
    return Expiry;
}

double VanillaOption::OptionPayOff(double Spot) const {
    return (*ThePayOff)(Spot);
}
