#include "Core/BytesSettings.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"

FString UBytesSettings::GetBackendUrl()
{
	FString Url = Get()->BackendUrl;
	FParse::Value(FCommandLine::Get(), TEXT("BytesBackend="), Url);
	Url.TrimStartAndEndInline();
	while (Url.EndsWith(TEXT("/")))
	{
		Url.LeftChopInline(1);
	}
	return Url;
}

FString UBytesSettings::GetServerKey()
{
	FString Key = Get()->ServerKey;
	FParse::Value(FCommandLine::Get(), TEXT("BytesServerKey="), Key);
	return Key;
}
