#pragma once

#include "../../Source/Memory/Memory.hpp"
#include "../../Source/Maths/Vector.hpp"
#include "../../Source/Globals/Globals.hpp"
#include "../../Source/ExternalLibs/ImGui/imgui.h"
#include "../Utilities/Bones.hpp"

class Entities {
public:
    int Team;
    int Health;
    int Armor;
    char Names[128] = { 0 };
    Vector3 Position;
    uintptr_t BoneMatrix;
    bool IsFiring;
    uint32_t Ping;
    Vector3 VecViewOffset;
    bool IsScoped;
    bool IsDormant;

public:
    // Met � jour les informations de l'entit� en lisant la m�moire du processus cible.
    void UpdateEntities(uintptr_t currentPawn, uintptr_t currentController) {
        // Lecture du nom du joueur
        uintptr_t NameAddress = mem.ReadMemory<uintptr_t>(currentController + Offsets::m_sSanitizedPlayerName);
        mem.ReadArray<char>(NameAddress, Names, sizeof(Names));

        // Lecture des autres attributs
        Team = mem.ReadMemory<int>(currentPawn + Offsets::m_iTeamNum);
        Health = mem.ReadMemory<int>(currentPawn + Offsets::m_iHealth);
        Armor = mem.ReadMemory<int>(currentPawn + Offsets::m_ArmorValue);
        Position = mem.ReadMemory<Vector3>(currentPawn + Offsets::m_vOldOrigin);
        BoneMatrix = GetBoneMatrix(currentPawn); // La fonction GetBoneMatrix doit �tre d�finie ailleurs dans votre projet
        IsFiring = mem.ReadMemory<bool>(currentPawn + Offsets::m_iShotsFired);
        Ping = mem.ReadMemory<uint32_t>(currentController + Offsets::m_iPing);
        VecViewOffset = mem.ReadMemory<Vector3>(currentPawn + Offsets::m_vecViewOffset);
        IsScoped = mem.ReadMemory<bool>(currentPawn + Offsets::m_bIsScoped);
        IsDormant = mem.ReadMemory<bool>(currentPawn + Offsets::m_bDormant);
    }

    // Calcule la hauteur de la t�te � partir des positions �cran (pour l'affichage par exemple)
    float GetHeadHeight(Vector2 screenPos, Vector2 headScreenPos) {
        return (screenPos.y - headScreenPos.y) / 8.0f;
    }

    // Retourne une couleur bas�e sur la sant� de l'entit�
    ImColor GetColorHealth() {
        if (Health >= 100)
            return ImColor(0, 255, 0, 255);   // Vert : sant� compl�te
        else if (Health >= 60)
            return ImColor(255, 255, 0, 255); // Jaune : sant� moyenne
        else if (Health >= 30)
            return ImColor(255, 165, 0, 255); // Orange : sant� faible
        else
            return ImColor(255, 0, 0, 255);   // Rouge : sant� critique
    }
};

// Instance globale (inline) d'un tableau de 64 entit�s (compatible avec C++17)
inline Entities entities[64];