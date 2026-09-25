#include "Core/BytesBackendHttp.h"
#include "Core/BytesSettings.h"
#include "ProjectBytes.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FString FBytesHttpResult::Describe() const
{
	if (Reasons.Num() == 0)
	{
		return Error;
	}
	return FString::Printf(TEXT("%s: %s"), *Error, *FString::Join(Reasons, TEXT("; ")));
}

namespace BytesHttp
{
	FString ToJsonString(const TSharedRef<FJsonObject>& Object)
	{
		FString Out;
		const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer =
			TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
		FJsonSerializer::Serialize(Object, Writer);
		return Out;
	}

	void Send(const FString& Verb, const FString& Path, const TSharedPtr<FJsonObject>& Body,
		const TMap<FString, FString>& Headers, FBytesHttpCallback Callback)
	{
		const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
		Request->SetURL(UBytesSettings::GetBackendUrl() + Path);
		Request->SetVerb(Verb);
		Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		Request->SetHeader(TEXT("Accept"), TEXT("application/json"));
		Request->SetTimeout(UBytesSettings::Get()->RequestTimeoutSeconds);
		for (const TPair<FString, FString>& Header : Headers)
		{
			Request->SetHeader(Header.Key, Header.Value);
		}
		if (Body.IsValid())
		{
			Request->SetContentAsString(ToJsonString(Body.ToSharedRef()));
		}

		Request->OnProcessRequestComplete().BindLambda(
			[Callback, Verb, Path](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bConnectedSuccessfully)
			{
				FBytesHttpResult Result;
				if (!bConnectedSuccessfully || !Response.IsValid())
				{
					Result.Error = FString::Printf(TEXT("Could not reach the backend at %s"), *UBytesSettings::GetBackendUrl());
					UE_LOG(LogBytes, Warning, TEXT("%s %s failed: %s"), *Verb, *Path, *Result.Error);
					if (Callback)
					{
						Callback(Result);
					}
					return;
				}

				Result.Status = Response->GetResponseCode();
				TSharedPtr<FJsonObject> Json;
				const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
				if (FJsonSerializer::Deserialize(Reader, Json) && Json.IsValid())
				{
					Result.Json = Json;
				}

				Result.bOk = Result.Status >= 200 && Result.Status < 300 && Result.Json.IsValid();
				if (!Result.bOk)
				{
					if (!Result.Json.IsValid() || !Result.Json->TryGetStringField(TEXT("error"), Result.Error))
					{
						Result.Error = FString::Printf(TEXT("Backend returned HTTP %d"), Result.Status);
					}
					if (Result.Json.IsValid())
					{
						Result.Json->TryGetStringArrayField(TEXT("reasons"), Result.Reasons);
					}
					UE_LOG(LogBytes, Verbose, TEXT("%s %s -> %d %s"), *Verb, *Path, Result.Status, *Result.Describe());
				}

				if (Callback)
				{
					Callback(Result);
				}
			});
		Request->ProcessRequest();
	}
}
