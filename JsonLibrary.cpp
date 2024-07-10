#include "JsonLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

TSharedPtr<FJsonObject> UJsonLibrary::LoadJSONFromFile(const FString& FilePath) {
    FString JsonString;
    FString AbsoluteFilePath = FPaths::ProjectContentDir() + FilePath;

    if (!FFileHelper::LoadFileToString(JsonString, *AbsoluteFilePath)) {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
        return nullptr;
    }

    return ParseJSONString(JsonString);
}

bool UJsonLibrary::SaveJSONToFile(const FString& FilePath, const TSharedPtr<FJsonObject>& JsonObject) {
    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)) {
        FString AbsoluteFilePath = FPaths::ProjectContentDir() + FilePath;
        return FFileHelper::SaveStringToFile(OutputString, *AbsoluteFilePath);
    }
    return false;
}

TSharedPtr<FJsonObject> UJsonLibrary::ParseJSONString(const FString& JsonString) {
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
        return JsonObject;
    }
    UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON string"));
    return nullptr;
}


bool UJsonLibrary::GetStringField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, FString& OutString) {
    if (JsonObject->HasField(FieldName)) {
        OutString = JsonObject->GetStringField(FieldName);
        return true;
    }
    return false;
}

bool UJsonLibrary::GetNumberField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, float& OutNumber) {
    if (JsonObject->HasField(FieldName)) {
        OutNumber = JsonObject->GetNumberField(FieldName);
        return true;
    }
    return false;
}

bool UJsonLibrary::GetBoolField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool& OutBool) {
    if (JsonObject->HasField(FieldName)) {
        OutBool = JsonObject->GetBoolField(FieldName);
        return true;
    }
    return false;
}

bool UJsonLibrary::GetObjectField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, TSharedPtr<FJsonObject>& OutObject) {
    if (JsonObject->HasField(FieldName)) {
        OutObject = JsonObject->GetObjectField(FieldName);
        return true;
    }
    return false;
}

bool UJsonLibrary::GetArrayField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, TArray<TSharedPtr<FJsonValue>>& OutArray) {
    if (JsonObject->HasField(FieldName)) {
        OutArray = JsonObject->GetArrayField(FieldName);
        return true;
    }
    return false;
}