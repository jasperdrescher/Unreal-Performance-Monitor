// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FUnrealPerformanceMonitorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
