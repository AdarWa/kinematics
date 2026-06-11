//
// Created by adarw on 6/11/26.
//

#ifndef KINEMATICS_WORLD_HPP
#define KINEMATICS_WORLD_HPP
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/View.h>
#include <filament/Camera.h>
#include <filament/Viewport.h>
#include <filament/LightManager.h>
#include <utils/EntityManager.h>
#include <gltfio/AssetLoader.h>
#include <gltfio/ResourceLoader.h>
#include <gltfio/MaterialProvider.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include "WorldCamera.hpp"
#include "../model/ModelProvider.hpp"

namespace kinematics::viewer {
    class World {
    private:
        filament::Engine* engine;
        filament::SwapChain* swapChain;
        filament::Renderer* renderer;
        filament::Scene* scene;

        WorldCamera* camera;
        filament::View* view;

        std::unique_ptr<ModelProvider> modelProvider;

        //entities
        utils::Entity sun;
        std::vector<utils::Entity> entities;

    public:
        explicit World();
        explicit World(filament::Engine::Config engineConfig, void* nativeWindowHandler, filament::Viewport viewport);
        ~World();
        utils::Entity& createSun(float intensity = 110000.0f);
        void injectEntity(utils::Entity entity);
    };
}

#endif //KINEMATICS_WORLD_HPP
