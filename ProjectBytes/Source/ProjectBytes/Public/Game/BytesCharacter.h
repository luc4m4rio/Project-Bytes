#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BytesCharacter.generated.h"

class UBytesAppearanceComponent;

/**
 * Playable character whose look comes from the backend-validated appearance replicated on its
 * ABytesPlayerState. Make a Blueprint child with your anim BP / movement setup and set it as the
 * DefaultPawnClass of your district game mode once your maps have floors.
 */
UCLASS()
class PROJECTBYTES_API ABytesCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABytesCharacter();

	UBytesAppearanceComponent* GetAppearance() const { return Appearance; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bytes")
	TObjectPtr<UBytesAppearanceComponent> Appearance;
};
