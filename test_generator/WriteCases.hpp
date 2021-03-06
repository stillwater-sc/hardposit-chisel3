#ifndef WRITECASES_HPP
#define WRITECASES_HPP

#include <cstdio>

namespace testposit {
    using namespace sw::unum;

    template<size_t nbits, size_t es>
    void writeHex_posit(sw::unum::posit <nbits, es> a, char sepChar) {
        fprintf(stdout, "%llx", a);
        if (sepChar) fputc(sepChar, stdout);
    }

    template<size_t nbits, size_t es>
    void writeUnaryTestCase(const posit <nbits, es> &pa, const posit <nbits, es> &pexpected) {
        writeHex_posit(pa, '\n');
        writeHex_posit(pexpected, '\n');
    }

    template<size_t nbits, size_t es>
    void writeBinaryTestCase(const posit <nbits, es> &pa, const posit <nbits, es> &pb, const posit <nbits, es> &pexpected) {
        writeHex_posit(pa, '\n');
        writeHex_posit(pb, '\n');
        writeHex_posit(pexpected, '\n');
    }

    template<size_t nbits, size_t es>
    void writeTernaryTestCase(const posit <nbits, es> &pa, const posit <nbits, es> &pb, const posit <nbits, es> &pc,
                              const posit <nbits, es> &pexpected) {
        writeHex_posit(pa, '\n');
        writeHex_posit(pb, '\n');
        writeHex_posit(pc, '\n');
        writeHex_posit(pexpected, '\n');
    }

    template<size_t nbits, size_t es>
    void writeCompareTestCase(const posit <nbits, es> &pa, const posit <nbits, es> &pb, bool expected) {
        writeHex_posit(pa, '\n');
        writeHex_posit(pb, '\n');
        fprintf(stdout, "%d\n", expected);
    }

    template<size_t nbits, size_t es>
    void writeP2ITestCase(const posit <nbits, es> &pa, int expected) {
        writeHex_posit(pa, '\n');
        fprintf(stdout, "%x\n", expected);
    }

    template<size_t nbits, size_t es>
    void writeP2ITestCase(const posit <nbits, es> &pa, unsigned int expected) {
        writeHex_posit(pa, '\n');
        fprintf(stdout, "%x\n", expected);
    }

    template<size_t nbits, size_t es>
    void writeP2ITestCase(const posit <nbits, es> &pa, long expected) {
        writeHex_posit(pa, '\n');
        fprintf(stdout, "%lx\n", expected);
    }

    template<size_t nbits, size_t es>
    void writeP2ITestCase(const posit <nbits, es> &pa, unsigned long expected) {
        writeHex_posit(pa, '\n');
        fprintf(stdout, "%lx\n", expected);
    }

    template<size_t nbits, size_t es>
    void writeI2PTestCase(int a, const posit <nbits, es> &pa) {
        fprintf(stdout, "%x\n", a);
        writeHex_posit(pa, '\n');
    }

    template<size_t nbits, size_t es>
    void writeI2PTestCase(unsigned int a, const posit <nbits, es> &pa) {
        fprintf(stdout, "%x\n", a);
        writeHex_posit(pa, '\n');
    }

    template<size_t nbits, size_t es>
    void writeI2PTestCase(long a, const posit <nbits, es> &pa) {
        fprintf(stdout, "%lx\n", a);
        writeHex_posit(pa, '\n');
    }

    template<size_t nbits, size_t es>
    void writeI2PTestCase(unsigned long a, const posit <nbits, es> &pa) {
        fprintf(stdout, "%lx\n", a);
        writeHex_posit(pa, '\n');
    }

    template<size_t ibits, size_t ies, size_t obits, size_t oes>
    void writeP2PTestCase(const posit <ibits, ies> &pa, const posit <obits, oes> &pb) {
        writeHex_posit(pa, '\n');
        writeHex_posit(pb, '\n');
    }
}

#endif
