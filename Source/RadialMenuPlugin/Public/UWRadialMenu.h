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
	float PrevAngle;

	UPROPERTY(BlueprintReadOnly)
	float Angle;

	UPROPERTY(BlueprintReadOnly)
	float AngleDiff;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UUWRadialMenuItem* HoveredItem;

	FVector2D Origin;

public:	
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemSelected(UUWRadialMenuItem* Item);
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void CalculateAngle(const FGeometry& MyGeometry);

	virtual void SelectItem();
};
