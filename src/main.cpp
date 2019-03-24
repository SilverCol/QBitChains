#include <gflags/gflags.h>
#include "experiments.hpp"

DEFINE_int32(N, 20, "Number of qbits.");
DEFINE_int32(Np, 100, "Number of random states.");

DEFINE_int32(M, 100, "Number of propagation steps.");
DEFINE_int32(steps, 1, "Number invisible steps inbetween.");
DEFINE_double(z, .03, "Propagation step coefficient.");

DEFINE_string(file, "../data/a.txt", "Path for the output file.");

int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    size_t dimH = (size_t)1 << FLAGS_N;

    std::cout << "Number of qbits: " << FLAGS_N << std::endl;
    std::cout << "Hilbert dimension: " << dimH << std::endl;

    std::list<qState> randomStates;
    std::cout << "Creating " << FLAGS_Np << " random states." << std::endl;
    addRandomStates(randomStates, FLAGS_Np, dimH);
    std::cout << "Generated " << sizeof(std::complex<double>) * randomStates.size() * randomStates.front().size()
    << " bytes of data." << std::endl;

    // TODO: make a switch, make parameters
    std::vector<double> output;
    Suzuki4 propagator(FLAGS_z);
    std::cout << "Calculating free energy." << std::endl;
    makeFreeEnergy(output, randomStates, FLAGS_N, FLAGS_M, FLAGS_steps, &propagator);
    std::cout << "Writting to file: " << FLAGS_file << std::endl;
    writeBinary(output, FLAGS_file);
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout   << "Finished in "
                << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count()
                << "ms" << std::endl;
    return 0;
}