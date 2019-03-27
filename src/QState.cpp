//
// Created by mitja on 25.3.2019.
//

#include "QState.h"

void QState::localSpin(size_t j)
{
    for (size_t n = 0; n < m_coefficients.size(); ++n)
    {
        if ((n>>j)&1) m_coefficients[n] *= -1;
    }
}

void QState::spinFlux()
{
    size_t dimH = m_coefficients.size();
    size_t N = 0;
    while(dimH >>= 1) ++N;

    std::complex<double> multiplier(0, 2);
    std::vector<std::complex<double> > temp(m_coefficients.size(), std::complex<double>(0, 0));
    for (size_t n = 0; n < m_coefficients.size(); ++n)
    {
        for (size_t j = 0; j < N; ++j)
        {
            size_t j1 = 0;
            if (j != N - 1) j1 = j + 1;

            if (((~n >> j)&1)&((n >> j1)&1)) // 01
            {
                size_t m = n ^ (1 << j);
                m ^= 1 << j1;
                temp[n] += m_coefficients[m];
            }
            else if (((n >> j)&1)&((~n >> j1)&1)) // 10
            {
                size_t m = n ^ (1 << j);
                m ^= 1 << j1;
                temp[n] -= m_coefficients[m];
            }
        }
    }
    m_coefficients.swap(temp);
}
