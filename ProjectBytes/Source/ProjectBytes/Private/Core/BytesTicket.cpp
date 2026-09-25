#include "Core/BytesTicket.h"
#include "JsonObjectConverter.h"
#include "Misc/Base64.h"
#include "Misc/DateTime.h"
#include "Misc/SecureHash.h"

namespace BytesTicket
{
	bool Base64UrlDecode(const FString& In, TArray<uint8>& Out)
	{
		FString Standard = In.Replace(TEXT("-"), TEXT("+")).Replace(TEXT("_"), TEXT("/"));
		while (Standard.Len() % 4 != 0)
		{
			Standard.AppendChar(TEXT('='));
		}
		return FBase64::Decode(Standard, Out);
	}

	bool Verify(const FString& Token, const TArray<uint8>& Key, FBytesTicketClaims& OutClaims, FString& OutError)
	{
		if (Key.Num() == 0)
		{
			OutError = TEXT("Server is not registered with the backend yet");
			return false;
		}

		FString PayloadPart;
		FString SignaturePart;
		if (!Token.Split(TEXT("."), &PayloadPart, &SignaturePart) || PayloadPart.IsEmpty() || SignaturePart.IsEmpty())
		{
			OutError = TEXT("Malformed ticket");
			return false;
		}

		// HMAC over the ASCII of the base64url payload, exactly as the backend signs it.
		const FTCHARToUTF8 PayloadAscii(*PayloadPart);
		uint8 Expected[FSHA1::DigestSize];
		FSHA1::HMACBuffer(Key.GetData(), Key.Num(), PayloadAscii.Get(), PayloadAscii.Length(), Expected);

		TArray<uint8> Signature;
		if (!Base64UrlDecode(SignaturePart, Signature) || Signature.Num() != FSHA1::DigestSize)
		{
			OutError = TEXT("Malformed ticket signature");
			return false;
		}
		uint8 Diff = 0;
		for (int32 Index = 0; Index < FSHA1::DigestSize; ++Index)
		{
			Diff |= Signature[Index] ^ Expected[Index];
		}
		if (Diff != 0)
		{
			OutError = TEXT("Invalid ticket signature");
			return false;
		}

		TArray<uint8> PayloadBytes;
		if (!Base64UrlDecode(PayloadPart, PayloadBytes))
		{
			OutError = TEXT("Malformed ticket payload");
			return false;
		}
		const FUTF8ToTCHAR PayloadJson(reinterpret_cast<const UTF8CHAR*>(PayloadBytes.GetData()), PayloadBytes.Num());
		const FString Json = FString::ConstructFromPtrSize(PayloadJson.Get(), PayloadJson.Length());

		OutClaims = FBytesTicketClaims();
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(Json, &OutClaims))
		{
			OutError = TEXT("Unreadable ticket payload");
			return false;
		}
		if (OutClaims.ExpiresAt < FDateTime::UtcNow().ToUnixTimestamp())
		{
			OutError = TEXT("Ticket expired, rejoin from the district list");
			return false;
		}
		return true;
	}
}
