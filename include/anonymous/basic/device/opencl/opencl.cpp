#pragma once

opencl::execution_context_type opencl::execution_context = opencl::execution_context_type(boost::compute::system::default_device().max_work_group_size());