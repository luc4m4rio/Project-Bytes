#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Core/BytesTypes.h"
#include "BytesPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBytesOnIdentityChanged, ABytesPlayerState*, PlayerState);

/** Carries the character identity (name, faction, rank, threat, clan) to every client in the district. */
UCLASS()
class PROJECTBYTES_API ABytesPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/** Server only. */
	void SetIdentity(const FBytesPublicIdentity& NewIdentity);

	const FBytesPublicIdentity& GetIdentity() const { return Identity; }

	UFUNCTION(BlueprintPure, Category = "Bytes")
	FBytesPublicIdentity GetCharacterIdentity() const { return Identity; }

	UFUNCTION(BlueprintPure, Category = "Bytes")
	bool HasIdentity() const { return !Identity.CharacterId.IsEmpty(); }

	/** Fires on server and clients whenever the identity changes (join, rank up, threat change). */
	UPROPERTY(BlueprintAssignable, Category = "Bytes")
	FBytesOnIdentityChanged OnIdentityChanged;

	/** Private to the owning player. */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Bytes")
	int32 Money = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Bytes")
	int32 Standing = 0;

	// Server-only bookkeeping (not replicated).
	FString AccountId;
	FString PendingTicketId;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CopyProperties(APlayerState* PlayerState) override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Identity, BlueprintReadOnly, Category = "Bytes", meta = (AllowPrivateAccess = "true"))
	FBytesPublicIdentity Identity;

	UFUNCTION()
	void OnRep_Identity();
};
