module;
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/unsupported/Eigen/FFT>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>

export module eigen;
import std;

namespace Eigen
{
    export using Eigen::Dynamic;
    export using Eigen::FFT;
    export using Eigen::Matrix;
    export using Eigen::Map;
    export using Eigen::Tensor;
    export using Eigen::TensorMap;
    export using Eigen::Vector;
}