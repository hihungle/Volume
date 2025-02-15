#pragma once
#include <vector>

class Volume {
    public:
    Volume(int _id) {
        id = _id;
    }
    ~Volume() {
        if(pTable != nullptr) {
            delete pTable;
        }
    }

    int* Create(int _size) {
        size = _size;
        if(size > 0 && size < MAX_SIZE ) {
            pTable = new int[size];
        }
        return pTable;        
    }

    void Write(int lpn, int val) {
        if(pTable != nullptr) {
            pTable[lpn] = val;
            writecount++;
        }
    }

    int Read(int lpn) {
        if(pTable != nullptr) {
            readcount++;
            return pTable[lpn];
        }
        return -1;
    }

    int getId() const {
        return id;
    }

    int getWriteCount() const {
        return writecount;
    }

    int getReadCount() const {
        return readcount;
    }

    private:
        const int MAX_SIZE = 100;

        int id { 0 };
        int size { 0 };
        int writecount { 0 };
        int readcount { 0 };

        int* pTable { nullptr };;

};