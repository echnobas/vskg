#include <iostream>
#include <random>
#include <stdint.h>

#include "product_key.h"

struct Product {
    uint32_t group;
    size_t cumulative_range;
    const char *pretty;
};

class Random {
private:
    std::random_device device;
    std::mt19937_64 rng;
    std::uniform_int_distribution< std::mt19937_64::result_type > dist;

public:
    Random(std::mt19937_64::result_type low, std::mt19937_64::result_type high)
            : rng(this->device()),
              dist(std::uniform_int_distribution< std::mt19937_64::result_type >(low, high)) {
    }
    std::mt19937_64::result_type operator()() {
        return this->dist(this->rng);
    }
};

int main() {
    const Product CFG[] = { { 4822, "Enterprise 2022", 0x55d4a7f },
                            { 4831, "Professional 2022", 0x68e777f },
                            { 4340, "Enterprise 2019", 0x98967f },
                            { 4353, "Professional 2019", 0x5b8d7f } };
    constexpr size_t CFG_SZ = sizeof(CFG) / sizeof(CFG[0]);

    size_t max_product_sz = std::strlen(CFG[0].pretty);
    for (size_t i = 0; i < CFG_SZ; i++)
        if (std::strlen(CFG[i].pretty) > max_product_sz)
            max_product_sz = std::strlen(CFG[i].pretty);

    for (size_t i = 0; i < 4; i++)
        std::cout << std::left << std::setw(max_product_sz) << CFG[i].pretty << " :: "
                  << ProductKey(CFG[i].group,
                                Random(0, CFG[i].cumulative_range)(),
                                Random(0, 0x1fffffffffffff)(),
                                false,
                                false)
                                        .to_product_key()
                  << "\n";

    return 0;
}
