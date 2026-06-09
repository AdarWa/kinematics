//
// Created by adarw on 6/9/26.
//

#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <cmath>
#include "mechanism/joint/Joint.hpp"
#include "mechanism/joint/PrismaticJoint.hpp"
#include "mechanism/joint/RevoluteJoint.hpp"

using namespace kinematics;

TEST(TransformTest, ToAndFromMatrix) {
    Transform original;
    original.translation = Eigen::Vector3d(1.0, 2.0, 3.0);
    original.rotation = Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitZ()).toRotationMatrix();

    Eigen::Matrix4d mat = original.toMatrix();
    Transform recovered = Transform::fromMatrix(mat);

    EXPECT_TRUE(original.translation.isApprox(recovered.translation, 1e-6));
    EXPECT_TRUE(original.rotation.isApprox(recovered.rotation, 1e-6));
}

TEST(PrismaticJointTest, CalculateTransformation) {
    Translation3d origin(0, 0, 0);
    Eigen::Vector3d axis(0, 0, 1); // Move along Z
    double theta = 5.0;            // Translate by 5 units

    PrismaticJoint joint(origin, axis, theta);
    Transform t = joint.calculateTransformation();

    EXPECT_TRUE(t.translation.isApprox(Eigen::Vector3d(0, 0, 5.0), 1e-6));
    EXPECT_TRUE(t.rotation.isApprox(Eigen::Matrix3d::Identity(), 1e-6));
}

TEST(PrismaticJointTest, CalculatePose) {
    PrismaticJoint joint(Translation3d(1, 1, 0), Eigen::Vector3d(1, 0, 0), 3.0);
    Pose3d pose = joint.calculatePose();

    // Expect translation by 3 along X, plus initial translation calculation in twist
    // For prismatic, twist linear = axis. So e^(twist_hat * theta) translates by theta*axis
    EXPECT_DOUBLE_EQ(pose(0), 3.0);
    EXPECT_DOUBLE_EQ(pose(1), 0.0);
    EXPECT_DOUBLE_EQ(pose(2), 0.0);

    // Euler angles should be 0
    EXPECT_DOUBLE_EQ(pose(3), 0.0);
    EXPECT_DOUBLE_EQ(pose(4), 0.0);
    EXPECT_DOUBLE_EQ(pose(5), 0.0);
}

TEST(RevoluteJointTest, CalculateTransformation) {
    Translation3d origin(0, 0, 0);
    Eigen::Vector3d axis(0, 0, 1); // Rotate around Z
    double theta = M_PI / 2.0;     // 90 degrees

    RevoluteJoint joint(origin, axis, theta);
    Transform t = joint.calculateTransformation();

    // Origin is 0,0,0 so translation remains 0,0,0
    EXPECT_TRUE(t.translation.isApprox(Eigen::Vector3d(0, 0, 0), 1e-6));

    Eigen::Matrix3d expected_rot = Eigen::AngleAxisd(theta, axis).toRotationMatrix();
    EXPECT_TRUE(t.rotation.isApprox(expected_rot, 1e-6));
}

TEST(RevoluteJointTest, SetAndGetTheta) {
    RevoluteJoint joint(Translation3d(0, 0, 0), Eigen::Vector3d(1, 0, 0), 0.0);
    EXPECT_DOUBLE_EQ(joint.getTheta(), 0.0);

    joint.setTheta(M_PI);
    EXPECT_DOUBLE_EQ(joint.getTheta(), M_PI);
}