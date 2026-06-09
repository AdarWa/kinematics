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
}
