#pragma once
#include <vector>

// === UI ===
#define UI_HEADER_LENGTH 80
#define UI_MENU_LENGTH 40
#define UI_OPERATION_RESULT_LENGTH UI_MENU_LENGTH
#define UI_LIST_LEFT_PADDING 2
#define UI_TABLE_WIDTH 60

// === TEXT Format ===
#define MAX_LINE_LENGTH 70

// === CONSTANT WORDS ===
#define ERROR_WORD "ОШИБКА"

static const std::vector<std::pair<char, char>> rule =
    {
        {'a', 'b'},
        {'b', 'e'},
        {'c', 'd'},
        {'d', 'g'},
        {'e', 'h'},
        {'f', 'a'},
        {'g', 'f'},
        {'h', 'c'},
};

static const char ZERO = rule[0].first;

static const char MAX_VALUE = []
{
    for (auto el : rule)
    {
        if (el.second == ZERO)
            return el.first;
    }
    throw std::runtime_error("Не существует максимального элемента");
}();

static const std::vector<char> elems = []
{
    std::vector<char> v;
    v.reserve(rule.size());
    for (const auto &e : rule)
        v.push_back(e.first);
    return v;
}();

static const int MAX_DIGITS = elems.size();

// === RANDOM ===
// #define IS_RANDOM_USE_SEED true
// #define RANDOM_SEED 4
