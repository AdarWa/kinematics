//
// Created by adarw on 6/8/26.
//

#ifndef KINEMATICS_REVOLUTEJOINT_HPP
#define KINEMATICS_REVOLUTEJOINT_HPP
#include "Joint.hpp"
#include "../../defs.hpp"

namespace kinematics {
    class PrismaticJoint : public Joint {
    private:
        Eigen::Vector3d axis;
    protected:
        Twist3d calculateTwist() override;
    public:
        explicit PrismaticJoint(const Translation3d& origin, const Eigen::Vector3d& axis, const double theta = 0) : Joint(origin, theta), axis(axis){}
    };
} // kinematics

#endif //KINEMATICS_REVOLUTEJOINT_HPP