//
// Created by adarw on 6/11/26.
//

#include "World.hpp"

#include "../transform/TransformUtils.hpp"
#include "../window/windowUtils.hpp"

namespace kinematics {
    namespace viewer {
        World::World() {
            filament::Engine::Config config; // TODO: use env vars to init
            config.minCommandBufferSizeMB = 250;
            config.driverHandleArenaSizeMB = 250;
            const filament::Viewport viewport = {0,0,800,600};
            sdl_window = std::make_shared<SDL_Window*>();
            void* nativeWindowHandler = setupNativeWindow("Kinematics Viewer", viewport.width, viewport.height, sdl_window);

            initWorld(config, nativeWindowHandler, viewport);
        }

        World::World(filament::Engine::Config engineConfig, void* nativeWindowHandler, filament::Viewport viewport) {
            initWorld(engineConfig, nativeWindowHandler, viewport);
        }

        void World::initWorld(filament::Engine::Config engineConfig, void* nativeWindowHandler, filament::Viewport viewport) {
            engine = filament::Engine::create(filament::Engine::Backend::OPENGL, nullptr, nullptr, &engineConfig);
            swapChain = engine->createSwapChain(nativeWindowHandler);
            renderer = engine->createRenderer();
            scene = engine->createScene();

            camera = new WorldCamera(engine);

            view = engine->createView();
            view->setScene(scene);
            view->setCamera(camera->camera);
            view->setViewport(viewport);
            renderer->setClearOptions({.clearColor = {0.1f, 0.15f, 0.25f, 1.0f}, .clear = true});

            camera->camera->lookAt({0.0, 0.0, 2.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0});
            camera->camera->setProjection(45.0, static_cast<double>(viewport.width) / viewport.height, 0.1, 100.0);

            modelProvider = std::make_unique<ModelProvider>(engine);

            createSun();
        }

        World::~World() {
            // Destroy all entities
            engine->destroy(view);
            engine->destroy(scene);

            modelProvider.reset();

            engine->destroy(sun);
            delete camera;

            for (const utils::Entity entity : entities) {
                engine->destroy(entity);
            }

            engine->destroy(renderer);
            engine->destroy(swapChain);


            filament::Engine::destroy(&engine);
            if (sdl_window && *sdl_window) {
                destroyWindow(*sdl_window);
            }
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


        utils::Entity World::loadModel(const std::string& file) {
            const filament::gltfio::FilamentAsset* asset = modelProvider->loadAsset(file);
            scene->addEntities(asset->getEntities(), asset->getEntityCount());
            const utils::Entity root = groupEntities(engine, asset->getEntities(), asset->getEntityCount());
            return root;
        }

        void World::injectEntity(const utils::Entity entity) {
            scene->addEntity(entity);
            entities.push_back(entity);
        }

        static void handleEvents(World* world) {
            static SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) world->stop();
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    uint32_t w = event.window.data1;
                    uint32_t h = event.window.data2;
                    world->handleResize(w,h);
                }
            }
        }

        void World::renderView() {
            if (renderer->beginFrame(swapChain)) {
                renderer->render(view);
                renderer->endFrame();
            }
        }

        void World::run() {
            while (running) {
                handleEvents(this);
                renderView();
            }
        }

        void World::stop() {
            running = false;
        }

        void World::handleResize(uint32_t width, uint32_t height) {
            view->setViewport({0, 0, width, height});
            camera->camera->setProjection(45.0, static_cast<double>(width) / height, 0.1, 100.0);
        }
    } // viewer
} // kinematics