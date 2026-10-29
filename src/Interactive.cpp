#include "Interactive.hpp"

std::vector<std::filesystem::path> interactiveLogic::UserPathsAsk(bool Recurse_EnterNewPaths)
{
    std::vector<std::filesystem::path> paths;
    bool is_UserPathsFile_Exists = std::filesystem::exists(JSONworker::Get_DefaultUserpaths_Filename());
    std::cout << "\n\n--------------------------------\n";

    //Вариант ветвления [1/2] - если файла с пользовательскими путями не найден
    //Предлагает записать свои пути или продолжить без этого
    if (!is_UserPathsFile_Exists) {
        char action;

        if (!Recurse_EnterNewPaths) {
            const std::string msg = "Would you like to add your own paths to the category?\n[0] - NO\n[1] - YES\n> ";
            while (action != '0' && action != '1') action = input<char>(msg, true);
        }
        else{
            action = '1'; //В случае если функция рекурсивно вызвала саму себя с флагом Recurse_EnterNewPaths автоматически запускается ввод новых путей
        }
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
        const std::string msg = "Do you want to fetch last paths from file?\n[0] - NO\n[1] - YES\n[2] - Enter new paths\n> ";
        char action = ' ';
        while (!(action >= '0' && action <= '2')) action = input<char>(msg, true);

        if (action == '0') return paths;
        else if (action == '1') {
            paths = JSONworker::get_UserPaths();
            return paths; //возращает пустой вектор(пользователь отказался)
        }
        else if (action == '2') {
            std::filesystem::remove(JSONworker::Get_DefaultUserpaths_Filename());

            return UserPathsAsk(true); //Рекурсивный запуск функции с предварительным удалением файла для запуска другого условия в начале
        }
    }

    std::cout << "\n--------------------------------\n";
    return std::vector<std::filesystem::path>(); //Заглушка для предупреждения
}

nlohmann::json interactiveLogic::DANGER_EditPresetContentAsk(nlohmann::json Content)
{
    const std::string msg = "Do you want to edit preset file(original file)\n[0] - NO\n[1] - YES\n> ";
   nlohmann::json result;
    
    std::cout << "\n\n--------------------------------\n";
    char action = ' ';
    while (action != '0' && action != '1') action = input<char>(msg, true);
    
    if (action == '1') {
        const std::string TempFileName = "TempFile.txt";

        std::filesystem::path preset_path = std::filesystem::absolute(".");
        preset_path /= TempFileName;

        std::fstream TempFile(TempFileName, std::ios::out);
        if (!TempFile.is_open()) {
            std::cout << "Unable to create temp file..." << std::endl;
            return Content;
        }

        TempFile << Content.dump(4);
        TempFile.close();
        system(preset_path.string().c_str()); //Открытие 

        TempFile.open(TempFileName, std::ios::in | std::ios::out);
        if (!TempFile.is_open()) {
            std::cout << "Unable to open temp file..." << std::endl;
            return Content;
        }

        result = nlohmann::json::parse(TempFile);
        TempFile.close();
        try {
            std::filesystem::remove(std::filesystem::absolute(".") / TempFileName);
        }
        catch(...) {
            std::cout << "Unable to delete tempfile" << std::endl;
        }
        return result;
    }
    std::cout << "\n--------------------------------\n";
    return Content;
}
