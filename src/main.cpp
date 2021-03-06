#include <gflags/gflags.h>
#include "experiments.hpp"

DEFINE_int32(N, 20, "Number of qbits.");
DEFINE_int32(Np, 100, "Number of random states.");

DEFINE_int32(M, 100, "Number of propagation steps.");
DEFINE_int32(steps, 1, "Number invisible steps inbetween.");
DEFINE_double(z, .03, "Propagation step coefficient.");
DEFINE_int32(scheme, 2, "Number of split-step scheme as S{scheme} (eg. 2 for S2).");

DEFINE_string(file, "../data/a.txt", "Path for the output file.");

DEFINE_int32(mode, 0, "Operation mode: 0-phaseSum, 1-localSpin, 2-spinFlux");

DEFINE_int32(j, 0, "Spin index, for local spin correlation");

int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    size_t dimH = (size_t)1 << FLAGS_N;

    std::list<QState> randomStates;
    std::cout << "Creating " << FLAGS_Np << " random states." << std::endl;
    addRandomStates(randomStates, FLAGS_Np, dimH);
    std::cout << "Generated " << sizeof(std::complex<double>) * randomStates.size() * randomStates.front().size()
    << " bytes of data." << std::endl;

    std::complex<double> z = 0;
    if (FLAGS_mode == 0) z = std::complex<double>(-FLAGS_z / 2, 0);
    else if (FLAGS_mode == 1) z = std::complex<double>(0, -FLAGS_z);
    else if (FLAGS_mode == 2) z = std::complex<double>(0, -FLAGS_z);

    Propagator* propagator;
    switch(FLAGS_scheme)
    {
        case 1:
            propagator = new Trotter(z);
            break;
        case 2:
            propagator = new Suzuki2(z);
            break;
        case 4:
            propagator = new Suzuki4(z);
            break;
        default:
            std::cerr << "Invalid scheme." << std::endl;
            return -1;
    }

    std::vector<double> output;
    switch(FLAGS_mode)
    {
        case 0: // Phase sum mode
            std::cout << "Calculating phase sums." << std::endl;
            FLAGS_file.append(std::to_string(FLAGS_N));
            makeFreeEnergy(output, randomStates, FLAGS_N, FLAGS_M, FLAGS_steps, propagator);
            break;
        case 1: // Local spin correlation
            std::cout << "Calculating local spin correlations." << std::endl;
            FLAGS_file.append(std::to_string(FLAGS_N));
            makeLocalSpinCorrelation(output, randomStates, FLAGS_j, FLAGS_N, FLAGS_M, FLAGS_steps, propagator);
            break;
        case 2: // Spin flux correlation
            std::cout << "Calculating spin flux correlations." << std::endl;
            FLAGS_file.append(std::to_string(FLAGS_N));
            makeSpinFluxCorrelation(output, randomStates, FLAGS_N, FLAGS_M, FLAGS_steps, propagator);
            break;
        default:
            std::cerr << "Invalid mode." << std::endl;
            free(propagator);
            return -1;
    }
    FLAGS_file.append(".bin");
    std::cout << "Writting to file: " << FLAGS_file << std::endl;
    writeBinary(output, FLAGS_file);

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout   << "Finished in "
                << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
                << "ms" << std::endl;
    return 0;
}