module;
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/unsupported/Eigen/FFT>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>

export module eigen;
import std;

export namespace Eigen
{
    using Eigen::Dynamic;
    using Eigen::FFT;
    using Eigen::Matrix;
    using Eigen::Map;
    using Eigen::Tensor;
    using Eigen::TensorMap;
    using Eigen::Vector;
}