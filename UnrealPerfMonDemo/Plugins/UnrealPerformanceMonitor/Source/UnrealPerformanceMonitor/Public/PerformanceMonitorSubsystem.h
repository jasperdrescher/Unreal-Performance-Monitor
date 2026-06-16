// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "PerformanceMonitorSubsystem.generated.h"

UCLASS()
class UNREALPERFORMANCEMONITOR_API UPerformanceMonitorSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;

    virtual bool IsTickable() const override { return true; }

    virtual TStatId GetStatId() const override;
	FString GetFramesPerSecond() const { return FramesPerSecond; }
	FString GetFrameTimeMs() const { return FrameTimeMs; }
	FString GetPhysicalMb() const { return PhysicalMb; }
	FString GetVirtualMb() const { return VirtualMb; }
	FString GetGpuName() const { return GpuName; }
	float GetAverageFps() const { return AverageFps; }
	float GetSmoothedDeltaTime() const { return SmoothedDeltaTime; }

private:
	void CalculateAverageFps(float DeltaTime);
	void CalculateAverageDeltaTime();

	TArray<float> DeltaTimeHistory;
	FString FramesPerSecond;
	FString FrameTimeMs;
	FString PhysicalMb;
	FString VirtualMb;
	FString GpuName;
	float TotalDeltaTime = 0.0f;
	float AverageFps = 0.0f;
	float SmoothedDeltaTime = 0.0f;
	float AccumulatedTime = 0.0f;
	float AccumulatedTimeThreshold = 5.0f;
	int32 MaxDeltaTimeSamples = 30;
	int32 FrameCount = 0;
	int32 FrametimeMsUniqueKey = -1;
	int32 FramesPerSecondUniqueKey = -1;
	int32 PhysicalMbUniqueKey = -1;
	int32 VirtualMbUniqueKey = -1;
	int32 GpuNameUniqueKey = -1;
};
