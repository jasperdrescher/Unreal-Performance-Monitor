// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "UnrealPerformanceMonitorBPLibrary.generated.h"

UCLASS()
class UUnrealPerformanceMonitorBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get GPU Name", Keywords = "Unreal Performance Monitor GPU name"), Category = "PerformanceMonitor", meta = (WorldContext = "WorldContextObject"))
	static FString GetGpuName(const UObject* WorldContextObject);
};
