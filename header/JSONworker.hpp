#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>

class JSONworker {
private:
    //Стандартный путь до файла с заранее заготовленными путями
    inline static const std::filesystem::path DefaultPreset_Filename = "presets.json";

    //Стандартный путь до файла с путями пользователя
    inline static const std::filesystem::path DefaultUserpaths_Filename = "UserPaths.json";
public:
    static std::vector<std::pair<std::string, std::filesystem::path>> get_PresetPaths();

    static std::vector<std::filesystem::path> get_UserPaths();
    static bool set_Userpaths(std::vector<std::filesystem::path> List);

    static std::filesystem::path Get_DefaultPreset_Filename() {
        return DefaultPreset_Filename;
    }
    static std::filesystem::path Get_DefaultUserpaths_Filename() {
        return DefaultUserpaths_Filename;
    }


};