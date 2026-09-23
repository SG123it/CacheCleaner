#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
#include <JSONworker.hpp>

//Класс для хранения интерактивных функций. Нужен для разбиения файла main.cpp
class interactiveLogic {
private:
    template <typename InputValue>
    static InputValue input(std::string msg, bool infinityLoop = false); 
public:
    
    //функция для уточнение пользовательских путей и сохранение их 
    static std::vector<std::filesystem::path> UserPathsAsk();

};

template <typename InputValue>
inline InputValue interactiveLogic::input(std::string msg, bool infinityLoop)
{
    InputValue variable;
    do {
        try {
            std::cout << std::endl << msg;
            std::cin >> variable;
        }
        catch(...) {
            std::cout << "\n\nERROR! Please enter correct value.";
            std::cin.clear();

            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return variable; //Если ввод был успешен и код до сюда дошёл
    }
    while(infinityLoop); //Если флаг InfinityLoop включен - цикл будет повторяться до успешного ввода

    return variable; //Заглушка чтобы убрать предупреждение
}
