//
// Created by adarw on 6/9/26.
//

#ifndef KINEMATICS_MATHUTILS_HPP
#define KINEMATICS_MATHUTILS_HPP
#include <Eigen/Eigen>
#include "../defs.hpp"

namespace kinematics {
    Eigen::Matrix3d makeSkewSymmetric(const Eigen::Vector3d v);
    Eigen::Matrix4d makeStateMatrix(const Vector6d vec);
}

#endif //KINEMATICS_MATHUTILS_HPP