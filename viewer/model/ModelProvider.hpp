//
// Created by adarw on 6/11/26.
//

#ifndef KINEMATICS_MODELPROVIDER_HPP
#define KINEMATICS_MODELPROVIDER_HPP


#include <memory>
#include <string>
#include <vector>
#include <filament/Engine.h>
#include <gltfio/AssetLoader.h>
#include <gltfio/ResourceLoader.h>
#include <gltfio/MaterialProvider.h>

namespace kinematics {
    namespace viewer {
        class ModelProvider {
        private:
            filament::gltfio::MaterialProvider* materialProvider;
            filament::gltfio::AssetLoader* assetLoader;
            std::unique_ptr<filament::gltfio::ResourceLoader> resourceLoader;
            std::vector<filament::gltfio::FilamentAsset*> assets;
        public:
            explicit ModelProvider(filament::Engine* engine);
            ~ModelProvider();
            filament::gltfio::FilamentAsset* loadAsset(std::string file);
            void destroyAsset(filament::gltfio::FilamentAsset* asset);
            std::vector<filament::gltfio::FilamentAsset*> getLoadedAssets();
        };
    } // viewer
} // kinematics

#endif //KINEMATICS_MODELPROVIDER_HPP