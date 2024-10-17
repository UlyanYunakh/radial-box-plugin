// Ullian Yunakh


#include "RadialBox.h"
#include "RadialBoxSlot.h"


void URadialBox::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(URadialBox, Radius))
	{
		RebuildWidget(); // I think better way is to use invalidate (need to implement different slot to invalidation correct work?)
	}
}


FVector2D URadialBox::GetStartVector()
{	
	float angleOffsetRad = FMath::DegreesToRadians(90 + AngleOffset);
	return FVector2D(FMath::Cos(angleOffsetRad), FMath::Sin(angleOffsetRad));
}

TObjectPtr<UWidget> URadialBox::GetChildAtAngle(float Angle)
{
	TObjectPtr<UWidget> result;

	int32 index = FMath::TruncToInt32(Angle / Theta);

	if (Slots.IsValidIndex(index))
	{
		result = Slots[index]->Content;
	}
	
	return result;
}

UClass* URadialBox::GetSlotClass() const
{
	return URadialBoxSlot::StaticClass();
}

TSharedRef<SWidget> URadialBox::RebuildWidget()
{
	MyOverlay = SNew(SOverlay);

	if (Slots.Num() > 0)
	{
		Theta = (PI * 2) / Slots.Num();
		float currAngle = Theta / 2 + FMath::DegreesToRadians(AngleOffset) - PI / 2;

		for (UPanelSlot* PanelSlot : Slots)
		{
			if (URadialBoxSlot* TypedSlot = Cast<URadialBoxSlot>(PanelSlot))
			{
				TypedSlot->Parent = this;
				TypedSlot->BuildSlot(MyOverlay.ToSharedRef());
				TypedSlot->SetTheta(Theta);

				TypedSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				TypedSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

				FVector2D translation;
				translation.X = Radius * FMath::Cos(currAngle);
				translation.Y = Radius * FMath::Sin(currAngle);
				TypedSlot->Content->SetRenderTranslation(translation);
			}
			currAngle += Theta;
		}
	}

	return MyOverlay.ToSharedRef();
}

