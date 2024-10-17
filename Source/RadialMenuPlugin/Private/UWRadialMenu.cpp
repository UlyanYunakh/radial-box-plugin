// Ullian Yunakh


#include "UWRadialMenu.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "RadialBox.h"
#include "UWRadialMenuItem.h"

void UUWRadialMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CalculateAngle(MyGeometry);
	
	SelectItem();
}

void UUWRadialMenu::CalculateAngle(const FGeometry& MyGeometry)
{
	FGeometry geometry = MyGeometry;
	FVector2D A;

	if (RadialBox)
	{
		geometry = RadialBox->GetTickSpaceGeometry();
		A = RadialBox->GetStartVector();
	}

	FVector2D center = geometry.GetAbsolutePositionAtCoordinates(FVector2f(0.5f, 0.5f));
	FVector2D cursorPos = FSlateApplication::Get().GetCursorPos(); 

	FVector2D B = center - cursorPos;

	A.Normalize();
	B.Normalize();

	float cosTheta = FVector2D::DotProduct(A, B);
	float cross = FVector2D::CrossProduct(A, B);
	float offset = cross < 0 ? PI : 0;
	Angle = FMath::Acos(cosTheta * FMath::Sign(cross)) + offset;

	UE_LOG(LogTemp, Log, TEXT("RadialMenu: angle = %f"), FMath::RadiansToDegrees(Angle));
}

void UUWRadialMenu::SelectItem()
{
	if (!RadialBox)
	{
		return;
	}

	if (TObjectPtr<UWidget> widget = RadialBox->GetChildAtAngle(Angle))
	{
		if (UUWRadialMenuItem* item = Cast<UUWRadialMenuItem>(widget))
		{
			if (item->IsRadialHovered)
			{
				return;
			}

			if (HoveredItem)
			{
				HoveredItem->UnHoverItem();
			}
			HoveredItem = item;
			HoveredItem->HoverItem();
		}
	}
}
