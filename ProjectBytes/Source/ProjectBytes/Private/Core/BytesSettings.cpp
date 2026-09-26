#include "Core/BytesSettings.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "HAL/PlatformMisc.h"

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
	// Preferred: environment variable (launchers use it; it doesn't show up in process lists or the engine log).
	const FString FromEnvironment = FPlatformMisc::GetEnvironmentVariable(TEXT("BYTES_SERVER_KEY"));
	if (!FromEnvironment.IsEmpty())
	{
		return FromEnvironment;
	}
	FString Key = Get()->ServerKey;
	FParse::Value(FCommandLine::Get(), TEXT("-BytesServerKey="), Key);
	return Key;
}
