#include "Settings.h"
#include "SimpleIni.h"

Settings* Settings::GetSingleton() {
    static Settings singleton;
    return std::addressof(singleton);
}

void Settings::LoadSettings() {
    logger::info("Loading settings");
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\LowHealthAutosave.ini)");

    health = std::atof(ini.GetValue("General", "fHealthPercent"));
    seconds = std::atoi(ini.GetValue("General", "uEveryXSeconds"));

    logger::info("Loaded settings");
}
