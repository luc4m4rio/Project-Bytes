#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"

/** Outcome of a backend call. The backend always answers JSON; errors look like {"error": "...", "reasons": [...]}. */
struct PROJECTBYTES_API FBytesHttpResult
{
	bool bOk = false;
	int32 Status = 0;
	FString Error;
	TArray<FString> Reasons;
	TSharedPtr<FJsonObject> Json;

	/** Error plus reasons on one line, for logs and HUDs. */
	FString Describe() const;

	template <typename TStruct>
	bool Parse(TStruct& Out) const
	{
		return Json.IsValid() && FJsonObjectConverter::JsonObjectToUStruct(Json.ToSharedRef(), &Out);
	}
};

using FBytesHttpCallback = TFunction<void(const FBytesHttpResult&)>;

namespace BytesHttp
{
	/**
	 * Sends a JSON request to the backend. Path is relative to the backend URL ("/v1/auth/login").
	 * Callback runs on the game thread. Callers capture weak pointers - the request may outlive them.
	 */
	PROJECTBYTES_API void Send(const FString& Verb, const FString& Path, const TSharedPtr<FJsonObject>& Body,
		const TMap<FString, FString>& Headers, FBytesHttpCallback Callback);

	PROJECTBYTES_API FString ToJsonString(const TSharedRef<FJsonObject>& Object);
}
