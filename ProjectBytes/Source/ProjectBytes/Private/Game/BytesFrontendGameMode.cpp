#include "Game/BytesFrontendGameMode.h"
#include "Game/BytesDebugHUD.h"
#include "Game/BytesPlayerController.h"
#include "Game/BytesPlayerState.h"

ABytesFrontendGameMode::ABytesFrontendGameMode()
{
	PlayerStateClass = ABytesPlayerState::StaticClass();
	PlayerControllerClass = ABytesPlayerController::StaticClass();
	HUDClass = ABytesDebugHUD::StaticClass();
}
