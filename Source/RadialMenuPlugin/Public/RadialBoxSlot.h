// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "Components/OverlaySlot.h"
#include "RadialBoxSlot.generated.h"

/**
 * Slot class
 */
UCLASS()
class RADIALMENUPLUGIN_API URadialBoxSlot : public UOverlaySlot
{
	GENERATED_BODY()

protected:
	/* Angle of the sector */
	float Theta;

public:
	FORCEINLINE void SetTheta(float InTheta) { Theta = InTheta; }
	FORCEINLINE float GetTheta() { return Theta; }
};
