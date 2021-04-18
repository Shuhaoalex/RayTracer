#ifndef EIGEN_TYPES_H
#define EIGEN_TYPES_H
#include <Eigen/Dense>
//dense types
using vec3 = Eigen::Vector3d;
using point3 = vec3;
using color = vec3;
//using Vector4d = Eigen::Matrix<double, 4, 1>;
//using Vector6d = Eigen::Matrix<double, 6, 1>;
//using Vector9d = Eigen::Matrix<double, 9, 1>;
//using Vector12d = Eigen::Matrix<double, 12, 1>;
//using Vector4b = Eigen::Matrix<bool, 4, 1>;

//using Matrix36d = Eigen::Matrix<double, 3, 6>;
//using Matrix34d = Eigen::Matrix<double, 3, 4>;
//using Matrix43d = Eigen::Matrix<double, 4, 3>;
//using Matrix66d = Eigen::Matrix<double, 6, 6>;
//using Matrix99d = Eigen::Matrix<double, 9, 9>;
//using Matrix1212d = Eigen::Matrix<double, 12, 12>;

//using Matrix44f = Eigen::Matrix<float, 4, 4>;
//using RMatrixX3d = Eigen::Matrix<double, Eigen::Dynamic, 3, Eigen::RowMajor>;
//using RMatrixX2i = Eigen::Matrix<int, Eigen::Dynamic, 2, Eigen::RowMajor>;
//using RMatrixX3i = Eigen::Matrix<int, Eigen::Dynamic, 3, Eigen::RowMajor>;
//using RMatrixX4i = Eigen::Matrix<int, Eigen::Dynamic, 4, Eigen::RowMajor>;

////sparse types
//using SparseMatrixd = Eigen::SparseMatrix<double>;
#endif