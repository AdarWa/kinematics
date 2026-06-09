//
// Created by adarw on 6/9/26.
//

#ifndef KINEMATICS_TRANSFORM_HPP
#define KINEMATICS_TRANSFORM_HPP
#include <Eigen/Eigen>

namespace kinematics {
    struct Transform {
        Eigen::Vector3d translation;
        Eigen::Matrix3d rotation;

        Eigen::Matrix4d toMatrix() const {
            Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
            T.block<3, 3>(0, 0) = rotation;
            T.block<3, 1>(0, 3) = translation;
            return T;
        }

        static Transform fromMatrix(Eigen::Matrix4d matrix) {
            Transform t;
            t.translation = matrix.block<3,1>(0,3);
            t.rotation = matrix.block<3,3>(0,0);
            return t;
        }
    };
}

#endif //KINEMATICS_TRANSFORM_HPP