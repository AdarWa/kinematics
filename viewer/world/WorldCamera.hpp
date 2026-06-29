//
// Created by adarw on 6/11/26.
//

#ifndef KINEMATICS_WORLDCAMERA_HPP
#define KINEMATICS_WORLDCAMERA_HPP
#include "filament/Camera.h"
#include "filament/Engine.h"
#include "filament/View.h"
#include "utils/Entity.h"
#include "utils/EntityManager.h"

namespace kinematics::viewer {
    struct WorldCamera {
    private:
        utils::Entity entity;
        filament::Engine* engine;
        filament::math::float3 lookAtPosition = {0.0f, 0.0f,0.0f};
        filament::Camera* camera = nullptr;

    public:
        explicit WorldCamera(filament::Engine* engine_) : engine(engine_) {
            entity = utils::EntityManager::get().create();
            camera = engine->createCamera(entity);
        }

        ~WorldCamera() {
            if (engine) {
                if (camera) {
                    engine->destroyCameraComponent(entity);
                    camera = nullptr;
                }
                engine->destroy(entity);
            }
        }

        filament::math::float3 getPosition() const {
            return camera->getPosition();
        }

        filament::math::float3 getLookAtPosition() const {
            return lookAtPosition;
        }

        void setPosition(const filament::math::float3 pose) const {
            camera->lookAt(pose, lookAtPosition);
        }

        void setLookAtPosition(const filament::math::float3 lookAtPose) {
            lookAtPosition = lookAtPose;
            camera->lookAt(getPosition(), lookAtPose);
        }

        void assignCamera(filament::View* view) const {
            view->setCamera(camera);
        }

        void handleResize(const int width, const int height) const {
            camera->setProjection(45.0, static_cast<double>(width) / height, 0.1, 100.0);
        }
    };
}

#endif //KINEMATICS_WORLDCAMERA_HPP