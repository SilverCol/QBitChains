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
#include <list>
#include "Suzuki4.h"
#include "Suzuki2.h"
#include "Trotter.h"

namespace
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<double> distribution (0.0,1.0);

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

void addRandomStates(std::list<qState>& target, size_t states, size_t size)
{
    for (size_t n = 0; n < states; ++n)
    {
        std::cout << "Creating state #" << n << std::endl;
        qState newState;
        fillRandomState(newState, size);
        std::cout << "Norm: " << absSquare(newState) << std::endl;
        target.push_front(newState);
    }
}

void makeFreeEnergy
(std::vector<double>& target, std::list<qState>& states, size_t N, size_t M, size_t steps, Propagator* propagator)
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

    double step = 2 * propagator->step() * steps;
    for (size_t i = 0; i < M; ++i)
    {
        double beta = (i+1) * step;
        target.push_back(beta);

        double mean = std::accumulate(results[i].begin(), results[i].end(), 0.0) / results[i].size();
        std::cout << "Mean: " << mean << std::endl;
        target.push_back(mean);

        std::vector<double> deviations(results[i].size());
        std::transform(results[i].begin(), results[i].end(), deviations.begin(),
                [mean](double x){return x - mean;});
        double stdDev = std::inner_product(deviations.begin(), deviations.end(), deviations.begin(), 0.0);
        stdDev = std::sqrt(stdDev / (results[i].size() - 1));
        target.push_back(stdDev);
    }
}

void makeLocalSpinCorrelation
(std::vector<double>& target, std::list<qState>& states, size_t j, size_t N, size_t M, size_t steps, Propagator* propagator)
{
    std::vector<std::vector<double> > results;
    size_t n = 0;
    for (qState& state : states)
    {
        std::cout << "Propagating random state #" << n << std::endl;

        qState xState;
        // TODO: this function was left unfinished

        for (size_t i = 0; i < M; ++i)
        {
            if (n == 0) results.emplace_back();
            propagator->propagate(state, N, steps);
            results[i].push_back(absSquare(state));
        }
        ++n;
    }
}

#endif //VAJA_II_2_EXPERIMENTS_HPP
