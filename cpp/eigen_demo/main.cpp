#include <iostream>
#include "Eigen/Dense"


int main() {
    std::cout << "Hello, Eigen!" << std::endl;
    Eigen::Matrix2d matrix; // 2*2矩阵 double类型
    matrix<< 2,3,2,1;

    std::cout << "matrix = \n"<< matrix <<std::endl;

    Eigen::MatrixXd matrix_x(2,2);
    matrix_x<<1,1,2,2;
//    matrix_x<<2,2;
    std::cout << "matrix_x = \n"<< matrix_x <<std::endl;
//    matrix_x<<2,2;
//    std::cout << "matrix_x = \n"<< matrix_x <<std::endl;
    Eigen::Vector2d v(1,2);

    Eigen::MatrixXf m_matrix_zero = Eigen::MatrixXf::Zero(5,5); // 零矩阵

    Eigen::MatrixXf m_matrix_identity = Eigen::MatrixXf::Identity(5,5); // 对角矩阵

    // 矩阵的大小
    std::cout<<matrix.cols()<<std::endl;
    std::cout<<matrix.rows()<<std::endl;

    // // 更多操作: https://guyuehome.com/34163
    // // 官方库: https://gitlab.com/libeigen/eigen.git

    return 0;
}
