// Ivan Piankouski / GazeePuk


#include "GameCards/FieldCard.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "Kismet/GameplayStatics.h"

UFieldCard::UFieldCard()
{
	
}

bool UFieldCard::IsCardValid()
{
	return Super::IsCardValid() && GetAbilitySystemComponent() && GetAttributeSet();		
}



void UFieldCard::UseGameCard(const UAbilitySystemComponent* SourceASC, const UAbilitySystemComponent* TargetASC)
{
	Super::UseGameCard(SourceASC, TargetASC);

	
}

UAbilitySystemComponent* UFieldCard::GetAbilitySystemComponent() const
{
	check(GetWorld());
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(UGameplayStatics::GetGameMode(GetWorld()));
	check(ASC);
	return ASC;
}

const UAttributeSet* UFieldCard::GetAttributeSet() const
{
	return GetAbilitySystemComponent()->GetAttributeSet(UBC_WarriorAttributeSet::StaticClass());
}

uint8 UFieldCard::GetPlayerLevel()
{
	return Super::GetPlayerLevel();
}
