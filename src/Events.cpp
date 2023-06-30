#include "Events.h"

#include "Settings.h"
#include "Utility.h"
#include "Hooks.h"

namespace Events {
    OnHitEventHandler* OnHitEventHandler::GetSingleton() {
        static OnHitEventHandler singleton;
        return std::addressof(singleton);
    }

    RE::BSEventNotifyControl OnHitEventHandler::ProcessEvent(const RE::TESHitEvent* a_event,
                                                             RE::BSTEventSource<RE::TESHitEvent>* a_eventSource) {
        if (!a_event) return RE::BSEventNotifyControl::kContinue;

        if (Utility::last == std::chrono::system_clock::time_point::min()) {
            Utility::last = std::chrono::system_clock::now();
        } else {
            if (std::chrono::system_clock::now() - Utility::last >= std::chrono::seconds(Settings::seconds)) {
                Utility::last = std::chrono::system_clock::now();
                if (a_event->target->IsPlayerRef()) {
                    const auto player = RE::PlayerCharacter::GetSingleton();
                    const auto health_as_pct = Hooks::GetActorValuePercent(player->As<RE::Actor>(), RE::ActorValue::kHealth);
                    if (health_as_pct <= Settings::health) {
                        const auto manager = RE::BGSSaveLoadManager::GetSingleton();
                        manager->Save(std::format("LowHealthSave_{}", std::chrono::system_clock::now()).c_str());
                    }
                }
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }

    void OnHitEventHandler::Register() {
        const auto holder = RE::ScriptEventSourceHolder::GetSingleton();
        holder->AddEventSink(GetSingleton());
        logger::info("Registered hit event handler");
    }
}
