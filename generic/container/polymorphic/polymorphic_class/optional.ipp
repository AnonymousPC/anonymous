#pragma once

/// Class optional

// Core

template < class types >
constexpr optional<types>::optional ( )
{

}

template < class types >
constexpr optional<types>::optional ( const optional& init )
    requires std::copyable<types>
    extends storage ( init.storage, init.flag ),
            flag    ( init.flag )
{

}

template < class types >
constexpr optional<types>::optional ( optional&& init )
    requires std::movable<types>
    extends storage ( std::move ( init.storage ), init.flag ),
            flag    ( std::exchange ( init.flag, false ) )
{

}

template < class types >
constexpr optional<types>::optional ( types init )
    requires std::movable<types>
    extends storage ( std::move ( init ) ),
            flag    ( true )
{

}

template < class types >
constexpr optional<types>::optional ( nullopt_t )
    extends optional()
{

}

template < class types >
constexpr optional<types>::~optional ( )
{
    if ( flag )
    {
        storage.clear();
        flag = false;
    }
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( const optional& right )
    requires std::copyable<types>
{
    self.storage.assign ( right.storage, self.flag, right.flag );
    self.flag = right.flag;

    return self;
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( optional&& right )
    requires std::movable<types>
{
    self.storage.assign ( std::move(right.storage), self.flag, right.flag );
    self.flag = std::exchange ( right.flag, false );

    return self;
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( types right )
    requires std::movable<types>
{
    self.storage.assign ( std::move(right), self.flag );
    self.flag = true;

    return self;
}

template < class types >
constexpr optional<types>& optional<types>::operator = ( nullopt_t )
{
    if ( flag )
    {
        storage.clear();
        flag = false;
    }

    return self;
}


// Member

template < class types >
constexpr bool optional<types>::empty ( ) const
{
    return not flag;
}

template < class types >
constexpr const std::type_info& optional<types>::type ( ) const
{
    return not empty() ? typeid(types) otherwise typeid(void);
}

template < class types >
constexpr types& optional<types>::value ( )
{
    if ( empty() )
        throw type_error("bad optional access: cannot to get {} from {} (whose empty = true, type = {})",
                         typeid(types), typeid(self), typeid(void));

    return storage.get();
}

template < class types >
constexpr const types& optional<types>::value ( ) const
{
    if ( empty() )
        throw type_error("bad optional access: cannot to get {} from {} (whose empty = true, type = {})",
                         typeid(types), typeid(self), typeid(void));

    return storage.get();
}










/// Class optional::union_obj

// Declaration

/* In optional::union_obj, the flag and storage are controlled seperately.
 * storage.clear() will always do destroy_at, and std::move() will always
 * clear the right one.
 */

template < class types >
union optional<types>::union_obj
{
    private:
        types type_storage;
        char  void_storage;

    public:
        constexpr  union_obj ( );
        constexpr  union_obj ( const union_obj&,  bool );
        constexpr  union_obj (       union_obj&&, bool );
        constexpr  union_obj ( types );
        constexpr ~union_obj ( );
        constexpr  union_obj& assign ( const union_obj&,  bool, bool );
        constexpr  union_obj& assign (       union_obj&&, bool, bool );
        constexpr  union_obj& assign (       types,        bool );

    public:
        constexpr       union_obj& clear ( );
        constexpr       types&     get   ( );
        constexpr const types&     get   ( ) const;
};



// Implemention

template < class types >
constexpr optional<types>::union_obj::union_obj ( )
{

}

template < class types >
constexpr optional<types>::union_obj::union_obj ( const union_obj& init, bool init_flag )
{
    if ( init_flag )
        std::construct_at ( &type_storage, init.type_storage );
}

template < class types >
constexpr optional<types>::union_obj::union_obj ( union_obj&& init, bool init_flag )
{
    if ( init_flag )
        std::construct_at ( &type_storage, std::move(init.type_storage) );
}

template < class types >
constexpr optional<types>::union_obj::union_obj ( types init )
{
    std::construct_at ( &type_storage, std::move(init) );
}

template < class types >
constexpr optional<types>::union_obj::~union_obj ( )
{

}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::assign ( const union_obj& right, bool self_flag, bool right_flag )
{
    if ( self_flag and right_flag )
        type_storage = right.type_storage;

    else if ( self_flag and not right_flag )
        self.clear();

    else if ( not self_flag and right_flag )
        std::construct_at ( &type_storage, right.type_storage );

    /* else if ( not self_flag and not right_flag ): Do nothing. */

    return self;
}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::assign ( union_obj&& right, bool self_flag, bool right_flag )
{
    if ( self_flag and right_flag )
    {
        type_storage = std::move(right.type_storage);
        right.clear();
    }

    else if ( self_flag and not right_flag )
        self.clear();

    else if ( not self_flag and right_flag )
    {
        std::construct_at ( &type_storage, std::move(right.type_storage) );
        right.clear();
    }

    /* else if ( not self_flag and not right_flag ): Do nothing. */

    return self;
}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::assign ( types right, bool self_flag )
{
    if ( self_flag )
        type_storage = std::move ( right );
    else
        std::construct_at ( &type_storage, std::move ( right ) );

    return self;
}

template < class types >
constexpr optional<types>::union_obj& optional<types>::union_obj::clear ( )
{
    std::destroy_at ( &type_storage );
    return self;
}

template < class types >
constexpr types& optional<types>::union_obj::get ( )
{
    return type_storage;
}

template < class types >
constexpr const types& optional<types>::union_obj::get ( ) const
{
    return type_storage;
}