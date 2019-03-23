//
// Created by mitja on 23.3.2019.
//

#ifndef VAJA_II_2_PROPAGATOR_H
#define VAJA_II_2_PROPAGATOR_H

#include <complex>
#include <complex>
#include <vector>

typedef std::vector<std::complex<double> > qState;

class Propagator
{
public:
    explicit Propagator(std::complex<double> z);
    void propagate(qState &state, size_t steps);
private:
    virtual void step(qState& state) = 0;
    std::complex<double> m_z;
};


#endif //VAJA_II_2_PROPAGATOR_H
