#include "../include/GICP.h"
#include <iostream>

int main() {
    // Generate two small clouds
    std::vector<GICPPoint> src, tgt;
    for (int i = 0; i < 100; ++i) {
        Eigen::Vector3f p = Eigen::Vector3f::Random();
        GICPPoint pt;
        pt.position = p;
        pt.covariance = Eigen::Matrix3f::Identity() * 0.01f;
        src.push_back(pt);

        pt.position = p + Eigen::Vector3f(0.1f, 0.0f, 0.0f); // shifted target
        tgt.push_back(pt);
    }

    GICP gicp(src, tgt);
    gicp.align();
    std::cout << "Estimated Translation: \n" << gicp.getTranslation() << std::endl;
    std::cout << "Estimated Rotation: \n" << gicp.getRotation() << std::endl;
}
