#include "Interactive.hpp"

std::vector<std::filesystem::path> interactiveLogic::UserPathsAsk()
{
    std::vector<std::filesystem::path> paths;

    //Вариант ветвления [1/2] - если файла с пользовательскими путями не найден
    //Предлагает записать свои пути или продолжить без этого
    if (!std::filesystem::exists(JSONworker::Get_DefaultUserpaths_Filename())) {
        char action;
        while (action != '0' && action != '1') action = input<char>("Would you like to add your own paths to the category?\n[1] - YES\n[0] - NO\n> ", true);
        if (action == '0') return paths; //возращает пустой вектор(пользователь отказался)
        
        int count = input<int>("Please enter count of paths: ", true);
        for (int i = 0; i < count; i++) {
            std::string path = "";
            while(!std::filesystem::is_directory(path)) path = input<std::string>("Enter path to the directory #" + std::to_string(i + 1) + ":", true);

            paths.push_back(path);
        }
        return paths;
    }
    //Вариант ветвления [2/2] - если файла с пользовательскими путями найден
    //Предлагает взять пути из файла, сохранить новые пути или продолжить без этого
    else {
        char action;
        while (action != '0' && action != '1') action = input<char>("Do you want to fetch last paths from file?\n[1] - YES\n[0] - NO\n> ", true);
        if (action == '0') return paths;
        else {
            paths = JSONworker::get_UserPaths();
            return paths;
        }
    }

}