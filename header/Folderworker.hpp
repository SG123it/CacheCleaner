#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>

class Folderworker
{
private:
    //Функция для безопасного удаления файла или папки. Возвращает результат
    static bool DeleteObject(std::filesystem::path path);

    //Функция для получения размера файла в байтах
    static unsigned long long int GetFileSize(std::filesystem::path path);
public:
    
    //Функция которая возвращает размер папки в мб
    static unsigned long long int GetFolderSize(std::filesystem::path path);

    //Функция которая возвращает весь список файлов в папке в векторе
    static std::vector<std::filesystem::path> GetFolderObjects(std::filesystem::path path);

    //Функция которая выполняет рекурсивное удаление в папке. Возвращает массив пар [результат, путь]
    static std::vector<std::pair<bool, std::filesystem::path>> RecursiveFolderDelete(std::filesystem::path path);

};
