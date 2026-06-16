// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#include "UnrealPerformanceMonitorBPLibrary.h"

#include "Engine/World.h"
#include "PerformanceMonitorSubsystem.h"
#include "UnrealPerformanceMonitor.h"

UUnrealPerformanceMonitorBPLibrary::UUnrealPerformanceMonitorBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UUnrealPerformanceMonitorBPLibrary::GetGpuName(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(UnrealPerformanceMonitor, Error, TEXT("Failed to get World Context Object"));
		return "Unknown";
	}

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		if (const UPerformanceMonitorSubsystem* PerformanceMonitorSubsystem = World->GetSubsystem<const UPerformanceMonitorSubsystem>())
		{
			return PerformanceMonitorSubsystem->GetGpuName();
		}
	}

	UE_LOG(UnrealPerformanceMonitor, Error, TEXT("Failed to get GPU Name"));
	return "Unknown";
}
