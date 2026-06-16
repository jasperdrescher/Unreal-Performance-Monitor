// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#include "PerformanceWidget.h"

#include "Kismet/GameplayStatics.h"
#include "PerformanceMonitorSubsystem.h"

void UPerformanceWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (const UWorld* World = GetWorld())
	{
		if (const UPerformanceMonitorSubsystem* PerformanceMonitorSubsystem = World->GetSubsystem<const UPerformanceMonitorSubsystem>())
		{
			FramesPerSecond = PerformanceMonitorSubsystem->GetFramesPerSecond();
			FrameTimeMs = PerformanceMonitorSubsystem->GetFrameTimeMs();
			PhysicalMb = PerformanceMonitorSubsystem->GetPhysicalMb();
			VirtualMb = PerformanceMonitorSubsystem->GetVirtualMb();
			GpuName = PerformanceMonitorSubsystem->GetGpuName();
		}
	}
}
