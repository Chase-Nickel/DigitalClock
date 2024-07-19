#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

// clang-format off
wchar_t digits_10x5[11][5][11] = {
    {
        L"  ██████  ",
        L"██    ▗▘██",
        L"██  ▗▘  ██",
        L"██▗▘    ██",
        L"  ██████  ",
    }, {
        L"   ███    ",
        L"██████    ",
        L"    ██    ",
        L"    ██    ",
        L"██████████",
    }, {
        L" ███████  ",
        L"██     ██ ",
        L"     ██   ",
        L"   ██     ",
        L"██████████",
    }, {
        L"██████    ",
        L"     █▉   ",
        L"██████    ",
        L"     █▉   ",
        L"██████    ",
    }, {
        L"██    ██  ",
        L"██    ██  ",
        L"█████████ ",
        L"      ██  ",
        L"      ██  ",
    }, {
        L"█████████ ",
        L"██        ",
        L"██████    ",
        L"     ███  ",
        L"████████  ",
    }, {
        L" ███████  ",
        L"██        ",
        L"██████    ",
        L"██    ██  ",
        L" ██████   ",
    }, {
        L"██████████",
        L"        ██",
        L"      ██  ",
        L"     ██   ",
        L"     ██   ",
    }, {
        L" ██████   ",
        L"██    ██  ",
        L" ██████   ",
        L"██    ██  ",
        L" ██████   ",
    }, {
        L" ███████  ",
        L"██     ██ ",
        L" ████████ ",
        L"      ██  ",
        L" ██████   ",
    }, {
        L"          ",
        L"    ██    ",
        L"          ",
        L"    ██    ",
        L"          ",
    },
};

// clang-format on

int print_time(struct tm *timeinfo);

int main(void) {
    setlocale(LC_CTYPE, "");
    int tm_sec_last = 0;
    while (1) {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);
        if (timeinfo->tm_sec != tm_sec_last) {
            system("clear");
            print_time(timeinfo);
            tm_sec_last = timeinfo->tm_sec;
        }
    }
}

int print_time(struct tm *timeinfo) {
    char numbuf[9] = {0};
    size_t num_length = 8;
    snprintf(numbuf, 9, "%.2i:%.2i:%.2i", timeinfo->tm_hour, timeinfo->tm_min,
             timeinfo->tm_sec);

    wchar_t *line = malloc(sizeof *line * (num_length * 11 + 1));
    if (!line) {
        return 1;
    }

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < num_length; j++) {
            size_t idx = 0;
            char to_display = numbuf[j];
            if ('0' <= to_display && to_display <= '9') {
                idx = numbuf[j] - '0';
            } else if (to_display == ':') {
                idx = 10;
            } else {
                goto exit;
            }
            wchar_t(*digit_lines)[11] = digits_10x5[idx];
            wchar_t *digit = digit_lines[i];
            memcpy(line + 11 * j, digit, 10 * sizeof(wchar_t));
            line[11 * j + 10] = L' ';
        }
        line[num_length * 11] = 0;
        printf("%ls\n", line);
    }

exit:
    free(line);
    return 0;
}
