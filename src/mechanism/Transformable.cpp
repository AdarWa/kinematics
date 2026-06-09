//
// Created by adarw on 6/9/26.
//

#include "Transformable.hpp"

#include "utils/MathUtils.hpp"

namespace kinematics {
    Pose3d Transformable::calculatePose() {
        Transform t = calculateTransformation();
        return makePose3dFromTransform(t);
    }
} // kinematics