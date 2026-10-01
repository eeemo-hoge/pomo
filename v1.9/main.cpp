#include <iostream>
#include <cstdio>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <cstdint>
#include <string>
#include <atomic>
#include <mutex>
#include <poll.h>
#include <termios.h>
#include "../lib/forprint.h"
//#include "../lib/last_session.h"  
using namespace std;

mutex command_mutex;
char pending_command = '\0';
termios original_terminal_settings{};
atomic<bool> terminal_settings_saved{false};
atomic<bool> input_monitor_running{false};

char take_command() {
    lock_guard<mutex> lock(command_mutex);
    char command = pending_command;
    pending_command = '\0';
    return command;
}



void start_key_monitor() {
    if (isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &original_terminal_settings) == 0) {
        termios settings = original_terminal_settings;
        settings.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
        settings.c_cc[VMIN] = 0;
        settings.c_cc[VTIME] = 0;
        if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == 0)
            terminal_settings_saved = true;
    }
    input_monitor_running = true;
}

void stop_key_monitor() {
    input_monitor_running = false;
    if (terminal_settings_saved) {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
        terminal_settings_saved = false;
    }
}

void show_ascii_art() {
    cout << "\nPress 'b' to begin the break timer.\n" << flush;
    forprint();
    while (true) {
        const char command = take_command();
        if (command == 'b' || command == 'B') {
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void clear_input_buffer() {
    int32_t character;
    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

int main() {
    forprint();
    cout << "Welcome to the Pomodoro Timer!\n" << flush;
    cout << "Current date and time output: " << flush;
    time_t now = time(NULL);
    tm *ltm = localtime(&now);
    int32_t year = 1900 + ltm->tm_year;
    int32_t month = 1 + ltm->tm_mon;
    int32_t day = ltm->tm_mday;
    int32_t hour = ltm->tm_hour;
    int32_t minute = ltm->tm_min;
    //forprint();
    cout << year << "-" << month << "-" << day << " " << hour << ":" << minute << "\n" << flush;
    forprint();
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
    int32_t additional_break_minutes = 0;
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
    int32_t additional_break_seconds = 0;
    int32_t break_length_progress = 0;
    int32_t break_progress_percent = 0;
    int32_t j = 0;
    int32_t session = 0;
    int32_t ad_additional_break = 0;
    int32_t current_additional_break = 0;
    char hoge = 'n';
    time_t start_time = 0;
    time_t current_time = 0;
    time_t break_start = 0;
    time_t break_current = 0;
    const int32_t gauge_width = 32;
    const int32_t percent_unit = 100;
    int8_t counter = 0;
    char quit = '\0';
    // 作業時間を分単位で入力する。入力値は後で秒に変換してタイマーに使う。
    cout << "Enter work time (Recommend 25-90) (minutes): " << flush;
    cin >> minutes;
    // 0以下の作業時間はタイマーとして使えないため、エラーメッセージを表示して終了する。
    if (minutes <= 0) {
        cout << "Work time (minutes) ? : " << flush;
        return 1;
    }

    cout << "Enter short break time (Recommend 5-20) (minutes): " << flush;
    cin >> break_minutes;
    if (break_minutes <= 0) {
        cout << "Short break time (Recommend 5-20) (minutes) ? : " << flush;
        return 1;
    }
    break_seconds = break_minutes * 60;

    cout << "Enter long break time (Recommend 20-60) (minutes): " << flush;
    cin >> long_break_minutes;
    if (long_break_minutes <= 0) {
        cout << "Long break time (minutes) ? : " << flush;
        return 1;
    }
    cout << "Enter additional break time (Recommend 60-90) (minutes): " << flush;
    cin >> additional_break_minutes;
    if (additional_break_minutes <= 0) {
        cout << "Additional break time (minutes) ? : " << flush;
        return 1;
    }
    additional_break_seconds = additional_break_minutes * 60;
    long_break_seconds = long_break_minutes * 60;
    cout << "Enter sessions (Recommended 4-12) (sessions number): " << flush;
    cin >> sessions;
    if(sessions > 12){
        cout << "Wish your health from bottom of my heart .. \n" << flush;
    }
    if (sessions <= 0) {
        cout << "Enter sessions (times) ? : " << flush;
        return 1;
    }
    cout << "Enter long interval spacing (Recommend 2 ~ 5): " << flush;
    cin >> long_break_interval;
    if (long_break_interval <= 0) {
      cout << "Long interval spacing ? : " << flush;
      return 1;
    }
    cout << "Enter reminder interval time (minutes) (Recommend " << minutes - 2 << "): " << flush;
    cin >> reminder_minutes;
    if (reminder_minutes <= 0) {
        cout << "Reminder interval time (minutes) ? : " << flush;
        return 1;
    }
    reminder_seconds = reminder_minutes * 60;
    forprint();
    clear_input_buffer(); 
    start_key_monitor();
    for (session = 1; session <= sessions; session++) {
        // Start reminder timing from zero for every work session.
        last_reminder_seconds = -1;
        cout << "\n========= Session " << session << "/" << sessions << " =========\n" << flush;
        cout << "Pomodoro timer started for " << minutes << " minutes ..\n" << flush;
        cout << "(Soon will continue, this is just a music preview ..)\n" << flush;
        system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &");
        this_thread::sleep_for(chrono::seconds(5));
        system("pkill -f ../media/2am.mp3");
        work_time:
        session_seconds = minutes * 60;
        seconds = session_seconds;
        start_time = time(NULL);
        //ここから〇〇行目までは、進捗バーなどの画面描写の処理が続きます。
        //具体的には、elapsed_secondsを使って進捗を計算し、画面に表示する処理です。
        while (true) {
            current_time = time(NULL);
            elapsed_seconds = static_cast<int32_t>(difftime(current_time, start_time));
            length_progress = (elapsed_seconds * gauge_width) / seconds;
            if (length_progress > gauge_width) length_progress = gauge_width;
            if (elapsed_seconds >= last_reminder_seconds + (reminder_seconds)) {// reminder_minutes分ごとにリマインダーを表示
                last_reminder_seconds = (int)elapsed_seconds;
                thread([] {
                    system("mpv ../media/aki.mp4 &");
                    this_thread::sleep_for(chrono::seconds(60));
                    //system("pkill -f ../media/reminder.txt"); // Close reminder.t
                    system("mousepad ../media/reminder.txt &");
                    // Avoid matching the pkill command itself, so the next
                    // reminder can start aki.mp4 normally.
                    system("pkill -f '[a]ki.mp4'"); // Close the video
                    system("pkill -f '../media/reminder.txt'"); // Close the reminder text file
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
            if (progress_percent > percent_unit) progress_percent = percent_unit;//この書き方は、if文を使って進捗が100%を超えないように制御していることを意味します。
            //if(x>y)x=y;という書き方は、他の書き方をすると、if(
            cout << "] " << progress_percent << "%" << " enter 'b' to break" << flush;
            pollfd input_fd{STDIN_FILENO, POLLIN, 0};//ここから下の処理はユーザーの入力をポーリングして、'b'キーが押されたかどうかを確認する処理です。
            char hhh = '\0';
            if (poll(&input_fd, 1, 1000) > 0 && (input_fd.revents & POLLIN)) {
                if (read(STDIN_FILENO, &hhh, 1) != 1) hhh = '\0';
            }
            if (hhh == 'b' || hhh == 'B') {
                counter++;
                cout << "\nBreak initiated by user.\n";
                goto portal_additional_break;
            }

            if (elapsed_seconds >= seconds) {
                cout << "\nSession " << session << "/" << sessions << " - Timer has finished!\n";
                ++long_break_counter;
                system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &");
                this_thread::sleep_for(chrono::seconds(10));
                system("pkill -f ../media/2am.mp3");
                cout << "Time's up! Take a break.\n";
                forprint();
                cout << flush;
                break;
            }
        }
        portal_additional_break:;
        ad_additional_break = (additional_break_minutes == 0);
        current_additional_break = (counter > 0);

        pollfd work_input_fd{STDIN_FILENO, POLLIN, 0};
        while (true) {
            work_input_fd.revents = 0;
            if (poll(&work_input_fd, 1, 0) <= 0 ||
                !(work_input_fd.revents & POLLIN)) {
                break;
            }

            char work_command = '\0';
            if (read(STDIN_FILENO, &work_command, 1) == 1 &&
                (work_command == 'b' || work_command == 'B')) {
                cout << "\nWork time restarted by user.\n";
                goto work_time;
            }
        }

        if (current_additional_break) {
            cout << "\n========= Additional Break Time! =========\n";
            cout << "Additional break duration: " << additional_break_minutes << " minutes.\n";
            cout << "Additional break time soon will be start .. " << endl;
            cout << flush;
            cout << "(Soon will continue, this is just a music preview ..)\n" << flush;
            system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &");
            this_thread::sleep_for(chrono::seconds(10));
            system("pkill -f ../media/2am.mp3");
            cout << flush;
            break_seconds = additional_break_seconds;
            break_start = time(NULL);
            
            while (1) {
                break_current = time(NULL);
                break_elapsed = static_cast<int32_t>(difftime(break_current, break_start));
                break_length_progress = (break_elapsed * gauge_width) / break_seconds;
                
                if (break_length_progress > gauge_width) break_length_progress = gauge_width;
            
                cout << "\r" << (is_long_break ? "Long Break" :
                              (current_additional_break ? "Additional Break" : "Break Time"))
                  << " - [";
                // 画面描写:休憩の進捗バーの経過部分を「#」で表示
                for(int32_t j = 0; j < break_length_progress; j++) {
                    cout << "#";
                }
                for(int32_t j = break_length_progress; j < gauge_width; j++) {
                    cout << " ";
                }
                break_progress_percent = (break_elapsed * percent_unit) / break_seconds;
                if (break_progress_percent > percent_unit) break_progress_percent = percent_unit;
                 cout << "] " << break_progress_percent << "%"
                     << " enter 'b' to back to Work Time" << flush;
                
                // Avoid busy-waiting and keep the terminal responsive on Linux.
                pollfd break_input_fd{STDIN_FILENO, POLLIN, 0};
                char break_command = '\0';
                if (poll(&break_input_fd, 1, 1000) > 0 &&
                    (break_input_fd.revents & POLLIN)) {
                    if (read(STDIN_FILENO, &break_command, 1) != 1)
                        break_command = '\0';
                }
                // Pressing b during Additional Break immediately returns to Work Time.
                if (current_additional_break &&
                    (break_command == 'b' || break_command == 'B')) {
                    cout << "\nAdditional Break cancelled; returning to Work Time.\n";
                    goto work_time;
                }
                if (break_command == 'b' || break_command == 'B') {
                    cout << "\nLeaving break; returning to Work Time.\n";
                    goto work_time;
                }
                
                if (break_elapsed >= break_seconds) {//breakはlongかshortかに関わらず終了する
                    cout << "\n" << (is_long_break ? "Long Break" :
                    (current_additional_break ? "Additional Break" : "Break Time")) << " finished!\n";
                    system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &");
                    this_thread::sleep_for(chrono::seconds(10));
                    system("pkill -f ../media/2am.mp3"); // Stop the audio
                    break;
                }
            }
            // The additional break has already been handled above.
            counter = 0;
            continue;
        } else {
            cout << "\nNo additional break this time.\n";
        }


        is_long_break = (long_break_counter >= long_break_interval);
        current_break_minutes = is_long_break ? long_break_minutes : break_minutes;
        if (!is_long_break && counter > 0) {
            current_break_minutes = additional_break_minutes;
            cout << "Additional break time: " << additional_break_minutes << " minutes\n";
        }
        break_seconds = current_break_minutes * 60;
        if (is_long_break) {
            forprint();
            cout << flush;
        
            cout << "\n========= Long Break Time! =========\n";
            if(counter > 0) {
                cout << "\nYou have taken " << counter << " additional breaks so far.\n";
            }
            system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &");
            this_thread::sleep_for(chrono::seconds(10));
            system("pkill -f ../media/2am.mp3");
            while (hoge == 'y' || hoge == 'Y') {
               // /system("mpv --no-terminal ../media >/dev/null 2>&1 &"); // Replace with the path to your audio file
                cout << "Stop the audio? (y/n): ";
                cin >> hoge;
                if (hoge == 'y' || hoge == 'Y') {
                 //   system("pkill -f ../media/rewind.mp3"); // mpv will also be terminated by pkill
                    goto portal1;
                }else if (hoge == 'n' || hoge == 'N') {
                    // Continue playing the audio
                    cout << "Enjoy the audio!\n";
                }
            } // Replace with the path to your audio file
            long_break_counter = 0; // Reset counter
        } else if (!current_additional_break) {
            system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
            cout << "\n========= Break Time! =========\n";
            cout << "(Soon will continue, this is just a music preview ..)\n" << flush;
            this_thread::sleep_for(chrono::seconds(10));
            system("pkill -f ../media/2am.mp3"); // Stop the audio
            //forprint();
            cout << flush;
        }
        break_seconds = current_break_minutes * 60;
        portal1:;
        cout << "Break duration: " << current_break_minutes << " minutes\n";
        break_start = time(NULL);
        



        while (1) {
            break_current = time(NULL);
            break_elapsed = static_cast<int32_t>(difftime(break_current, break_start));
            break_length_progress = (break_elapsed * gauge_width) / break_seconds;
            
            if (break_length_progress > gauge_width) break_length_progress = gauge_width;
            
              cout << "\r" << (is_long_break ? "Long Break" :
                              (current_additional_break ? "Additional Break" : "Break Time"))
                  << " - [";
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
            pollfd break_input_fd{STDIN_FILENO, POLLIN, 0};
            char break_command = '\0';
            if (poll(&break_input_fd, 1, 1000) > 0 &&
                (break_input_fd.revents & POLLIN)) {
                if (read(STDIN_FILENO, &break_command, 1) != 1)
                    break_command = '\0';
            }
            // In Additional Break, 'b' immediately starts the next Work Time.
            if (current_additional_break &&
                (break_command == 'b' || break_command == 'B')) {
                cout << "\nLeaving Additional Break; returning to Work Time.\n";
                goto work_time;
            }
            if (break_command == 'b' || break_command == 'B') {
                cout << "\nLeaving break; returning to Work Time.\n";
                goto work_time;
            }
            
            if (break_elapsed >= break_seconds) {//breakはlongかshortかに関わらず終了する
                 cout << "\n" << (is_long_break ? "Long Break" :
                (current_additional_break ? "Additional Break" : "Break Time")) << " finished!\n";
                system("mpv --no-terminal ../media/2am.mp3 >/dev/null 2>&1 &");
                this_thread::sleep_for(chrono::seconds(10));
                system("pkill -f ../media/2am.mp3"); // Stop the audio
                break;
            }
        }
    }
    stop_key_monitor();
    cout << "\n\n========= All sessions completed! Great work! =========\n";
    system("vlc --play-and-exit ../media/jazz_dj.mp3 >/dev/null 2>&1 &"); // Replace with the path to your audio file
    cout << "This BGM will terminate within " << 5 << " seconds ..\n" << flush;
    std::this_thread::sleep_for(std::chrono::seconds(360));
    system("pkill -f ../media/jazz_dj.mp3"); // Stop the audio
    forprint();
    return 0;
}   