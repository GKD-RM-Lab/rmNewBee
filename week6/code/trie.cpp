//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// trie.cpp
//
// 标识：src/primer/trie.cpp
//
// 版权所有 (c) 2015 - 2025，卡内基梅隆大学数据库组
//
//===----------------------------------------------------------------------===//

#include "trie.h"
#include <cassert>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string_view>

namespace bustub {

    /**
     * @brief 获取与给定键相关联的值。
     * 1. 如果该键不在字典树中，返回 nullptr。
     * 2. 如果该键在字典树中但类型不匹配，返回 nullptr。
     * 3. 否则，返回该值。
     */
    template <class T>
    auto Trie::Get(std::string_view key) const -> const T * {
        auto Now = root_;
        if (!Now) {
            return nullptr;
        }
        
        for (const char c : key) {
            auto it = Now->children_.find(c);
            if (it == Now->children_.end()) {
                return nullptr;
            }
            Now = it->second;
        }

        auto ValueNode = dynamic_cast<const TrieNodeWithValue<T> *>(Now.get());
        if (!ValueNode) {
            return nullptr;
        }
        
        return ValueNode->value_.get();
    }


    /**
     * @brief 向字典树中插入一个新的键值对。如果该键已经存在，则覆盖其对应的值。
     * @return 新的字典树。
     */
    template <class T>
    auto Trie::Put(std::string_view key, T value) const -> Trie {
        auto NewRoot = root_ ? root_->Clone() : std::make_unique<TrieNode>();
        TrieNode *Now = NewRoot.get();

        for (size_t i = 0; i < key.length(); i++) {
            char c = key[i];
            auto &ChildRef = Now->children_[c];
            if (ChildRef) {
                ChildRef = std::shared_ptr<const TrieNode>(ChildRef->Clone());
            } 
            else {
                ChildRef = std::make_shared<TrieNode>();
            }
            Now = const_cast<TrieNode *>(static_cast<const TrieNode *>(ChildRef.get()));
        }

        auto ValueNode = std::make_shared<TrieNodeWithValue<T>>(
            Now->children_,
            std::make_shared<T>(std::move(value))
        );

        if (key.empty()) {
            NewRoot = std::unique_ptr<TrieNode>(ValueNode->Clone());
        } 
        else {
            auto Father = NewRoot.get();
            for (size_t i = 0; i < key.length() - 1; i++) {
                Father = const_cast<TrieNode *>(static_cast<const TrieNode *>(Father->children_[key[i]].get()));
            }
            Father->children_[key.back()] = ValueNode;
        }

        return Trie(std::move(NewRoot));
    }

    /**
     * @brief 从字典树中移除指定的键。
     * @return 如果该键不存在，返回原始的字典树。否则，返回新的字典树。
     */
    auto Trie::Remove(std::string_view key) const -> Trie {
        if (key.empty() || !root_) {
            return *this;
        }

        auto NewRoot = root_->Clone();
        auto Now = NewRoot.get();
        std::vector<std::pair<TrieNode*, char>> Path;
        for (char c : key) {
            auto it = Now->children_.find(c);
            if (it == Now->children_.end()) {
                return *this;
            }

            it->second = std::shared_ptr<const TrieNode>(it->second->Clone());
            Path.push_back({Now, c});
            Now = const_cast<TrieNode *>(it->second.get());
        }

        if (!Now->is_value_node_) {
            return *this;
        }

        auto NewNode = std::make_shared<TrieNode>(Now->children_);
        if (Path.empty()) {
            NewRoot = std::unique_ptr<TrieNode>(NewNode->Clone());
            return *this;
        } 
        else {
            Path.back().first->children_[Path.back().second] = NewNode;
        }

        for (int i = Path.size() - 1; i >= 0; --i) {
            TrieNode* Parent = Path[i].first;
            char Edge = Path[i].second;
            auto& Ptr = Parent->children_[Edge];
            if (Ptr->children_.empty() && !Ptr->is_value_node_) {
                Parent->children_.erase(Edge);
            } 
            else {
                break;
            }
        }

        if (NewRoot->children_.empty() && !NewRoot->is_value_node_) {
            return Trie();
        }
        
        return Trie(std::move(NewRoot));
    }

    // 以下是模板函数的显式实例化。
    //
    // 一般来说，人们会在头文件中编写模板类和函数的实现。然而，我们
    // 将实现分离到一个 .cpp 文件中，以使内容更清晰。为了让编译器了解
    // 模板函数的实现，我们需要在这里显式地实例化它们，以便链接器能够
    // 找到它们。

    template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const uint32_t *;

    template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const uint64_t *;

    template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const std::string *;

    // 如果你的解决方案无法通过不可复制测试的编译，你可以删除以下几行以获得部分分数。

    using Integer = std::unique_ptr<uint32_t>;

    template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const Integer *;

    template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;

}  // namespace bustub