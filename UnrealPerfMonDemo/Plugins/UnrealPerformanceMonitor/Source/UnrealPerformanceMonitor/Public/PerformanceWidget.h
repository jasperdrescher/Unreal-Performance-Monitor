// Copyright (c) 2026 Jasper Drescher. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PerformanceWidget.generated.h"

UCLASS()
class UNREALPERFORMANCEMONITOR_API UPerformanceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "PerformanceMonitor")
	FString FramesPerSecond;

	UPROPERTY(BlueprintReadOnly, Category = "PerformanceMonitor")
	FString FrameTimeMs;

	UPROPERTY(BlueprintReadOnly, Category = "PerformanceMonitor")
	FString PhysicalMb;

	UPROPERTY(BlueprintReadOnly, Category = "PerformanceMonitor")
	FString VirtualMb;

	UPROPERTY(BlueprintReadOnly, Category = "PerformanceMonitor")
	FString GpuName;
};
