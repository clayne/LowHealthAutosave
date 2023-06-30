#pragma once

class Utility {
protected:
    Utility() = default;
    ~Utility() = default;

public:
    Utility(const Utility&) = delete;
    Utility(Utility&&) = delete;
    Utility& operator=(const Utility&) = delete;
    Utility& operator=(Utility&&) = delete;

    static Utility* GetSingleton() {
        static Utility singleton;
        return std::addressof(singleton);
    }

    inline static std::chrono::time_point last = std::chrono::system_clock::time_point::min();
};
