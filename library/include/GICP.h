#pragma once
#include "KDTree.h"
#include <Eigen/Dense>
#include <vector>
#include <utility>

struct GICPPoint {
    Eigen::Vector3f position;
    Eigen::Matrix3f covariance;
};

class GICP {
public:
    GICP(std::vector<GICPPoint>& source, std::vector<GICPPoint>& target);

    void align(int max_iterations = 20, float tolerance = 1e-4);
    Eigen::Matrix3f getRotation() const;
    Eigen::Vector3f getTranslation() const;

private:
    std::vector<GICPPoint> source_points_;
    std::vector<GICPPoint> target_points_;
    KDTree target_kdtree_;

    Eigen::Matrix3f R_;
    Eigen::Vector3f t_;

    void transformSource();
    float computeCost();
    void optimizeStep();
};

