#include <iostream>
#include <opencv2\opencv.hpp>
#include <fstream>

#include "zcore\zcore.h"
#include "zimgproc\zimgproc.h"
#include "zimgproc\transform.h"
#include "zgui\zgui.h"
#include "zcore\debug.h"

int main(int argc, char *argv[])
{
    z::Matrix dft_dst_res(4, 8, 2);
    z::Matrix idft_dst_res(4, 8, 2);
    z::Matrix fft_dst_res(4, 8, 2);
    z::Matrix ifft_dst_res(4, 8, 2);
    z::Matrix dft_dst, idft_dst, fft_dst, ifft_dst;

    z::Matrix test(4, 8);
    test = {
        0, 1, 2, 3, 4, 5, 6, 7,
        1, 2, 3, 4, 5, 6, 7, 0,
        2, 3, 4, 5, 6, 7, 0, 1,
        3, 4, 5, 6, 7, 0, 1, 2
    };
    z::Matrix dft_test = test.clone();

    // dft and test
    z::dft(dft_test, dft_dst);
    dft_dst_res = {
        112, 0, -27.3137, 2.32703e-13, 8.26006e-14, 8.34888e-14, -4.68629, 2.05169e-13, 0, 1.67591e-13, -4.68629, 3.78364e-13, -2.01617e-13, 2.52243e-13, -27.3137, 1.60938e-12,
        1.93808e-13, 1.95399e-13, 19.3137, 19.3137, -16, 16, -8, -8, -8.34269e-14, -2.84217e-14, -3.31371, -3.31371, -4.79616e-14, -1.19904e-13, -8, -8,
        0, 3.91046e-13, 2.05169e-13, 11.3137, -8.34888e-14, -2.88658e-14, 4.56524e-13, 11.3137, -16, 7.82092e-13, -6.8745e-13, -11.3137, 4.9738e-14, -8.34888e-14, -7.30083e-13, -11.3137,
        -5.84978e-13, 5.86198e-13, -8, 8, -5.55112e-14, -1.12799e-13, -3.31371, 3.31371, 2.80531e-14, -8.39329e-14, -8, 8, -16, -16, 19.3137, -19.3137
    };
    for (size_t i = 0;i < dft_dst_res.size(); ++i)
        if (!dequ(dft_dst_res.data[i] - dft_dst.data[i]))
            exit(-1);

    // idft and test
    z::idft(dft_dst, idft_dst);
    idft_dst_res = {
        -6.66134e-16, -7.77156e-16, 1, 1.22125e-15, 2, -4.60743e-15, 3, -4.77396e-15, 4, -3.21965e-15, 5, 6.66134e-16, 6, 4.88498e-15, 7, -1.9984e-15,
        1, -1.9984e-15, 2, 1.44329e-15, 3, -2.16493e-15, 4, 2.22045e-16, 5, -7.21645e-16, 6, -1.9984e-15, 7, 1.55431e-15, -1.33227e-15, -1.9984e-15,
        2, -7.77156e-16, 3, 8.32667e-16, 4, -1.9984e-15, 5, -1.22125e-15, 6, -3.88578e-16, 7, 1.77636e-15, 3.10862e-15, 3.10862e-15, 1, 2.9976e-15,
        3, 4.996e-16, 4, 3.33067e-16, 5, -1.55431e-15, 6, 6.10623e-16, 7, -5.55112e-17, -3.9968e-15, 3.88578e-15, 1, 1.77636e-15, 2, 7.10543e-15
    };
    for (size_t i = 0;i < idft_dst_res.size(); ++i)
        if (!dequ(idft_dst_res.data[i] - idft_dst.data[i]))
            exit(-1);

    // fft and test
    z::fft(test, fft_dst);
    fft_dst_res = {
        112, 0, -27.3137, 4.08562e-14, 0, 0, -4.68629, -7.81597e-14, 0, 0, -4.68629, -4.08562e-14, 0, 0, -27.3137, 7.81597e-14,
        0, 0, 19.3137, 19.3137, -16, 16, -8, -8, 0, 0, -3.31371, -3.31371, 0, -5.50671e-14, -8, -8,
        0, 0, 3.90799e-14, 11.3137, 0, 0, 8.03801e-14, 11.3137, -16, 0, -3.9968e-14, -11.3137, 0, 0, -7.99361e-14, -11.3137,
        0, 0, -8, 8, 0, -5.68434e-14, -3.31371, 3.31371, 0, 0, -8, 8, -16, -16, 19.3137, -19.3137
    };
    for (size_t i = 0;i < fft_dst_res.size(); ++i)
        if (!dequ(fft_dst_res.data[i] - fft_dst.data[i]))
            exit(-1);

    // ifft and test
    z::ifft(fft_dst, ifft_dst);
    ifft_dst_res = {
        0, 1.11022e-16, 1, 0, 2, 2.91434e-16, 3, 1.11022e-16, 4, -1.66533e-16, 5, 0, 6, -1.80411e-16, 7, -1.11022e-16,
        1, 5.72119e-18, 2, -2.71835e-16, 3, 2.69399e-16, 4, 1.72255e-16, 5, 5.72119e-18, 6, 1.4937e-16, 7, -2.2533e-16, 1.11022e-16, 6.12323e-17,
        64, -3.55271e-15, 96, 0, 128, 2.22045e-15, 160, -3.55271e-15, 192, 5.32907e-15, 224, 0, 0, -5.77316e-15, 32, 3.55271e-15,
        96, -1.83078e-16, 128, 8.69871e-15, 160, 8.25462e-15, 192, -5.51215e-15, 224, -1.83078e-16, 0, -4.77984e-15, 32, -9.66482e-15, 64, -1.95943e-15
    };
    for (size_t i = 0;i < ifft_dst.size(); ++i)
        if (!dequ(ifft_dst.data[i] - ifft_dst_res.data[i]))
            exit(-1);

    return 0;
}