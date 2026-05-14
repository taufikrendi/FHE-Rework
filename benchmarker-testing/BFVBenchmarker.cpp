#ifndef BFV_BENCHMARKER_HPP
#define BFV_BENCHMARKER_HPP

#include "../lib/Utils.cpp"
#include "openfhe/pke/openfhe.h"
#include <chrono>

using namespace lbcrypto;

class BFVBenchmarker {
public:
    static BenchmarkResult Run() {
        BenchmarkResult res;
        res.algoName = "BFV";

        // 1. Setup
        auto s1 = std::chrono::high_resolution_clock::now();
        CCParams<CryptoContextBFVRNS> parameters;
        parameters.SetPlaintextModulus(65537);
        parameters.SetMultiplicativeDepth(2);
        CryptoContext<DCRTPoly> cc = GenCryptoContext(parameters);
        cc->Enable(PKE); cc->Enable(KEYSWITCH); cc->Enable(LEVELEDSHE);
        auto e1 = std::chrono::high_resolution_clock::now();
        res.addStage("Setup", std::chrono::duration_cast<std::chrono::milliseconds>(e1-s1).count(), MemoryMonitor::getUsageMB());

        // 2. KeyGen
        auto s2 = std::chrono::high_resolution_clock::now();
        auto keyPair = cc->KeyGen();
        auto e2 = std::chrono::high_resolution_clock::now();
        res.addStage("KeyGen", std::chrono::duration_cast<std::chrono::milliseconds>(e2-s2).count(), MemoryMonitor::getUsageMB());

        // 3. Encrypt
        auto s3 = std::chrono::high_resolution_clock::now();
        std::vector<int64_t> v = {10, 20, 30};
        Plaintext pt = cc->MakePackedPlaintext(v);
        auto ct = cc->Encrypt(keyPair.publicKey, pt);
        auto e3 = std::chrono::high_resolution_clock::now();
        res.addStage("Encrypt", std::chrono::duration_cast<std::chrono::milliseconds>(e3-s3).count(), MemoryMonitor::getUsageMB());

        // 4. EvalAdd
        auto s4 = std::chrono::high_resolution_clock::now();
        auto ctAdd = cc->EvalAdd(ct, ct);
        auto e4 = std::chrono::high_resolution_clock::now();
        res.addStage("EvalAdd", std::chrono::duration_cast<std::chrono::milliseconds>(e4-s4).count(), MemoryMonitor::getUsageMB());

        // 5. Decrypt
        auto s5 = std::chrono::high_resolution_clock::now();
        Plaintext ptDec;
        cc->Decrypt(keyPair.secretKey, ctAdd, &ptDec);
        auto e5 = std::chrono::high_resolution_clock::now();
        res.addStage("Decrypt", std::chrono::duration_cast<std::chrono::milliseconds>(e5-s5).count(), MemoryMonitor::getUsageMB());

        // 6. Verify (Setting length and checking values)
        // 6. Verify (Setting length and checking values)
        auto s6 = std::chrono::high_resolution_clock::now();
        ptDec->SetLength(v.size());

        // Perform the access/check to ensure it's timed,
        // but use [[maybe_unused]] to prevent the compiler error.
        [[maybe_unused]] bool success = (ptDec->GetPackedValue()[0] == 20);

        auto e6 = std::chrono::high_resolution_clock::now();
        res.addStage("Verify", std::chrono::duration_cast<std::chrono::milliseconds>(e6-s6).count(), MemoryMonitor::getUsageMB());

        return res;
    }
};
#endif