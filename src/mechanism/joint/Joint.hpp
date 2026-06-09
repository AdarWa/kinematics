//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_JOINT_HPP
#define KINEMATICS_JOINT_HPP
#include <optional>
#include <utility>

#include "../../defs.hpp"

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

    class Joint {
    protected:
        Translation3d origin;
        std::optional<Twist3d> twist;
        double theta;
    public:
        virtual ~Joint() = default;
        explicit Joint(Translation3d  origin_pose = Translation3d(), const double theta = 0) : origin(std::move(origin_pose)), theta(theta) {}
        virtual Twist3d calculateTwist() = 0;
        Transform calculateTransformation();
        Pose3d calculatePose();
        void setTheta(double newTheta);
        [[nodiscard]] double getTheta() const;
        Translation3d& getOrigin();

    };
} // kinematics

#endif //KINEMATICS_JOINT_HPP