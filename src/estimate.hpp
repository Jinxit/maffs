#pragma once

#include <complex>
#include <cmath>

namespace maffs
{
    // returns (mean, stddev)
    template<class InputIt, class T>
    std::pair<float, float>
    estimate_wrapped_normal_distribution(InputIt first, InputIt last, T min, T max)
    {
        std::complex<T> z;
        T r2_cos{};
        T r2_sin{};
        for (auto it = first; it != last; ++it)
        {
            z += std::exp(std::complex<T>(0, *it));
            r2_cos += std::cos(*it);
            r2_sin += std::sin(*it);
        }
        z /= std::distance(first, last);
        auto r2 = std::pow(r2_cos / std::distance(first, last), 2)
                + std::pow(r2_sin / std::distance(first, last), 2);
        auto variance = std::log(1.0f / r2);

        auto mu = std::log(z).imag();

        return {mu, std::sqrt(variance)};
    }
}
