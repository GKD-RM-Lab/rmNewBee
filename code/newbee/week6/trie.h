//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// trie.h
//
// Identification: src/include/primer/trie.h
//
// Copyright (c) 2015-2025, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <algorithm>
#include <cstddef>
#include <future>  // 不进行风格检查
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string_view>
#include <string>

namespace bustub {

/// 一种特殊类型，会阻止移动构造函数和移动赋值运算符。用于TrieStore测试。
class MoveBlocked {
 public:
  // 显式构造函数，接收一个std::future<int>类型的参数
  explicit MoveBlocked(std::future<int> wait) : wait_(std::move(wait)) {}

  // 删除拷贝构造函数
  MoveBlocked(const MoveBlocked &) = delete;
  // 移动构造函数
  MoveBlocked(MoveBlocked &&that) noexcept {
    // 如果另一个对象还未等待
    if (!that.waited_) {
      // 等待future完成
      that.wait_.get();
    }
    // 标记两个对象都已等待
    that.waited_ = waited_ = true;
  }

  // 删除拷贝赋值运算符
  auto operator=(const MoveBlocked &) -> MoveBlocked & = delete;
  // 移动赋值运算符
  auto operator=(MoveBlocked &&that) noexcept -> MoveBlocked & {
    // 如果另一个对象还未等待
    if (!that.waited_) {
      // 等待future完成
      that.wait_.get();
    }
    // 标记两个对象都已等待
    that.waited_ = waited_ = true;
    return *this;
  }

  // 标记是否已经等待
  bool waited_{false};
  // 存储一个future对象
  std::future<int> wait_;
};

// TrieNode是Trie（字典树）中的一个节点。
class TrieNode {
 public:
  // 默认构造函数，创建一个没有子节点的TrieNode。
  TrieNode() = default;

  // 显式构造函数，创建一个带有一些子节点的TrieNode。
  explicit TrieNode(std::map<char, std::shared_ptr<const TrieNode>> children) : children_(std::move(children)) {}

  // 虚析构函数，确保正确释放派生类对象。
  virtual ~TrieNode() = default;

  // Clone方法返回此TrieNode的一个副本。如果TrieNode有值，则该值也会被复制。
  // 此函数的返回类型是一个指向TrieNode的unique_ptr。
  //
  // 不能使用拷贝构造函数来克隆节点，因为它不知道`TrieNode`是否包含值。
  //
  // 注意：如果要将`unique_ptr`转换为`shared_ptr`，可以使用`std::shared_ptr<T>(std::move(ptr))`。
  virtual auto Clone() const -> std::unique_ptr<TrieNode> { return std::make_unique<TrieNode>(children_); }

  // 子节点的映射，键是键中的下一个字符，值是下一个TrieNode。
  // 必须使用此结构存储子节点信息。不允许从该结构中移除`const`。
  std::map<char, std::shared_ptr<const TrieNode>> children_;

  // 指示该节点是否为终端节点。
  bool is_value_node_{false};

  // 除存储子节点外，你可以在此处添加额外的字段和方法。但一般来说，完成此项目不需要添加额外字段。
};

// TrieNodeWithValue是一个TrieNode，它还关联了一个类型为T的值。
template <class T>
class TrieNodeWithValue : public TrieNode {
 public:
  // 创建一个没有子节点但有值的字典树节点。
  explicit TrieNodeWithValue(std::shared_ptr<T> value) : value_(std::move(value)) { this->is_value_node_ = true; }

  // 创建一个带有子节点和值的字典树节点。
  TrieNodeWithValue(std::map<char, std::shared_ptr<const TrieNode>> children, std::shared_ptr<T> value)
      : TrieNode(std::move(children)), value_(std::move(value)) {
    this->is_value_node_ = true;
  }

  // 重写Clone方法以同时克隆值。
  //
  // 注意：如果要将`unique_ptr`转换为`shared_ptr`，可以使用`std::shared_ptr<T>(std::move(ptr))`。
  auto Clone() const -> std::unique_ptr<TrieNode> override {
    return std::make_unique<TrieNodeWithValue<T>>(children_, value_);
  }

  // 与此字典树节点关联的值。
  std::shared_ptr<T> value_;
};

// Trie是一种将字符串映射到类型T的值的数据结构。Trie上的所有操作都不应修改Trie本身。
// 它应尽可能重用现有节点，并创建新节点来表示新的Trie。
//
// 不允许在本项目中移除任何`const`，也不允许使用`mutable`来绕过`const`检查。
class Trie {
 private:
  // 字典树的根节点。
  std::shared_ptr<const TrieNode> root_{nullptr};

  // 使用给定的根节点创建一个新的字典树。
  explicit Trie(std::shared_ptr<const TrieNode> root) : root_(std::move(root)) {}

 public:
  // 创建一个空的字典树。
  Trie() = default;

  // 根据给定的键获取对应的值
  
  template <class T>
  auto Get(std::string_view key) const -> const T *;

  // 根据给定的键值对插入或更新数据
  template <class T>
  auto Put(std::string_view key, T value) const -> Trie;

  // 根据给定的键删除数据
  template <class T>
  auto Remove(std::string_view key) const -> Trie;

  // 获取字典树的根节点，仅应在测试用例中使用。
  auto GetRoot() const -> std::shared_ptr<const TrieNode> { return root_; }
};

}  // namespace bustub
