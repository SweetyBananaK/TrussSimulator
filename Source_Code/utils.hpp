#pragma once
#include <Eigen/Dense>

namespace Utils {
    const int Dynamic=Eigen::Dynamic;
    const double JointR = 5.5;

    const double arrow_head_angle = M_PI/7;
    const double displacement_arrow_head_length = 6.0;
    const double force_arrow_head_length = 10;
    const double ForceArrowScaling = 0.28;

    const double support_width = 10.0;
    const double support_height = 18.0;

    const double newton_tol = 0.0000001;
}
