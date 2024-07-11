#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JsonLibrary.generated.h"

UCLASS() class FRAMEWORKBUILDER_API UJsonLibrary : public UObject {
	GENERATED_BODY()
	
public:
    static TSharedPtr<FJsonObject> LoadJSONFromFile(const FString& FilePath);

    static bool SaveJSONToFile(const FString& FilePath, const TSharedPtr<FJsonObject>& JsonObject);

    static TSharedPtr<FJsonObject> ParseJSONString(const FString& JsonString);

public:
    static TSharedPtr<FJsonObject> LoadJSONFromFile(const FString& FilePath);

    static bool SaveJSONToFile(const FString& FilePath, const TSharedPtr<FJsonObject>& JsonObject);

    static TSharedPtr<FJsonObject> ParseJSONString(const FString& JsonString);

    static bool GetStringField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FString& OutString);

    static bool GetNumberField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, float& OutNumber);

    static bool GetBoolField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool& OutBool);

    static bool GetObjectField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, TSharedPtr<FJsonObject>& OutObject);

    static bool GetArrayField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, TArray<TSharedPtr<FJsonValue>>& OutArray);
};
