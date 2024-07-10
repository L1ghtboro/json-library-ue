#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JsonLibrary.generated.h"

UCLASS() class FRAMEWORKBUILDER_API UJsonLibrary : public UObject {
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "JSON")
    static TSharedPtr<FJsonObject> LoadJSONFromFile(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool SaveJSONToFile(const FString& FilePath, const TSharedPtr<FJsonObject>& JsonObject);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static TSharedPtr<FJsonObject> ParseJSONString(const FString& JsonString);

public:
    UFUNCTION(BlueprintCallable, Category = "JSON")
    static TSharedPtr<FJsonObject> LoadJSONFromFile(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool SaveJSONToFile(const FString& FilePath, const TSharedPtr<FJsonObject>& JsonObject);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static TSharedPtr<FJsonObject> ParseJSONString(const FString& JsonString);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetStringField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FString& OutString);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetNumberField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, float& OutNumber);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetBoolField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool& OutBool);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetObjectField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, TSharedPtr<FJsonObject>& OutObject);

    UFUNCTION(BlueprintCallable, Category = "JSON")
    static bool GetArrayField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, TArray<TSharedPtr<FJsonValue>>& OutArray);
};
