       // ============================================================
        // shortbreak.h / longbreak.h 共通範囲
        // 休憩時間の計測と進捗表示を担当。
        // 分割時は break_timer() のような共通関数にすると重複を避けられる。
        // ============================================================
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <cstdio>
#include "forprint.h"
using namespace std;
void short_break(time_t break_start, int32_t break_seconds, bool is_long_break) {
        while (1) {
            time_t break_current = time(NULL);
            int32_t break_elapsed = static_cast<int32_t>(difftime(break_current, break_start));
            int32_t break_length_progress = (break_elapsed * 48) / break_seconds;
            
            if (break_length_progress > 48) break_length_progress = 48;
            
            cout << "\r" << (is_long_break ? "Long Break" : "Break Time") << " - [";
            // 画面描写:休憩の進捗バーの経過部分を「#」で表示
            for(int32_t j = 0; j < break_length_progress; j++) {
                cout << "#";
            }
            for(int32_t j = break_length_progress; j < 48; j++) {
                cout << " ";
            }
            int32_t break_progress_percent = (break_elapsed * 100) / break_seconds;
            if (break_progress_percent > 100) break_progress_percent = 100;
            cout << "] " << break_progress_percent << "%" << flush;
            
            // Avoid busy-waiting and keep the terminal responsive on Linux.
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (break_elapsed >= break_seconds) {
                cout << "\n" << (is_long_break ? "Long break" : "Break") << " finished!\n";
                cout << "\a"; // Beep sound
                system("vlc --play-and-exit ../media/dj.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
                std::this_thread::sleep_for(std::chrono::seconds(35));
                system("pkill -f ../media/dj.mp3"); // Stop the audio
                break;
            }
        }
    }
