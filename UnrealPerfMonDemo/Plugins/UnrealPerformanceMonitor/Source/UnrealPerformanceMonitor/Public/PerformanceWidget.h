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
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	FString FramesPerSecond;

	UPROPERTY(BlueprintReadOnly)
	FString FrameTimeMs;

	UPROPERTY(BlueprintReadOnly)
	FString PhysicalMb;

	UPROPERTY(BlueprintReadOnly)
	FString VirtualMb;

	UPROPERTY(BlueprintReadOnly)
	FString GpuName;

private:
	void CalculateAverageFps(float InDeltaTime);
	void CalculateAverageDeltaTime();

	TArray<float> DeltaTimeHistory;
	float TotalDeltaTime = 0.0f;
	float AverageFps = 0.0f;
	float SmoothedDeltaTime = 0.0f;
	float AccumulatedTime = 0.0f;
	float AccumulatedTimeThreshold = 5.0f;
	int32 MaxDeltaTimeSamples = 30;
	int32 FrameCount = 0;
};
