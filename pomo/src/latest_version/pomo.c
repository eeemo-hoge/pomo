#include <stdio.h>
#include <time.h>
#include <unistd.h>   // usleepのために追加(Linux/Mac用)

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void run_timer(const char* label, int total_seconds) {
    time_t start_time = time(NULL);
    int last_progress = -1;
    while (1) {
        time_t current_time = time(NULL);
        double elapsed_seconds = difftime(current_time, start_time);
        int progress = (int)((elapsed_seconds / total_seconds) * 100);
        if (progress > 100) progress = 100;
        // 進捗が変わった時だけ描画する
        if (progress != last_progress) {
            printf("\r%s - [", label);
            for (int j = 0; j < progress; j++) printf("#");
            for (int j = progress; j < 100; j++) printf(" ");
            printf("] %d%%", progress);
            fflush(stdout);
            last_progress = progress;
        }
        if (elapsed_seconds >= total_seconds) {
            printf("\n%s finished!\n", label);
            printf("\a");
            break;
        }
        usleep(200 * 1000); // 200ms分待つ。usecs単位なので1000倍する
    }
}

int main()
{
    char input;
    int minutes;
    printf("=== welcome pomo timer ===\n");
    printf("Sometimes this program is glitching.\n");
    printf("How many minutes ? : ");
    scanf("%d", &minutes);
    int break_minutes;
    printf("How many minutes for the break? : ");
    scanf("%d", &break_minutes);
    int long_break_minutes;
    printf("How many minutes for the long break? : ");
    scanf("%d", &long_break_minutes);
    int sessions;
    printf("How many sessions? : ");
    scanf("%d", &sessions);
 
    clear_input_buffer();
    int long_break_counter = 0;
    for (int session = 1; session <= sessions; session++) {
        printf("\n=== Session %d/%d ===\n", session, sessions);
        printf("Started for %d minutes.\n", minutes);
        char work_label[32];
        snprintf(work_label, sizeof(work_label), "Work Time");
        run_timer(work_label, minutes * 60);
        printf("Session %d/%d - Timer has finished!\n", session, sessions);
        printf("Break.\n");
        long_break_counter++;
        int is_long_break = (long_break_counter == 4);
        int current_break_minutes = is_long_break ? long_break_minutes : break_minutes;
        if (is_long_break) {
            printf("\n=== Long Break ===\n");
            long_break_counter = 0;
        } else {
            printf("\n=== Short Break ===\n");
        }
        printf("Break duration: %d minutes\n", current_break_minutes);

        char break_label[32];
        snprintf(break_label, sizeof(break_label), "Break Time");
        run_timer(break_label, current_break_minutes * 60);
    }
    printf("\n\n======== All sessions completed ===========\n");
    printf("\n\n=== Your dog is always watching you BTW ===\n");
    printf("\n\n======== Do not forget that\n =============\n");
    printf("\n\n========--sesssion %d/%d completed-========\n", sessions, sessions);
    printf("\n\nTo save [s], to show data [d], to exit [e] : \n ");
    scanf(" %c", &input);
    return 0;
}