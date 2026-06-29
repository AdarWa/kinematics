//
// Created by adarw on 6/28/26.
//

#include "TransformUtils.hpp"

#include <filament/Engine.h>
#include <filament/TransformManager.h>
#include <math/mat4.h>
#include <math/vec3.h>
#include <stdexcept>
#include "utils/Entity.h"
#include "utils/EntityManager.h"
#include "utils/ExceptionUtils.hpp"

namespace kinematics::viewer {
    static filament::TransformManager::Instance getEntityInstance(filament::TransformManager& tcm, const utils::Entity& entity) {
        auto instance = tcm.getInstance(entity);
        if (!instance.isValid()) {
            throw std::runtime_error("Caught invalid entity!");
        }
        return instance;
    }

    utils::Entity groupEntities(filament::Engine* engine, const utils::Entity* entities, int count) {
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
        filament::math::mat4f currTransform = tcm.getTransform(getEntityInstance(tcm, entity)) *transform;
        teleportEntity(engine, entity, currTransform);
        KINEMATICS_CATCH
    }

    filament::math::mat4f transforms::makeXYZTransform(float x, float y, float z) {
        return filament::math::mat4f::translation(filament::math::float3{x, y, z});
    }

    /**
     *
     * @param roll roll angle in radians
     * @param pitch pitch angle in radians
     * @param yaw yaw angle in radians
     * @return A rotation matrix
     */
    filament::math::mat4f transforms::makeEulerAngleTransform(float roll, float pitch, float yaw) {
        filament::math::mat4f rRoll  = filament::math::mat4f::rotation(roll,  filament::math::float3{0.0f, 0.0f, 1.0f});
        filament::math::mat4f rPitch = filament::math::mat4f::rotation(pitch, filament::math::float3{1.0f, 0.0f, 0.0f});
        filament::math::mat4f rYaw   = filament::math::mat4f::rotation(yaw,   filament::math::float3{0.0f, 1.0f, 0.0f});

        return rYaw * rPitch * rRoll;
    }

    filament::math::mat4f transforms::makeScaleTransform(float scale) {
        return filament::math::mat4f::scaling(filament::math::float3{scale});
    }
}
