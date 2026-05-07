#include "AntiThetic.h"

AntiThetic::AntiThetic(const RandomBase& innerGenerator)
    : RandomBase(innerGenerator.GetDimensionality()), InnerGenerator(innerGenerator.clone()), OddEven(true), NextVariates(innerGenerator.GetDimensionality()) {}

RandomBase* AntiThetic::clone() const {
    return new AntiThetic(*InnerGenerator);
}

void AntiThetic::GetUniforms(MJArray& variates) {
    if (OddEven) {
        InnerGenerator->GetUniforms(variates);
        for (unsigned long i = 0; i < GetDimensionality(); i++)
            NextVariates[i] = 1.0 - variates[i];
        OddEven = false;
    } else {
        variates = NextVariates;
        OddEven = true;
    }
}

void AntiThetic::Skip(unsigned long numberOfPaths) {
    if (numberOfPaths == 0)
        return;

    if (!OddEven) {
        OddEven = true;
        numberOfPaths--;
    }

    InnerGenerator->Skip(numberOfPaths / 2);

    if (numberOfPaths % 2) {
        MJArray temp(GetDimensionality());
        GetUniforms(temp);
    }
}

void AntiThetic::SetSeed(unsigned long Seed) {
    InnerGenerator->SetSeed(Seed);
    OddEven = true;
}

void AntiThetic::Reset() {
    InnerGenerator->Reset();
    OddEven = true;
}
