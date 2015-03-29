#include "ApiPluginPrivatePCH.h"

/// Concrete API implementation
class FApiPlugin : public IApiPlugin {
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FApiPlugin, ApiPlugin )

/// Initialize
void FApiPlugin::StartupModule() {
}

/// Shutdown
void FApiPlugin::ShutdownModule() {
}
