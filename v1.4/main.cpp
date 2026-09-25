#include <iostream>
#include <cstdio>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <cstdint>
#include <string>
#include "../lib/forprint.h"
//#include "../lib/last_session.h"  
using namespace std;

void clear_input_buffer() {
    int32_t character;
    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

int main() {
    forprint();
    cout << flush;
    cout << "Welcome to the Pomodoro Timer!\n" << flush;
    cout << "Input accordingly.\n" << flush;
    int32_t minutes = 0;
    int32_t break_seconds = 0;
    int32_t long_break_seconds = 0;
    int32_t session_seconds = 0;
    int32_t is_long_break = 0;
    int32_t long_break_interval = 0; // Long break every 2 sessions
    int32_t long_break_counter = 0;
    int32_t session_count = 0;
    int32_t break_minutes = 0;
    int32_t long_break_minutes = 0;
    int32_t sessions = 0;
    int32_t current_break_minutes = 0;
    int32_t seconds = 0;
    int32_t elapsed_seconds = 0;
    int32_t length_progress = 0;
    int32_t progress_percent = 0;
    int32_t last_reminder_seconds = -1;
    int32_t reminder_minutes = 0;
    int32_t reminder_seconds = 0;
    int32_t break_elapsed = 0;
    int32_t break_length_progress = 0;
    int32_t break_progress_percent = 0;
    int32_t j = 0;
    int32_t session = 0;
    char hoge = 'n';
    time_t start_time = 0;
    time_t current_time = 0;
    time_t break_start = 0;
    time_t break_current = 0;
    const int32_t gauge_width = 32;
    const int32_t percent_unit = 100;
    cout << "Enter work time: " << flush;
    cin >> minutes;
    if (minutes <= 0) {
        cout << "Work time ? : " << flush;
        return 1;
    }

    cout << "Enter short break time: " << flush;
    cin >> break_minutes;
    if (break_minutes <= 0) {
        cout << "Short break ? : " << flush;
        return 1;
    }
    break_seconds = break_minutes * 60;

    cout << "Enter long break time: " << flush;
    cin >> long_break_minutes;
    if (long_break_minutes <= 0) {
        cout << "Long break ? : " << flush;
        return 1;
    }
    long_break_seconds = long_break_minutes * 60;

    cout << "Enter sessions : " << flush;
    cin >> sessions;
    if (sessions <= 0) {
        cout << "Enter sessions : " << flush;
        return 1;
    }
    cout << "Long interval spacing(何回に一回長い休憩を取るか): " << flush;
  cin >> long_break_interval;
  if (long_break_interval <= 0) {
      cout << "Long interval spacing ? : " << flush;
      return 1;
  }
    cout << "Reminder interval: " << flush;
    cin >> reminder_minutes;
    if (reminder_minutes <= 0) {
        cout << "Reminder interval ? (何分に一回リマインダーを表示するか): " << flush;
        return 1;
    }
    reminder_seconds = reminder_minutes * 60;
    forprint();
    clear_input_buffer(); 
    for (session = 1; session <= sessions; session++) {
        // Start reminder timing from zero for every work session.
        last_reminder_seconds = -1;
        cout << "\n=== Session " << session << "/" << sessions << " ===\n" << flush;
        cout << "Pomodoro timer started for " << minutes << " minutes.\n" << flush;
        session_seconds = minutes * 60;
        seconds = session_seconds;
        start_time = time(NULL);
        while (true) {
            current_time = time(NULL);
            elapsed_seconds = static_cast<int32_t>(difftime(current_time, start_time));
            length_progress = (elapsed_seconds * gauge_width) / seconds;
            if (length_progress > gauge_width) length_progress = gauge_width;
            if (elapsed_seconds >= last_reminder_seconds + (reminder_seconds)) {// reminder_minutes分ごとにリマインダーを表示
                last_reminder_seconds = (int)elapsed_seconds;
                thread([] {
                    // Force-kill any leftover instance from a previous
                    // reminder before starting a new one, otherwise a
                    // lingering process/IPC socket can prevent aki.mp4
                    // from opening again on later sessions.
                    system("pkill -9 -f '[a]ki.mp4' 2>/dev/null");
                    system("mpv ../media/aki.mp4 &");
                    this_thread::sleep_for(chrono::seconds(60));
                    //system("pkill -f ../media/reminder.txt"); // Close reminder.t
                    system("mousepad ../media/reminder.txt &");
                    // Avoid matching the pkill command itself, so the next
                    // reminder can start aki.mp4 normally.
                    system("pkill -9 -f '[a]ki.mp4'"); // Close the video
                    system("pkill -9 -f '../media/reminder.txt'"); // Close the reminder text file
                }).detach();//detachとはスレッドをバックグラウンドで実行させ、メインスレッドから切り離すことを意味します。
            }

            cout << "\rWork Time - [";
            // 画面描写：進捗バーの経過部分を「#」で表示
            for(int64_t j = 0; j < length_progress; j++) {
                cout << "#";
            }
            for(int32_t j = length_progress; j < gauge_width; j++) {
                cout << " ";
            }
            progress_percent = (elapsed_seconds * percent_unit) / seconds;
            if (progress_percent > percent_unit) progress_percent = percent_unit;
            cout << "] " << progress_percent << "%" << flush;
            sleep(1);

            if (elapsed_seconds >= seconds) {
                cout << "\nSession " << session << "/" << sessions << " - Timer has finished!\n";
                system("mpv --no-terminal ../media/jazz_dj.mp3 >/dev/null 2>&1 &");
                this_thread::sleep_for(chrono::seconds(20));
                system("pkill -f ../media/jazz_dj.mp3"); 
                cout << "Time's up! Take a break.\n";
                forprint();
                cout << flush;
                break;
            }
        }
        long_break_counter++;
        is_long_break = (long_break_counter == long_break_interval);
        current_break_minutes = is_long_break ? long_break_minutes : break_minutes;
        break_seconds = current_break_minutes * 60;
        if (is_long_break) {
            forprint();
            cout << flush;
            cout << "\n=== Long Break Time! ===\n";
            while (hoge == 'y' || hoge == 'Y') {
                system("mpv --no-terminal ../media/rewind.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
                cout << "Stop the audio? (y/n): ";
                cin >> hoge;
                if (hoge == 'y' || hoge == 'Y') {
                    system("pkill -f ../media/rewind.mp3"); // mpv will also be terminated by pkill
                    goto portal1;
                }else if (hoge == 'n' || hoge == 'N') {
                    // Continue playing the audio
                    cout << "Enjoy the audio!\n";
                }
            } // Replace with the path to your audio file
            long_break_counter = 0; // Reset counter
        } else {
            system("mpv --no-terminal ../media/rewind.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
            cout << "\n=== Break Time ===\n";
            this_thread::sleep_for(chrono::seconds(30));
            system("pkill -f ../media/rewind.mp3"); // Stop the audio
            forprint();
            cout << flush;
        }
        portal1:;
        cout << "Break duration: " << current_break_minutes << " minutes\n";
        break_start = time(NULL);

        while (1) {
            break_current = time(NULL);
            break_elapsed = static_cast<int32_t>(difftime(break_current, break_start));
            break_length_progress = (break_elapsed * gauge_width) / break_seconds;
            
            if (break_length_progress > gauge_width) break_length_progress = gauge_width;
            
            cout << "\r" << (is_long_break ? "Long Break" : "Break Time") << " - [";
            // 画面描写:休憩の進捗バーの経過部分を「#」で表示
            for(int32_t j = 0; j < break_length_progress; j++) {
                cout << "#";
            }
            for(int32_t j = break_length_progress; j < gauge_width; j++) {
                cout << " ";
            }
            break_progress_percent = (break_elapsed * percent_unit) / break_seconds;
            if (break_progress_percent > percent_unit) break_progress_percent = percent_unit;
            cout << "] " << break_progress_percent << "%" << flush;
            
            // Avoid busy-waiting and keep the terminal responsive on Linux.
            sleep(1);
            
            if (break_elapsed >= break_seconds) {//breakはlongかshortかに関わらず終了する
                cout << "\n" << (is_long_break ? "Long break" : "Break") << " finished!\n";
                cout << "\a"; // Beep sound
                break;
            }
        }
    }
    cout << "\n\n=== All sessions completed! Great work! ===\n";
    system("vlc --play-and-exit ../media/jazz_dj.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
    std::this_thread::sleep_for(std::chrono::seconds(360));
    system("pkill -f ../media/jazz_dj.mp3"); // Stop the audio
    forprint();
    return 0;
}   