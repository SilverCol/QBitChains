//
// Created by mitja on 25.3.2019.
//

#ifndef VAJA_II_2_QSTATE_H
#define VAJA_II_2_QSTATE_H

#include <vector>
#include <complex>

class QState
{
public:
    QState() = default;
    QState(const QState&) = default;
    QState(size_t size, std::complex<double> val): m_coefficients(size, val){}
    inline void push_back(std::complex<double> coefficient){m_coefficients.push_back(coefficient);}
    inline size_t size() const {return m_coefficients.size();}
    inline void swap(QState& state){m_coefficients.swap(state.coeffs());}
    inline std::vector<std::complex<double> >& coeffs(){return m_coefficients;}
    inline std::complex<double>& operator[](size_t i){return m_coefficients[i];}
    inline std::complex<double> operator[](size_t i) const {return m_coefficients[i];}
    inline std::complex<double>& back(){return m_coefficients.back();}
    inline std::complex<double> back() const {return m_coefficients.back();}
    inline std::vector<std::complex<double> >::iterator begin(){return m_coefficients.begin();}
    inline std::vector<std::complex<double> >::const_iterator begin() const {return m_coefficients.begin();}
    inline std::vector<std::complex<double> >::iterator end(){return m_coefficients.end();}
    inline std::vector<std::complex<double> >::const_iterator end() const {return m_coefficients.end();}

    void localSpin(size_t j);
    void spinFlux();
private:
    std::vector<std::complex<double> > m_coefficients;
    size_t m_N;
};


#endif //VAJA_II_2_QSTATE_H
