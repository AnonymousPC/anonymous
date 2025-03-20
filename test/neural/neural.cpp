namespace ap::neural
{

    using my_model = sequence_model<linear_layer <array<double>,array<double>>,
                                    sigmoid_layer<array<double>,array<double>>,
                                    linear_layer <array<double>,array<double>>,
                                    sigmoid_layer<array<double>,array<double>>,
                                    linear_layer <array<double>,array<double>>,
                                    sigmoid_layer<array<double>,array<double>>>;

    using my_optimizer = sgd<linear_layer <array<double>,array<double>>,
                             sigmoid_layer<array<double>,array<double>>,
                             linear_layer <array<double>,array<double>>,
                             sigmoid_layer<array<double>,array<double>>,
                             linear_layer <array<double>,array<double>>,
                             sigmoid_layer<array<double>,array<double>>>;

    my_model     model;
    my_optimizer optimizer;

    struct model_initializer
    {
        model_initializer()
        {
            model[1c] = linear_layer<array<double>,array<double>>(784, 128);
            model[3c] = linear_layer<array<double>,array<double>>(128, 64 );
            model[5c] = linear_layer<array<double>,array<double>>(64,  10 );

            model[1c][1c] = xavier_normal_initialize(std::move(model[1c][1c]), 784, 128);
            model[3c][1c] = xavier_normal_initialize(std::move(model[3c][1c]), 128, 64 );
            model[5c][1c] = xavier_normal_initialize(std::move(model[5c][1c]), 64,  10 );
        }
    };
    model_initializer model_initializer_instance;

    struct optimizer_initializer
    {
        optimizer_initializer()
        {
            optimizer[1c].learning_rate() = 0.01;
            //optimizer[1c].momentum()      = 0.9;
           // optimizer[1c].dampening()     = 1e-4;
           // optimizer[1c].nesterov()      = true;

            optimizer[3c].learning_rate() = 0.01;
           // optimizer[3c].momentum()      = 0.9;
           // optimizer[3c].dampening()     = 1e-4;
           // optimizer[3c].nesterov()      = true;

            optimizer[5c].learning_rate() = 0.01;
           // optimizer[5c].momentum()      = 0.9;
           // optimizer[5c].dampening()     = 1e-4;
           // optimizer[5c].nesterov()      = true;
        }
    };
    optimizer_initializer optimizer_initializer_instance;



    void train ( )
    {
        let raw_images = file_idx("files/train-images.idx3-ubyte").value<array<uint8_t,3>>();
        let raw_labels = file_idx("files/train-labels.idx1-ubyte").value<array<uint8_t,1>>();
        let images     = array<double,2>(raw_images.shape()[1],     [&] (int i)        { return raw_images[i].flatten(); });
        let labels     = array<double,2>(raw_labels.shape()[1], 10, [&] (int i, int j) { return raw_labels[i] == 0 ? j == 10 otherwise j == raw_labels[i]; });
        images.flatten().transform([&] (auto x) { return (x / 255 - 0.1307) / 0.3081; });

        let total_size = raw_images.shape()[1];
        let epoch_size = 2;
        let batch_size = 30;

        for ( int batch_idx in range(total_size * epoch_size / batch_size) )
        {
            let chosen       = array(batch_size, [=] (int i) { return random(1, total_size); });
            let this_images  = matrix<double>(batch_size, [&] (int i) { return images[chosen[i]]; });
            let this_labels  = matrix<double>(batch_size, [&] (int i) { return labels[chosen[i]]; });

            let this_outputs = model.forward(std::move(this_images), optimizer);
            let this_loss    = mse_loss<matrix<double>>(std::move(this_outputs), std::move(this_labels));
            model.backward(this_loss, optimizer);

            if ( batch_idx * batch_size % 100 == 0 )
                print("train {} images in {} total"s.format(batch_idx * batch_size, total_size * epoch_size));
        }
    }

    void test ( )
    {
        let raw_images = file_idx("files/t10k-images.idx3-ubyte").value<array<uint8_t,3>>();
        let raw_labels = file_idx("files/t10k-labels.idx1-ubyte").value<array<uint8_t,1>>();
        let images     = array<double,2>(raw_images.shape()[1], [&] (int i) { return raw_images[i].flatten(); });
        let labels     = array<int>     (raw_labels);
        images.flatten().transform([&] (auto x) { return (x / 255 - 0.1307) / 0.3081; });

        let outputs = model.forward(images);
        let results = array<int>(outputs.shape()[1], [&] (int i) { return (&outputs[i].max() - outputs[i].begin() + 1) % 10; });

        int correct = 0;
        for ( int i in range(results.size()) )
            if ( results[i] == labels[i] )
                correct++;
        print("test {} images with {} correct"s.format(results.size(), correct));

        print("input q to query");
        if ( input() == 'q' )
            for ( int i in range(results.size()) )
                print("my = {}, key = {}"s.format(results[i], labels[i]));

    }


}
