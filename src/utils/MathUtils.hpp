//
// Created by adarw on 6/9/26.
//

#ifndef KINEMATICS_MATHUTILS_HPP
#define KINEMATICS_MATHUTILS_HPP
#include <Eigen/Eigen>

namespace kinematics {
    Eigen::Matrix3d makeSkewSymmetric(const Eigen::Vector3d v);
}

#endif //KINEMATICS_MATHUTILS_HPP