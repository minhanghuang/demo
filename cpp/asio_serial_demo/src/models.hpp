#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

struct DataFrame {
    uint64_t timestamp;
    uint64_t frame_count;
    uint64_t frame_size;
    std::vector<uint8_t> data;
};