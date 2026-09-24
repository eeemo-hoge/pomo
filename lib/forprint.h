#ifndef FORPRINT_H
#define FORPRINT_H
#include <iostream>
using namespace std;

void forprint() {
    for(int a=0; a<64; a++) {
        printf("=");
    }
    cout << "\n" << flush;  
}

#endif // FORPRINT_H
