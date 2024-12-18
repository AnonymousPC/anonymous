#pragma once

class cpu
{
    public: // Allocator
        template < class type > using allocator = std::allocator<type>;

    public: // Compare
        template < class type = void > using equal_to      = std::equal_to<type>;
        template < class type = void > using not_equal_to  = std::not_equal_to<type>;
        template < class type = void > using less          = std::less<type>;
        template < class type = void > using less_equal    = std::less_equal<type>;
        template < class type = void > using greater       = std::greater<type>;
        template < class type = void > using greater_equal = std::greater_equal<type>; 

    public: // Container
        template < class type >          using vector = std::vector<type>;
        template < class type, int len > using array  = std::array<type,len>;

    public: // Algorithm
        static constexpr decltype(auto) copy          ( auto&&... args ) { return std::copy         (std::forward<decltype(args)>(args)...); }
        static constexpr decltype(auto) copy_n        ( auto&&... args ) { return std::copy_n       (std::forward<decltype(args)>(args)...); }
        static constexpr decltype(auto) copy_backward ( auto&&... args ) { return std::copy_backward(std::forward<decltype(args)>(args)...); }
        static constexpr decltype(auto) move          ( auto&&... args ) { return std::move         (std::forward<decltype(args)>(args)...); }
        static constexpr decltype(auto) move_backward ( auto&&... args ) { return std::move_backward(std::forward<decltype(args)>(args)...); }
};