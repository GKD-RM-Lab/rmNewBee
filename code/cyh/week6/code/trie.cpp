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
#include <iostream>

namespace bustub {

	/**
	 * @brief Get the value associated with the given key.
	 * 1. If the key is not in the trie, return nullptr.
	 * 2. If the key is in the trie but the type is mismatched, return nullptr.
	 * 3. Otherwise, return the value.
	 */

	template <class T>
	auto Trie::Get(std::string_view key) const -> const T * {
		
		if(root_ == nullptr){
			return nullptr;
		}

		auto current = root_;
		for(auto c : key){
			auto it = current->children_.find(c);
			if(it == current->children_.end()){
				return nullptr;
			}
			current = it->second; //it的second本身就是ptr，不需要（）来调用
		}
	
		if(!current->is_value_node_){
			return nullptr;
		}

		const TrieNodeWithValue<T>* node_with_value = dynamic_cast<const TrieNodeWithValue<T>*> (current.get());

		if(node_with_value == nullptr){
			return nullptr;
		}
	
		return node_with_value->value_.get();

	  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
	  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
	  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
	  // Otherwise, return the value.
	}
	
	/**
	 * @brief Put a new key-value pair into the trie. If the key already exists, overwrite the value.
	 * @return the new trie.
	 */
	template <class T>
	auto Trie::Put(std::string_view key, T value) const -> Trie {
		if(key.empty()){
			auto new_root = std::make_shared<TrieNodeWithValue<T>>(root_ ? root_->children_ : std::map<char, std::shared_ptr<const TrieNode>>(), std::make_shared<T>(std::move(value)));
			return Trie(new_root);
		}
	
		auto new_root = root_ ? root_->Clone() : std::make_unique<TrieNode>();
		std::vector<std::unique_ptr<TrieNode>> node_path; 
		node_path.push_back(std::move(new_root));
		
		for(int i = 0; i < key.size(); i++){
			char c = key[i];
			std::unique_ptr<TrieNode> new_node;
			
			if(i == key.size() - 1){
				auto children = node_path.back()->children_.count(c) ? node_path.back()->children_.at(c)->children_ : std::map<char, std::shared_ptr<const TrieNode>>();
				new_node = std::make_unique<TrieNodeWithValue<T>>(children, std::make_shared<T>(std::move(value)));
			}else{
				new_node = node_path.back()->children_.count(c) ? node_path.back()->children_.at(c)->Clone() : std::make_unique<TrieNode>();
			}
			
			node_path.push_back(std::move(new_node));
		}
	
		for (int i = key.size(); i > 0; i--) {
			char c = key[i - 1]; 
			node_path[i - 1]->children_[c] = std::shared_ptr<const TrieNode>(node_path[i].release());
		}

		return Trie(std::shared_ptr<const TrieNode>(node_path[0].release()));
	}
	
	/**
	 * @brief Remove the key from the trie.
	 * @return If the key does not exist, return the original trie. Otherwise, returns the new trie.
	 */
	auto Trie::Remove(std::string_view key) const -> Trie {
		
		if(!root_){
			return Trie(root_);  
		}
	
		if (key.empty()){
			if(root_->is_value_node_){
				if(root_->children_.empty()){
					return Trie(); 
				}
				auto new_root = std::make_shared<TrieNode>(root_->children_);
				return Trie(new_root);
			}
			return Trie(root_);  
		}

		std::vector<std::unique_ptr<TrieNode>> node_path;
		node_path.push_back(std::move(root_->Clone()));
	
		for(int i = 0; i < key.size(); i++){
			char c = key[i];
			if (!node_path.back()->children_.count(c)) {
				return Trie(root_);  
			}
	
			auto new_node = node_path.back()->children_.at(c)->Clone();
			node_path.push_back(std::move(new_node));
		}
	
		if(!node_path.back()->is_value_node_){
			return Trie(root_);  
		}
	
		auto last_node = std::make_unique<TrieNode>(node_path.back()->children_);
		node_path.back() = std::move(last_node);
	

		for(int i = key.size(); i > 0; i--){
			char c = key[i - 1];
			if (node_path[i]->children_.empty() && !node_path[i]->is_value_node_) {
				node_path[i - 1]->children_.erase(c);
			} else {
				node_path[i - 1]->children_[c] = std::shared_ptr<const TrieNode>(node_path[i].release());
			}
		}
	
		auto new_root = std::shared_ptr<const TrieNode>(node_path[0].release());

		if (new_root->children_.empty() && !new_root->is_value_node_) {
			return Trie();
		}

		return Trie(new_root);
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
	