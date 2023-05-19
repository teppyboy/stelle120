#include <cstdio>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <winreg.h>
#include <fstream>
#include "lib/json.hpp"
using json = nlohmann::json;


int _main(bool dryRun = false, int targetFPS = -1, int VSync = -1) {
    LONG lResult;
    HKEY hKey;
    DEVMODE devMode; 
    int displayRefreshRate = 0;

    SetConsoleTitleA("Stelle120 v0.1.2");
    printf("Stelle120 v0.1.2\n\n");
    printf("By using this software you agree that you love Stelle <3\n\n");
    printf("Setting the FPS to custom value will break the graphics settings menu.\n");
    printf("To fix that simply set the FPS again to 60/30.\n\n");

    // Get display refresh rate
    if (EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &devMode) != 0) {
        displayRefreshRate = devMode.dmDisplayFrequency;
    }

    printf("Opening Star Rail registry key...\n");
    lResult = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Cognosphere\\Star Rail", 0, KEY_ALL_ACCESS, &hKey);
    if (lResult != ERROR_SUCCESS) 
    {
        if (lResult == ERROR_FILE_NOT_FOUND) {
            printf("Star Rail registry key not found.\n");
            printf("You need to open Star Rail at least once.\n");
            return 1;
        } 
        else {
            printf("Error opening Star Rail registry key: ");
            std::cout << lResult << std::endl;
            return -1;
        }
    }
    DWORD bufferSize = 256;
    char buffer[bufferSize];
    printf("Reading settings...\n");
    lResult = RegGetValueA(hKey, NULL, "GraphicsSettings_Model_h2986158309", RRF_RT_ANY, NULL, (PVOID)&buffer, (LPDWORD)&bufferSize);
    if (lResult != ERROR_SUCCESS) 
    {
        if (lResult == ERROR_FILE_NOT_FOUND) {
            printf("Star Rail graphics settings registry key not found.\n");
            printf("You need to open Star Rail and change its graphics settings at least once.\n");
            return 1;
        } 
        else {
            printf("Error opening Star Rail registry key: ");
            std::cout << lResult << std::endl;
            return -1;
        }
    }
    json settings = json::parse((std::string)buffer);

    printf("\nCurrent FPS: ");
    printf(settings["FPS"].dump().c_str());
    printf("\n");
    printf("Set current FPS target to: ");
    if (targetFPS == -1) {
        std::cin >> targetFPS;
    } else {
        printf("%d\n", targetFPS);
    }
    if (targetFPS > 120) 
    {
        std::string answer;
        printf("Target FPS is higher than 120, which is not supported and will be reset by the game.\n");
        printf("Continue? [N/y]: ");
        std::cin >> answer;
        if (answer == "y") {
            printf("Continuing (at your own risk)...\n");
        }
        else {
            printf("Aborting...\n");
            return 2;
        }
    }
    printf("\n");
    printf("Changing FPS target... ");
    settings["FPS"] = targetFPS;
    printf("OK\n");
    if (settings["EnableVSync"].dump() == "true") 
    {
        if (VSync == 0) {
            printf("Disabling VSync... ");
            settings["EnableVSync"] = false;
            printf("OK\n");
        }
        else if (VSync =! 1) {
            if (targetFPS > displayRefreshRate && displayRefreshRate != 0) 
            {
                printf("VSync is enabled, and your monitor current refresh rate is smaller than the target FPS.\n");
                printf("Do you want to disable VSync? [Y/n]: ");
            }
            else {
                printf("VSync is enabled, do you want to disable VSync? [Y/n]: ");
            }
            std::string answer;
            std::cin >> answer;
            if (answer == "n") {
                printf("Okay, just keep in mind that the FPS will be limited to your monitor refresh rate.\n");
            }
            else {
                printf("Disabling VSync... ");
                settings["EnableVSync"] = false;
                printf("OK\n");
            }
        }
    }
    else if (VSync == 1) {
        printf("Enabling VSync... ");
        settings["EnableVSync"] = true;
        printf("OK\n");
    }
    char newSettings[bufferSize];
    sprintf(newSettings, settings.dump().c_str());
    printf("New settings: ");
    printf(newSettings);
    printf("\n");
    printf("Writing settings... ");
    if (!dryRun) {
        const BYTE *newSettingsBytes = reinterpret_cast<const BYTE*>(newSettings);
        lResult = RegSetValueExA(hKey, "GraphicsSettings_Model_h2986158309", 0, REG_BINARY, newSettingsBytes, sizeof(newSettings));
        if (lResult != ERROR_SUCCESS) 
        {
            printf("Error setting Star Rail registry key: ");
            std::cout << lResult << std::endl;
            return -2;
        }
    }
    RegCloseKey(hKey);
    printf("OK\n\n");
    printf("To apply the changes you need to restart Star Rail.\n");
    printf("Do NOT open the graphics settings before restarting or the settings will be reset.\n\n");
    return 0;
}

int main(int argc, char* argv[]) {
    bool dryRun = false;
    bool noPause = false;
    int targetFPS = -1;
    int VSync = -1;
    for (int i = 0; i < argc; i++)
    {
        std::string arg = std::string(argv[i]);
        if (argv[i] == "--no-pause") {
            noPause = true;
        } else if (argv[i] == "--dry-run") {
            printf("Dry run enabled, changes will not be saved.\n");
            dryRun = true;
        } else if (arg.substr(0, 12) == "--target-fps=") {
            targetFPS = std::stoi(arg.substr(13));
        } else if (arg.substr(0, 8) == "--vsync=") {
            VSync = std::stoi(arg.substr(9));
        }
    }
    int result = _main(dryRun, targetFPS, VSync);
    if (!noPause) {
        printf("Press any key to exit...");
        std::cin.ignore();
        std::cin.get();
    }
    return result;
}
