//
// Created by adarw on 6/28/26.
//

#ifndef KINEMATICS_TRANSFORMUTILS_HPP
#define KINEMATICS_TRANSFORMUTILS_HPP

#include "filament/Engine.h"

namespace kinematics::viewer {

    utils::Entity groupEntities(filament::Engine* engine, utils::Entity* entities, int count);
    void teleportEntity(filament::Engine* engine, utils::Entity entity, filament::math::mat4f transform);
    void transformEntity(filament::Engine* engine, utils::Entity& entity, filament::math::mat4f& transform);
}

#endif //KINEMATICS_TRANSFORMUTILS_HPP