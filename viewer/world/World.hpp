//
// Created by adarw on 6/11/26.
//

#ifndef KINEMATICS_WORLD_HPP
#define KINEMATICS_WORLD_HPP
#include <memory>
#include <string>
#include <vector>
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <gltfio/ResourceLoader.h>
#include <SDL.h>

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
        std::shared_ptr<SDL_Window*> sdl_window;

        std::unique_ptr<ModelProvider> modelProvider;

        //entities
        utils::Entity sun;
        std::vector<utils::Entity> entities;
        bool running = true;
        void renderView();
        utils::Entity& createSun(float intensity = 110000.0f);
        void initWorld(filament::Engine::Config engineConfig, void* nativeWindowHandler, filament::Viewport viewport);

    public:
        explicit World();
        explicit World(filament::Engine::Config engineConfig, void* nativeWindowHandler, filament::Viewport viewport);
        ~World();
        World(const World&) = delete;
        World& operator=(const World&) = delete;
        utils::Entity loadModel(const std::string& file);
        void injectEntity(utils::Entity entity);
        void run();
        void stop();
        void handleResize(uint32_t width, uint32_t height);
        filament::Engine* getEngine() const;
    };
}

#endif //KINEMATICS_WORLD_HPP
