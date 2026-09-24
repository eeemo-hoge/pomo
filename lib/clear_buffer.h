#include <iostream>
using namespace std;

void clear_buffer() {
    int32_t character;
    while ((character = getchar()) != '\n' && character != EOF) {
    }
    return;
}
