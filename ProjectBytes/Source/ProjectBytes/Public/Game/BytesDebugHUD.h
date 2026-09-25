#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BytesDebugHUD.generated.h"

/**
 * Asset-free text HUD so the whole account -> character -> district loop can be playtested before any UMG
 * exists. Frontend: account, characters, districts with eligibility, last error. In a district: instance and
 * every player's identity. Toggle with the console variable bytes.HUD 0/1.
 */
UCLASS()
class PROJECTBYTES_API ABytesDebugHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawFrontend(class UBytesAccountSubsystem* Account);
	void DrawDistrict(class UBytesAccountSubsystem* Account);
	void Line(const FString& Text, const FLinearColor& Color = FLinearColor::White, float Indent = 0.f);

	float CursorX = 0.f;
	float CursorY = 0.f;
};
