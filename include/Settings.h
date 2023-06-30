#pragma once

class Settings {
protected:
    Settings() = default;
    ~Settings() = default;

public:
    Settings(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings& operator=(Settings&&) = delete;

    static Settings* GetSingleton();
    static void LoadSettings();

    inline static float health = 20.0f;
    inline static int seconds = 20;
};
