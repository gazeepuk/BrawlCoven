// Ivan Piankouski / GazeePuk

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidgets/BC_UserWidget.h"
#include "BC_CardWidget.generated.h"

class USizeBox;
class UButton;
/**
 * 
 */
UCLASS()
class BRAWLCOVEN_API UBC_CardWidget : public UBC_UserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Generic")
	FName CardName = "Card Name";
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|SizeBox")
	FVector2D BoxSize = FVector2D(150.f, 200.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|SizeBox", meta =(BindWidget))
	TObjectPtr<USizeBox> SizeBoxRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Foreground")
	TObjectPtr<UTexture2D> CardImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Background")
	TObjectPtr<UTexture2D> BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card|Interaction", meta =(BindWidget))
	TObjectPtr<UButton> CardButton;

	UFUNCTION(Category = "Card|Interaction")
	void OnButtonClicked();
};
