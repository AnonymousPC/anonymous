#pragma once

/// Class mfcc_extractor

// Core

mfcc_extractor::mfcc_extractor ( int audio_size, int audio_rate )
{
    // Check.
    if ( audio_rate < 4000 or audio_rate > 20000 )
        throw value_error("mfcc_extractor initialized with rate out of domain (with rate = {}Hz, expected = [4000Hz, 20000Hz])", audio_rate);
    if ( let audio_length = float(audio_size) / audio_rate; audio_length < 0.02 or audio_length > 0.04 )
        throw value_error("mfcc_extractor initialized with length out of domain (with size = {}frames, rate = {}Hz, length = {}ms, expected = [20ms, 40ms])", audio_size, audio_rate, audio_length*1000);

    // Deafult parameters.
    let mel_size   = 26;  // Mel-channels, usually set to [20,40].

    // Utility.
    let hz_to_mel  = [] (float hz)  { return 2595 * log10(hz/700+1);       };
    let mel_to_hz  = [] (float mel) { return 700  * (pow(10, mel/2595)-1); };

    // Define the working range in [[hz-space]].
    let low_hz     = 0;
    let high_hz    = audio_rate / 2;

    // Create points that is uniform-distributed on [[mel-space]].
    let low_mel    = hz_to_mel(low_hz);
    let high_mel   = hz_to_mel(high_hz);
    let mel_points = array(mel_size+2, [&] (int i) { return low_mel + (i-1) * (high_mel - low_mel)/(mel_size+1); });

    // Reflect it to [[hz-space]]
    let hz_points  = array(mel_size+2, [&] (int i) { return mel_to_hz(mel_points[i]); });

    // Reflect it to [[fft-space]]
    let fft_bin    = array(((audio_size+1) * hz_points / audio_rate).transform(floor<float>).template as_type<int>());

    // Create the mel filter bank (with n filter-units, and each unit with half audio_size coeffs)
    let mfcc = matrix<float>(mel_size, audio_size/2+1);
    for ( int m in range(2, mel_size+1) ) // Total audio_size+2 points in fft_bin.
    {
        let fl = fft_bin[m-1];
        let fm = fft_bin[m  ];
        let fr = fft_bin[m+1];

        for ( int k in range(fl, fm-1) )
            mfcc[m-1][k+1] = float(k-fl) / (fm-fl);
        for ( int k in range(fm, fr-1) )
            mfcc[m-1][k+1] = float(k-fr) / (fm-fr);
    }

    // Store the mfcc filter.
    mfcc_t = transpose(mfcc);
}

// Interface

int mfcc_extractor::size ( ) const
{
    return mfcc_t.row();
}

int mfcc_extractor::rate ( ) const
{
    return mfcc_t.column();
}
