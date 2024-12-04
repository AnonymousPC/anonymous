#pragma once

#ifndef __cpp_lib_ranges_join_with
    namespace ranges
    {
        template < class... Rs >
        using concat_reference_t = common_reference_t<range_reference_t<Rs>...>;

        template < class... Rs >
        using concat_value_t = common_type_t<range_value_t<Rs>...>;

        template < class... Rs >
        using concat_rvalue_reference_t = common_reference_t<ranges_rvalue_referenece_t<Rs>...>;

        template < class Ref, class RRef, class It >
        concept concat_indirectly_readable_impl = 
            requires ( const It it )
            {
                { *it } -> convertible_to<Ref>;
                { iter_move(it) } -> convertible_to<RRef>;
            }

        template < class... Rs >
        concept concat_indirectly_readable = 
            common_reference_with<concat_reference_t<Rs...>&&,
                                  concat_value_t<Rs...>&> &&
            common_reference_with<concat_reference_t<Rs...>&&,
                                  concat_rvalue_reference_t<Rs...>&&> &&
            common_reference_with<concat_rvalue_reference_t<Rs...>&&,
                                  concat_value_t<Rs...> const&> &&
            (concat_indirectly_readable_impl<concat_reference_t<Rs...>,
                                             concat_rvalue_reference_t<Rs...>,
                                             iterator_t<Rs>> && ...);

        template < class... Rs >
        concept concatable = requires
        {
            typename concat_reference_t<Rs...>;
            typename concat_value_t<Rs...>;
            typename concat_rvalue_reference_t<Rs...>;
        } && concat_indirectly_readable<Rs...>;

        template < input_range V, forward_range Pattern >
            requires view<V> &&
                     input_range<range_reference_t<V>> &&
                     view<Pattern> /*&&*/
                     /*concatable<ranges::range_reference_t<V>, Pattern>*/
        class join_with_view
            extends public view_interface<join_with_view<V, Pattern>>
        {
            private:
                using InnerRng = ranges::range_reference_t<V>;
                V                   base_;
                Pattern             pattern_;
                iterator_t<V>       outer_it_;
                remove_cv<InnerRng> inner_;

            public:
                join_with_view ( )
                    requires default_initializable<V> &&
                             default_initializable<Pattern> = default;

                constexpr explicit join_with_view ( V base, Pattern pattern )
                    extends base_    ( std::move(base) ),
                            pattern_ ( std::move(pattern) )
                {
                    
                }

                template < input_range R >
                    requires std::constructible_from<V, views::all_t<R>> &&
                             std::constructible_from<Pattern, single_view<range_value_t<InnerRng>>>
                constexpr explicit join_with_view ( R&& r, range_value_t<InnerRng> e )
                    extends base_    ( views::all(std::forward<R>(r)) ),
                            pattern_ ( views::single(std::move(e)) )
                {

                }

                constexpr V base ( ) const& requires std::copy_constructible<V>
                {
                    return base_;
                }

                constexpr V base ( ) &&
                {
                    return std::move(base_);
                }

                constexpr auto 


        };
    } // namespace ranges

    namespace views
    {
        inline constexpr auto join_with = [] (const auto& pt) { return }
    } // namespace views
    
