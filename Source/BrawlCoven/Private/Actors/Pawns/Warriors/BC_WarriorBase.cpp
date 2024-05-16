// Ivan Piankouski / GazeePuk


#include "Actors/Pawns/Warriors/BC_WarriorBase.h"
#include "AbilitySystemComponent.h"
#include "Actors/Pawns/Warriors/WarriorDataAsset.h"
#include "Combat/Components/CombatComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/AbilitySystemComponents/BC_AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AttributeSets/BC_WarriorAttributeSet.h"
#include "GameplayAbilitySystem/Abilities/WarriorAbilities/WarriorAbility.h"
#include "Net/UnrealNetwork.h"
#include "UI/UserWidgets/Cards/BC_CardWidget.h"
#include "UI/WidgetControllers/BC_WarriorCardWidgetController.h"

ABC_WarriorBase::ABC_WarriorBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Root);
	StaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CardWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("CardWidget");
	CardWidgetComponent->SetupAttachment(Root);
	
	WarriorCardWidgetController = CreateDefaultSubobject<UBC_WarriorCardWidgetController>("CardWidgetController");
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

UBC_GameplayAbility* ABC_WarriorBase::GetNormalAttackAbility() const
{
	const TSubclassOf<UGameplayAbility> NormalAttackAbilityClass = WarriorDataAsset->NormalAttackAbility;
	const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(NormalAttackAbilityClass, 1);
	return Cast<UBC_GameplayAbility>(AbilitySpec.Ability);
}

UBC_GameplayAbility* ABC_WarriorBase::GetSkillAbility() const
{
	const TSubclassOf<UGameplayAbility> SkillAbilityClass = WarriorDataAsset->SkillAbility;
	const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SkillAbilityClass, 1);
	return Cast<UBC_GameplayAbility>(AbilitySpec.Ability);
}

UBC_GameplayAbility* ABC_WarriorBase::GetUltimateAbility() const
{
	const TSubclassOf<UGameplayAbility> UltimateAbilityClass = WarriorDataAsset->UltimateAbility;
	const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(UltimateAbilityClass, 1);
	return Cast<UBC_GameplayAbility>(AbilitySpec.Ability);
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

void ABC_WarriorBase::Server_SetPlayerIndex_Implementation(int32 InPlayerIndex)
{
	PlayerIndex = InPlayerIndex;
}


void ABC_WarriorBase::Server_UseWarriorAbility_Implementation(UWarriorAbility* AbilityToUse, const TArray<AActor*>& Targets)
{
	TArray<FGameplayAbilitySpec> AbilitySpecs = AbilitySystemComponent->GetActivatableAbilities();
	for (const FGameplayAbilitySpec& AbilitySpec : AbilitySpecs)
	{
		if(AbilitySpec.Ability.Get()->IsA(AbilityToUse->GetClass()))
		{
			AbilitySystemComponent->TryActivateAbility(AbilitySpec.Handle);
		}
	} 
}

void ABC_WarriorBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PlayerIndex);
	DOREPLIFETIME(ThisClass, bActive);
}

void ABC_WarriorBase::BeginPlay()
{
	Super::BeginPlay();
	WarriorCardWidgetController->SetWidgetControllerParams(FWidgetControllerParams(nullptr,nullptr,AbilitySystemComponent,AttributeSet),this);

	UUserWidget* Widget = CardWidgetComponent->GetWidget();
	check(Widget);
	UBC_CardWidget* CardWidget = CastChecked<UBC_CardWidget>(Widget);
	CardWidget->SetWidgetController(WarriorCardWidgetController);
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
	check(CombatComponent);
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


void ABC_WarriorBase::Server_InitAbilityActorInfo_Implementation()
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
