// Ivan Piankouski / GazeePuk


#include "Input/BC_InputConfig.h"

const UInputAction* UBC_InputConfig::FindAbilityActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FBCInputAction& AbilityInputAction : AbilityInputActions)
	{
		if(AbilityInputAction.InputAction && AbilityInputAction.InputTag == InputTag)
		{
			return AbilityInputAction.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for for InputTag [%s], on InputCongig [%s]"),
		       *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
