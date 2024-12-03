#pragma once

/// Class mfcc_extractor

// Interface

array_type auto mfcc_extractor::extract ( const array_type auto& inputs ) const
{
    // Check.
    static_assert(array_type<decay<decltype(inputs)>,float,1> or array_type<decay<decltype(inputs)>,float,2>,"invalid audio type");
    if ( inputs.shape()[1] / 2 + 1 != mfcc_t.shape()[1] )
        throw value_error("audio.size mismatches the mfcc_extractor.slice.size (with audio.size = {}, expected = {})", inputs.shape()[1], mfcc_t.shape()[1]);
    if constexpr ( requires { inputs.rate(); } )
        if ( inputs.rate() != mfcc_t.shape()[2] )
            throw value_error("audio.rate mismatches the mfcc_extractor.slice.rate (with audio.size = {}, expected = {})", inputs.shape()[2], mfcc_t.shape()[2]);

    // Single-channelize.
    array audio = [&]
    {
        if constexpr ( inputs.dimension() == 1 )
            return inputs;
        else if constexpr ( inputs.dimension() == 2 )
            return inputs
                 | std::views::transform([] (const auto& frame) { return frame.average(); })
                 | std::ranges::to<vector<float>>(inputs.shape()[1]);
    } ();

    // Process audio.
    pre_emphasis  (audio);
    hamming_window(audio);
    normalize     (audio);
    real_fft      (audio);
    mel_filter    (audio);
    power_to_db   (audio);
    inplace_dct   (audio);

    // Output.
    return array(audio[1,12]);
}

// Auxilliary

void mfcc_extractor::pre_emphasis ( array_type auto& audio ) const
{
    for ( int i in range(audio.size(), 2, -1) )
        audio[i] -= 0.95 * audio[i-1]; // Apply pre-emphasis: y[i] = x[i] - p * x[i-1]. p is usually set to [0.95,0.97].

    audio[1] -= 0.95 * audio[1];
}

void mfcc_extractor::hamming_window ( array_type auto& audio ) const
{
    for ( int i in range(audio.size()) )
    {
        let pos = float(i-1) / (audio.size() - 1);           // The position of sample point in current hamming windows.
        audio[i] *= 0.54 - 0.46 * cos(radian(2 * pi * pos)); // Apply window: w(x) = 0.54 - 0.46 * cos(2*pi*pos).
    }
}

void mfcc_extractor::normalize ( array_type auto& audio ) const
{
    audio /= audio.max();
}

void mfcc_extractor::real_fft ( array_type auto& audio ) const
{
    audio = fft(audio)
          | std::views::transform([] (auto val) { return abs(val); }) // Turn complex into amplitude.
          | std::views::take(audio.size()/2+1)                        // Real field fft is symmetric on amplitude.
          | std::ranges::to<decay<decltype(audio)>>();
}

void mfcc_extractor::mel_filter ( array_type auto& audio ) const
{
    // Apply mel filter bank.
    audio = transpose(audio) * mfcc_t;
}

void mfcc_extractor::power_to_db ( array_type auto& audio ) const
{
    audio.transform([] (const auto& val) { return val > 0 ? ln(val) otherwise -inf; });
}

void mfcc_extractor::inplace_dct ( array_type auto& audio ) const
{
    audio = dct<2>(audio);
}
