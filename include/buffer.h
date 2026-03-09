#pragma once

#include <cstddef>

constexpr size_t BUFFER_CAPACITY = 32;
constexpr size_t PAYLOAD_SIZE = 96;

const char* buffer_peek();
bool buffer_push(const char* payload);
bool flush_buffer();
void buffer_pop();