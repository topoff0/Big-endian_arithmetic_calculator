#pragma once

#include "colors.h"

#include <vector>

using std::pair;
using std::vector;

struct menu_item
{
    int id;
    const char *title;
    COLOR clr;
};

inline pair<int, int> menu_min_max_id(const vector<menu_item> &menu)
{
    int min_id = menu[0].id;
    int max_id = menu[0].id;

    for (auto &i : menu)
    {
        if (i.id < min_id)
            min_id = i.id;
        if (i.id > max_id)
            max_id = i.id;
    }

    return {min_id, max_id};
}

static const vector<menu_item> MAIN_MENU = {
    {1, "Начать работу", GREEN},
    {2, "Описание", YELLOW},
    {3, "О диаграмме Хассе", BLUE},
    {4, "Правило '+1' для варианта №33", BLUE},
    {0, "Завершить работу", RED}};

static const vector<menu_item> START_WORK_MENU = {
    {1, "Перейти в калькулятор большой конечной арифметики", GREEN},
    {2, "Вывести таблицу сложения малой конечной арифметики", BLUE},
    {3, "Вывести таблицу умножения малой конечной арифметики", BLUE},
    {4, "Вывести таблицу переноса малой конечной арифметики", BLUE},
    {-1, "Вернуться в главное меню", RED},
    {0, "Завершить работу", RED}};

static const vector<menu_item> CALCULATOR_MENU = {
    {1, "Сложение", YELLOW},
    {2, "Вычитание", YELLOW},
    {3, "Умножение", BLUE},
    {4, "Деление", BLUE},
    {5, "Возведение в степень", PURPLE},
    {-1, "Вернуться в главное меню", RED},
    {0, "Завершить работу", RED}};
