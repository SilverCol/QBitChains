//
// Created by mitja on 23.3.2019.
//

#ifndef VAJA_II_2_PROPAGATOR_H
#define VAJA_II_2_PROPAGATOR_H

#include <complex>
#include <complex>
#include <vector>
#include "QState.h"


class Propagator
{
public:
    explicit Propagator(std::complex<double> z);
    void propagate(QState& state, size_t N, size_t steps);
    inline double step(){return std::abs(m_z);}
protected:
    virtual void step(QState& state, size_t N) = 0;
    void update(QState& state, std::vector<std::complex<double> >::iterator gate, size_t start, size_t N);
    std::complex<double> m_z;
};


#endif //VAJA_II_2_PROPAGATOR_H
