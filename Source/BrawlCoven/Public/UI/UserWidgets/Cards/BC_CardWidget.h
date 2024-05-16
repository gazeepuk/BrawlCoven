// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgets/BC_UserWidget.h"
#include "BC_CardWidget.generated.h"

class UTextBlock;
class UBorder;
class USizeBox;
class UButton;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_CardWidget : public UBC_UserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetCardName(const FString& InCardNameString);
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Generic")
	FText CardName {FText::FromString("Card Name")};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Generic", meta =(BindWidget))
	TObjectPtr<UTextBlock> CardNameTextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|SizeBox")
	FVector2D BoxSize = FVector2D(150.f, 200.f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|SizeBox", meta =(BindWidget))
	TObjectPtr<USizeBox> SizeBoxRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Foreground")
	TObjectPtr<UTexture2D> CardForegroundTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Foreground")
	TObjectPtr<UBorder> CardForegroundBorder;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Interaction", meta =(BindWidget))
	TObjectPtr<UButton> CardButton;
	UFUNCTION(BlueprintImplementableEvent, Category = "Card|Interaction")
	void OnButtonClicked();
};