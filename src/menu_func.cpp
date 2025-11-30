#include "menu_func.h"
#include "io.h"
#include "info.h"
#include "calculator.h"
#include "exceptions.h"
#include "config.h"

using BigNumber = calculator::BigArithmetic::BigNumber;

void menu_func::MainMenu::description()
{
    io::print_text_with_header(info::description, "Описание программы");
    io::wait_enter();
}

void menu_func::MainMenu::hasse()
{
    io::print_text_with_header(info::hasse_diagram, "Диаграмма Хассе");
    io::wait_enter();
}

void menu_func::MainMenu::variant_33_rule()
{
    io::print_text_with_header(info::variant_33_rule, "Правило '+1' для варианта №33");
    io::wait_enter();
}

void menu_func::back_to_main_menu(bool &back)
{
    back = true;
}

void menu_func::StartWorkMenu::print_addition_table()
{
    auto a_table = calculator::SmallArithmetic::addition_table();
    io::print_table("Таблица сложения малой конечной арифметики", a_table, '+');
    io::wait_enter();
}

void menu_func::StartWorkMenu::print_multiplication_table()
{
    auto m_table = calculator::SmallArithmetic::multiplication_table();
    io::print_table("Таблица умножения малой конечной арифметики", m_table, '*');
    io::wait_enter();
}

void menu_func::StartWorkMenu::print_carry_table()
{
    auto c_table = calculator::SmallArithmetic::carry_table();
    io::print_table("Таблица переноса малой конечной арифметики", c_table, '~');
    io::wait_enter();
}

void menu_func::CalculatorMenu::add()
{
    bool finish = false;
    bool first_input_ok = false;
    while (!finish)
    {
        try
        {
            static BigNumber num1;
            static BigNumber num2;
            if (!first_input_ok)
            {
                string num1_str = io::read_string("Введите первое слагаемое");
                num1 = BigNumber(num1_str);
                first_input_ok = true;
            }
            string num1_str = io::read_string("Введите второе слагаемое");
            num2 = BigNumber(num1_str);

            BigNumber result = calculator::BigArithmetic::add(num1, num2);
            io::print_operation_result(result.str());
            finish = true;
        }
        catch (const BigNumberException &e)
        {
            io::print_error(e.what());
        }
        catch (const std::exception &e)
        {
            io::print_error(e.what());
        }
    }
    io::wait_enter();
}

void menu_func::CalculatorMenu::sub()
{
    bool finish = false;
    bool first_input_ok = false;
    while (!finish)
    {
        try
        {
            static BigNumber num1;
            static BigNumber num2;
            if (!first_input_ok)
            {
                string num1_str = io::read_string("Введите уменьшаемое");
                num1 = BigNumber(num1_str);
                first_input_ok = true;
            }
            string num1_str = io::read_string("Введите вычитаемое");
            num2 = BigNumber(num1_str);

            BigNumber result = calculator::BigArithmetic::sub(num1, num2);
            io::print_operation_result(result.str());
            finish = true;
        }
        catch (const BigNumberException &e)
        {
            io::print_error(e.what());
        }
        catch (const std::exception &e)
        {
            io::print_error(e.what());
        }
    }
    io::wait_enter();
}

void menu_func::CalculatorMenu::mul()
{
    bool finish = false;
    bool first_input_ok = false;
    while (!finish)
    {
        try
        {
            static BigNumber num1;
            static BigNumber num2;
            if (!first_input_ok)
            {
                string num1_str = io::read_string("Введите первый множитель");
                num1 = BigNumber(num1_str);
                first_input_ok = true;
            }
            string num1_str = io::read_string("Введите второй множитель");
            num2 = BigNumber(num1_str);

            BigNumber result = calculator::BigArithmetic::sub(num1, num2);
            io::print_operation_result(result.str());
            finish = true;
        }
        catch (const BigNumberException &e)
        {
            io::print_error(e.what());
        }
        catch (const std::exception &e)
        {
            io::print_error(e.what());
        }
    }
    io::wait_enter();
}

void menu_func::CalculatorMenu::div()
{
    bool finish = false;
    bool first_input_ok = false;
    while (!finish)
    {
        try
        {
            static BigNumber num1;
            static BigNumber num2;
            if (!first_input_ok)
            {
                string num1_str = io::read_string("Введите делимое");
                num1 = BigNumber(num1_str);
                first_input_ok = true;
            }
            string num1_str = io::read_string("Введите делитель");
            num2 = BigNumber(num1_str);

            auto result = calculator::BigArithmetic::div(num1, num2);
            string quotient = result.first.str();
            string remainder = result.second.str();
            string out = remainder == string(1, ZERO)
                             ? quotient
                             : quotient + "(" + remainder + ")";
            io::print_operation_result(out);
            finish = true;
        }
        catch (const BigNumberDivisionException &e)
        {
            io::print_operation_result(e.what());
            finish = true;
        }
        catch (const BigNumberException &e)
        {
            io::print_error(e.what());
        }
        catch (const std::exception &e)
        {
            io::print_error(e.what());
        }
    }
    io::wait_enter();
}

void menu_func::CalculatorMenu::exp()
{
    io::print_header("Еще в разработке -.-", BOXED, PURPLE);
    io::wait_enter();
}
