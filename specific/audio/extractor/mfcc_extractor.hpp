#pragma once

class mfcc_extractor
{
    public: // Core
        mfcc_extractor ( int, int );

    public: // Interface
        array_type auto extract ( const array_type auto& ) const;

    public: // Interface
        int size ( ) const;
        int rate ( ) const;

    private: // Auxiliary
        void pre_emphasis   ( array_type auto& ) const;
        void hamming_window ( array_type auto& ) const;
        void normalize      ( array_type auto& ) const;
        void real_fft       ( array_type auto& ) const;
        void mel_filter     ( array_type auto& ) const;
        void power_to_db    ( array_type auto& ) const;
        void inplace_dct    ( array_type auto& ) const;

    private: // Parameters
        matrix<float> mfcc_t = {}; // Transpose of mfcc.
};


#include "mfcc_extractor.ipp"
#if dll
    #include "mfcc_extractor.cpp"
#endif // dll
