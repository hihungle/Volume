#pragma once
#include <vector>
#include <algorithm> // std::copy, std::fill 사용

static constexpr int MAX_BLOCK = 32;
static constexpr int PAGES_PER_BLOCK = 1024;
static constexpr int DATA_PER_PAGE = 4; // 4 bytes per page

class Flash {
public:
    Flash() : pFlash(MAX_BLOCK, std::vector<std::vector<char>>(PAGES_PER_BLOCK, std::vector<char>(DATA_PER_PAGE, 0))) {}

    bool Program(int block, int page, const char data[DATA_PER_PAGE]) {
        if (block < 0 || block >= MAX_BLOCK || page < 0 || page >= PAGES_PER_BLOCK) {
            return false; // 범위를 벗어나면 실패
        }
        std::copy(data, data + DATA_PER_PAGE, pFlash[block][page].begin());
        return true;
    }

    std::vector<char>& Read(int block, int page) {
        return pFlash[block][page];
    }

    bool Erase(int block) {
        if (block < 0 || block >= MAX_BLOCK) {
            return false; // 유효하지 않은 블록 번호
        }
        for (int page = 0; page < PAGES_PER_BLOCK; ++page) {
            std::fill(pFlash[block][page].begin(), pFlash[block][page].end(), 0);
        }
        return true;
    }

private:
    std::vector<std::vector<std::vector<char>>> pFlash;
};