#include "TMath.h"
#include <iostream>
void solidangle()
{
    double sum = 0;
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    double delta = 1;
    for (double x1 = 0; x1 < 49.5; x1 += delta)
        for (double y1 = 0; y1 < 49.5; y1 += delta)
            for (double x2 = 0; x2 < 49.5; x2 += delta)
                for (double y2 = 0; y2 < 49.5; y2 += delta)
                    sum += 38 * TMath::Power((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + 38 * 38, -1.5) * delta * delta;

    std::cout << "solidangle: " << sum / 49.5 / 49.5 << '\n'
              << "eff: " << 100 * sum / 49.5 / 49.5 / 4 / 3.1415 << "%" << std::endl;
}
