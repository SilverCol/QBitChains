//
// Created by mitja on 22.3.2019.
//

#ifndef VAJA_II_2_EXPERIMENTS_HPP
#define VAJA_II_2_EXPERIMENTS_HPP

#include <iostream>
#include <complex>
#include <vector>
#include <random>
#include <chrono>

typedef std::vector<std::complex<double> > qState;

void fillRandomState(qState& target, size_t size)
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution (0.0,1.0);

    double norm = 0;
    for (size_t n = 0; n < size; ++n)
    {
        double real = distribution(generator);
        double imag = distribution(generator);
        norm += real * real + imag * imag;
        target.push_back(std::complex<double>(real, imag));
    }

    norm = sqrt(norm);
    std::cout << "To norm: " << norm << std::endl;
    for (auto& element : target)
    {
        element /= norm;
    }
}

void addRandomStates(std::vector<qState>& target, size_t states, size_t size)
{
    for (size_t n = 0; n < states; ++n)
    {
        std::cout << "Creating state #" << n << std::endl;
        qState newState;
        fillRandomState(newState, size);
        target.push_back(newState);
    }
}

#endif //VAJA_II_2_EXPERIMENTS_HPP
