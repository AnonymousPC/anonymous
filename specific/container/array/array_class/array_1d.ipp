#pragma once

template < class type, class device >
constexpr array<type,1,device>::array ( const array& init )
    requires copyable<type>
    extends vector ( /*initialized latter*/ )
{
    if ( right.independent() ) [[likely]]
        vector::operator=(static_cast<const vector&>(right));
    else
    {
        vector::resize(right.size());
        device::copy(right.begin(), right.end(), vector::begin());
    }
} 

template < class type, class device >
constexpr array<type,1,device>::array ( array&& init )
    extends vector ( /*initialized latter*/ )
{
    if ( right.independent() ) [[likely]]
        vector::operator=(static_cast<vector&&>(right));
    else
    {
        vector::resize(right.size());
        device::move(right.begin(), right.end(), vector::begin());
    }
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( const array& right )
    requires copyable<type>
{
    if ( independent() and right.independent() ) [[likely]]
        vector::operator=(static_cast<const vector&>(right));

    else if ( independent() and not right.independent() )
    {
        vector::resize(right.size());
        device::copy(right.begin(), right.end(), vector::begin());
    }

    else if ( not independent() and right.independent() )
    {
        #if debug
        if ( size() != right.size() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on size (with left_size = {}, right_size = {})", size(), right.size());
        #endif
        device::copy(right.vector::begin(), right.vector::end(), begin());
    }

    else /* if ( not independent() and not right.independent() ) */
    {
        #if debug
        if ( size() != right.size() )
            throw logic_error("cannot copy assign array: the left array does not own its data, and the right array mismatches on size (with left_size = {}, right_size = {})", size(), right.size());
        #endif
        device::copy(right.begin(), right.end(), begin());
    }

    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::operator = ( array&& right )
{
    if ( independent() and right.independent() ) [[likely]]
        vector::operator=(static_cast<vector&&>(right));

    else if ( independent() and not right.independent() )
    {
        vector::resize(right.size());
        device::move(right.begin(), right.end(), vector::begin());
    }

    else if ( not independent() and right.independent() )
    {
        #if debug
        if ( size() != right.size() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on size (with left_size = {}, right_size = {})", size(), right.size());
        #endif
        device::move(right.vector::begin(), right.vector::end(), begin());
    }
    
    else /* if ( not independent() and not right.independent() ) */
    {
        #if debug
        if ( size() != right.size() )
            throw logic_error("cannot move assign array: the left array does not own its data, and the right array mismatches on size (with left_size = {}, right_size = {})", size(), right.size());
        #endif
        device::move(right.begin(), right.end(), begin());
    }

    return self;
}


template < class type, class device >
constexpr array<type,1,device>::array ( int init_size )
    extends vector ( init_size )
{
    #if debug
    if ( init_size < 0 )
        throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const type& init_value )
    requires copyable<type>
    extends vector ( init_size, init_value )
{
    #if debug
    if ( init_size < 0 )
        throw value_error("initialize array with negative size {}", init_size);
    #endif
}

template < class type, class device >
constexpr array<type,1,device>::array ( const std::initializer_list<type>& init )
    requires copyable<type>
    extends vector ( init )
{

}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type()> auto init_value )
    extends array ( init_size )
{
    device::generate(vector::begin(), vector::end(), init_value);
}

template < class type, class device >
constexpr array<type,1,device>::array ( int init_size, const function_type<type(int)> auto init_value )
    extends array ( init_size )
{
    for ( int i in range(init_size) )
        self[i] = init_value(i);
}

template < class type, class device >
constexpr array<type,1,device>::array ( const range<type>& init )
    requires copyable<type>
    extends array ( init.size() )
{
    device::copy(init.begin(), init.end(), vector::begin());
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r )
    requires convertible_to<decltype(*r.begin()),type>
{
    if constexpr ( requires { std::ranges::size(r); } )
    {
        #if debug
        if ( r.size() < 0 )
            throw value_error("initialize array with negative size {}", r.size());
        #endif

        vector::resize(std::ranges::size(r));
        if constexpr ( requires { device::move(std::ranges::begin(r), std::ranges::end(r), vector::begin()); } )
            device::move(std::ranges::begin(r), std::ranges::end(r), vector::begin());
        else
            std::ranges::move(r, vector::begin());
    }
    else
        for ( auto&& val in r )
            vector::push_back(std::forward<decltype(val)>(val));
}

template < class type, class device >
constexpr array<type,1,device>::array ( std::from_range_t, std::ranges::input_range auto&& r, int init_size )
    requires convertible_to<decltype(*r.begin()),type>
    extends array ( init_size )
{
    #if debug
    if constexpr ( requires { std::ranges::size(r); } )
        if ( std::ranges::size(r) != init_size )
            throw value_error("initialize array with ambiguous size (with range_size = {}, explicit_size = {})", std::ranges::size(r), init_size);
    #endif

    if constexpr ( requires { device::move(std::ranges::begin(r), std::ranges::end(r), vector::begin()); } )
        device::move(std::ranges::begin(r), std::ranges::end(r), vector::begin());
    else
        std::ranges::move(r, vector::begin());
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires convertible_to<type2,type> but ( not same_as<type,type2> )
    extends array ( cvt.size() )
{
    if ( cvt.independent() ) [[likely]]
        device::transform(cvt.array<type2,1,device>::vector::begin(), cvt.array<type2,1,device>::vector::end(), vector::begin(), [] (const auto& val) { return type(val); });
    else
        device::transform(cvt.begin(), cvt.end(), vector::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < class type2 >
constexpr array<type,1,device>::array ( const array<type2,1,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    if ( cvt.independent() ) [[likely]]
        device::transform(cvt.array<type2,1,device>::vector::begin(), cvt.array<type2,1,device>::vector::end(), vector::begin(), [] (const auto& val) { return type(val); });
    else
        device::transform(cvt.begin(), cvt.end(), vector::begin(), [] (const auto& val) { return type(val); });
}

template < class type, class device >
template < int len >
constexpr array<type,1,device>::array ( const inplace_array<type,len,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    device::copy(cvt.begin(), cvt.end(), vector::begin());
}

template < class type, class device >
template < int len >
constexpr array<type,1,device>::array ( const static_array<type,len,device>& cvt )
    requires constructible_from<type,type2> but ( not convertible_to<type2,type> )
    extends array ( cvt.size() )
{
    device::copy(cvt.begin(), cvt.end(), vector::begin());
}

template < class type, class device >
constexpr int array<type,1,device>::dimension ( )
{
    return 1;
}

template < class type, class device >
constexpr int array<type,1,device>::size ( ) const
{
    if ( independent() ) [[likely]]
        return vector::size();
    else
        return upper::size();
}

template < class type, class device >
constexpr array<int> array<type,1,device>::shape ( ) const
{
    return { size() };
}

// template < class type, class device >
// constexpr static_array<int,1> array<type,1,device>::static_shape ( ) const
// {
//     return { size() };
// }

// template < class type, class device >
// constexpr inplace_array<int,1> array<type,1,device>::inplace_shape ( ) const
// {
//     return { size() };
// }

template < class type, class device >
constexpr bool array<type,1,device>::empty ( ) const
{
    if ( independent() ) [[likely]]
        return vector::empty();
    else
        return upper::empty();
}

template < class type, class device >
constexpr array<type,1,device>::pointer array<type,1,device>::data ( )
{
    if constexpr ( requires { { vector::data() } -> convertible_to<const_pointer>; } )
        if ( independent() ) [[likely]]
            return vector::data();
        else if ( ( upper::category() == upper::row_category    and same_as<typename device::layout_type,std::layout_right> ) or 
                  ( upper::category() == upper::column_category and same_as<typename device::layout_type,std::layout_left > ) )
            return begin();
        else
            throw logic_error("cannot get native data from array: it does not own its data, and the borrowed data might be not contiguous");
    else
        static_assert(false, "cannot get native data from array: not supported on this device");
}

template < class type, class device >
constexpr array<type,1,device>::const_pointer array<type,1,device>::data ( ) const
{
    if constexpr ( requires { { vector::data() } -> convertible_to<const_pointer>; } )
        if ( independent() ) [[likely]]
            return vector::data();
        else if ( ( upper::category() == upper::row_category    and same_as<typename device::layout_type,std::layout_right> ) or 
                  ( upper::category() == upper::column_category and same_as<typename device::layout_type,std::layout_left > ) )
            return begin();
        else
            throw logic_error("cannot get native data from array: it does not own its data, and the borrowed data might be not contiguous");
    else
        static_assert(false, "cannot get native data from array: not supported on this device");
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::begin ( )
{
    if ( independent() ) [[likely]]
        return iterator(vector::begin());
    else
        return upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::begin ( ) const
{
    if ( independent() ) [[likely]]
        return const_iterator(vector::begin());
    else
        return upper::begin();
}

template < class type, class device >
constexpr array<type,1,device>::iterator array<type,1,device>::end ( )
{
    if ( independent() ) [[likely]]
        return iterator(vector::end());
    else
        return upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::const_iterator array<type,1,device>::end ( ) const
{
    if ( independent() ) [[likely]]
        return const_iterator(vector::end());
    else
        return upper::end();
}

template < class type, class device >
constexpr array<type,1,device>::reference array<type,1,device>::operator [] ( int auto pos )
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( independent() ) [[likely]]
        return pos >= 0 ? vector::operator[](pos-1) otherwise
                          vector::operator[](pos+size());
    else
        return upper::operator[](pos);
}

template < class type, class device >
constexpr array<type,1,device>::const_reference array<type,1,device>::operator [] ( int auto pos ) const
{
    #if debug
    if ( pos < -size() or pos == 0 or pos > size() )
        throw index_error("index {} is out of range with size {}", pos, size());
    #endif
    
    if ( independent() ) [[likely]]
        return pos >= 0 ? vector::operator[](pos-1) otherwise
                          vector::operator[](pos+size());
    else
        return upper::operator[](pos);
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::clear ( )
{
    #if debug
    if ( not independent() ) [[unlikely]]
        throw logic_error("cannot clear array: it does not own its data");
    #endif

    vector::clear();
    vector::shrink_to_fit();
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::resize ( int new_size )
{
    #if debug
    if ( not independent() ) [[unlikely]]
        throw logic_error("cannot resize array: it does not own its data");
    if ( new_size < 0 )
        throw value_error("resize array with negative size {}", new_size);
    #endif

    vector::resize(new_size);
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::push ( type new_value )
{
    #if debug
    if ( not independent() ) [[unlikely]]
        throw logic_error("cannot push into array: it does not own its data");
    #endif

    vector::push_back(std::move(new_value));
    return self;
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::pop ( int old_pos )
{
    #if debug
    if ( not independent() ) [[unlikely]]
        throw logic_error("cannot pop from array: it does not own its data");
    if ( old_pos < -size() or old_pos == 0 or old_pos > size() )
        throw index_error("index {} is out of range with size {}", old_pos, size());
    #endif

    vector::erase(old_pos >= 0 ? vector::begin() + old_pos - 1 otherwise vector::begin() + old_pos + size());
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::insert ( int new_pos, type new_value )
{
    #if debug
    if ( not independent() ) [[unlikely]]
        throw logic_error("cannot insert into array: it does not own its data");
    if ( new_pos < -size() or new_pos == 0 or new_pos > size() )
        throw index_error("index {} is out of range with size {}", new_pos, size());
    #endif
    
    vector::insert(new_pos >= 0 ? vector::begin() + new_pos - 1 otherwise vector::begin() + new_pos + size(), std::move(new_value));
}

template < class type, class device >
constexpr array<type,1,device>& array<type,1,device>::erase ( int old_pos_1, int old_pos_2 )
{
    #if debug
    if ( not independent() ) [[unlikely]]
        throw logic_error("cannot erase from array: it does not own its data");
    #endif

    let p1 = old_pos_1 >= 0 ? old_pos_1 otherwise old_pos_1 + size();
    let p2 = old_pos_2 >= 0 ? old_pos_2 otherwise old_pos_2 + size();

    #if debug
    if ( ( ( p1 < 1 or p1 > size() ) or
           ( p2 < 1 or p2 > size() ) )
    and not // Except for below:
         ( ( p1 == size() + 1 or p2 == 0 ) and p1 == p2 + 1 ) )
        throw index_error("index [{},{}] is out of range with size {}", old_pos_1, old_pos_2, size());
    #endif

    vector::erase(vector::begin() + p1 - 1, vector::begin() + p2 - 1);
}

template < class type, class device >
constexpr bool array<type,1,device>::independent ( ) const
{
    return upper::independent();
}

template < class type, class device >
class array<type,1,device>::iterator
{
    private: // Data
        int step = 1;

    private: // Typedef
        using base = device::template vector<type>::iterator;

    private: // Data
        base iter = base();
        int  step = 1;

    public: // Typedef
        using iterator_concept = common_type<typename std::iterator_traits<base>::iterator_category,std::random_access_iterator_tag>;
        using value_type       = decay<typename std::iterator_traits<base>::reference>;
        using reference        = std::iterator_traits<base>::reference;
        using pointer          = std::iterator_traits<base>::pointer;
        using difference_type  = std::iterator_traits<base>::difference_type;

    public: // Core
        constexpr iterator ( ) = default;
        constexpr iterator ( base init_iter )                extends iter ( init_iter )                     { };
        constexpr iterator ( base init_iter, int init_step ) extends iter ( init_iter ), step ( init_step ) { }; 

    public: // Operator.member
        constexpr           operator base ( )                   const { return  iter;    }
        constexpr reference operator *    ( )                   const { return *iter;    }
        constexpr pointer   operator ->   ( )                   const { return  iter;    }
        constexpr reference operator []   ( difference_type t ) const { return  iter[t]; }

    public: // Operator.global
        friend constexpr bool                 operator ==  ( const iterator&       left, const iterator&       right ) { return left.iter == right.iter;                                    }
        friend constexpr std::strong_ordering operator <=> ( const iterator&       left, const iterator&       right ) { return std::compare_strong_order_fallback(left.iter, right.iter);  }
        friend constexpr iterator             operator  +  ( const iterator&       left,       difference_type right ) { return iterator(left .iter + left .step * right, left .step);      }
        friend constexpr iterator             operator  +  (       difference_type left, const iterator&       right ) { return iterator(right.iter + right.step * left,  right.step);      }
        friend constexpr iterator             operator  -  ( const iterator&       left,       difference_type right ) { return iterator(left .iter - left .step * right, left .step);      }
        friend constexpr difference_type      operator  -  ( const iterator&       left, const iterator&       right ) { [[assume(left.step == right.step)]]; return (left.iter - right.iter) / left.step; }
        friend constexpr iterator&            operator ++  (       iterator&       left                              ) { left.iter += left.step;         return left; }
        friend constexpr iterator             operator ++  (       iterator&       left,       int                   ) { let it = left; ++left;          return it;   }
        friend constexpr iterator&            operator --  (       iterator&       left                              ) { left.iter -= left.step;         return left; }
        friend constexpr iterator             operator --  (       iterator&       left,       int                   ) { let it = left; --left;          return it;   }
        friend constexpr iterator&            operator +=  (       iterator&       left,       difference_type right ) { left.iter += left.step * right; return left; }
        friend constexpr iterator&            operator -=  (       iterator&       left,       difference_type right ) { left.iter -= left.step * right; return left; }
};

template < class type, class device >
class array<type,1,device>::const_iterator
{
    private: // Base
        using base = device::template vector<type>::const_iterator

    private: // Data
        base iter = base();
        int  step = 1;

    public: // Typedef
        using iterator_concept = common_type<typename std::iterator_traits<base>::iterator_category,std::random_access_iterator_tag>;
        using value_type       = decay<typename std::iterator_traits<base>::reference>;
        using reference        = std::iterator_traits<base>::reference;
        using pointer          = std::iterator_traits<base>::pointer;
        using difference_type  = std::iterator_traits<base>::difference_type;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( base init_iter )                extends iter ( init_iter )                     { }
        constexpr const_iterator ( base init_iter, int init_step ) extends iter ( init_iter ), step ( init_step ) { } 

    public: // Operator.member
        constexpr           operator base ( )                   const { return  iter;    }
        constexpr reference operator *    ( )                   const { return *iter;    }
        constexpr pointer   operator ->   ( )                   const { return  iter;    }
        constexpr reference operator []   ( difference_type t ) const { return  iter[t]; }

    public: // Operator.global
        friend constexpr bool                 operator ==  ( const const_iterator& left, const const_iterator& right ) { return left.iter == right.iter;                                     }                  
        friend constexpr std::strong_ordering operator <=> ( const const_iterator& left, const const_iterator& right ) { return std::compare_strong_order_fallback(left.iter, right.iter);   }
        friend constexpr const_iterator       operator  +  ( const const_iterator& left,       difference_type right ) { return const_iterator(left .iter + left .step * right, left .step); }
        friend constexpr const_iterator       operator  +  (       difference_type left, const const_iterator& right ) { return const_iterator(right.iter + right.step * left,  right.step); }
        friend constexpr const_iterator       operator  -  ( const const_iterator& left,       difference_type right ) { return const_iterator(left .iter - left .step * right, left .step); }
        friend constexpr difference_type      operator  -  ( const const_iterator& left, const const_iterator& right ) { [[assume(left.step == right.step)]]; return (left.iter - right.iter) / left.step;  }
        friend constexpr const_iterator&      operator ++  (       const_iterator& left                              ) { left.iter += left.step;         return left; }
        friend constexpr const_iterator       operator ++  (       const_iterator& left,       int                   ) { let it = left; ++left;          return it;   }
        friend constexpr const_iterator&      operator --  (       const_iterator& left                              ) { left.iter -= left.step;         return left; }
        friend constexpr const_iterator       operator --  (       const_iterator& left,       int                   ) { let it = left; --left;          return it;   }
        friend constexpr const_iterator&      operator +=  (       const_iterator& left,       difference_type right ) { left.iter += left.step * right; return left; }
        friend constexpr const_iterator&      operator -=  (       const_iterator& left,       difference_type right ) { left.iter -= left.step * right; return left; }
};