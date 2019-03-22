#include <iostream>

#include <gflags/gflags.h>

DEFINE_int32(N, 20, "Number of qbits.");

int main(int argc, char* argv[])
{

    gflags::ParseCommandLineFlags(&argc, &argv, true);

    std::cout << "Number of qbits: " << FLAGS_N << std::endl;
    return 0;
}