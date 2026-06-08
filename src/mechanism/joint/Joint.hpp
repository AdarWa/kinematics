//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_JOINT_HPP
#define KINEMATICS_JOINT_HPP
#include <optional>
#include <utility>

#include "../../defs.hpp"

namespace kinematics {
    class Joint {
    protected:
        Translation3d origin;
        std::optional<Twist3d> twist;
        double theta;
    public:
        virtual ~Joint() = default;
        explicit Joint(Translation3d  origin_pose = Translation3d(), const double theta = 0) : origin(std::move(origin_pose)), theta(theta) {}
        virtual Twist3d calculateTwist() = 0;
        Pose3d calculatePose();
        void setTheta(double theta);
        [[nodiscard]] double getTheta() const;

    };
} // kinematics

#endif //KINEMATICS_JOINT_HPP