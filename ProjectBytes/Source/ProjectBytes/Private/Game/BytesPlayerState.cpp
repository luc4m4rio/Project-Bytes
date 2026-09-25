#include "Game/BytesPlayerState.h"
#include "Net/UnrealNetwork.h"

void ABytesPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABytesPlayerState, Identity);
	DOREPLIFETIME_CONDITION(ABytesPlayerState, Money, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ABytesPlayerState, Standing, COND_OwnerOnly);
}

void ABytesPlayerState::SetIdentity(const FBytesPublicIdentity& NewIdentity)
{
	Identity = NewIdentity;
	SetPlayerName(Identity.Name);
	ForceNetUpdate();
	OnRep_Identity(); // RepNotify doesn't run on the server
}

void ABytesPlayerState::OnRep_Identity()
{
	OnIdentityChanged.Broadcast(this);
}

void ABytesPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (ABytesPlayerState* Other = Cast<ABytesPlayerState>(PlayerState))
	{
		Other->Identity = Identity;
		Other->Money = Money;
		Other->Standing = Standing;
		Other->AccountId = AccountId;
	}
}
