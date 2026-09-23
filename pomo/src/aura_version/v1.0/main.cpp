#include <cstdio>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std;
// Function to clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void forprint() {
    for(int a=0; a<64; a++) {
        printf("=");
    }
}

int main(){
    char hoge[2];
    printf("このプログラムはゆるポモドーロタイマーです。\n");
    printf("通常のタイマーは4セッション1回の長い休憩がありますが、このプログラムでは2セッションごとに長い休憩があります。\n");
    printf("15分ごとに動画とテキストファイルが表示されます。\n");
    cout << "This timer is designed to help you maintain a relaxed pace while staying productive.\n";
    cout << "Work and break sessions will be tracked, and reminders will appear every 15 minutes.\n";
    int minutes;
    printf("Enter work time: ");
    if (scanf("%d", &minutes) != 1 || minutes <= 0) {
        printf("Work time must be a positive number.\n");
        return 1;
    }
    
    int break_minutes;
    printf("Enter short break time: ");
    if (scanf("%d", &break_minutes) != 1 || break_minutes <= 0) {
        printf("Short break time must be a positive number.\n");
        return 1;
    }
    
    int long_break_minutes;
    printf("Enter long break time: ");
    if (scanf("%d", &long_break_minutes) != 1 || long_break_minutes <= 0) {
        printf("Long break time must be a positive number.\n");
        return 1;
    }

    int sessions;
    printf("How many sessions do you want (in number of sessions)? ");
    if (scanf("%d", &sessions) != 1 || sessions <= 0) {
        printf("The number of sessions must be a positive number.\n");
        return 1;
    }
    

    
    clear_input_buffer(); // Clear input buffer after scanf
    
    int long_break_counter = 0;

    for(int session = 1; session <= sessions; session++) {
        printf("\n=== Session %d/%d ===\n", session, sessions);
        printf("Pomodoro timer started for %d minutes.\n", minutes);
        
        // Convert minutes to seconds
        int seconds = minutes * 60;
        
        // Start the timer for THIS session
        time_t start_time = time(NULL);
        
        // Work timer
        int last_reminder_seconds = -1;
        while (1) {
            // Calculate elapsed time
            time_t current_time = time(NULL);
            double elapsed_seconds = difftime(current_time, start_time);
            int progress = (int)((elapsed_seconds / seconds) * 100);
            
            if (progress > 100) progress = 100;
            
            printf("\rWork Time - [");
            for(int j = 0; j < progress; j++) {
                printf("#");
                //15分間隔で、何も焦ることはないこと、姿勢を正すこと、ACTの今ここをリマンドと、朝起きたときのメモ蝶を思い出すことと、人生は長距離走であることと、このタイマーは全然まったりやりましょう的なことをコメントすること。
                /*if (j % (15 * 60) == 0) { // Every 15 minutes
                    std::cout << "Don't rush\n"
                         << "Correct your posture\n"
                         << "Remember the ACT 'here and now'\n"
                         << "Recall your morning notes\n"
                         << "Life is a long-distance run\n"
                         << "Take it easy with this timer\n"
                         << "Rest your arms\n";
                         // Run VLC in the background so the work timer keeps running.
                         // VLC exits automatically when the video finishes.
                         system("vlc /home/emo/git/git_win/src/aki_realizing_his_life_span.mp4 >/dev/null 2>&1 &"); // Play reminder video.
                }*/
            if (elapsed_seconds >= last_reminder_seconds + (15 * 60)) { // Every 15 minutes
                last_reminder_seconds = (int)elapsed_seconds;
                    //forprint();
                    std::cout << "\n";
                    system("mousepad reminder.txt >/dev/null 2>&1 &");
                    // VLC must run in the background. Without '&', system()
                    // waits for VLC to exit and never reaches the 35-second wait.
                    system("vlc --play-and-exit /home/emo/git/git_win/src/aki_realizing_his_life_span.mp4 >/dev/null 2>&1 &");
                    // 35秒経過後にreminder.txtとmp4を閉じる
                    std::this_thread::sleep_for(std::chrono::seconds(35));
                    system("pkill -f reminder.txt"); // Close reminder.txt
                    system("pkill -f aki_realizing_his_life_span.mp4"); // Close the video
                    break;
                }
            }
            for(int j = progress; j < 100; j++) {
                printf(" ");
            }
            printf("] %d%%", progress);
            fflush(stdout);
            // Debugging: print elapsed seconds and progress
            // printf("\nElapsed seconds: %.2f, Progress: %d%%\n", elapsed_seconds, progress);
            // Avoid busy-waiting and keep the terminal responsive on Linux.
            sleep(1);

            if (elapsed_seconds >= seconds) {
                printf("\nSession %d/%d - Timer has finished!\n", session, sessions);
                // add this mp3 files in here
                system("vlc /home/emo/git/git_win/src/jazz_dj.mp3"); // Replace with the path to your audio file

                printf("\a"); // Beep sound
                printf("Time's up! Take a break.\n");
                break;
            }
        }
    
        // Decide break type
        long_break_counter++;
        int is_long_break = (long_break_counter == 2); // Long break every 2 sessions
        
        int current_break_minutes = is_long_break ? long_break_minutes : break_minutes;
        int break_seconds = current_break_minutes * 60;
        
        if (is_long_break) {
            printf("\n=== Long Break Time! ===\n");
            while (hoge[0] == 'y' || hoge[0] == 'Y') {
                system("vlc /home/emo/git/git_win/src/jazz_dj.mp3"); // Replace with the path to your audio file
                cout << "Stop the audio? (y/n): ";
                cin >> hoge;
                if (hoge[0] == 'y' || hoge[0] == 'Y') {
                    goto portal1;
                }else if (hoge[0] == 'n' || hoge[0] == 'N') {
                    // Continue playing the audio
                    cout << "Enjoy the audio!\n";
                }
            } // Replace with the path to your audio file
            long_break_counter = 0; // Reset counter
        } else {
            system("vlc /home/emo/git/git_win/src/jazz_dj.mp3"); // Replace with the path to your audio file
            printf("\n=== Break Time ===\n");
        }
        portal1:;

        printf("Break duration: %d minutes\n", current_break_minutes);
        
        time_t break_start = time(NULL);
        
        while (1) {
            time_t break_current = time(NULL);
            double break_elapsed = difftime(break_current, break_start);
            int break_progress = (int)((break_elapsed / break_seconds) * 100);
            
            if (break_progress > 100) break_progress = 100;
            
            printf("\r%s - [", is_long_break ? "Long Break" : "Break Time");
            for(int j = 0; j < break_progress; j++) {
                printf("#");
            }
            for(int j = break_progress; j < 100; j++) {
                printf(" ");
            }
            printf("] %d%%", break_progress);
            fflush(stdout);

            // Avoid busy-waiting and keep the terminal responsive on Linux.
            sleep(1);
            
            if (break_elapsed >= break_seconds) {
                printf("\n%s finished!\n", is_long_break ? "Long break" : "Break");
                printf("\a"); // Beep sound
                system("vlc /home/emo/git/git_win/src/jazz_dj.mp3"); // Replace with the path to your audio file
                
                break;
            }
        }
    }
    
    printf("\n\n=== All sessions completed! Great work! ===\n");
    
    return 0;
}