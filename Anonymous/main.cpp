#include "../generic/basic/interface.hpp"
#include "../generic/container/interface.hpp"
#include "../generic/io/interface.hpp"
#include "../generic/math/interface.hpp"
#include "../specific/audio/interface.hpp"
#include "../specific/neural/interface.hpp"
#include "../specific/spirit/interface.hpp"
#include "../specific/stock/interface.hpp"
#include "example.cpp"
#include <any>
using namespace ap;

int main ( )
{
//    try
//    {
//        let wav = input("[[input]] where is the audio wav-file (e.g.: ./audio/a.wav): ");
//        let idx = input("[[input]] where to save the texture file (e.g.: ./texture/a.idx): ");
//
//        let sound = file_wav(wav);
//        sound = sound[1,-1,3];
//        sound.rate() /= 3;
//
//        mfcc_create_texture(sound, idx);
//
//        print("texture created successfully");
//    }
//    catch ( const std::exception& e )
//    {
//        print(e.what());
//    }




    let udp = input("[[input]] where is the UDP address of RinaChanBoard (e.g.: udp://10.64.105.150:1234): ");
    let texture_root = input("[[input]] where is the texture directory (e.g.: ./texture): ");

    while(true)
        try
        {
            let src = input("[[input]] where is wav-file to lipsync (e.g.: audio/wow.wav): ");

            // Read audio file.
            let sound = file_wav(src);
            sound = sound[1,-1,3];
            sound.rate() /= 3;

            // Read texture file.
            let texture = array{"{}/a.idx"s .format(texture_root),
                                "{}/ae.idx"s.format(texture_root),
                                "{}/e.idx"s .format(texture_root),
                                "{}/i.idx"s .format(texture_root),
                                "{}/o.idx"s .format(texture_root),
                                "{}/wu.idx"s.format(texture_root),
                                "{}/yu.idx"s.format(texture_root)};

            // Classify.
            let face_list = mfcc_batch_classify(sound, texture);

            // Animate.
            animate_and_send_to(face_list, udp, sound.rate());
            print();
        }
        catch ( const std::exception& e )
        {
            print(e.what());
        }
}


