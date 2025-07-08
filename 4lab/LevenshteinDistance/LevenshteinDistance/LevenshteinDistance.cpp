#define _CRT_SECURE_NO_WARNINGS
#include "Levenshtein.h"
#include "lcs.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono> 
#include <random> 

std::string generate_random_string(int length) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, sizeof(alphabet) - 2);

    std::string result;
    for (int i = 0; i < length; ++i) {
        result += alphabet[dis(gen)];
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int lx = 300; // длина первой строки
    int ly = 200; // длина второй строки
    std::string x = generate_random_string(lx);
    std::string y = generate_random_string(ly);

    std::cout << "Сгенерированная строка x: " << x << std::endl;
    std::cout << "Сгенерированная строка y: " << y << std::endl;

    std::cout << std::endl << "-- расстояние Левенштейна -----" << std::endl;
    std::cout << std::endl << "--длина --- рекурсия(мс) -- дин.програм.(мс) ---" << std::endl;

    for (int i = 8; i < std::min(lx, ly); i++)
    {
        auto start1 = std::chrono::high_resolution_clock::now();
        levenshtein_r(i, x.c_str(), i - 2, y.c_str());
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1).count();

        auto start2 = std::chrono::high_resolution_clock::now();
        levenshtein(i, x.c_str(), i - 2, y.c_str());
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count();

        std::cout << std::right << std::setw(2) << i - 2 << "/" << std::setw(2) << i
            << "        " << std::left << std::setw(10) << duration1
            << "      " << std::setw(10) << duration2 << std::endl;
    }

    char z[100] = "";
    char x1[] = "HRWCYUJ", y1[] = "WLPCAU";

    int l = lcsd(x1, y1, z);
    std::cout << std::endl << "-- наибольшая общая подпоследовательость - LCS(динамическое программирование)" << std::endl;
    std::cout << std::endl << "последовательость X: " << x1;
    std::cout << std::endl << "последовательость Y: " << y1;
    std::cout << std::endl << "                LCS: " << z;
    std::cout << std::endl << "          длина LCS: " << l << std::endl;

    char z2[100] = "";
    char x2[] = "ABCBDABSDMOMSDFCK,SEFцчуыквсманигрнп6ак5в4ууксеманигтшоьщор8н7п6а5в5кеманпигртшоьщллльщоштрнпеXK,SED",
        y2[] = "BDCABACва спмиртолбщошимескчыуксвмнигтьщбдюхдщлш9876ка5вуак6пнргоS:lmclsdomVPloxMC";

    int min_length = std::min(strlen(x2), strlen(y2));

    std::cout << std::endl << "-- Сравнение времени выполнения LCS (рекурсия vs динамическое программирование) --" << std::endl;
    std::cout << std::endl << "Длина | Рекурсия (мкс) | Динамическое программирование (мкс) | Длина LCS" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    for (int i = 1; i <= min_length; ++i) {
        char x_cut[100] = { 0 };
        char y_cut[100] = { 0 };

        strncpy(x_cut, x2, i);
        strncpy(y_cut, y2, i);

        auto start_recursion = std::chrono::high_resolution_clock::now();
        // int l_recursion = lcs(i, x_cut, i, y_cut); // если есть рекурсивная реализация LCS
        auto end_recursion = std::chrono::high_resolution_clock::now();
        auto duration_recursion = std::chrono::duration_cast<std::chrono::microseconds>(end_recursion - start_recursion).count();

        auto start_dp = std::chrono::high_resolution_clock::now();
        int l_dp = lcsd(x_cut, y_cut, z2);
        auto end_dp = std::chrono::high_resolution_clock::now();
        auto duration_dp = std::chrono::duration_cast<std::chrono::microseconds>(end_dp - start_dp).count();

        std::cout << std::right << std::setw(5) << i << " | "
            << std::setw(14) << duration_recursion << " | "
            << std::setw(32) << duration_dp << " | "
            << std::setw(10) << l_dp << std::endl;
    }

    system("pause");
    std::cout << std::endl;

    return 0;
}
