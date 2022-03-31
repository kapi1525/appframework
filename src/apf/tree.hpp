#pragma once
#include <deque>
#include <memory>       // Wow clangd is 100000x better than vscode intelisense, it even added this header for me lol.
#include "common.hpp"




namespace apf {

    template<typename type, template<typename> class container>
    class tree_impl : public container<tree_impl<type, container>> {
    public:
        tree_impl();
        tree_impl(type new_data);
        ~tree_impl();

        operator type();

        type& get();
        void set(type&& new_data);

    private:
        type data;
    };
    

    // Weird hack to stop clang from complaining
    #ifdef APF_CLANG
        template<typename type>
        using deque = std::deque<type>;

        template<typename type>
        using tree = tree_impl<type, deque>;
    #else
        template<typename type>
        using tree = tree_impl<type, std::deque>;
    #endif
}



template<typename type, template<typename> class container>
inline apf::tree_impl<type, container>::tree_impl::tree_impl() {
}

template<typename type, template<typename> class container>
inline apf::tree_impl<type, container>::tree_impl::tree_impl(type new_data) {
    data = new_data;
}

template<typename type, template<typename> class container>
inline apf::tree_impl<type, container>::tree_impl::~tree_impl() {
}



template<typename type, template<typename> class container>
inline apf::tree_impl<type, container>::tree_impl::operator type() {
    return data;
}


template<typename type, template<typename> class container>
inline type& apf::tree_impl<type, container>::tree_impl::get() {
    return data;
}

template<typename type, template<typename> class container>
inline void apf::tree_impl<type, container>::tree_impl::set(type&& new_data) {
    data = new_data;
}