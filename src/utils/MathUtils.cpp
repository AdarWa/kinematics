//
// Created by adarw on 6/9/26.
//

#include "MathUtils.hpp"

namespace kinematics {
    Eigen::Matrix3d makeSkewSymmetric(const Eigen::Vector3d& v) {
        Eigen::Matrix3d skew;
        skew << 0.0, -v.z(), v.y(),
            v.z(), 0.0, -v.x(),
            -v.y(), v.x(), 0.0;
        return skew;
    }

    Eigen::Matrix4d makeStateMatrix(Vector6d& vec) {
        const Eigen::Vector3d translation(vec(0), vec(1), vec(2));

        const double roll  = vec(3); // Rotation around X
        const double pitch = vec(4); // Rotation around Y
        const double yaw   = vec(5); // Rotation around Z

        Eigen::Matrix3d rotation;
        rotation = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ())
                 * Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY())
                 * Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX());

        Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
        T.block<3, 3>(0, 0) = rotation;
        T.block<3, 1>(0, 3) = translation;
        return T;
    }
}
