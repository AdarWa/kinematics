//
// Created by adarw on 6/28/26.
//

#include "TransformUtils.hpp"

#include <filament/Engine.h>
#include <filament/TransformManager.h>
#include <math/mat4.h>
#include <math/vec3.h>

#include "utils/Entity.h"
#include "utils/EntityManager.h"
#include "utils/ExceptionUtils.hpp"

namespace kinematics::viewer {
    static filament::TransformManager::Instance getEntityInstance(filament::TransformManager& tcm, utils::Entity& entity) {
        auto instance = tcm.getInstance(entity);
        if (!instance.isValid()) {
            throw std::runtime_error("Caught invalid entity!");
        }
        return instance;
    }

    utils::Entity groupEntities(filament::Engine* engine, utils::Entity* entities, int count) {
        auto& tcm = engine->getTransformManager();
        utils::Entity groupRoot = utils::EntityManager::get().create();
        tcm.create(groupRoot);

        filament::TransformManager::Instance rootInst;

        KINEMATICS_TRY
        rootInst = getEntityInstance(tcm, groupRoot);
        KINEMATICS_CATCH

        for (int i = 0; i < count; i++) {
            KINEMATICS_TRY
            tcm.setParent(getEntityInstance(tcm, entities[i]), rootInst);
            KINEMATICS_CATCH
        }
        return groupRoot;
    }

    void teleportEntity(filament::Engine* engine, utils::Entity& entity, filament::math::mat4f& transform) {
        filament::TransformManager& tcm = engine->getTransformManager();

        KINEMATICS_TRY
        tcm.setTransform(getEntityInstance(tcm, entity), transform);
        KINEMATICS_CATCH
    }

    void transformEntity(filament::Engine* engine, utils::Entity& entity, filament::math::mat4f& transform) {
        filament::TransformManager& tcm = engine->getTransformManager();

        KINEMATICS_TRY
        filament::math::mat4f currTransform = tcm.getTransform(getEntityInstance(tcm, entity));
        teleportEntity(engine, entity, currTransform*transform);
        KINEMATICS_CATCH
    }

}
