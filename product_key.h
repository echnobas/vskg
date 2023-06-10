
#include <assert.h>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string>

class ProductKey {
public:
    ProductKey(uint32_t group, uint32_t serial, uint64_t security, bool upgrade, bool extra);
    std::string to_product_key();

private:
    // 20 bits
    uint32_t group;
    // 30 bits
    uint32_t serial;
    // 53 bits
    uint64_t security;
    // 10 bits
    uint16_t checksum;
    // 1 bit
    bool upgrade;
    // < 1 bit
    bool extra;

public:
    static uint32_t hash(__int128_t x);
    static std::string raw_key_to_product_key(__uint128_t raw_key);
};