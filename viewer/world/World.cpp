//
// Created by adarw on 6/11/26.
//

#include "World.hpp"

#include "../window/windowUtils.hpp"

namespace kinematics {
    namespace viewer {
        World::World() {
            filament::Engine::Config config; // TODO: use env vars to init
            config.minCommandBufferSizeMB = 250;
            config.driverHandleArenaSizeMB = 250;
            const filament::Viewport viewport = {0,0,800,600};
            void* nativeWindowHandler = setupNativeWindow("Kinematics Viewer", viewport.width, viewport.height);

            World(config, nativeWindowHandler, viewport);
        }

        World::World(filament::Engine::Config engineConfig, void* nativeWindowHandler, filament::Viewport viewport) {
            engine = filament::Engine::create(filament::Engine::Backend::DEFAULT, nullptr, nullptr, &engineConfig);
            swapChain = engine->createSwapChain(nativeWindowHandler);
            renderer = engine->createRenderer();
            scene = engine->createScene();

            camera = new WorldCamera(engine);

            view = engine->createView();
            view->setScene(scene);
            view->setCamera(camera->camera);
            view->setViewport(viewport);
            renderer->setClearOptions({.clearColor = {0.1f, 0.15f, 0.25f, 1.0f}, .clear = true});

            camera->camera->lookAt({0.0, 0.0, 5.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0});
            camera->camera->setProjection(45.0, 800.0 / 600.0, 0.1, 100.0);
        }

        World::~World() {
            // Destroy all entities
            engine->destroy(sun);
            delete camera;

            // TODO: Destroy all populated entities

            engine->destroy(view);
            engine->destroy(scene);
            engine->destroy(renderer);
            engine->destroy(swapChain);
            filament::Engine::destroy(&engine);
        }

        utils::Entity& World::createSun(float intensity) {
            sun = utils::EntityManager::get().create();
            filament::LightManager::Builder(filament::LightManager::Type::DIRECTIONAL)
                .color(filament::Color::toLinear<filament::ACCURATE>(filament::sRGBColor(1.0f, 1.0f, 1.0f)))
                .intensity(intensity)
                .direction({0.5f, -1.0f, -0.5f})
                .build(*engine, sun);
            scene->addEntity(sun);
            return sun;
        }

        void World::injectEntity(utils::Entity entity) {
            entities.push_back(entity);
        }
    } // viewer
} // kinematics