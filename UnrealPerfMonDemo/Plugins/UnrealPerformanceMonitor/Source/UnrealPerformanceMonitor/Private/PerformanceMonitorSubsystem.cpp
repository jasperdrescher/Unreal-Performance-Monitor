// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#include "PerformanceMonitorSubsystem.h"

#include "GenericPlatform/GenericPlatformDriver.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "RHIGlobals.h"

static TAutoConsoleVariable<int32> CVarShowPerfStats(
    TEXT("UrealPerfMon.ShowPerfStats"),
    0,
    TEXT("Toggles performance stats.\n0: Off\n1: On"),
    ECVF_Cheat
);

void UPerformanceMonitorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    DeltaTimeHistory.Reserve(MaxDeltaTimeSamples + 1);

    const FGPUDriverInfo GPUDriverInfo = FPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);
    GPUName = GPUDriverInfo.DeviceDescription;
}

void UPerformanceMonitorSubsystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DeltaTimeHistory.Add(DeltaTime);

    if (DeltaTimeHistory.Num() > MaxDeltaTimeSamples)
        DeltaTimeHistory.RemoveAt(0);

    CalculateAverageDeltaTime();
    FrameTime = FString::Printf(TEXT("Frametime %.1f (%.1f) ms"), SmoothedDeltaTime * 1000.f, DeltaTime * 1000.f);

    CalculateAverageFPS(DeltaTime);
    FramesPerSecond = FString::Printf(TEXT("FPS %.0f (%.0f)"), AverageFPS, 1.0f / DeltaTime);

    const FPlatformMemoryStats MemoryStats = FPlatformMemory::GetStats();
    PhysicalMB = FString::Printf(TEXT("Physical %s / %s"), *FGenericPlatformMemory::PrettyMemory(MemoryStats.UsedPhysical), *FGenericPlatformMemory::PrettyMemory(MemoryStats.AvailablePhysical));
    VirtualMB = FString::Printf(TEXT("Virtual %s / %s"), *FGenericPlatformMemory::PrettyMemory(MemoryStats.UsedVirtual), *FGenericPlatformMemory::PrettyMemory(MemoryStats.AvailableVirtual));

    if (CVarShowPerfStats.GetValueOnGameThread() == 1 && GEngine)
    {
        float CurrentFPS = 1.0f / DeltaTime;
        FString StatText = FString::Printf(TEXT("FPS Counter: %.2f"), CurrentFPS);

        GEngine->AddOnScreenDebugMessage(5, 0.0f, FColor::Cyan, StatText);
    }
}

TStatId UPerformanceMonitorSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UYourPerfSubsystem, STATGROUP_Tickables);
}

void UPerformanceMonitorSubsystem::CalculateAverageFPS(float DeltaTime)
{
    TotalDeltaTime += DeltaTime;
    FrameCount++;

    AverageFPS = FrameCount / TotalDeltaTime;

    AccumulatedTime += DeltaTime;
    if (AccumulatedTime >= AccumulatedTimeThreshold)
    {
        TotalDeltaTime = 0.0f;
        FrameCount = 0;
        AccumulatedTime = 0.0f;
    }
}

void UPerformanceMonitorSubsystem::CalculateAverageDeltaTime()
{
    float Sum = 0.0f;
    for (const float DeltaTime : DeltaTimeHistory)
        Sum += DeltaTime;

    SmoothedDeltaTime = Sum / DeltaTimeHistory.Num();
}
