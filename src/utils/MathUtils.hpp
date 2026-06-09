//
// Created by adarw on 6/9/26.
//

#ifndef KINEMATICS_MATHUTILS_HPP
#define KINEMATICS_MATHUTILS_HPP
#include <Eigen/Eigen>
#include "../defs.hpp"
#include "mechanism/joint/Joint.hpp"

namespace kinematics {
    Eigen::Matrix3d makeSkewSymmetric(const Eigen::Vector3d& v);
    Eigen::Matrix4d makeStateMatrix(Vector6d& vec);
    Pose3d makePose3dFromTransform(Transform& t);
}

#endif //KINEMATICS_MATHUTILS_HPP