//
// Created by mitja on 23.3.2019.
//

#ifndef VAJA_II_2_SUZUKI4_H
#define VAJA_II_2_SUZUKI4_H


#include "Propagator.h"

class Suzuki4: public Propagator
{
public:
    explicit Suzuki4(std::complex<double> z);
private:
    void step(qState& state, size_t N) override;
    std::vector<std::complex<double> > m_gate;
};


#endif //VAJA_II_2_SUZUKI4_H
