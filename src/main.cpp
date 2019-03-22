#include <gflags/gflags.h>
#include "experiments.hpp"

DEFINE_int32(N, 20, "Number of qbits.");
DEFINE_int32(Np, 100, "Number of random states.");

int main(int argc, char* argv[])
{

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    size_t dimH = (size_t)1 << FLAGS_N;

    std::cout << "Number of qbits: " << FLAGS_N << std::endl;
    std::cout << "Hilbert dimension: " << dimH << std::endl;

    std::vector<qState> randomStates;
    std::cout << "Creating " << FLAGS_Np << " random states." << std::endl;
    addRandomStates(randomStates, FLAGS_Np, dimH);
    std::cout << "Generated " << sizeof(std::complex<double>) * randomStates.size() * randomStates[0].size()
    << " bytes of data." << std::endl;
    return 0;
}