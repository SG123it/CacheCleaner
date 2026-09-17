#include "JSONworker.hpp"
#include <fstream>
#include <iomanip>

std::vector<std::pair<std::string, std::filesystem::path>> JSONworker::get_PresetPaths()
{
    nlohmann::json JsonData;
    std::vector<std::pair<std::string, std::filesystem::path>> all_paths;

    if (!std::filesystem::exists(DefaultPreset_Filename) || std::filesystem::is_directory(DefaultPreset_Filename)) throw std::runtime_error("Unable to exists preset file");

    try {
        std::ifstream file(DefaultPreset_Filename);
        file >> JsonData;
        file.close();
    }
    catch(...) {
        throw std::runtime_error("Unable to read data from preset file");
    }
    
    std::string OS = "";
    #if defined(_WIN32)
        OS = "Windows";
    #elif defined(__linux__)
        OS = "Linux";
    #else
        #error "Unsupported OS"
    #endif


    for (auto [CategoryName, pathsArray] : JsonData[OS].items()) {
            std::pair<std::string, std::filesystem::path> CategoryFile;
            CategoryFile.first = CategoryName;

            for (auto filepath : pathsArray) {
                if (!filepath.is_string()) continue;
                CategoryFile.second = std::filesystem::path(filepath);
                all_paths.push_back(CategoryFile);
            }
        }
        return all_paths;
}

std::vector<std::filesystem::path> JSONworker::get_UserPaths()
{
    nlohmann::json JsonData;
    std::vector<std::filesystem::path> all_paths;

    if (!std::filesystem::exists(DefaultUserpaths_Filename) || std::filesystem::is_directory(DefaultUserpaths_Filename)) throw std::runtime_error("Unable to exists file with user paths");

    try {
        std::ifstream file(DefaultUserpaths_Filename);
        file >> JsonData;
        file.close();
    }
    catch(...) {
        throw std::runtime_error("Unable to read data from file file with user paths");
    }

    for (auto el : JsonData["Paths"]) {
        all_paths.push_back(el);
    }

    return all_paths;
}

bool JSONworker::set_UserPaths(std::vector<std::filesystem::path> List)
{
    //Заполнение...
    nlohmann::json JsonData;
    
    for (auto el : List) {
        JsonData["Paths"].push_back(el);
    }

    //Запись...
    std::ofstream file(DefaultUserpaths_Filename);
    if (!file.is_open()) return false;

    file << std::setw(4) << JsonData;
    file.close();

    return true;
}
