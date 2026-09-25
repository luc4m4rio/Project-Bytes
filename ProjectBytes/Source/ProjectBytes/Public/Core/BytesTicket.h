#pragma once

#include "CoreMinimal.h"
#include "Core/BytesTypes.h"

/**
 * Join tickets are issued by the backend (sign_ticket in Backend/server.py):
 *
 *     base64url(JSON claims) "." base64url(HMAC-SHA1(TicketKey, first part))
 *
 * District servers get TicketKey when they register, so they can verify a ticket synchronously in PreLogin
 * without a backend round-trip. One-time use is enforced afterwards by redeeming the ticket id.
 */
namespace BytesTicket
{
	PROJECTBYTES_API bool Base64UrlDecode(const FString& In, TArray<uint8>& Out);

	PROJECTBYTES_API bool Verify(const FString& Token, const TArray<uint8>& Key, FBytesTicketClaims& OutClaims, FString& OutError);
}
