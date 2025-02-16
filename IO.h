#pragma once
#include <unordered_map>
#include <vector>
#include <cstring> // memcpy 사용
#include "Flash.h"

class IO {
public:
    IO(Flash* flash) : pFlash(flash), unit(0), block(0), page(0) {}

    bool WriteUnit(int lpn, char data) {
        if (!pFlash) return false; // Flash가 nullptr이면 실패

        pagebuf[unit++] = data;

        if (unit == DATA_PER_PAGE) {
            //std::vector<char> dataVec(pagebuf, pagebuf + DATA_PER_PAGE);
            if (pFlash->Program(block, page, pagebuf)) {
                // PPN(Physical Page Number) 매핑
                int ppn = (block * PAGES_PER_BLOCK + page) * DATA_PER_PAGE + (lpn%DATA_PER_PAGE);
                map[lpn] = ppn;

                unit = 0;
                page++;
                if (page == PAGES_PER_BLOCK) {
                    block++;
                    page = 0;
                }
                if (block == MAX_BLOCK) {
                    return false; // 저장 공간 초과
                }
            }
        }
        
        return true; // 정상적으로 데이터 저장됨
    }

    char ReadUnit(int lpn) {
        if (map.find(lpn) == map.end()) return '\0'; // 존재하지 않는 경우

        int ppn = map[lpn];
        int offset = ppn % DATA_PER_PAGE;
        int page = (ppn / DATA_PER_PAGE) % PAGES_PER_BLOCK;
        int block = (ppn / DATA_PER_PAGE) / PAGES_PER_BLOCK;

        std::vector<char>& data = pFlash->Read(block, page);
        return data[offset];
    }

    bool EraseBlock(int block) {
        return pFlash->Erase(block);
    }

private:
    Flash* pFlash;
    char pagebuf[DATA_PER_PAGE];
    int unit;   // unit index on a page
    int block;  // block index
    int page;   // page offset

    std::unordered_map<int, int> map;  // LPN to PPN 매핑
};