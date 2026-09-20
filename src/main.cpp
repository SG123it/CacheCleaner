#include <iostream>
#include <argparse/argparse.hpp>
#include <JSONworker.hpp>
#include <Folderworker.hpp>
#include <Interactive.hpp>

//Константные значения для программы
//Макросы определены в CMAKELISTS
const std::string PROGRAM_NAME = ProgramName;
const std::string PROGRAM_DESCRIPTION = ProgramDescription;
const std::string PROGRAM_VERSION = VERSION;

// Это главная функция, здесь происходит парсинг аргументов и последующий запуск программы
int main(int argc, char* argv[]) {
    argparse::ArgumentParser program(PROGRAM_NAME,PROGRAM_VERSION);
    program.add_description(PROGRAM_DESCRIPTION);
    program.parse_args(argc, argv);

    std::cout << "CacheCleaner - personal memory assistant\n";
    std::cout << "VERSION: " << PROGRAM_VERSION << "\n----------------\n\n\n";

    //Шаг [1/3] получение путей из preset файла
    //------------------------------------
    if (!std::filesystem::exists(JSONworker::Get_DefaultPreset_Filename())) std::cout << "\nPreset file not found!\n";

    //Unordered map для хранения путей ; [категория, вектор путей<fs::path>]
    std::unordered_map<std::string, std::vector<std::filesystem::path>> all_categories;

    //Сохранение всех ключей в отдельный вектор для получения доступа к unordered_map выше
    std::set<std::string> categories_keys;

    for (auto el : JSONworker::get_PresetPaths()) {
        categories_keys.insert(el.first);
        all_categories[el.first].push_back(el.second);
    }

    //Шаг [2/3] Уточнение пользовательских путей и сохранение 
    //------------------------------------
    std::vector<std::filesystem::path> UserPaths = interactiveLogic::UserPathsAsk();
    if (!JSONworker::set_UserPaths(UserPaths)) std::cout << "\nUnable to save user paths!";

    //Шаг [3/3] Запуск очистки
    //------------------------------------
    std::cout << "\nPress any key to start cleaning...\n";
    std::cin.get();

    //Вес всех удалённых файлов в мб
    int total_removed_mb = 0;
    for (auto catetogy : categories_keys) {
        //Вес удалённых файлов в категории в мб
        int deleted_mb = 0;

        std::cout << std::endl << catetogy << " : ";
        for (auto path : all_categories[catetogy]) {
            int before_size = 0;
            int after_size = 0;

            try {
                before_size = Folderworker::GetFolderSize(path);
                Folderworker::RecursiveFolderDelete(path);
                after_size = Folderworker::GetFolderSize(path);

                deleted_mb += (before_size - after_size);
                total_removed_mb += (before_size - after_size);
            }
            catch(...) {
                continue;
            }
        }

        std::cout << "Deleted: " << deleted_mb << "mb\n";
    }

    std::cout << "\n---------------\n";
    std::cout << "The cleaning has been successfully completed.\n";
    std::cout << "Total cleaned: " << total_removed_mb << " MB";
    std::cout << "\n\nPress any key to exit...";
    std::cin.get();
    return 0;
}