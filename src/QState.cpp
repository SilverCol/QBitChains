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
