#pragma once

namespace detail
{
    std::string clblast_error_message ( clblast::StatusCode c )
    {
        static const let dict = std::map<clblast::StatusCode,std::string>
        {
            // Status codes in common with the OpenCL standard
            {clblast::StatusCode::kSuccess                   , "CL_SUCCESS"},
            {clblast::StatusCode::kOpenCLCompilerNotAvailable, "CL_COMPILER_NOT_AVAILABLE"},
            {clblast::StatusCode::kTempBufferAllocFailure    , "CL_MEM_OBJECT_ALLOCATION_FAILURE"},
            {clblast::StatusCode::kOpenCLOutOfResources      , "CL_OUT_OF_RESOURCES"},
            {clblast::StatusCode::kOpenCLOutOfHostMemory     , "CL_OUT_OF_HOST_MEMORY"},
            {clblast::StatusCode::kOpenCLBuildProgramFailure , "CL_BUILD_PROGRAM_FAILURE"},
            {clblast::StatusCode::kInvalidValue              , "CL_INVALID_VALUE"},
            {clblast::StatusCode::kInvalidCommandQueue       , "CL_INVALID_COMMAND_QUEUE"},
            {clblast::StatusCode::kInvalidMemObject          , "CL_INVALID_MEM_OBJECT"},
            {clblast::StatusCode::kInvalidBinary             , "CL_INVALID_BINARY"},
            {clblast::StatusCode::kInvalidBuildOptions       , "CL_INVALID_BUILD_OPTIONS"},
            {clblast::StatusCode::kInvalidProgram            , "CL_INVALID_PROGRAM"},
            {clblast::StatusCode::kInvalidProgramExecutable  , "CL_INVALID_PROGRAM_EXECUTABLE"},
            {clblast::StatusCode::kInvalidKernelName         , "CL_INVALID_KERNEL_NAME"},
            {clblast::StatusCode::kInvalidKernelDefinition   , "CL_INVALID_KERNEL_DEFINITION"},
            {clblast::StatusCode::kInvalidKernel             , "CL_INVALID_KERNEL"},
            {clblast::StatusCode::kInvalidArgIndex           , "CL_INVALID_ARG_INDEX"},
            {clblast::StatusCode::kInvalidArgValue           , "CL_INVALID_ARG_VALUE"},
            {clblast::StatusCode::kInvalidArgSize            , "CL_INVALID_ARG_SIZE"},
            {clblast::StatusCode::kInvalidKernelArgs         , "CL_INVALID_KERNEL_ARGS"},
            {clblast::StatusCode::kInvalidLocalNumDimensions , "CL_INVALID_WORK_DIMENSION"},
            {clblast::StatusCode::kInvalidLocalThreadsTotal  , "CL_INVALID_WORK_GROUP_SIZE"},
            {clblast::StatusCode::kInvalidLocalThreadsDim    , "CL_INVALID_WORK_ITEM_SIZE"},
            {clblast::StatusCode::kInvalidGlobalOffset       , "CL_INVALID_GLOBAL_OFFSET"},
            {clblast::StatusCode::kInvalidEventWaitList      , "CL_INVALID_EVENT_WAIT_LIST"},
            {clblast::StatusCode::kInvalidEvent              , "CL_INVALID_EVENT"},
            {clblast::StatusCode::kInvalidOperation          , "CL_INVALID_OPERATION"},
            {clblast::StatusCode::kInvalidBufferSize         , "CL_INVALID_BUFFER_SIZE"},
            {clblast::StatusCode::kInvalidGlobalWorkSize     , "CL_INVALID_GLOBAL_WORK_SIZE"},

            // Status codes in common with the clBLAS library
            {clblast::StatusCode::kNotImplemented            , "Routine or functionality not implemented yet"},
            {clblast::StatusCode::kInvalidMatrixA            , "Matrix A is not a valid OpenCL buffer"},
            {clblast::StatusCode::kInvalidMatrixB            , "Matrix B is not a valid OpenCL buffer"},
            {clblast::StatusCode::kInvalidMatrixC            , "Matrix C is not a valid OpenCL buffer"},
            {clblast::StatusCode::kInvalidVectorX            , "Vector X is not a valid OpenCL buffer"},
            {clblast::StatusCode::kInvalidVectorY            , "Vector Y is not a valid OpenCL buffer"},
            {clblast::StatusCode::kInvalidDimension          , "Dimensions M, N, and K have to be larger than zero"},
            {clblast::StatusCode::kInvalidLeadDimA           , "LD of A is smaller than the matrix's first dimension"},
            {clblast::StatusCode::kInvalidLeadDimB           , "LD of B is smaller than the matrix's first dimension"},
            {clblast::StatusCode::kInvalidLeadDimC           , "LD of C is smaller than the matrix's first dimension"},
            {clblast::StatusCode::kInvalidIncrementX         , "Increment of vector X cannot be zero"},
            {clblast::StatusCode::kInvalidIncrementY         , "Increment of vector Y cannot be zero"},
            {clblast::StatusCode::kInsufficientMemoryA       , "Matrix A's OpenCL buffer is too small"},
            {clblast::StatusCode::kInsufficientMemoryB       , "Matrix B's OpenCL buffer is too small"},
            {clblast::StatusCode::kInsufficientMemoryC       , "Matrix C's OpenCL buffer is too small"},
            {clblast::StatusCode::kInsufficientMemoryX       , "Vector X's OpenCL buffer is too small"},
            {clblast::StatusCode::kInsufficientMemoryY       , "Vector Y's OpenCL buffer is too small"},

            // Custom additional status codes for CLBlast
            {clblast::StatusCode::kInsufficientMemoryTemp    , "Temporary buffer provided to GEMM routine is too small"},
            {clblast::StatusCode::kInvalidBatchCount         , "The batch count needs to be positive"},
            {clblast::StatusCode::kInvalidOverrideKernel     , "Trying to override parameters for an invalid kernel"},
            {clblast::StatusCode::kMissingOverrideParameter  , "Missing override parameter(s) for the target kernel"},
            {clblast::StatusCode::kInvalidLocalMemUsage      , "Not enough local memory available on this device"},
            {clblast::StatusCode::kNoHalfPrecision           , "Half precision (16-bits) not supported by the device"},
            {clblast::StatusCode::kNoDoublePrecision         , "Double precision (64-bits) not supported by the device"},
            {clblast::StatusCode::kInvalidVectorScalar       , "The unit-sized vector is not a valid OpenCL buffer"},
            {clblast::StatusCode::kInsufficientMemoryScalar  , "The unit-sized vector's OpenCL buffer is too small"},
            {clblast::StatusCode::kDatabaseError             , "Entry for the device was not found in the database"},
            {clblast::StatusCode::kUnknownError              , "A catch-all error code representing an unspecified error"},
            {clblast::StatusCode::kUnexpectedError           , "A catch-all error code representing an unexpected exception"},
        };

        let it = dict.find(c);
        return it != dict.end() ? it->second otherwise std::format("unknown clblast error message (with code = {})", int(c));
    }
    
} // namespace detail
