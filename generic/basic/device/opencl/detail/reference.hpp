#pragma once

template < class type >
class opencl::reference
{
    private: // Data
        boost::compute::buffer buf;
        size_t                 idx;

    public: // Core
        reference ( ) = delete;

        reference ( const reference& ) = default;

        reference operator = ( const reference& right )
        {
            static let program = boost::compute::program::build_with_source_type(
                __kernel void assign ( __global type* self_buf, int self_idx, __global type* right_buf, int right_idx )
                {
                    self_buf[self_idx] = right_buf[right_idx];
                }
            );
            
            let kernel = boost::compute::kernel(program, "assign");
            kernel.set_args(self.buf, self.idx, right.buf, right.idx);
            opencl::execution_context.get_command_queue().enqueue_task(kernel);
            opencl::execution_context.get_command_queue().finish();
            return self;
        }

    public: // Conversion (type)
        template < class type2 >
        reference operator = ( reference<type2> right )
        {
            using type1 = type;
            static let program = boost::compute::program::build_with_source_type1_type2(
                __kernel void assign ( __global type1* self_buf, int self_idx, __global type2* right_buf, int right_idx )
                {
                    self_buf[self_idx] = right_buf[right_idx];
                }
            );
            
            let kernel = boost::compute::kernel(program, "assign");
            kernel.set_args(self.buf, self.idx, right.buf, right.idx);
            opencl::execution_context.get_command_queue().enqueue_task(kernel);
            opencl::execution_context.get_command_queue().finish();
            return self;
        }

    public: // Conversion (device)
        reference operator = ( type cvt )
        {
            boost::compute::detail::write_single_value<type>(cvt, buf, idx, opencl::execution_context.get_command_queue());
            opencl::execution_context.get_command_queue().finish();
            return self;
        }

        operator type ( ) const
        {
            let cvt = boost::compute::detail::read_single_value<type>(buf, idx, opencl::execution_context.get_command_queue());
            opencl::execution_context.get_command_queue().finish();
            return cvt;
        }

    public: // Conversion (boost::compute)
        reference ( boost::compute::buffer init_buf, size_t init_idx )
            extends buf ( init_buf ),
                    idx ( init_idx )
        {
            
        }

        reference ( boost::compute::detail::buffer_value<type> cvt )
            extends reference ( (&cvt).get_buffer(), (&cvt).get_index() / sizeof(type) )
        {
            
        }

        operator boost::compute::detail::buffer_value<type> ( ) const
        {
            return boost::compute::detail::buffer_value<type>(get_buffer(), get_index() * sizeof(type));
        }

    public: // Member
        boost::compute::buffer get_buffer ( ) const
        {
            return buf;
        }

        size_t get_index ( ) const
        {
            return idx;
        }
};



// Operator

/* Binary operator (+, -, *, /, ...) which accepts two
 * device value, but returns a host value, does not need
 * to be declared. They will use built-in operators.
 */

template < class type1, class type2 >
bool operator == ( opencl::template const_reference<type1> left, opencl::template const_reference<type2> right )
{
    static let program = boost::compute::program::build_with_source_type1_type2(
        __kernel void equal_to ( __global type1* left_buf, int left_idx, __global type2* right_buf, int right_idx, __global bool* result_buf )
        {
            result_buf[0] = (left_buf[left_idx] == right_buf[right_idx]);
        }
    );

    let kernel = boost::compute::kernel(program, "equal_to");
    let result = boost::compute::buffer(opencl::execution_context.get_command_queue().get_context(), sizeof(bool));
    kernel.set_args(left.get_buffer(), left.get_index(), right.get_buffer(), right.get_index(), result);
    opencl::execution_context.get_command_queue().enqueue_task(kernel);
    let sign = boost::compute::detail::read_single_value<bool>(result, 0, opencl::execution_context.get_command_queue());
    opencl::execution_context.get_command_queue().finish();
    return sign;
}

template < class type1, class type2 >
compare_result<type1,type2> operator <=> ( opencl::template const_reference<type1> left, opencl::template const_reference<type2> right )
{
    if constexpr ( same_as<compare_result<type1,type2>,std::strong_ordering> or
                   same_as<compare_result<type1,type2>,std::partial_ordering> )
    {
        static let program = boost::compute::program::build_with_source_type1_type2(
            __kernel void three_way_compare ( __global type1* left_buf, int left_idx, __global type2* right_buf, int right_idx, __global int* result_buf )
            {
                result_buf[0] = left_buf[left_idx] == right_buf[right_idx] ?  0 :
                                left_buf[left_idx] <  right_buf[right_idx] ? -1 :
                                                                              1;
            }
        );

        let kernel = boost::compute::kernel(program, "three_way_compare");
        let result = boost::compute::buffer(opencl::execution_context.get_command_queue().get_context(), sizeof(int));
        kernel.set_args(left.get_buffer(), left.get_index(), right.get_buffer(), right.get_index(), result);
        opencl::execution_context.get_command_queue().enqueue_task(kernel);
        let sign = boost::compute::detail::read_single_value<int>(result, 0, opencl::execution_context.get_command_queue());
        opencl::execution_context.get_command_queue().finish();
        return sign ==  0 ? compare_result<type1,type2>::equivalent otherwise
               sign == -1 ? compare_result<type1,type2>::less       otherwise
                            compare_result<type1,type2>::greater; 
    }

    else if constexpr ( same_as<compare_result<type1,type2>,std::partial_ordering> )
    {
        static let program = boost::compute::program::build_with_source_type1_type2(
            __kernel void three_way_compare ( __global type1* left_buf, int left_idx, __global type2* right_buf, int right_idx, __global int* result_buf )
            {
                result_buf[0] = left_buf[left_idx] == right_buf[right_idx] ?  0 :
                                left_buf[left_idx] <  right_buf[right_idx] ? -1 :
                                left_buf[left_idx] >  right_buf[right_idx] ?  1 :
                                                                              2;
            }
        );

        let kernel = boost::compute::kernel(program, "three_way_compare");
        let result = boost::compute::buffer(opencl::execution_context.get_command_queue().get_context(), sizeof(int));
        kernel.set_args(left.get_buffer(), left.get_index(), right.get_buffer(), right.get_index(), result);
        opencl::execution_context.get_command_queue().enqueue_task(kernel);
        let sign = boost::compute::detail::read_single_value<int>(result, 0, opencl::execution_context.get_command_queue());
        opencl::execution_context.get_command_queue().finish();
        return sign ==  0 ? compare_result<type1,type2>::equivalent otherwise
               sign == -1 ? compare_result<type1,type2>::less       otherwise
               sign ==  1 ? compare_result<type1,type2>::greater    otherwise
                            compare_result<type1,type2>::unordered; 
    }
}

template < class type >
opencl::template reference<type> operator ++ ( opencl::template reference<type> left )
{
    static let program = boost::compute::program::build_with_source_type(
        __kernel void increment ( __global type* left_buf, int left_idx )
        {
            ++left_buf[left_idx];
        }
    );

    let kernel = boost::compute::kernel(program, "increment");
    kernel.set_args(left.get_buffer(), left.get_index());
    opencl::execution_context.get_command_queue().enqueue_task(kernel);
    opencl::execution_context.get_command_queue().finish();
    return left;
}

template < class type > 
type operator ++ ( opencl::template reference<type> left, int )
{
    type tmp = left;
    ++left;
    return tmp;
}

template < class type >
opencl::template reference<type> operator -- ( opencl::template reference<type> left )
{
    static let program = boost::compute::program::build_with_source_type(
        __kernel void decrement ( __global type* left_buf, int left_idx )
        {
            --left_buf[left_idx];
        }
    );

    let kernel = boost::compute::kernel(program, "decrement");
    kernel.set_args(left.get_buffer(), left.get_index());
    opencl::execution_context.get_command_queue().enqueue_task(kernel);
    opencl::execution_context.get_command_queue().finish();
    return left;
}

template < class type > 
type operator -- ( opencl::template reference<type> left, int )
{
    type tmp = left;
    --left;
    return tmp;
}