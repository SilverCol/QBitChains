//
// Created by mitja on 24.3.2019.
//

#ifndef VAJA_II_2_TROTTER_H
#define VAJA_II_2_TROTTER_H


#include "Propagator.h"

class Trotter: public Propagator
{
public:
    explicit Trotter(std::complex<double> z);
private:
    void step(QState& state, size_t N) override;
    std::vector<std::complex<double> > m_gate;
};


#endif //VAJA_II_2_TROTTER_H
