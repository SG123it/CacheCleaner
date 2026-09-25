#include <iostream>
#include <argparse/argparse.hpp>
#include <JSONworker.hpp>
#include <Folderworker.hpp>
#include <Interactive.hpp>
#include <RequestWorker.hpp>

//Константные значения для программы
//Макросы определены в CMAKELISTS
const std::string PROGRAM_NAME = ProgramName;
const std::string PROGRAM_DESCRIPTION = ProgramDescription;
const std::string PROGRAM_VERSION = VERSION;

const std::string repository_releases_url = "https://github.com/SG123it/CacheCleaner/releases";

const std::string PresetFileUrlStandart = "https://raw.githubusercontent.com/SG123it/CacheCleaner/refs/heads/main/dependencies/presets.json";
const std::string PresetFileFileNameStandart = "presets.json";

const std::string VersionFileUrlStandart = "https://raw.githubusercontent.com/SG123it/CacheCleaner/refs/heads/main/version.txt";

// Это главная функция, здесь происходит парсинг аргументов и последующий запуск программы
int main(int argc, char* argv[]) {    
    argparse::ArgumentParser program(PROGRAM_NAME,PROGRAM_VERSION);
    program.add_description(PROGRAM_DESCRIPTION);
    program.add_argument("--FAST", "--F")
    .help("quickly clean files without user paths")
    .flag();

    program.add_argument("--VERBOSE_RESULT", "--VR")
    .help("Outputs the result in an expanded form.")
    .flag();

    program.parse_args(argc, argv);
    bool FAST_FLAG = program["--FAST"] == true;
    bool VERBOSE_RESULT_FLAG = program["--VERBOSE_RESULT"] == true;
    //---------------------

    std::cout << PROGRAM_DESCRIPTION << std::endl;
    std::cout << "VERSION: " << PROGRAM_VERSION << "\n----------------\n\n\n";

    //Если доступна новая версия
    if (RequestWorker::CheckProgramUpdates(VersionFileUrlStandart, std::stof(PROGRAM_VERSION))) {
        std::cout << "\nHey! New version available! Learn more at: " << repository_releases_url << std::endl;
    }
    if (!std::filesystem::exists(PresetFileFileNameStandart)) {
        RequestWorker::DownloadFIle(PresetFileUrlStandart, PresetFileFileNameStandart);
    }

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
    //Вектор с пользовательскими путями. Если включён флаг FAST интерактивная часть просто пропускается а вектор остаётся пустым
    std::vector<std::filesystem::path> UserPaths = (FAST_FLAG ? std::vector<std::filesystem::path>() : interactiveLogic::UserPathsAsk());
    if (!JSONworker::set_UserPaths(UserPaths)) std::cout << "\nUnable to save user paths!";

    //Добавление пользовательских категорий в общий вектор all_categories
    categories_keys.insert("UserPaths");
    for (auto el : UserPaths) all_categories["UserPaths"].push_back(el);

    //Шаг [3/3] Запуск очистки
    //------------------------------------
    if(!FAST_FLAG) { //Отключение подтверждение с флагом FAST
        std::cout << "\nPress any key to start cleaning...\n";
        std::cin.get();
    }

    //Вектор пар для хранения выполнения всех результатов
    std::vector<std::pair<bool, std::filesystem::path>> all_results;

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
                //Вектор пар для временного хранения результатов. В дальнейшем всё копируется в all_results
                std::vector<std::pair<bool, std::filesystem::path>> temp_result;

                before_size = Folderworker::GetFolderSize(path);
                temp_result = Folderworker::RecursiveFolderDelete(path);
                after_size = Folderworker::GetFolderSize(path);

                deleted_mb += (before_size - after_size);
                total_removed_mb += (before_size - after_size);

                all_results.insert(all_results.end(), temp_result.begin(), temp_result.end());
            }
            catch(...) {
                continue;
            }
        }

        std::cout << "Deleted: " << deleted_mb << "mb\n";
    }

    std::cout << "\n---------------\n";
    std::cout << "The cleaning has been successfully completed.\n";
    std::cout << "Total cleaned: " << total_removed_mb << " MB\n";

    unsigned int count = all_results.size();
    if (VERBOSE_RESULT_FLAG) {
        std::cout << "\n\nVERBOSE RESULT: " << "Total elements - " << count << std::endl;
        for (int i = 0; i < count; i++) {
            std::cout << i + 1 << " " << (all_results[i].first ? "OK" : "BAD") << " : " << all_results[i].second.string() << std::endl;
        }
    }
    else {
        unsigned int OK_count = 0;
        unsigned int BAD_count = 0;
        
        for (int i = 0; i < count; i++) {
            if (all_results[i].first) OK_count++;
            else BAD_count++;
        }

        std::cout << "\n----------------\n";
        std::cout << "| OK = " << OK_count << " | BAD = " << BAD_count;
        std::cout << "\n----------------\n";
        std::cout << "If you want to see VERBOSE result please rerun program with \"--VR\" argument\n";
    }
    
    if (!FAST_FLAG) { //Отключение нажатие на кнопку после завершения с флагом FAST
        std::cout << "\n\nPress any key to exit...";
        std::cin.get();
    }
    return 0;
}