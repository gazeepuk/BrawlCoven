// Ivan Piankouski / GazeePuk


#include "GameplayAbilitySystem/Data/BC_AttributeInfo.h"

FAttributeInfo UBC_AttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	const FAttributeInfo* AttributeInfo = AttributeInformation.FindByPredicate([&AttributeTag](const FAttributeInfo& AttributeInfoPredicate)
	{
		return AttributeInfoPredicate.AttributeTag.MatchesTagExact(AttributeTag);
	});

	if(AttributeInfo != nullptr)
	{
		return *AttributeInfo;
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAttributeInfo();
}
