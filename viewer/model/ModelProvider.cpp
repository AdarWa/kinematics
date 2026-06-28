//
// Created by adarw on 6/11/26.
//

#include "ModelProvider.hpp"

#include <algorithm>
#include <format>
#include <fstream>
#include <stdexcept>

#include "utils/EntityManager.h"

namespace kinematics {
    namespace viewer {
        ModelProvider::ModelProvider(filament::Engine* engine) {
            materialProvider = filament::gltfio::createJitShaderProvider(engine);

            const filament::gltfio::AssetConfiguration assetConfiguration = {
                .engine = engine,
                .materials = materialProvider,
                .entities = &utils::EntityManager::get()
            };
            assetLoader = filament::gltfio::AssetLoader::create(assetConfiguration);

            filament::gltfio::ResourceConfiguration resourceConfiguration{.engine = engine, .normalizeSkinningWeights = true};
            resourceLoader = std::make_unique<filament::gltfio::ResourceLoader>(resourceConfiguration);
        }

        ModelProvider::~ModelProvider() {
            for (filament::gltfio::FilamentAsset* asset : assets) {
                assetLoader->destroyAsset(asset);
            }
            filament::gltfio::AssetLoader::destroy(&assetLoader);
            materialProvider->destroyMaterials();
            delete materialProvider;
        }

        static std::vector<uint8_t> loadFile(std::string file) {
            std::ifstream in(file, std::ios::binary | std::ios::ate);
            if (!in) {
                throw std::runtime_error(std::format("Could not open file: {}", file));
            }
            const size_t size = in.tellg();
            in.seekg(0, std::ios::beg);
            std::vector<uint8_t> buffer(size);
            in.read(reinterpret_cast<char*>(buffer.data()), size);
            return buffer;
        }

        filament::gltfio::FilamentAsset* ModelProvider::loadAsset(std::string file) {
            filament::gltfio::FilamentAsset* asset = nullptr;

            std::vector<uint8_t> fileBuffer = loadFile(file);
            if (fileBuffer.empty()) {
                throw std::runtime_error(std::format("Tried to load asset {}, it seems to be empty!", file));
            }

            asset = assetLoader->createAsset(fileBuffer.data(), fileBuffer.size());
            if (asset == nullptr) {
                throw std::runtime_error(std::format("Failed to parse GLB model {}", file));
            }

            resourceLoader->loadResources(asset);

            assets.push_back(asset);
            return asset;
        }

        void ModelProvider::destroyAsset(filament::gltfio::FilamentAsset* asset) {
            std::erase(assets, asset);
            assetLoader->destroyAsset(asset);
        }

        std::vector<filament::gltfio::FilamentAsset*> ModelProvider::getLoadedAssets() {
            return assets;
        }
    } // viewer
} // kinematics