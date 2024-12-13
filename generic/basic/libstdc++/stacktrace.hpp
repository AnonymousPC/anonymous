#pragma once

namespace std
{
    struct stacktrace_entry : public boost::stacktrace::frame
    {
        std::string description ( ) const { return name(); }
    };

    struct stacktrace : public boost::stacktrace::stacktrace
    {
        struct const_iterator : public boost::stacktrace::stacktrace::const_iterator
        {
            const_iterator ( boost::stacktrace::stacktrace::const_iterator it ) : boost::stacktrace::stacktrace::const_iterator(it) { }
            const stacktrace_entry& operator *  ( ) const { return static_cast<const stacktrace_entry&>(boost::stacktrace::stacktrace::const_iterator::operator* ()); }
            const stacktrace_entry* operator -> ( ) const { return static_cast<const stacktrace_entry*>(boost::stacktrace::stacktrace::const_iterator::operator->()); } 
                  const_iterator&   operator ++ ( )       { boost::stacktrace::stacktrace::const_iterator::operator++(); return *this; }
                  const_iterator    operator ++ ( int )   { auto it = *this; boost::stacktrace::stacktrace::const_iterator::operator++(); return it; }
                  const_iterator&   operator -- ( )       { boost::stacktrace::stacktrace::const_iterator::operator--(); return *this; }
                  const_iterator    operator -- ( int )   { auto it = *this; boost::stacktrace::stacktrace::const_iterator::operator--(); return it; } 
        };
        using iterator = const_iterator;

        stacktrace ( ) : boost::stacktrace::stacktrace(0, 0) { };
        stacktrace ( boost::stacktrace::stacktrace trace ) : boost::stacktrace::stacktrace(std::move(trace)) { }
        static stacktrace current ( ) { return static_cast<stacktrace>(boost::stacktrace::stacktrace()); }

        const_iterator begin   ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::begin());   }
        const_iterator cbegin  ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::cbegin());  }
        const_iterator end     ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::end());     }
        const_iterator cend    ( ) const { return static_cast<const_iterator>(boost::stacktrace::stacktrace::cend());    }

        const stacktrace_entry& operator [] ( int i ) { return static_cast<const stacktrace_entry&>(boost::stacktrace::stacktrace::operator[](i));     }
        const stacktrace_entry& at          ( int i ) { return static_cast<const stacktrace_entry&>(boost::stacktrace::stacktrace::as_vector().at(i)); }
    };
    
} // namespace std