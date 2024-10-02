#pragma once

#include <conio.h>

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_LEFT 68
#define KEY_RIGHT 67
#define KEY_ENTER 10
#define KEY_BACKSPACE 127

using namespace std;

inline int getArrowKey() {
    int c = getch();
    if (c == 0 || c == 27) {
        const auto something =  getch();
        if (something == 91) {
            return getch();
        }
        return something;
    }

    return c;
}

inline int getNumberInput() {
    int number = 0;
    int c;
    while ((c = getch()) != KEY_ENTER) {
        gotox(40);
        if (c >= '0' && c <= '9') {
            number = number * 10 + c - '0';
            wprintf(L"%hc", char(c));
        } else if (c == KEY_BACKSPACE && number > 0) {
            number /= 10;
            wprintf(L"\b \b");
        }
    }

    return number;
}

inline wstring getInput() {
    wstring input;
    int c;
    while ((c = getch()) != KEY_ENTER) {
        if (c == KEY_BACKSPACE && !input.empty()) {
            input.pop_back();
            wprintf(L"\b \b");
        } else if (c >= 32 && c <= 126) {
            input.push_back(wchar_t(c));
            wprintf(L"%lc", wchar_t(c));
        }
    }

    return input;
}

inline double getDoubleInput() {
    wstring input;
    int c;
    while ((c = getch()) != KEY_ENTER) {
        if (c == KEY_BACKSPACE && !input.empty()) {
            input.pop_back();
            wprintf(L"\b \b");
        } else if ((c >= '0' && c <= '9') || c == '.') {
            input.push_back(wchar_t(c));
            wprintf(L"%lc", wchar_t(c));
        }
    }

    return stod(input);
}