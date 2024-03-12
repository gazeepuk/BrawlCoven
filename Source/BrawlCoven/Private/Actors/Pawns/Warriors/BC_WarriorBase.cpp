// Ivan Piankouski / GazeePuk


#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "AbilitySystemComponent.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "PlayerStates/BC_BattlePlayerState.h"


ABC_WarriorBase::ABC_WarriorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);
}

UAbilitySystemComponent* ABC_WarriorBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABC_WarriorBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ABC_WarriorBase::BeginPlay()
{
	Super::BeginPlay();
}


void ABC_WarriorBase::InitializeDefaultAttributes() const
{
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
}

void ABC_WarriorBase::InitializePrimaryAttributes() const
{
	ApplyEffectSpecToSelf(DefaultPrimaryAttributes);
}

void ABC_WarriorBase::InitializeSecondaryAttributes() const
{
	ApplyEffectSpecToSelf(DefaultSecondaryAttributes);
}


void ABC_WarriorBase::InitAbilityActorInfo()
{
	ABC_BattlePlayerState* BC_PlayerState = GetPlayerState<ABC_BattlePlayerState>();
	check(BC_PlayerState)
	BC_PlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BC_PlayerState, this);

	AbilitySystemComponent = BC_PlayerState->GetAbilitySystemComponent();
	AttributeSet = BC_PlayerState->GetAttributeSet();

	UBC_AbilitySystemComponent* BC_AbilitySystemComponent = Cast<UBC_AbilitySystemComponent>(AbilitySystemComponent);
	if(BC_AbilitySystemComponent)
	{
		BC_AbilitySystemComponent->AbilityActorInfoSet();
	}

	InitializeDefaultAttributes();
}

void ABC_WarriorBase::ApplyEffectSpecToSelf(const TSubclassOf<UGameplayEffect>& AttributeClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(AttributeClass);

	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(AttributeClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ABC_WarriorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABC_WarriorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABC_WarriorBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init actor info for the server
	InitAbilityActorInfo();
}

void ABC_WarriorBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init actor info for the client
	InitAbilityActorInfo();
}

