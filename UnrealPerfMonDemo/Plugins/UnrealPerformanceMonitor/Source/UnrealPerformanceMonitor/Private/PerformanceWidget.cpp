// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#include "PerformanceWidget.h"

#include "GenericPlatform/GenericPlatformDriver.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "RHIGlobals.h"

void UPerformanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DeltaTimeHistory.Reserve(MaxDeltaTimeSamples + 1);

	const FGPUDriverInfo GPUDriverInfo = FPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);
	GPUName = GPUDriverInfo.DeviceDescription;
}

void UPerformanceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	DeltaTimeHistory.Add(InDeltaTime);

	if (DeltaTimeHistory.Num() > MaxDeltaTimeSamples)
		DeltaTimeHistory.RemoveAt(0);

	CalculateAverageDeltaTime();
	FrameTime = FString::Printf(TEXT("Frametime %.1f (%.1f) ms"), SmoothedDeltaTime * 1000.f, InDeltaTime * 1000.f);

	CalculateAverageFPS(InDeltaTime);
	FramesPerSecond = FString::Printf(TEXT("FPS %.0f (%.0f)"), AverageFPS, 1.0f / InDeltaTime);

	const FPlatformMemoryStats MemoryStats = FPlatformMemory::GetStats();
	PhysicalMB = FString::Printf(TEXT("Physical %s / %s"), *FGenericPlatformMemory::PrettyMemory(MemoryStats.UsedPhysical), *FGenericPlatformMemory::PrettyMemory(MemoryStats.AvailablePhysical));
	VirtualMB = FString::Printf(TEXT("Virtual %s / %s"), *FGenericPlatformMemory::PrettyMemory(MemoryStats.UsedVirtual), *FGenericPlatformMemory::PrettyMemory(MemoryStats.AvailableVirtual));
}

void UPerformanceWidget::CalculateAverageFPS(float InDeltaTime)
{
	TotalDeltaTime += InDeltaTime;
	FrameCount++;

	AverageFPS = FrameCount / TotalDeltaTime;

	AccumulatedTime += InDeltaTime;
	if (AccumulatedTime >= AccumulatedTimeThreshold)
	{
		TotalDeltaTime = 0.0f;
		FrameCount = 0;
		AccumulatedTime = 0.0f;
	}
}

void UPerformanceWidget::CalculateAverageDeltaTime()
{
	float Sum = 0.0f;
	for (const float DeltaTime : DeltaTimeHistory)
		Sum += DeltaTime;

	SmoothedDeltaTime = Sum / DeltaTimeHistory.Num();
}
