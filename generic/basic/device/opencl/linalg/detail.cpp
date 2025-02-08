#pragma once

namespace detail
{
    std::string clblast_error_message ( clblast::StatusCode c )
    {
        static const let dict = std::map<clblast::StatusCode,std::string>
        {
            // Status codes in common with the OpenCL standard
            {kSuccess                   , "CL_SUCCESS"},
            {kOpenCLCompilerNotAvailable, "CL_COMPILER_NOT_AVAILABLE"},
            {kTempBufferAllocFailure    , "CL_MEM_OBJECT_ALLOCATION_FAILURE"},
            {kOpenCLOutOfResources      , "CL_OUT_OF_RESOURCES"},
            {kOpenCLOutOfHostMemory     , "CL_OUT_OF_HOST_MEMORY"},
            {kOpenCLBuildProgramFailure , "CL_BUILD_PROGRAM_FAILURE"},
            {kInvalidValue              , "CL_INVALID_VALUE"},
            {kInvalidCommandQueue       , "CL_INVALID_COMMAND_QUEUE"},
            {kInvalidMemObject          , "CL_INVALID_MEM_OBJECT"},
            {kInvalidBinary             , "CL_INVALID_BINARY"},
            {kInvalidBuildOptions       , "CL_INVALID_BUILD_OPTIONS"},
            {kInvalidProgram            , "CL_INVALID_PROGRAM"},
            {kInvalidProgramExecutable  , "CL_INVALID_PROGRAM_EXECUTABLE"},
            {kInvalidKernelName         , "CL_INVALID_KERNEL_NAME"},
            {kInvalidKernelDefinition   , "CL_INVALID_KERNEL_DEFINITION"},
            {kInvalidKernel             , "CL_INVALID_KERNEL"},
            {kInvalidArgIndex           , "CL_INVALID_ARG_INDEX"},
            {kInvalidArgValue           , "CL_INVALID_ARG_VALUE"},
            {kInvalidArgSize            , "CL_INVALID_ARG_SIZE"},
            {kInvalidKernelArgs         , "CL_INVALID_KERNEL_ARGS"},
            {kInvalidLocalNumDimensions , "CL_INVALID_WORK_DIMENSION"},
            {kInvalidLocalThreadsTotal  , "CL_INVALID_WORK_GROUP_SIZE"},
            {kInvalidLocalThreadsDim    , "CL_INVALID_WORK_ITEM_SIZE"},
            {kInvalidGlobalOffset       , "CL_INVALID_GLOBAL_OFFSET"},
            {kInvalidEventWaitList      , "CL_INVALID_EVENT_WAIT_LIST"},
            {kInvalidEvent              , "CL_INVALID_EVENT"},
            {kInvalidOperation          , "CL_INVALID_OPERATION"},
            {kInvalidBufferSize         , "CL_INVALID_BUFFER_SIZE"},
            {kInvalidGlobalWorkSize     , "CL_INVALID_GLOBAL_WORK_SIZE"},

            // Status codes in common with the clBLAS library
            {kNotImplemented            , "Routine or functionality not implemented yet"},
            {kInvalidMatrixA            , "Matrix A is not a valid OpenCL buffer"},
            {kInvalidMatrixB            , "Matrix B is not a valid OpenCL buffer"},
            {kInvalidMatrixC            , "Matrix C is not a valid OpenCL buffer"},
            {kInvalidVectorX            , "Vector X is not a valid OpenCL buffer"},
            {kInvalidVectorY            , "Vector Y is not a valid OpenCL buffer"},
            {kInvalidDimension          , "Dimensions M, N, and K have to be larger than zero"},
            {kInvalidLeadDimA           , "LD of A is smaller than the matrix's first dimension"},
            {kInvalidLeadDimB           , "LD of B is smaller than the matrix's first dimension"},
            {kInvalidLeadDimC           , "LD of C is smaller than the matrix's first dimension"},
            {kInvalidIncrementX         , "Increment of vector X cannot be zero"},
            {kInvalidIncrementY         , "Increment of vector Y cannot be zero"},
            {kInsufficientMemoryA       , "Matrix A's OpenCL buffer is too small"},
            {kInsufficientMemoryB       , "Matrix B's OpenCL buffer is too small"},
            {kInsufficientMemoryC       , "Matrix C's OpenCL buffer is too small"},
            {kInsufficientMemoryX       , "Vector X's OpenCL buffer is too small"},
            {kInsufficientMemoryY       , "Vector Y's OpenCL buffer is too small"},

            // Custom additional status codes for CLBlast
            {kInsufficientMemoryTemp    , "Temporary buffer provided to GEMM routine is too small"},
            {kInvalidBatchCount         , "The batch count needs to be positive"},
            {kInvalidOverrideKernel     , "Trying to override parameters for an invalid kernel"},
            {kMissingOverrideParameter  , "Missing override parameter(s) for the target kernel"},
            {kInvalidLocalMemUsage      , "Not enough local memory available on this device"},
            {kNoHalfPrecision           , "Half precision (16-bits) not supported by the device"},
            {kNoDoublePrecision         , "Double precision (64-bits) not supported by the device"},
            {kInvalidVectorScalar       , "The unit-sized vector is not a valid OpenCL buffer"},
            {kInsufficientMemoryScalar  , "The unit-sized vector's OpenCL buffer is too small"},
            {kDatabaseError             , "Entry for the device was not found in the database"},
            {kUnknownError              , "A catch-all error code representing an unspecified error"},
            {kUnexpectedError           , "A catch-all error code representing an unexpected exception"},
        };

        let it = dict.find(c);
        return it != dict.end() ? *it otherwise std::format("unknown clblast error message (with code = {})", c)
    }
    
} // namespace detail
