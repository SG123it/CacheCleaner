#include "RequestWorker.hpp"

cpr::Response RequestWorker::get_request(std::string URL)
{
    cpr::Response request;
    for (int i = 0; i < basic_request_limit; i++) {
        try {
            request = cpr::Get(cpr::Url(URL));
        }
        catch(...) {
            return request;
        }
        if (request.status_code != 200) {
            std::cout << "[" << i << "]" << "Unable to execute GET request: " << request.status_code << std::endl;
            std::cout << "Site: " << URL << "\n\n";
            continue;
        }
    }

    return request;
}

bool RequestWorker::DownloadFIle(std::string URL, std::string path)
{
    std::cout << "Downloading file: " << URL << "\n\n";
    cpr::Response Data = get_request(URL);
    if (Data.status_code != 200) return false;

    try {
        std::ofstream file(path);
        if (!file.is_open()) return false;

        file << Data.text;
        file.close();
    }
    catch(...) {
        std::cout << "Unable to open file";
        if (std::filesystem::exists(path)) std::filesystem::remove(path);

        return false;
    }

    return true;
}

bool RequestWorker::CheckProgramUpdates(std::string RemoteVersionURL, float version)
{
    cpr::Response data = get_request(RemoteVersionURL);
    if (!data.status_code == 200) return false;

    //Корвертирование удалённой строки с версией в float
    float RemoteVersion = 0.0;
    try {
        RemoteVersion = std::stoi(data.text);
    }
    catch(...) {
        std::cout << "Unable to convert string to int: " << data.text << std::endl;
        return false;
    }

    return (RemoteVersion > version);


}
