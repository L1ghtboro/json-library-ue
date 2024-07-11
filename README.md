# Unreal Engine JSON Parsing Library

This library provides a universal and flexible way to parse JSON data in Unreal Engine projects. It is designed to work with JSON files without requiring predefined data structures, making it easy to integrate and use in various contexts.

## Features

- Load and parse JSON files into Unreal Engine objects.
- Extract values of different types (strings, numbers, arrays, objects) from JSON objects.
- Easily integrate with existing Unreal Engine projects.
- Universal parsing capabilities to handle dynamic JSON structures.

## Installation

1. Clone or download this repository.
2. Copy the `JsonLibrary.h` and `JsonLibrary.cpp` files into your Unreal Engine project's `Source` directory.
3. Create your `AssetStruct.h` file in your Unreal Engine project's `Source` directory.
4. If you sort your project as Public and Private remember to store .cpp and .h in separate folders.

		PublicIncludePaths.AddRange( new string[] { "Example/Public" } );
        PrivateIncludePaths.AddRange( new string[] { "Example/Private"} );

## Usage

### Include the Library

Include the JSON library and the data structures in your class:

```cpp
#include "JsonLibrary.h"
#include "RoomAssetStruct.h"

// Function to parse room assets from a JSON file and return an FRoomAssetStruct
FRoomAssetStruct ParseRoomAssets(const FString& FilePath) {
    FRoomAssetStruct RoomAssets; // Create a structure to hold the room assets

    // Load JSON data from the specified file path into a JsonObject
    TSharedPtr<FJsonObject> JsonObject = UJsonLibrary::LoadJSONFromFile(FilePath);

    // Check if the JsonObject is valid (i.e., the file was loaded and parsed successfully)
    if (!JsonObject.IsValid()) {
        UE_LOG(LogTemp, Error, TEXT("Failed to load or parse JSON file: %s"), *FilePath); // Log an error if the JSON is invalid
        return RoomAssets; // Return the empty RoomAssets struct
    }

    // Declare a shared pointer to hold the "rooms" JSON object
    TSharedPtr<FJsonObject> RoomsObject;
    // Try to get the "rooms" field from the main JsonObject
    if (UJsonLibrary::GetObjectField(JsonObject, TEXT("rooms"), RoomsObject)) {
        // Iterate over each key-value pair in the "rooms" object
        for (const auto& RoomPair : RoomsObject->Values) {
            FRoomAssetInfo RoomInfo; // Create a structure to hold the information for each room
            RoomInfo.RoomName = RoomPair.Key; // Set the room name to the current key

            // Declare an array to hold the "assets" array from the current room
            TArray<TSharedPtr<FJsonValue>> AssetsArray;
            // Try to get the "assets" field from the current room object
            if (UJsonLibrary::GetArrayField(RoomPair.Value->AsObject(), TEXT("assets"), AssetsArray)) {
                // Iterate over each element in the "assets" array
                for (const auto& AssetValue : AssetsArray) {
                    FAssetStruct Asset; // Create a structure to hold the information for each asset

                    // Declare a shared pointer to hold the current asset object
                    TSharedPtr<FJsonObject> AssetObject;
                    // Try to convert the current asset value to a JSON object
                    if (AssetValue->TryGetObject(AssetObject)) {
                        // Get the "asset_name" field from the current asset object
                        UJsonLibrary::GetStringField(AssetObject, TEXT("asset_name"), Asset.AssetName);
                        // Get the "directory" field from the current asset object
                        UJsonLibrary::GetStringField(AssetObject, TEXT("directory"), Asset.Directory);
                        
                        // Add the current asset to the room's assets array
                        RoomInfo.Assets.Add(Asset);
                    }
                }
            }
            
            // Add the current room's information to the RoomAssets map
            RoomAssets.Rooms.Add(RoomPair.Key, RoomInfo);
        }
    } else {
        // Log an error if the "rooms" field was not found in the JSON
        UE_LOG(LogTemp, Error, TEXT("Failed to find 'rooms' field in JSON file: %s"), *FilePath);
    }

    // Return the populated RoomAssets struct
    return RoomAssets;
}
void CalloutMethod() {
    FRoomAssetStruct RoomAssets = ParseRoomAssets(TEXT("path/to/your/file.json"));
}
