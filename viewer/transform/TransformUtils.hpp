//
// Created by adarw on 6/28/26.
//

#ifndef KINEMATICS_TRANSFORMUTILS_HPP
#define KINEMATICS_TRANSFORMUTILS_HPP

#include "filament/Engine.h"
#include <math/mat4.h>
#include <utils/Entity.h>
#include <numbers>

namespace kinematics::viewer {

    utils::Entity groupEntities(filament::Engine* engine, const utils::Entity* entities, int count);
    void teleportEntity(filament::Engine* engine, utils::Entity& entity, filament::math::mat4f& transform);
    void transformEntity(filament::Engine* engine, utils::Entity& entity, filament::math::mat4f& transform);

    namespace transforms {
        constexpr float deg2rad(const float deg) {
            return deg * (std::numbers::pi / 180.0);
        }

        constexpr float rad2deg(const float rad) {
            return rad * (180.0 / std::numbers::pi);
        }
        filament::math::mat4f makeXYZTransform(float x, float y, float z);
        filament::math::mat4f makeEulerAngleTransform(float roll, float pitch, float yaw);
        filament::math::mat4f makeScaleTransform(float scale);
    }
}

#endif //KINEMATICS_TRANSFORMUTILS_HPP