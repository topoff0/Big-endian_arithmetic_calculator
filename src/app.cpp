#include "app.h"
#include "config.h"
#include "menu_.h"
#include "info.h"
#include "menu_func.h"
#include "calculator.h"

bool app::_running = true;
bool app::_back = false;

void app::run()
{
    io::print_header("Курсовая работа. Калькулятор <Z; +, *>.", HEADER_STYLE::SIMPLE);
    io::v_space(1);

    menu main_menu("Главное меню");

    while (_running)
    {
        _back = false;
        main_menu.show(MAIN_MENU, "Список команд");
        int choice = io::read_number(menu_min_max_id(MAIN_MENU), "Введите номер команды");
        handle_main_menu(choice);
    }
    io::print_header("Программа завершила свою работу", BOLD, GREEN);
}

void app::start()
{
    while (_running && !_back)
    {
        menu start_work_menu("Стартовое меню");
        start_work_menu.show(START_WORK_MENU, "Список команд");
        int choice = io::read_number(menu_min_max_id(START_WORK_MENU), "Введите номер команды");
        handle_start_work_menu(choice);
    }
}

void app::start_calculator()
{
    while (_running && !_back)
    {
        menu calculator_menu("Меню калькулятора большой конечной арифметики");
        calculator_menu.show(CALCULATOR_MENU, "Список операций");
        int choice = io::read_number(menu_min_max_id(CALCULATOR_MENU), "Введите номер операции");
        handle_calculator_menu(choice);
    }
}

void app::handle_main_menu(int choice)
{
    switch (choice)
    {
    case 0:
        _running = false;
        break;
    case 1:
        start();
        break;
    case 2:
        menu_func::MainMenu::description();
        break;
    case 3:
        menu_func::MainMenu::hasse();
        break;
    case 4:
        menu_func::MainMenu::variant_33_rule();
        break;

    default:
        break;
    }
}

void app::handle_start_work_menu(int choice)
{
    switch (choice)
    {
    case -1:
        menu_func::back_to_main_menu(_back);
        break;
    case 0:
        _running = false;
        break;
    case 1:
        start_calculator();
        break;
    case 2:
        menu_func::StartWorkMenu::print_addition_table();
        break;
    case 3:
        menu_func::StartWorkMenu::print_multiplication_table();
        break;
    case 4:
        menu_func::StartWorkMenu::print_carry_table();
        break;

    default:
        break;
    }
}

void app::handle_calculator_menu(int choice)
{
    switch (choice)
    {
    case -1:
        menu_func::back_to_main_menu(_back);
        break;
    case 0:
        _running = false;
        break;
    case 1:
        menu_func::CalculatorMenu::add();
        break;
    case 2:
        menu_func::CalculatorMenu::sub();
        break;
    case 3:
        menu_func::CalculatorMenu::mul();
        break;
    case 4:
        menu_func::CalculatorMenu::div();
        break;
        break;
    case 5:
        menu_func::CalculatorMenu::exp();
        break;

    default:
        break;
    }
}
