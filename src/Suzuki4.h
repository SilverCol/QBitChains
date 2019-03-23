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
    std::vector<std::complex<double> > m_u0;
    std::vector<std::complex<double> > m_u1;
    std::vector<std::complex<double> > m_u2;
    std::vector<std::complex<double> > m_u3;
};


#endif //VAJA_II_2_SUZUKI4_H
