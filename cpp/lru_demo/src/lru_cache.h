/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Huang Minhang <huangminhang@trunk.tech>, 2021/11/21 16:52
*/
#ifndef LRU_DEMO_LRU_CACHE_H
#define LRU_DEMO_LRU_CACHE_H
#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>

namespace cache {

    template<typename key_t, typename value_t>
    class lru_cache {
    public:
        typedef typename std::pair<key_t, value_t> key_value_pair_t;
        typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

        explicit lru_cache(size_t max_size) :
                m_max_size(max_size) {
        }

        void put(const key_t& key, const value_t& value) {
            auto it = m_cache_items_map.find(key);
            m_cache_items_list.push_front(key_value_pair_t(key, value));
            if (it != m_cache_items_map.end()) {
                m_cache_items_list.erase(it->second);
                m_cache_items_map.erase(it);
            }
            m_cache_items_map[key] = m_cache_items_list.begin();

            if (m_cache_items_map.size() > m_max_size) {
                auto last = m_cache_items_list.end();
                last--;
                m_cache_items_map.erase(last->first);
                m_cache_items_list.pop_back();
            }
        }

        const value_t& get(const key_t& key) {
            auto it = m_cache_items_map.find(key);
            if (it == m_cache_items_map.end()) {
                throw std::range_error("There is no such key in cache");
            } else {
                m_cache_items_list.splice(m_cache_items_list.begin(), m_cache_items_list, it->second);
                return it->second->second;
            }
        }

        bool exists(const key_t& key) const {
            return m_cache_items_map.find(key) != m_cache_items_map.end();
        }

        size_t size() const {
            return m_cache_items_map.size();
        }

    private:
        std::list<key_value_pair_t> m_cache_items_list;
        std::unordered_map<key_t, list_iterator_t> m_cache_items_map;
        size_t m_max_size;
    };

} // namespace cache


#endif//LRU_DEMO_LRU_CACHE_H
