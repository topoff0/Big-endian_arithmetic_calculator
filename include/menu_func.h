struct menu_func
{
    struct MainMenu
    {
        static void description();
        static void hasse();
        static void variant_33_rule();
    };

    struct StartWorkMenu
    {
        static void print_addition_table();
        static void print_multiplication_table();
        static void print_carry_table();
    };

    struct CalculatorMenu
    {
        static void add();
        static void sub();
        static void mul();
        static void div();
        static void exp();
    };

    // === EXIT ===
    static void back_to_main_menu(bool &back);
};