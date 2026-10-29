#pragma once

#include <iostream>
#include <vector>
#include <filesystem>

class NoInternetPaths {
public:
    const inline static std::string Win[] = {
        "C:\\Windows\\Temp",
        "$WIN_USERS$\\AppData\\Local\\Temp",
        "$WIN_USERS$\\AppData\\Local\\Temp\\Low",

        "$WIN_USERS$\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Code Cache",
        "$WIN_USERS$\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cache",
        "$WIN_USERS$\\AppData\\Local\\Yandex\\YandexBrowser\\User Data\\Default\\Cache",


        "$WIN_USERS$\\AppData\\Local\\Adobe\\Acrobat\\DC\\Cache",
        "$WIN_USERS$\\AppData\\Local\\Steam\\appcache",
        "$WIN_USERS$\\AppData\\Local\\Epic Games\\Launcher\\Saved\\webcache",
        "$WIN_USERS$\\AppData\\Local\\Microsoft\\Office\\16.0\\OfficeFileCache"
    };

    const inline static std::string Linux[] = {

        "~/.cache",
        "~/.cache/google-chrome",  

        "/tmp",
        "/var/tmp",
        "/var/cache/apt/archives",

        "~/.steam/steam/appcache",
        "~/.local/share/Steam/appcache",
        "~/.config/TelegramDesktop/tdata/cache"

    };

};
