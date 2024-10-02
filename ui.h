#pragma once

#include <iostream>
#include <sstream>

constexpr int WIDTH = 81;
constexpr int HEIGHT = 16;


const auto TOP_LEFT = L"┏";
const auto TOP_RIGHT = L"┓";
const auto BOTTOM_LEFT = L"┗";
const auto BOTTOM_RIGHT = L"┛";

const auto TABLE_INTERSECTION = L"╋";
const auto TABLE_LEFT_INTERSECTION = L"┠";
const auto TABLE_TOP_INTERSECTION = L"┳";
const auto TABLE_RIGHT_INTERSECTION = L"┫";
const auto TABLE_BOTTOM_INTERSECTION = L"┻";

const auto HORIZONTAL = L"━";
const auto VERTICAL = L"┃";

void clearScreen() {
    system("clear");
}



wstring getSelectionString(vector<wstring> items, int selected, const wstring &prefixSuffix = L"[]") {
    std::wstringstream ss;
    for (int i = 0; i < items.size(); i++) {
        if (i == selected) {
            ss << prefixSuffix[0] << items[i] << prefixSuffix[1];
        } else {
            ss << " " << items[i];
        }

        ss << " ";
    }

    return ss.str();
}



void printTopBorder() {
    std::wcout << TOP_LEFT;
    for (int i = 0; i < WIDTH - 2; i++) {
        std::wcout << HORIZONTAL;
    }
    std::wcout << TOP_RIGHT;
    std::wcout << std::endl;
}

void printBottomBorder() {
    std::wcout << BOTTOM_LEFT;
    for (int i = 0; i < WIDTH - 2; i++) {
        std::wcout << HORIZONTAL;
    }
    std::wcout << BOTTOM_RIGHT;
    std::wcout << std::endl;
}

void printEmptySpace() {
    std::wcout << VERTICAL;
    for (int i = 0; i < WIDTH - 2; i++) {
        std::wcout << L" ";
    }
    std::wcout << VERTICAL;
    std::wcout << std::endl;
}

void printCenteredText(const std::wstring& text) {
    // print the text centered, taking into account the borders
    // and the width of the text
    const int textWidth = text.length();
    const int leftSpace = (WIDTH - textWidth) / 2;



    std::wcout << VERTICAL;
    for (int i = 0; i < leftSpace - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << text;
    for (int i = 0; i < WIDTH - leftSpace - textWidth - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << VERTICAL;
    std::wcout << std::endl;
}


void drawBorder() {
    printTopBorder();
    for (int i = 0; i < HEIGHT - 2; i++) {
        printEmptySpace();
    }
    printBottomBorder();
}

void printMovementHint() {
    printCenteredText(L"Use arrow keys to move, Enter to select.");
}


void showNotice(const wstring &message) {
    clearScreen();
    printTopBorder();
    printEmptySpace();

    // split the message into multiple lines
    std::wstringstream ss(message);
    std::wstring line;
    while (std::getline(ss, line)) {
        printCenteredText(line);
    }

    printEmptySpace();
    printEmptySpace();
    printCenteredText(L"Press any key to continue...");
    printEmptySpace();
    printBottomBorder();
    getch();
}

void printTable(vector<wstring> headers, vector<vector<wstring>> rows) {
    int availableWidth = WIDTH - 2;
    int columnWidth = availableWidth / headers.size();

    std::wcout << TABLE_LEFT_INTERSECTION;
    for (int i = 0; i < headers.size(); i++) {

        for (int j = 0; j < columnWidth; j++) {
            std::wcout << HORIZONTAL;
        }

        if (i != headers.size() - 1) {
            std::wcout << TABLE_TOP_INTERSECTION;
        }
    }
    std::wcout << TABLE_RIGHT_INTERSECTION;
    std::wcout << std::endl;

    for (int i = 0; i < headers.size(); i++) {
        std::wcout << VERTICAL;
        std::wcout << headers[i];
        for (int j = 0; j < columnWidth - headers[i].length(); j++) {
            std::wcout << L" ";
        }
    }
    std::wcout << VERTICAL;
    std::wcout << std:: endl;
    std::wcout << TABLE_LEFT_INTERSECTION;

    // print bottom table border
    for (int i = 0; i < headers.size(); i++) {
        for (int j = 0; j < columnWidth; j++) {
            std::wcout << HORIZONTAL;
        }

        if (i != headers.size() - 1) {
            std::wcout << TABLE_INTERSECTION;
        }
    }

    std::wcout << VERTICAL;
    std::wcout << std::endl;

    // print the rows
    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            std::wcout << VERTICAL;
            std::wcout << rows[i][j];
            for (int k = 0; k < columnWidth - rows[i][j].length(); k++) {
                std::wcout << L" ";
            }
        }
        std::wcout << VERTICAL;
        std::wcout << std::endl;

        // if not end, print the intersection
        if (i != rows.size() - 1) {
            std::wcout << TABLE_LEFT_INTERSECTION;
            for (int j = 0; j < headers.size(); j++) {
                for (int k = 0; k < columnWidth; k++) {
                    std::wcout << HORIZONTAL;
                }

                if (j != headers.size() - 1) {
                    std::wcout << TABLE_INTERSECTION;
                }
            }
            std::wcout << VERTICAL;
            std::wcout << std::endl;
        } // if last item, print the bottom border
        else {
            std::wcout << TABLE_LEFT_INTERSECTION;
            for (int j = 0; j < headers.size(); j++) {
                for (int k = 0; k < columnWidth; k++) {
                    std::wcout << HORIZONTAL;
                }

                if (j != headers.size() - 1) {
                    std::wcout << TABLE_BOTTOM_INTERSECTION;
                }
            }
            std::wcout << TABLE_RIGHT_INTERSECTION;
            std::wcout << std::endl;
        }
    }


}
