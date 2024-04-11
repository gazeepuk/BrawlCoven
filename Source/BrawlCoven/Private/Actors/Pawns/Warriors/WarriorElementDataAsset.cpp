// Ivan Piankouski / GazeePuk


#include "Actors/Pawns/Warriors/WarriorElementDataAsset.h"

const UTexture2D* UWarriorElementDataAsset::GetWarriorSlateBrushForElement(const FGameplayTag& InWarriorElementTag) const
{
	const FWarriorElementInfo* WarriorElementInfo = WarriorTypeInfos.FindByPredicate([&InWarriorElementTag](const FWarriorElementInfo& InnerWarriorElementInfo)
	{
		return InnerWarriorElementInfo.ElementTag == InWarriorElementTag;
	});
	return WarriorElementInfo->Texture;
}
