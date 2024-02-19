#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <class_loader/class_loader.hpp>
#include <rclcpp_components/node_factory.hpp>


int main(int argc, char *argv[]) {
  std::cout << "ros2 component" << std::endl;
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;
  rclcpp::NodeOptions options;
  std::vector<class_loader::ClassLoader *> loaders;
  std::vector<rclcpp_components::NodeInstanceWrapper> node_wrappers;

  auto loader = new class_loader::ClassLoader("libpub_component.so");
  auto classes = loader->getAvailableClasses<rclcpp_components::NodeFactory>();
  for (auto clazz : classes) {
      std::cout << "class:" << clazz.c_str() << std::endl;
      auto node_factory = loader->createInstance<rclcpp_components::NodeFactory>(clazz);
      auto wrapper = node_factory->create_node_instance(options);
      auto node = wrapper.get_node_base_interface();
      node_wrappers.push_back(wrapper);
      exec.add_node(node);
  }
  loaders.push_back(loader);

  exec.spin();

  for (auto wrapper : node_wrappers) {
    exec.remove_node(wrapper.get_node_base_interface());
  }
  node_wrappers.clear();

  rclcpp::shutdown();

  return 0;
}
