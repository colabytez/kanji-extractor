#pragma execution_character_set( "utf-8" )
#include <iostream>
#include <clocale>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <string>
#include <io.h>
using namespace std;

#define KANJI_MIN 0x4E00
#define KANJI_MAX 0x9FAF

union pools {
    struct kanjipool {
    public:
        std::wstring kanjipool[4096];
    };
};

pools::kanjipool kanjilexer(std::wstring kanjilines) {

    pools::kanjipool kanjipool;

    int iterator = 0;
    int kanjiindex = 0;
    int wordindex = 0;
    int comboiterator = 0;

    for (iterator = 0; kanjilines[iterator] != L'\0'; iterator++)
    {
        // Check for a kanji, if we get a kaji, store it in kanjipool.
        if (kanjilines[iterator] > KANJI_MIN && kanjilines[iterator] < KANJI_MAX)
        {
            if (kanjilines[iterator] > KANJI_MIN && kanjilines[iterator] < KANJI_MAX) {
                while (kanjilines[iterator] > KANJI_MIN && kanjilines[iterator] < KANJI_MAX) {
                    kanjipool.kanjipool[kanjiindex] += kanjilines[iterator];
                    iterator++;
                }
                kanjiindex++;
            }
            else {
                kanjipool.kanjipool[kanjiindex] += kanjilines[iterator];
                kanjiindex++;
            }
        }
    }

    return kanjipool;
}

void printkanji(pools::kanjipool kanjiobj) {

    int iterator = 0;

    for (iterator = 0; kanjiobj.kanjipool[iterator] != L"\0"; iterator++)
    {
        std::wcout << iterator + 1 << L": " << kanjiobj.kanjipool[iterator] << std::endl;
    }
}

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "ja_JP.UTF-8");

    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    std::wstring filename;
    
    if (argc == 1) {
        std::wcout << L"Enter the filename: ";
        std::wcin >> filename;

        std::wfstream kanjifile(filename);

        kanjifile.imbue(std::locale("ja_JP.UTF-8"));

        std::wstring kanjilines;

        std::wstring line;
        for (int iterator = 0; std::getline(kanjifile, line); iterator++) {
            kanjilines += line;
        }

        pools::kanjipool kanjiobj = kanjilexer(kanjilines);

        printkanji(kanjiobj);

        system("pause");
    }

    else if (argc == 2) {
        char*(filename) = argv[1];

        std::wfstream kanjifile(filename);

        kanjifile.imbue(std::locale("ja_JP.UTF-8"));

        std::wstring kanjilines;

        std::wstring line;
        for (int iterator = 0; std::getline(kanjifile, line); iterator++) {
            kanjilines += line;
        }

        pools::kanjipool kanjiobj = kanjilexer(kanjilines);

        printkanji(kanjiobj);

        system("pause");
    }

    else if (argc > 2) {
        std::wcout << L"Too many arguments..." << std::endl;
        return 1;
    }

    else {
        std::wcout << L"Something went wrong..." << std::endl;
        return 1;
    }

    return 0;
}