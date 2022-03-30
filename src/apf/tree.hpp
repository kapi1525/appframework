#pragma once
#include <deque>
#include <memory>       // Wow clangd is 100000x better than vscode intelisense, it even added this header for me lol.
#include "common.hpp"




namespace apf {

    // TODO: I wanted to add a way of changing container which is used to store data, but clang didnt like that, so std::deque it is... for now.
    template<typename type>
    class tree {
    public:
        tree();
        tree(type new_data);
        ~tree();

        operator type();

        tree<type>& operator[](size_t index);
        tree<type>& at(size_t index);

        type& get();
        void set(type&& new_data);

        size_t size();

        void push_back(type&& new_data);

        void clear();

    private:
        type data;
        std::shared_ptr<std::deque<tree<type>>> branches = std::make_shared<std::deque<tree<type>>>();
    };
}



template<typename type>
inline apf::tree<type>::tree::tree() {
}

template<typename type>
inline apf::tree<type>::tree::tree(type new_data) {
    data = new_data;
}

template<typename type>
inline apf::tree<type>::tree::~tree() {
}



template<typename type>
inline apf::tree<type>::tree::operator type() {
    return data;
}

template<typename type>
inline apf::tree<type>& apf::tree<type>::tree::operator[](size_t index) {
    return branches->at(index);
}

template<typename type>
inline apf::tree<type>& apf::tree<type>::tree::at(size_t index) {
    return branches->at(index);
}



template<typename type>
inline type& apf::tree<type>::tree::get() {
    return data;
}

template<typename type>
inline void apf::tree<type>::tree::set(type&& new_data) {
    data = new_data;
}



template<typename type>
inline size_t apf::tree<type>::tree::size() {
    return branches->size();
}



template<typename type>
inline void apf::tree<type>::tree::push_back(type&& new_data) {
    branches->push_back(tree<type>(new_data));
}



template<typename type>
inline void apf::tree<type>::tree::clear() {
    branches->clear();
}