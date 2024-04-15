// Ivan Piankouski / GazeePuk


#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "AbilitySystemComponent.h"
#include "Actors/Pawns/Warriors/WarriorDataAsset.h"
#include "Combat/Components/CombatComponent.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "PlayerStates/BC_BattlePlayerState.h"


ABC_WarriorBase::ABC_WarriorBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);

	//GAS
	AbilitySystemComponent = CreateDefaultSubobject<UBC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UBC_WarriorAttributeSet>("AttributeSet");
	Cast<UBC_WarriorAttributeSet>(AttributeSet)->OnEmptyHealth.AddDynamic(this, &ThisClass::OnDeath);
	//Battle Components
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	CombatComponent->SetProperties(Cast<UBC_AbilitySystemComponent>(AbilitySystemComponent), Cast<UBC_WarriorAttributeSet>(AttributeSet), this);
}

UAbilitySystemComponent* ABC_WarriorBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABC_WarriorBase::GetAttributeSet() const
{
	return AttributeSet;
}


template <class T>
T* ABC_WarriorBase::GetAttributeSet() const
{
	return Cast<T>(AttributeSet);
}

float ABC_WarriorBase::GetActionSpeed() const
{
	return GetAttributeSet<UBC_WarriorAttributeSet>()->GetActionSpeed();
}

bool ABC_WarriorBase::IsAlive() const
{
	const UBC_WarriorAttributeSet* WarriorAttributeSet = CastChecked<UBC_WarriorAttributeSet>(AttributeSet);
	return WarriorAttributeSet->GetHealth() > 0;
}

void ABC_WarriorBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo_Server();
}

#pragma region Initializing Attributes 
void ABC_WarriorBase::InitializeDefaultAttributes() const
{
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
	InitializeVitalAttributes();
}

void ABC_WarriorBase::InitializePrimaryAttributes() const
{
	ApplyEffectSpecToSelf(WarriorDataAsset->PrimaryAttributesEffect);
}

void ABC_WarriorBase::InitializeSecondaryAttributes() const
{
	ApplyEffectSpecToSelf(WarriorDataAsset->SecondaryAttributesEffect);
}

void ABC_WarriorBase::InitializeVitalAttributes() const
{
	ApplyEffectSpecToSelf(WarriorDataAsset->VitalAttributesEffect);
	CombatComponent->SetDefaultActionSpeed();
}

#pragma endregion

void ABC_WarriorBase::AddWarriorAbilities() const
{
	check(WarriorDataAsset);

	const TArray<TSubclassOf<UBC_GameplayAbility>> WarriorStartupAbilities
	{
		WarriorDataAsset->NormalAttackAbility,
		WarriorDataAsset->SkillAbility,
		WarriorDataAsset->UltimateAbility
	};

	UBC_AbilitySystemComponent* ASC = CastChecked<UBC_AbilitySystemComponent>(AbilitySystemComponent);
	ASC->AddWarriorAbilities(WarriorStartupAbilities);
}


void ABC_WarriorBase::InitAbilityActorInfo_Client_Implementation()
{

	AddWarriorAbilities();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);


	UBC_AbilitySystemComponent* BC_AbilitySystemComponent = Cast<UBC_AbilitySystemComponent>(AbilitySystemComponent);
	if (BC_AbilitySystemComponent)
	{
		BC_AbilitySystemComponent->AbilityActorInfoSet();
	}

	InitializeDefaultAttributes();
}

void ABC_WarriorBase::InitAbilityActorInfo_Server_Implementation()
{

	InitAbilityActorInfo_Client_Implementation();
	/*APlayerController* PlayerController = GetController<APlayerController>();
	if(PlayerController)
		ABC_HUD* HUD = PlayerController->GetHUD<ABC_HUD>();
		if(!HUD)
		{
			return;
		}
		
		HUD->InitOverlay(PlayerController, BC_PlayerState, AbilitySystemComponent, AttributeSet);
	}*/
}


void ABC_WarriorBase::ApplyEffectSpecToSelf(const TSubclassOf<UGameplayEffect>& AttributeClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(AttributeClass);

	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		AttributeClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ABC_WarriorBase::OnDeath()
{
	//TODO: death behavior
}

void ABC_WarriorBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	
	//Init actor info for the server
	//InitAbilityActorInfo();
}

void ABC_WarriorBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init actor info for the client
	//InitAbilityActorInfo();
}
