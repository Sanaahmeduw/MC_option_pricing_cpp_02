#ifndef ANTITHETIC_H
#define ANTITHETIC_H

#include "Random2.h"

class AntiThetic : public RandomBase {
public:
    AntiThetic(const RandomBase& innerGenerator);

    virtual RandomBase* clone() const;
    virtual void GetUniforms(MJArray& variates);
    virtual void Skip(unsigned long numberOfPaths);
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();

private:
    RandomBase* InnerGenerator;
    bool OddEven;
    MJArray NextVariates;
};

#endif
