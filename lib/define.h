#ifndef TIMER_SETTINGS_H
#define TIMER_SETTINGS_H
#include <iostream>
#include <cstdint>
using namespace std;
void define(int32_t &minutes, int32_t &break_seconds, int32_t &long_break_seconds, int32_t &session_seconds) {
    minutes = 0;
    break_seconds = 0;
    long_break_seconds = 0;
    session_seconds = 0;
    char hoge = 'n';
    int32_t long_break_counter = 0;
    int32_t last_reminder_seconds = -1;
}

#endif // TIMER_SETTINGS_H