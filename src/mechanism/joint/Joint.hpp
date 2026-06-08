//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_JOINT_HPP
#define KINEMATICS_JOINT_HPP
#include <optional>

#include "../../defs.hpp"

namespace kinematics {
    class Joint {
    protected:
        Translation3d origin;
        std::optional<Twist3d> twist;
        double theta;
        virtual Twist3d calculateTwist();
    public:
        virtual ~Joint() = default;
        explicit Joint(const Translation3d& origin_pose = Translation3d(), const double theta = 0) : origin(origin_pose), theta(theta) {}
        Pose3d calculatePose();
        void setTheta(double theta);
        double getTheta() const;

    };
} // kinematics

#endif //KINEMATICS_JOINT_HPP