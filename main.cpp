#include <iostream>

#include "Volume.h"

using namespace std;


#include <iostream>
#include "Flash.h"
#include "IO.h"

int main() {
    Flash flash;
    IO io(&flash);
    char data[4] = {'A', 'B', 'C', 'D'};

    for(int lpn = 0; lpn < 100; lpn++ )
    {
        for(int i=0; i<4; i++) {
            // 블록 0, 페이지 0에 데이터 쓰기
           io.WriteUnit(lpn, data[i]);
       }
    }

    for(int lpn = 0; lpn < 100; lpn++) {
        char result = io.ReadUnit(lpn);
        std::cout << result << " "; // 출력: A B C D
        if(lpn % 4 == 0)
            std::cout << endl;
    }

    // 블록 0 지우기
    flash.Erase(0);

    for(int lpn = 0; lpn < 100; lpn++) {
        char result = io.ReadUnit(lpn);
        std::cout << result << " "; // 출력: A B C D
        if(lpn % 4 == 0)
            std::cout << endl;
    }

    return 0;
}