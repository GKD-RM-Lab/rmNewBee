//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// trie.cpp
//
// Identification: src/primer/trie.cpp
//
// Copyright (c) 2015-2025, Carnegie Mellon University Database Group
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
	 * @brief Get the value associated with the given key.
	 * 1. If the key is not in the trie, return nullptr.
	 * 2. If the key is in the trie but the type is mismatched, return nullptr.
	 * 3. Otherwise, return the value.
	 */
	template <class T>
    const T* get(int i, std::string_view key, std::shared_ptr<TrieNode> node) {
        if (i == key.size()) {
            auto valueNode = std::dynamic_pointer_cast<TrieNodeWithValue<T>>(node);
            if (valueNode) {
                return &(valueNode->value);
            }
            return nullptr;
        }
        char c = key[i];
        if (node->children_.count(c)) {
            return get<T>(i + 1, key, node->children_[c]);
        }
        return nullptr;
    }
	template <class T>
	auto Trie::Get(std::string_view key) const -> const T * {
		return get<T>(0, key, root_);
	}
	
	/**
	 * @brief Put a new key-value pair into the trie. If the key already exists, overwrite the value.
	 * @return the new trie.
	 */
	template <class T>
	std::shared_ptr<TrieNode>  put(int i,T value,std::string_view key,std::shared_ptr<TrieNode>node){
		if(i==key.size()){
			return std::make_shared<TrieNodeWithValue>(value);
		}
		char c=key[i];
		if(!node->children_.count(c)){
			node->children_[c]=std::shared_ptr<TrieNode>();
		}
		node->children_[c]=put(i+1,value,key,node->children_[c]);
		return node;
	};
	template <class T>
	auto Trie::Put(std::string_view key, T value) const -> Trie {
	  // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
	  Trie newtrie;
	  newtrie.root_=put(0,value,key,root_)
	  return newtrie;
	  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
	  // exists, you should create a new `TrieNodeWithValue`.
	}
	
	/**
	 * @brief Remove the key from the trie.
	 * @return If the key does not exist, return the original trie. Otherwise, returns the new trie.
	 */
	template <class T>
	std::shared_ptr<TrieNode> remove(int i, std::string_view key, std::shared_ptr<TrieNode> node) {
        if (i == key.size()) {
            auto valueNode = std::dynamic_pointer_cast<TrieNodeWithValueBase>(node);
            if (valueNode) {
                if (node->children_.empty()) {
                    return nullptr;
                }
                auto newNode = std::make_shared<TrieNode>();
                newNode->children_ = node->children_;
                return newNode;
            }
            return node;
        }
        char c = key[i];
        if (node->children_.count(c)) {
            node->children_[c] = remove(i + 1, key, node->children_[c]);
            if (node->children_[c] == nullptr) {
                node->children_.erase(c);
            }
        }
        return node;
    }
	template <class T>
	auto Trie::Remove(std::string_view key) const -> Trie {
		Trie newtrie = *this;
        newtrie.root_ = remove(0, key, newtrie.root_);
        return newtrie;
	  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
	  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
	}
	
	// Below are explicit instantiation of template functions.
	//
	// Generally people would write the implementation of template classes and functions in the header file. However, we
	// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
	// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
	// by the linker.
	
	template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
	template auto Trie::Get(std::string_view key) const -> const uint32_t *;
	
	template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
	template auto Trie::Get(std::string_view key) const -> const uint64_t *;
	
	template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
	template auto Trie::Get(std::string_view key) const -> const std::string *;
	
	// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.
	
	using Integer = std::unique_ptr<uint32_t>;
	
	template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
	template auto Trie::Get(std::string_view key) const -> const Integer *;
	
	template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
	template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;
	
	}  // namespace bustub
	