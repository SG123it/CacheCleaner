#include "Folderworker.hpp"


bool Folderworker::DeleteObject(std::filesystem::path path)
{
    if (!std::filesystem::exists(path)) return false;

    try {
        if (std::filesystem::is_directory(path)) std::filesystem::remove_all(path);
        else std::filesystem::remove(path);
    }
    catch(...) {
        return false;
    }

    //Если в конце концов путь найден значит файл всё таки не удалён
    if (std::filesystem::exists(path)) return false;

    return true;

}

unsigned long long int Folderworker::GetFileSize(std::filesystem::path path)
{
    if (!std::filesystem::exists(path)) return 0;

    return (std::filesystem::file_size(path));
}

std::filesystem::path Folderworker::VariablesToText(std::string path)
{
    if (path.find("$WIN_USERS$") != std::string::npos) {
        const std::string marker = "$WIN_USERS$";
        auto pos = path.find(marker);

        const char* windir = std::getenv("windir");
        const char* username = std::getenv("username");
        if (!windir || !username) throw std::runtime_error("Unable to get windows env");

        std::filesystem::path replace_to = windir;
        replace_to = replace_to.root_path() / "Users" / username;

        path.replace(pos, marker.size(), replace_to.string());
        return path;
    }

    return std::filesystem::path(); //заглушка для предупреждения
}

unsigned long long int Folderworker::GetFolderSize(std::filesystem::path path)
{
    path = VariablesToText(path.string());
    if (!std::filesystem::exists(path)) return 0;
    if (!std::filesystem::is_directory(path)) throw std::runtime_error("Error! " + path.string() + " - NOT DIRECTORY! (GetFolderSize)");

    unsigned long long int return_value = 0;

    for (auto el : std::filesystem::recursive_directory_iterator(path)) {

        if (std::filesystem::is_directory(el)) {
            return_value += GetFolderSize(el);
        }
        else {
            return_value += GetFileSize(el.path());
        }

    }
    return (return_value / 1024) / 1024;
}

std::vector<std::filesystem::path> Folderworker::GetFolderObjects(std::filesystem::path path)
{
    path = VariablesToText(path.string());
    if (!std::filesystem::is_directory(path)) throw std::runtime_error("Error! " + path.string() + " - NOT DIRECTORY! (GetFolderObjects)");

    std::vector<std::filesystem::path> return_value;

    for (auto el : std::filesystem::recursive_directory_iterator(path)) return_value.push_back(el.path());
    return return_value;
}

std::vector<std::pair<bool, std::filesystem::path>> Folderworker::RecursiveFolderDelete(std::filesystem::path path)
{
    path = VariablesToText(path.string());
    if (!std::filesystem::is_directory(path)) throw std::runtime_error("Error! " + path.string() + " - NOT DIRECTORY! (RecursiveFolderDelete)");
    std::vector<std::pair<bool, std::filesystem::path>> return_value;
    
    for (auto el : std::filesystem::recursive_directory_iterator(path)) {
        std::pair<bool, std::filesystem::path> object;

        object.second = el.path();
        object.first = DeleteObject(el.path());
        return_value.push_back(object);
    }

    return return_value;
}
