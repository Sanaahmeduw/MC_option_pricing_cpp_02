#include "Normals.h"
#include <cmath>

// This is the Beasley-Springer/Moro algorithm for approximating the inverse CDF of the standard normal distribution
double InverseCumulativeNormal(double u) {
    static double a[4] = { 2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637 };
    static double b[4] = { -8.4735109309, 23.08336743743, -21.06224101826, 3.13082909833 };
    static double c[9] = { 0.3374754822726147, 0.9761690190917186, 0.1607979714918209, 0.0276438810333863,
        0.0038405729373609, 0.0003951896511919, 0.0000321767881768, 0.0000002888167364, 0.0000003960315187 };
    
    if (u <= 0.0 || u >= 1.0) {
        throw("Argument out of range.");
    }

    double x = u - 0.5;
    double r;

    if (fabs(x) < 0.42) {
        r = x * x;
        r = x * (((a[3] * r + a[2]) * r + a[1]) * r + a[0]) / ((((b[3] * r + b[2]) * r + b[1]) * r + b[0]) * r + 1.0);
        return r;
    }

    r = u;
    if (x > 0.0) r = 1.0 - u;
    r = log(-log(r));
    r = c[0] + r * (c[1] + r * (c[2] + r * (c[3] + r * (c[4] + r * (c[5] + r * (c[6] + r * (c[7] + r * c[8])))))));
    
    if (x < 0.0) r = -r;
    
    return r;
}

double CumulativeNormal(double x) {
    static double a1 = 0.254829592;
    static double a2 = -0.284496736;
    static double a3 = 1.421413741;
    static double a4 = -1.453152027;
    static double a5 = 1.061405429;
    static double p = 0.3275911;

    int sign = 1;
    if (x < 0) sign = -1;
    x = fabs(x) / sqrt(2.0);

    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return 0.5 * (1.0 + sign * y);
}
