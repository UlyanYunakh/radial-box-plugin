// Ullian Yunakh

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWRadialMenuItem.generated.h"

/**
 * Base widget fot radial menu item
 */
UCLASS()
class RADIALMENUPLUGIN_API UUWRadialMenuItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	bool IsRadialHovered;
	
public:
	void HoverItem();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRadialHover();

	void UnHoverItem();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRadialUnHover();

};
