#pragma once

#ifdef BOOST_COMPUTE_HPP
    class opencl
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Context
            class  execution_context_type;
            static execution_context_type execution_context;

        public: // Layout
            using layout_type = std::layout_left;

        public: // Allocator
            template < class type > using allocator = boost::compute::buffer_allocator<type>;

        public: // Compare
            template < class type > using equal_to      = boost::compute::equal_to<type>;
            template < class type > using not_equal_to  = boost::compute::not_equal_to<type>;
            template < class type > using less          = boost::compute::less<type>;
            template < class type > using less_equal    = boost::compute::less_equal<type>;
            template < class type > using greater       = boost::compute::greater<type>;
            template < class type > using greater_equal = boost::compute::greater_equal<type>; 

        public: // Hash
            template < class type > using hash = boost::compute::hash<type>;

        public: // Container
            template < class type, class alloc = allocator<type> >                        using vector       = boost::compute::vector<type,alloc>;
            template < class type, int len >                                              using array        = boost::compute::array<type,len>;
            template < class type >                                                       using stack        = boost::compute::stack<type>;
            template < class type >                                                       using flat_set     = boost::compute::flat_set<type>;
            template < class type1, class type2 >                                         using flat_map     = boost::compute::flat_map<type1,type2>;
            template < class char_type, class char_traits = std::char_traits<char_type> > using basic_string = boost::compute::basic_string<char_type,char_traits>;
                                                                                          using string       = basic_string<char>;

        public: // Algorithm
            constexpr static decltype(auto) accumulate               ( auto&&... args ) { return boost::compute::accumulate              (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) adjacent_difference      ( auto&&... args ) { return boost::compute::adjacent_difference     (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) adjacent_find            ( auto&&... args ) { return boost::compute::adjacent_find           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) all_of                   ( auto&&... args ) { return boost::compute::all_of                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) any_of                   ( auto&&... args ) { return boost::compute::any_of                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) binary_search            ( auto&&... args ) { return boost::compute::binary_search           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) copy                     ( auto&&... args ) { return boost::compute::copy                    (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) copy_backward            ( auto&&... args ) { return boost::compute::copy_backward           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) copy_if                  ( auto&&... args ) { return boost::compute::copy_if                 (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) copy_n                   ( auto&&... args ) { return boost::compute::copy_n                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) count                    ( auto&&... args ) { return boost::compute::count                   (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) count_if                 ( auto&&... args ) { return boost::compute::count_if                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) equal                    ( auto&&... args ) { return boost::compute::equal                   (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) equal_range              ( auto&&... args ) { return boost::compute::equal_range             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) exclusive_scan           ( auto&&... args ) { return boost::compute::exclusive_scan          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) fill                     ( auto&&... args ) { return boost::compute::fill                    (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) fill_n                   ( auto&&... args ) { return boost::compute::fill_n                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) find                     ( auto&&... args ) { return boost::compute::find                    (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) find_end                 ( auto&&... args ) { return boost::compute::find_end                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) find_first_of            ( auto&&... args ) { return boost::compute::find_first_of           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) find_if                  ( auto&&... args ) { return boost::compute::find_if                 (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) find_if_not              ( auto&&... args ) { return boost::compute::find_if_not             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) for_each                 ( auto&&... args ) { return boost::compute::for_each                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) for_each_n               ( auto&&... args ) { return boost::compute::for_each_n              (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) generate                 ( auto&&... args ) { return boost::compute::generate                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) generate_n               ( auto&&... args ) { return boost::compute::generate_n              (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) includes                 ( auto&&... args ) { return boost::compute::includes                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) inclusive_scan           ( auto&&... args ) { return boost::compute::inclusive_scan          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) inner_product            ( auto&&... args ) { return boost::compute::inner_product           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) inplace_merge            ( auto&&... args ) { return boost::compute::inplace_merge           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) iota                     ( auto&&... args ) { return boost::compute::iota                    (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) is_partitioned           ( auto&&... args ) { return boost::compute::is_partitioned          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) is_permutation           ( auto&&... args ) { return boost::compute::is_permutation          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) is_sorted                ( auto&&... args ) { return boost::compute::is_sorted               (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) is_sorted_until          ( auto&&... args ) { return boost::compute::is_sorted_until         (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) lower_bound              ( auto&&... args ) { return boost::compute::lower_bound             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) lexicographical_compare  ( auto&&... args ) { return boost::compute::lexicographical_compare (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) max_element              ( auto&&... args ) { return boost::compute::max_element             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) merge                    ( auto&&... args ) { return boost::compute::merge                   (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) min_element              ( auto&&... args ) { return boost::compute::min_element             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) minmax_element           ( auto&&... args ) { return boost::compute::minmax_element          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) mismatch                 ( auto&&... args ) { return boost::compute::mismatch                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
      /*!*/ constexpr static decltype(auto) move                     ( auto&&... args ) { return boost::compute::copy                    (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) move_backward            ( auto&&... args ) { return boost::compute::move_backward           (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) next_permutation         ( auto&&... args ) { return boost::compute::next_permutation        (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) none_of                  ( auto&&... args ) { return boost::compute::none_of                 (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) nth_element              ( auto&&... args ) { return boost::compute::nth_element             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) partial_sort             ( auto&&... args ) { return boost::compute::partial_sort            (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) partial_sort_copy        ( auto&&... args ) { return boost::compute::partial_sort_copy       (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) partial_sum              ( auto&&... args ) { return boost::compute::partial_sum             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) partition                ( auto&&... args ) { return boost::compute::partition               (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) partition_copy           ( auto&&... args ) { return boost::compute::partition_copy          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) partition_point          ( auto&&... args ) { return boost::compute::partition_point         (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) prev_permutation         ( auto&&... args ) { return boost::compute::prev_permutation        (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) reduce                   ( auto&&... args ) { return boost::compute::reduce                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) remove                   ( auto&&... args ) { return boost::compute::remove                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) remove_copy              ( auto&&... args ) { return boost::compute::remove_copy             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) remove_copy_if           ( auto&&... args ) { return boost::compute::remove_copy_if          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) remove_if                ( auto&&... args ) { return boost::compute::remove_if               (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) replace                  ( auto&&... args ) { return boost::compute::replace                 (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) replace_copy             ( auto&&... args ) { return boost::compute::replace_copy            (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) replace_copy_if          ( auto&&... args ) { return boost::compute::replace_copy_if         (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) replace_if               ( auto&&... args ) { return boost::compute::replace_if              (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) reverse                  ( auto&&... args ) { return boost::compute::reverse                 (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) reverse_copy             ( auto&&... args ) { return boost::compute::reverse_copy            (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) rotate                   ( auto&&... args ) { return boost::compute::rotate                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) rotate_copy              ( auto&&... args ) { return boost::compute::rotate_copy             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) sample                   ( auto&&... args ) { return boost::compute::sample                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) search                   ( auto&&... args ) { return boost::compute::search                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) search_n                 ( auto&&... args ) { return boost::compute::search_n                (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) set_difference           ( auto&&... args ) { return boost::compute::set_difference          (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) set_intersection         ( auto&&... args ) { return boost::compute::set_intersection        (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) set_symmetric_difference ( auto&&... args ) { return boost::compute::set_symmetric_difference(std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) set_union                ( auto&&... args ) { return boost::compute::set_union               (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) shift_left               ( auto&&... args ) { return boost::compute::shift_left              (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) shift_right              ( auto&&... args ) { return boost::compute::shift_right             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
         // constexpr static decltype(auto) shuffle                  ( auto&&... args ) { return boost::compute::shuffle                 (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) sort                     ( auto&&... args ) { return boost::compute::sort                    (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) stable_partition         ( auto&&... args ) { return boost::compute::stable_partition        (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) stable_sort              ( auto&&... args ) { return boost::compute::stable_sort             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) swap_ranges              ( auto&&... args ) { return boost::compute::swap_ranges             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) transform                ( auto&&... args ) { return boost::compute::transform               (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) unique                   ( auto&&... args ) { return boost::compute::unique                  (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) unique_copy              ( auto&&... args ) { return boost::compute::unique_copy             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
            constexpr static decltype(auto) upper_bound              ( auto&&... args ) { return boost::compute::upper_bound             (std::forward<decltype(args)>(args)..., execution_context_type::command_queue()); execution_context_type::command_queue().finish(); }
    
        public: // Context.detail  
            class execution_context_type
                extends public execpools::thread_pool_base<execution_context_type>
            {
                public: // Constructor
                             execution_context_type ( ) = default;
                    explicit execution_context_type ( int ) { };

                public: // Member
                    std::uint32_t available_parallelism ( ) const
                    {
                        return boost::compute::system::default_device().compute_units();
                    }

                    static boost::compute::command_queue& command_queue ( )
                    {
                        thread_local auto cmd_queue = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
                        return cmd_queue;
                    }

                public: // Friend
                                                                 friend        execpools::thread_pool_base<execution_context_type>;
                    template < class pool_type, class receiver > friend struct execpools::operation;  

                private: // Member
                    constexpr static std::execution::forward_progress_guarantee forward_progress_guarantee ( )
                    {
                        return std::execution::forward_progress_guarantee::parallel;
                    };

                    void enqueue ( execpools::task_base* task, std::uint32_t tid = 0 )
                    {
                        thread_local auto task_queue = boost::compute::command_queue(boost::compute::system::default_context(), boost::compute::system::default_device());
                        //task_queue.enqueue_native_kernel(enqueue_callback, new task_type(task, tid), sizeof(task_type), 0, 0, 0);
                        task_queue.enqueue_native_kernel(+[] { int a = 1; a++; });
                        task_queue.flush();
                    }

                    static void BOOST_COMPUTE_CL_CALLBACK enqueue_callback ( void* args )
                    {
                        let ptr = static_cast<task_type*>(args);
                        ptr->task->__execute(ptr->task, /*tid=*/ptr->tid);
                    }

                    struct task_type
                    {
                        execpools::task_base* task;
                        std::uint32_t         tid;
                    };   
            };
    };
    opencl::execution_context_type opencl::execution_context = opencl::execution_context_type(boost::compute::system::default_device().max_work_group_size());
#else
    class opencl
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }
    };
#endif
