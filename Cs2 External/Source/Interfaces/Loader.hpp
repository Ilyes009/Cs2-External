#pragma once
#include "../ExternalLibs/ImGui/imgui.h"
#include <wtypes.h>
#include <fstream>
#include <cassert>

// Convertir les macros en constexpr pour une meilleure sécurité
constexpr int ICON_MIN_FA = 0xf000;
constexpr int ICON_MAX_FA = 0xf3ff;

namespace ImGui_Loader
{
    static ImFont* Font_Size_17 = nullptr;
    static ImFont* Font_Size_15 = nullptr;
    static ImFont* Font_Size_22 = nullptr;
    static ImFont* Icon_Font = nullptr;
    static ImFont* Roboto = nullptr; // Utilisé ici pour Roboto Bold

    // Fonction de vérification de l'existence d'un fichier
    inline bool FileExists(const char* filename) {
        std::ifstream ifs(filename);
        return ifs.good();
    }

    inline bool LoadFont() {
        ImGuiIO& io = ImGui::GetIO();
        io.LogFilename = nullptr;
        io.IniFilename = nullptr;

        // Chemins absolus pour les fichiers de police
        const char* arialPath = "C:/Windows/Fonts/arial.ttf";
        const char* arialBoldPath = "C:/Windows/Fonts/arialbd.ttf";
        const char* fontAwesomePath = "C:/Windows/Fonts/fontawesome-webfont.ttf";
        const char* robotoBoldPath = "C:/Windows/Fonts/Roboto-Bold.ttf";

        // Charger Arial pour différentes tailles
        if (FileExists(arialPath)) {
            Font_Size_17 = io.Fonts->AddFontFromFileTTF(arialPath, 17.0f);
            Font_Size_15 = io.Fonts->AddFontFromFileTTF(arialPath, 15.0f);
            Font_Size_22 = io.Fonts->AddFontFromFileTTF(arialPath, 22.0f);
            IM_ASSERT(Font_Size_17 && "Failed to load Arial at 17.0f");
            IM_ASSERT(Font_Size_15 && "Failed to load Arial at 15.0f");
            IM_ASSERT(Font_Size_22 && "Failed to load Arial at 22.0f");
        }
        else {
            // Si Arial n'est pas disponible, utiliser la police par défaut d'ImGui
            Font_Size_17 = io.Fonts->AddFontDefault();
            Font_Size_15 = Font_Size_17;
            Font_Size_22 = Font_Size_17;
        }

        // Charger FontAwesome pour les icônes
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.FontDataOwnedByAtlas = false;
        if (FileExists(fontAwesomePath)) {
            Icon_Font = io.Fonts->AddFontFromFileTTF(fontAwesomePath, 22.0f, &icons_config, icons_ranges);
            IM_ASSERT(Icon_Font && "Failed to load FontAwesome!");
        }
        else {
            // En cas d'absence, on peut ne pas fusionner d'icône ou utiliser une alternative
            Icon_Font = nullptr;
        }

        // Charger Roboto Bold
        if (FileExists(robotoBoldPath)) {
            Roboto = io.Fonts->AddFontFromFileTTF(robotoBoldPath, 15.0f);
            IM_ASSERT(Roboto && "Failed to load Roboto Bold!");
        }
        else {
            // Si Roboto Bold n'est pas trouvé, utiliser Arial Bold s'il est disponible
            if (FileExists(arialBoldPath)) {
                Roboto = io.Fonts->AddFontFromFileTTF(arialBoldPath, 15.0f);
                IM_ASSERT(Roboto && "Failed to load Arial Bold as fallback!");
            }
            else {
                Roboto = nullptr;
            }
        }

        // Optionnel : Construire l'atlas de polices maintenant (ImGui_ImplXXXX_CreateFontsTexture() le fera si nécessaire)
        // io.Fonts->Build();

        return true;
    }
}