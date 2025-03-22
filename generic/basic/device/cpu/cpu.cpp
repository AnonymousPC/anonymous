#pragma once

             cpu::execution_context_type cpu::execution_context = cpu::execution_context_type(/*std::thread::hardware_concurrency() - */1);
thread_local cpu::random_context_type    cpu::random_context    = cpu::random_context_type   (std::random_device()());
