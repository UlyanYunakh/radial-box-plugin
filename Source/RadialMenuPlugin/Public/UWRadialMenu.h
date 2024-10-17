// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWRadialMenu.generated.h"

class URadialBox;
class UUWRadialMenuItem;
/**
 * Radial menu base class
 */
UCLASS()
class RADIALMENUPLUGIN_API UUWRadialMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<URadialBox> RadialBox;

	UPROPERTY(BlueprintReadOnly)
	float Angle;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UUWRadialMenuItem* HoveredItem;
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void CalculateAngle(const FGeometry& MyGeometry);

	virtual void SelectItem();
};
