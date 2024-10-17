// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "Components/Overlay.h"
#include "RadialBox.generated.h"

/**
 * Radial box overlay
 */
UCLASS()
class RADIALMENUPLUGIN_API URadialBox : public UOverlay
{
	GENERATED_BODY()

public:
	// UObject
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End UObject

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radial Menu")
	float Radius = 100.0f;

	/* In degree */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Radial Menu")
	float AngleOffset = -90.0f;

protected:
	float Theta;


public:
	virtual FVector2D GetStartVector();

	virtual TObjectPtr<UWidget> GetChildAtAngle(float Angle);

protected:
	// UPanelWidget
	virtual UClass* GetSlotClass() const override;
	// End UPanelWidget
	
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface
};
