module;
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/unsupported/Eigen/FFT>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>

export module eigen;
export namespace Eigen
{
    using Eigen::Matrix;
    using Eigen::Vector;
}