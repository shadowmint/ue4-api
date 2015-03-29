#pragma once

#include "ModuleManager.h"

class IApiPlugin : public IModuleInterface {
  public:

    /// Get access directly to the plugin
    static inline IApiPlugin& Get() {
      return FModuleManager::LoadModuleChecked< IApiPlugin >( "ApiPlugin" );
    }

    /// Check if the plugin is loaded
    static inline bool IsAvailable() {
      return FModuleManager::Get().IsModuleLoaded( "ApiPlugin" );
    }
};
