//
// Created by mitja on 23.3.2019.
//

#ifndef VAJA_II_2_SUZUKI4_H
#define VAJA_II_2_SUZUKI4_H


#include "Propagator.h"

class Suzuki4: public Propagator
{
public:
    Suzuki4(std::complex<double> z);
private:
    void step(qState& state) override;
    void update(qState& state, qState::iterator gate, size_t start);
    std::vector<std::complex<double> > m_gate;
};


#endif //VAJA_II_2_SUZUKI4_H
