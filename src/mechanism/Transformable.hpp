//
// Created by adarw on 6/9/26.
//

#ifndef KINEMATICS_TRANSFORMABLE_HPP
#define KINEMATICS_TRANSFORMABLE_HPP
#include "defs.hpp"
#include "Transform.hpp"

namespace kinematics {
    class Transformable {
    public:
        virtual ~Transformable() = default;
        explicit Transformable(){}
        virtual Transform calculateTransformation() = 0;
        Pose3d calculatePose();
    };
} // kinematics

#endif //KINEMATICS_TRANSFORMABLE_HPP