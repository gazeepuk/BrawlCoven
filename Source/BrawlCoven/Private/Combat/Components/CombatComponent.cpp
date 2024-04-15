// Ivan Piankouski / GazeePuk


#include "Combat/Components/CombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BC_GameplayTags.h"
#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatComponent::DecreaseActionSpeed(float InSubtractionValue)
{
	check(SetActionSpeedAttributeEffectClass);
	if (InSubtractionValue <= 0)
	{
		return;
	}

	float ActionSpeed = BC_AttributeSet->GetActionSpeed() - InSubtractionValue;
	ActionSpeed = FMath::Max(ActionSpeed, 0.f);

	const FGameplayEffectSpecHandle SpecHandle = BC_AbilitySystemComponent->MakeOutgoingSpec(
		SetActionSpeedAttributeEffectClass, 1.f,BC_AbilitySystemComponent->MakeEffectContext());

	const FBC_GameplayTags GameplayTags = FBC_GameplayTags::Get();
	const FGameplayEffectSpecHandle ActionSpeedSpecHandle =
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			SpecHandle, GameplayTags.Attributes_Vital_ActionSpeed, ActionSpeed);

	BC_AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
		*ActionSpeedSpecHandle.Data, BC_AbilitySystemComponent);
}

void UCombatComponent::SetDefaultActionSpeed() const
{
	check(SetActionSpeedAttributeEffectClass);

	const float ActionSpeed = 1000 / BC_AttributeSet->GetSpeed();

	const FGameplayEffectSpecHandle SpecHandle = BC_AbilitySystemComponent->MakeOutgoingSpec(
		SetActionSpeedAttributeEffectClass, 1.f, BC_AbilitySystemComponent->MakeEffectContext());

	const FBC_GameplayTags GameplayTags = FBC_GameplayTags::Get();
	const FGameplayEffectSpecHandle ActionSpeedSpecHandle =
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			SpecHandle, GameplayTags.Attributes_Vital_ActionSpeed, ActionSpeed);

	BC_AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
		*ActionSpeedSpecHandle.Data, BC_AbilitySystemComponent);
}

void UCombatComponent::SetProperties(UBC_AbilitySystemComponent* InASC, UBC_WarriorAttributeSet* InAS,
	ABC_WarriorBase* InWarriorOwner)
{
	check(InASC && InAS && InWarriorOwner);
	
	BC_AbilitySystemComponent = InASC;
	BC_AttributeSet = InAS;
	WarriorOwner = InWarriorOwner;
}

void UCombatComponent::StartWarriorTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, "Warrior Started Turn: " + GetOwner()->GetName());
}

void UCombatComponent::EndWarriorTurn() const
{
	SetDefaultActionSpeed();
	OnTurnEnded.Broadcast();
}
