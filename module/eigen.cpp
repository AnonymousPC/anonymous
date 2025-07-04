module;
#undef in
#undef self
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/FFT>
#include <unsupported/Eigen/CXX11/Tensor>

export module eigen;
import std;

export namespace Eigen
{
    using Eigen::Matrix;
    using Eigen::Vector;
    using Eigen::operator<<;
}