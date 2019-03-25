//
// Created by mitja on 24.3.2019.
//

#ifndef VAJA_II_2_SUZUKI2_H
#define VAJA_II_2_SUZUKI2_H

#include "Propagator.h"

class Suzuki2: public Propagator
{
public:
    Suzuki2(std::complex<double> z);
private:
    void step(QState& state, size_t N) override;
    std::vector<std::complex<double> > m_gate;
};


#endif //VAJA_II_2_SUZUKI2_H
