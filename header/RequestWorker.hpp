#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

class RequestWorker {
private:

    //Количество попыток для выполнения запроса
    static inline const int basic_request_limit = 5;

    static cpr::Response get_request(std::string URL);

public:

    //Функция для проверки наличие обновлений у программы. Возвращает то есть ли обновление или нет
    static bool CheckProgramUpdated(std::string RemoteVersionURL, float version);

    //Функция для загрузки файла. Возвращает результат операции
    static bool DownloadFIle(std::string URL, std::string path);

};