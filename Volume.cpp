#include <iostream>

#include "Volume.h"

using namespace std;

int main(int argc, char* argv[]) {

    Volume vol0(0);
    vol0.Create(32);

    for(int i=0; i<32; i++)
    {
        vol0.Write(i,'a'+i);
        char val = vol0.Read(i);
    
        cout << "VolumeID" << vol0.getId() << " Read Data " <<  val << endl;
    }

    return 0;
}