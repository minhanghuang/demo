#include <iostream>
#include "Eigen/Dense"


int main() {
    std::cout << "Hello, Eigen!" << std::endl;
    Eigen::Matrix2d m_matrix; // 2*2矩阵 double类型
    m_matrix<< 2,3,2.2,1;
    std::cout << "m_matrix = \n"<< m_matrix <<std::endl;

    Eigen::MatrixXf m_matrix_zero = Eigen::MatrixXf::Zero(5,5); // 零矩阵

    Eigen::MatrixXf m_matrix_identity = Eigen::MatrixXf::Identity(5,5); // 对角矩阵

    // 矩阵的大小
    std::cout<<m_matrix.cols()<<std::endl;
    std::cout<<m_matrix.rows()<<std::endl;

    // // 更多操作: https://guyuehome.com/34163
    // // 官方库: https://gitlab.com/libeigen/eigen.git

    return 0;
}
