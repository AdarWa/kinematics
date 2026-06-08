//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_DEFS_HPP
#define KINEMATICS_DEFS_HPP
#include <Eigen/Eigen>

namespace kinematics {
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    typedef Eigen::Vector3d Pose2d;
    typedef Vector6d Pose3d;
    typedef Eigen::Vector3d Translation3d;
    // [linear, angular]
    typedef Vector6d Twist3d;
}

#endif //KINEMATICS_DEFS_HPP