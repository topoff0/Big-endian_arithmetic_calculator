#pragma once
#include "io.h"

class app
{
public:
    static void run();

private:
    // === App working flags ===
    static bool _running;
    static bool _back;

    static void start();
    static void start_calculator();

    static void handle_main_menu(int choice);
    static void handle_start_work_menu(int choice);
    static void handle_calculator_menu(int choice);
};
