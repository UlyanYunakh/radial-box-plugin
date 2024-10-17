// Ullian Yunakh


#include "UWRadialMenuItem.h"

void UUWRadialMenuItem::HoverItem()
{
	IsRadialHovered = true;
	OnRadialHover();
}

void UUWRadialMenuItem::UnHoverItem()
{
	IsRadialHovered = false;
	OnRadialUnHover();
}
