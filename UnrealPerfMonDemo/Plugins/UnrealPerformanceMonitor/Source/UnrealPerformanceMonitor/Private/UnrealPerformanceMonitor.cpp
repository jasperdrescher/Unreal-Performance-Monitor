// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#include "UnrealPerformanceMonitor.h"

DEFINE_LOG_CATEGORY(UnrealPerformanceMonitor);

#define LOCTEXT_NAMESPACE "FUnrealPerformanceMonitorModule"

void FUnrealPerformanceMonitorModule::StartupModule()
{
	UE_LOG(UnrealPerformanceMonitor, Log, TEXT("UnrealPerformanceMonitor has started"));
}

void FUnrealPerformanceMonitorModule::ShutdownModule()
{
	UE_LOG(UnrealPerformanceMonitor, Log, TEXT("UnrealPerformanceMonitor has shutdown"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealPerformanceMonitorModule, UnrealPerformanceMonitor)
