//
// Created by mitja on 22.3.2019.
//

#ifndef VAJA_II_2_EXPERIMENTS_HPP
#define VAJA_II_2_EXPERIMENTS_HPP

#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>
#include "Suzuki4.h"

namespace
{
    std::complex<double> inner(const qState& state1, const qState& state2)
    {
        std::complex<double> product;
        for (size_t i = 0; i < state1.size(); ++i)
        {
            product += std::conj(state1[i]) * state2[i];
        }
        return product;
    }

    double absSquare(const qState& state)
    {
        double product = 0;
        for (auto& coeff : state)
        {
            product += std::norm(coeff);
        }
        return product;
    }
}

void writeBinary(std::vector<double>& data, const std::string& file)
{
    std::ofstream output(file, std::ios::binary);
    for (double& x : data)
    {
        output.write(reinterpret_cast<char*>(&x), sizeof(x));
    }
    output.close();
}

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
        target.push_back(std::complex<double>(real, imag));
        norm += std::norm(target.back());
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

void makeFreeEnergy
(std::vector<double>& target, std::vector<qState>& states, size_t N, size_t M, size_t steps, Propagator* propagator)
{
    std::vector<std::vector<double> > results;
    size_t n = 0;
    for (qState& state : states)
    {
        std::cout << "Propagating random state #" << n << std::endl;
        for (size_t i = 0; i < M; ++i)
        {
            if (n == 0) results.emplace_back();
            propagator->propagate(state, N, steps);
            results[i].push_back(absSquare(state));
        }
        ++n;
    }

    double step = propagator->step();
    for (size_t i = 0; i < M; ++i)
    {
        double beta = (i+1) * step;
        target.push_back(beta);
        double mean = std::accumulate(results[i].begin(), results[i].end(), 0.0) / results[i].size();
        target.push_back(-std::log(mean) / beta);
        std::vector<double> deviations(results[i].size());
        std::transform(results[i].begin(), results[i].end(), deviations.begin(),
                [mean](double x){return x - mean;});
        double stdDev = std::inner_product(deviations.begin(), deviations.end(), deviations.begin(), 0.0);
        stdDev = std::sqrt(stdDev / (results.size() - 1));
        target.push_back(-stdDev / (beta * mean));
    }
}


#endif //VAJA_II_2_EXPERIMENTS_HPP
