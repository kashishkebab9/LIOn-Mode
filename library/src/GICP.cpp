
#include "GICP.h"
#include <iostream>
#include <Eigen/Geometry> // for AngleAxis

GICP::GICP(std::vector<GICPPoint>& source, std::vector<GICPPoint>& target)
    : source_points_(source), target_points_(target), R_(Eigen::Matrix3f::Identity()), t_(Eigen::Vector3f::Zero()) {
    std::vector<Eigen::Vector3f> target_coords;
    for (const auto& pt : target)
        target_coords.push_back(pt.position);
    target_kdtree_.buildTree(target_coords);
}

void GICP::align(int max_iterations, float tolerance) {
    float last_cost = std::numeric_limits<float>::max();
    for (int iter = 0; iter < max_iterations; ++iter) {
        optimizeStep();
        float cost = computeCost();
        std::cout << "Iter " << iter << ": Cost = " << cost << std::endl;
        if (std::abs(last_cost - cost) < tolerance) break;
        last_cost = cost;
    }
}

void GICP::transformSource() {
    for (auto& pt : source_points_)
        pt.position = R_ * pt.position + t_;
}

float GICP::computeCost() {
    float cost = 0.0f;
    for (const auto& p : source_points_) {
        auto [nn, _] = target_kdtree_.nearestNeighbor(p.position);
        Eigen::Vector3f q = nn->coordinate;

        // Mahalanobis matrix
        Eigen::Matrix3f Σp = p.covariance;
        Eigen::Matrix3f Σq = Eigen::Matrix3f::Identity() * 1e-2;  // Approx. or load per-node
        Eigen::Matrix3f M = (Σp + Σq).inverse();

        Eigen::Vector3f e = p.position - q;
        cost += e.transpose() * M * e;
    }
    return cost;
}

void GICP::optimizeStep() {
    // Placeholder: you can plug in Gauss-Newton, Ceres, etc.
    // For now we assume a small constant delta for illustration
    Eigen::Vector3f delta_t(0.001f, 0.0f, 0.0f);
    Eigen::AngleAxisf delta_R(0.001f, Eigen::Vector3f::UnitZ());

    t_ += delta_t;
    R_ = delta_R.toRotationMatrix() * R_;
    transformSource();
}

Eigen::Matrix3f GICP::getRotation() const { return R_; }
Eigen::Vector3f GICP::getTranslation() const { return t_; }
