//
// Created by adarw on 6/11/26.
//

#ifndef KINEMATICS_WORLDCAMERA_HPP
#define KINEMATICS_WORLDCAMERA_HPP
#include "filament/Engine.h"
#include "utils/Entity.h"
#include "utils/EntityManager.h"

namespace kinematics::viewer {
    struct WorldCamera {
    private:
        utils::Entity entity;
        filament::Engine* engine;
    public:
        filament::Camera* camera = nullptr;
        explicit WorldCamera(filament::Engine* engine_) : engine(engine_) {
            entity = utils::EntityManager::get().create();
            camera = engine->createCamera(entity);
        }
        ~WorldCamera() {
            if (camera) {
                engine->destroyCameraComponent(entity); // <--- Use the dedicated Camera destroyer
            }
        }
    };
}

#endif //KINEMATICS_WORLDCAMERA_HPP