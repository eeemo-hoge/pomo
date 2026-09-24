#ifndef LAST_SESSION_H
#define LAST_SESSION_H
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <cstdio>
#include "forprint.h"

using namespace std;
void last_session() {
    cout << "\n\n=== All sessions completed! Great work! ===\n";
    system("vlc --play-and-exit ../media/dj.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("pkill -f ../media/dj.mp3"); // Stop the audio
    forprint();
    cout << flush;
}

#endif // LAST_SESSION_H