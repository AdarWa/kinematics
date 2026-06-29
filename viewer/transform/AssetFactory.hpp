//
// Created by adarw on 6/29/26.
//

#ifndef KINEMATICS_BASICWORLDUTILS_HPP
#define KINEMATICS_BASICWORLDUTILS_HPP
#include "filament/Engine.h"

namespace kinematics::viewer {
    enum class BasicMaterialType {
        DEFAULT_WHITE,
        DEBUG_RED,
        DEBUG_GREEN,
        DEBUG_BLUE,
        METALLIC_GOLD
    };

    class AssetFactory {
    public:
        AssetFactory(const AssetFactory&) = delete;
        AssetFactory& operator=(const AssetFactory&) = delete;
        AssetFactory(AssetFactory&&) = delete;
        AssetFactory& operator=(AssetFactory&&) = delete;

        static AssetFactory& getInstance() {
            static AssetFactory instance;
            return instance;
        }

        void initialize(filament::Engine* engine, const std::string& baseMaterialPath = "materials/aiDefaultMat.filamat");
        void shutdown();

        // Factory methods
        utils::Entity createCuboid(BasicMaterialType matType, filament::math::float3 size);
        utils::Entity createSphere(BasicMaterialType matType, float radius = 0.5f);

    private:
        AssetFactory() = default;
        ~AssetFactory() = default;

        filament::Engine* engine = nullptr;
        filament::Material* masterMaterial = nullptr;
        std::unordered_map<BasicMaterialType, filament::MaterialInstance*> materials;

        std::vector<std::pair<filament::VertexBuffer*, filament::IndexBuffer*>> allocatedBuffers;

        void setupMaterials();
    };
}

#endif //KINEMATICS_BASICWORLDUTILS_HPP