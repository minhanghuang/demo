#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include <flann/flann.hpp>

typedef struct Point PointType;
typedef std::vector<PointType> Points;
typedef std::pair<PointType, double> Target;
struct Point {
  double x = 0;
  double y = 0;
  double z = 0;
};

class Knn {
public:
  typedef std::vector<std::vector<size_t>> Indices;
  typedef std::vector<std::vector<double>> Dists;
  ~Knn() {
    if (matrix_data_) {
      delete[] matrix_data_->ptr();
    }
  };
  Knn(size_t width = 100, size_t length = 100)
      : width_(width), length_(length) {
    GeneratePoints();
    GenerateMatrix();
  }
  Target SearchPoint(const Point &point) {
    Target target;
    Indices indices;
    Dists dists;
    size_t k = 1;
    Search(point.x, point.y, indices, dists, k);
    if (0 <= indices[0][0] && indices[0][0] < pts_.size()) {
      target.first = pts_.at(indices[0][0]);
      target.second = std::sqrt(dists[0][0]);
    }
    return target;
  }

private:
  void GeneratePoints() {
    for (int i = 0; i < length_; i++) {
      for (int j = 0; j < width_; j++) {
        Point p;
        p.x = i * 1.0;
        p.y = j * 1.0;
        pts_.emplace_back(p);
      }
    }
  }
  void GenerateMatrix() {
    matrix_data_ = std::make_shared<flann::Matrix<double>>(
        new double[pts_.size() * 2], pts_.size(), 2);
    for (size_t i = 0; i < pts_.size(); ++i) {
      (*matrix_data_)[i][0] = pts_[i].x;
      (*matrix_data_)[i][1] = pts_[i].y;
    }
    index_.buildIndex((*matrix_data_));
  }
  bool Search(double x, double y, Indices &indices, Dists &dists,
              size_t k /*个数*/) {
    if (pts_.empty()) {
      return false;
    }
    flann::Matrix<double> query(new double[1 * 2], 1, 2);
    query[0][0] = x;
    query[0][1] = y;
    index_.knnSearch(query, indices, dists, k, flann::SearchParams(128));
    delete[] query.ptr();
    return true;
  }
  const size_t width_;
  const size_t length_;
  Points pts_;
  flann::Index<flann::L2<double>> index_{flann::KDTreeIndexParams(2)};
  std::shared_ptr<flann::Matrix<double>> matrix_data_;
};

int main(int argc, char *argv[]) {
  std::cout << "flann demo" << std::endl;
  std::shared_ptr<Knn> knn = std::make_shared<Knn>(100, 100);
  Point point{1, 2};
  auto target = knn->SearchPoint(point);
  std::cout << "target:" << target.first.x << "," << target.first.y << ","
            << target.second << std::endl;

  return 0;
}
