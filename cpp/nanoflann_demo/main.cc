#include <cstdlib>
#include <ctime>
#include <iostream>
#include <nanoflann.hpp>
#include <vector>

struct Point {
  double x;
  double y;
};
typedef Point SamplePoint;
typedef std::vector<SamplePoint> SamplePoints;
typedef std::vector<double> KDTreeNode;
typedef std::vector<KDTreeNode> KDTreeNodes;

class KDTreeAdaptor {
 public:
  typedef nanoflann::KDTreeSingleIndexAdaptor<
      nanoflann::metric_L2::template traits<double, KDTreeAdaptor>::distance_t,
      KDTreeAdaptor, 2 /* dimensionality */, size_t /* index type */>
      KDTreeIndex;
  KDTreeAdaptor() {}
  inline size_t kdtree_get_point_count() const { return matrix_.size(); }
  inline double kdtree_get_pt(const size_t idx, const size_t dim) const {
    return matrix_[idx][dim];
  }
  template <class BBOX>
  bool kdtree_get_bbox(BBOX& /*bb*/) const {
    return false;
  }
  void Init(const SamplePoints& samples) {
    matrix_.clear();
    matrix_.reserve(samples.size());
    KDTreeNode node(2);
    for (const auto& point : samples) {
      node[0] = point.x;
      node[1] = point.y;
      matrix_.emplace_back(node);
    }
  }
  const KDTreeNodes& matrix() const { return matrix_; }

 private:
  KDTreeNodes matrix_;
};

class KDTree {
 public:
  KDTree() {}
  void Init(const SamplePoints& samples) {
    adaptor_.Init(samples);
    index_.reset(new KDTreeAdaptor::KDTreeIndex(
        samples.size(), adaptor_, nanoflann::KDTreeSingleIndexAdaptorParams()));
  }
  SamplePoints Query(const SamplePoint& query_point, size_t num_closest) {
    SamplePoints ret;
    std::vector<size_t> indexes(num_closest);    // 必须设置长度
    std::vector<double> dists_sqr(num_closest);  // 必须设置长度
    KDTreeNode query_node(2);
    query_node[0] = query_point.x;
    query_node[1] = query_point.y;
    std::cout << "target x: " << query_node[0] << std::endl;
    std::cout << "target y: " << query_node[1] << std::endl;
    index_->knnSearch(&query_node[0], num_closest, &indexes[0], &dists_sqr[0]);
    if (indexes.size() > adaptor_.matrix().size()) {
      return ret;
    }
    for (const auto& index : indexes) {
      SamplePoint node;
      node.x = adaptor_.matrix().at(index)[0];
      node.y = adaptor_.matrix().at(index)[1];
      ret.emplace_back(node);
    }
    return ret;
  }

 private:
  KDTreeAdaptor adaptor_;
  std::shared_ptr<KDTreeAdaptor::KDTreeIndex> index_;
};

int main(int argc, char* argv[]) {
  KDTree kdtree;
  SamplePoints samples;
  SamplePoint point;
  for (int i = 0; i < 10; i++) {
    point.x = i;
    point.y = i + 1;
    samples.emplace_back(point);
  }
  kdtree.Init(samples);
  SamplePoint target{1, 2};
  auto ret = kdtree.Query(target, 2);
  std::cout << "x1: " << ret.front().x << std::endl;  // 1
  std::cout << "y1: " << ret.front().y << std::endl;  // 2
  std::cout << "x2: " << ret.back().x << std::endl;   // 0
  std::cout << "y2: " << ret.back().y << std::endl;   // 1
}
