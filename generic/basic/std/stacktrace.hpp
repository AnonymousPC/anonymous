#pragma once

namespace std
{
    struct stacktrace_entry : public boost::stacktrace::frame
    {
        std::string description   ( ) const { return name(); }
        auto        native_handle ( ) const { return address(); }
    };

    struct stacktrace : public boost::stacktrace::stacktrace
    {
        using  value_type             = stacktrace_entry;
        struct const_iterator;
        using  const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using  iterator               = const_iterator;
        using  reverse_iterator       = std::reverse_iterator<iterator>;

        struct const_iterator : public boost::stacktrace::stacktrace::const_iterator
        {          
            using value_type = stacktrace_entry;
            using pointer    = const stacktrace_entry*;
            using reference  = const stacktrace_entry&;

            const_iterator ( ) = default;
            const_iterator ( boost::stacktrace::stacktrace::const_iterator it ) : boost::stacktrace::stacktrace::const_iterator(it) { }
            const stacktrace_entry& operator *  ( )       const { return static_cast<const stacktrace_entry&>(boost::stacktrace::stacktrace::const_iterator::operator* ()); }
            const stacktrace_entry* operator -> ( )       const { return static_cast<const stacktrace_entry*>(boost::stacktrace::stacktrace::const_iterator::operator->()); } 
                  const_iterator    operator +  ( int s ) const { return boost::stacktrace::stacktrace::const_iterator::operator+(s); }
                  const_iterator    operator -  ( int s ) const { return boost::stacktrace::stacktrace::const_iterator::operator-(s); }
                  const_iterator&   operator ++ ( )             { boost::stacktrace::stacktrace::const_iterator::operator++(); return *this; }
                  const_iterator    operator ++ ( int )         { auto it = *this; boost::stacktrace::stacktrace::const_iterator::operator++(); return it; }
                  const_iterator&   operator -- ( )             { boost::stacktrace::stacktrace::const_iterator::operator--(); return *this; }
                  const_iterator    operator -- ( int )         { auto it = *this; boost::stacktrace::stacktrace::const_iterator::operator--(); return it; } 
        };

        stacktrace ( ) : boost::stacktrace::stacktrace(0, 0) { };
        stacktrace ( boost::stacktrace::stacktrace trace ) : boost::stacktrace::stacktrace(std::move(trace)) { }
        static stacktrace current ( ) { return static_cast<stacktrace>(boost::stacktrace::stacktrace()); }

        const_iterator         begin   ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::begin());   }
        const_iterator         cbegin  ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::cbegin());  }
        const_iterator         end     ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::end());     }
        const_iterator         cend    ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::cend());    }
        const_reverse_iterator rbegin  ( ) const { return std::reverse_iterator(begin()); }
        const_reverse_iterator crbegin ( ) const { return std::reverse_iterator(cbegin()); }
        const_reverse_iterator rend    ( ) const { return std::reverse_iterator(end()); }
        const_reverse_iterator crend   ( ) const { return std::reverse_iterator(cend()); }

        const stacktrace_entry& operator [] ( int i ) { return static_cast<const stacktrace_entry&>(boost::stacktrace::stacktrace::operator[](i));     }
        const stacktrace_entry& at          ( int i ) { return static_cast<const stacktrace_entry&>(boost::stacktrace::stacktrace::as_vector().at(i)); }
    };
    
} // namespace std