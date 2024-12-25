#pragma once

#ifdef BOOST_COMPUTE_HPP
    class opencl
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Layout
            using layout_type = std::layout_left;

        public: // Allocator
            template < class type > using allocator = boost::compute::buffer_allocator<type>;

        public: // Container
            template < class type, class alloc = allocator<type> >                        using vector       = boost::compute::vector<type,alloc>;
            template < class type, int len >                                              using array        = boost::compute::array<type,len>;
            template < class type >                                                       using stack        = boost::compute::stack<type>;
            template < class type >                                                       using flat_set     = boost::compute::flat_set<type>;
            template < class type1, class type2 >                                         using flat_map     = boost::compute::flat_map<type1,type2>;
            template < class char_type, class char_traits = std::char_traits<char_type> > using basic_string = boost::compute::basic_string<char_type,char_traits>;
                                                                                          using string       = basic_string<char>;
    };
#else
    class opencl
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }
    };
#endif