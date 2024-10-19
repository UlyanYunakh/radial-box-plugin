// Ullian Yunakh


#include "UWRadialMenu.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "RadialBox.h"
#include "UWRadialMenuItem.h"

void UUWRadialMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (RadialBox)
	{
		Origin = RadialBox->GetStartVector();
	}
}

void UUWRadialMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CalculateAngle(MyGeometry);
	
	SelectItem();
}

FReply UUWRadialMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (HoveredItem)
	{
		OnItemSelected(HoveredItem);

		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
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
	PrevAngle = Angle;
	Angle = FMath::Acos(cosTheta * FMath::Sign(cross)) + offset;

	offset = PI / 2 - FMath::Acos(A.X);
	A = Origin;

	cosTheta = FVector2D::DotProduct(A, B);
	//offset = cross < 0 ? PI : 0;

	AngleDiff = FMath::Acos(cosTheta) - PI / 2 + offset;

	Origin = FVector2D(FMath::Cos(Angle), FMath::Sin(Angle));

	UE_LOG(LogTemp, Log, TEXT("angle %f"), AngleDiff);
	//UE_LOG(LogTemp, Log, TEXT("RadialMenu: angle = %f"), FMath::RadiansToDegrees(Angle));
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
