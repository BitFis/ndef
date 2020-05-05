#ifndef __NDEF_NDEF_H__
#define __NDEF_NDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NO_ID 0

#include <stdbool.h>
#include <stdint.h>

struct ndef_message {
    size_t length;
    struct ndef_record* records;
};

// A zero-copy data structure for storing ndef records. All fields should be
// accessed using accessors defined below.
typedef struct ndef_record {
    char* buffer;
    size_t length;

    uint8_t type_length;
    size_t type_offset;

    uint8_t id_length;
    size_t id_offset;

    uint32_t payload_length;
    size_t payload_offset;
} ndef_record;

ndef_record* ndef_parse(char* buffer, size_t offset);
ndef_record* ndef_create(
        uint8_t tnf, bool is_begin, bool is_end, bool is_chunk,
        bool is_short, bool has_length,
        const char* type, uint8_t type_length,
        const char* id, uint8_t id_length,
        const char* payload, uint32_t payload_length);

ndef_record* ndef_destroy_buffer(ndef_record*);
ndef_record* ndef_destroy(ndef_record*);

uint8_t ndef_tnf(ndef_record*);
bool ndef_is_message_begin(ndef_record*);
bool ndef_is_message_end(ndef_record*);
bool ndef_is_chunk(ndef_record*);
bool ndef_is_short_record(ndef_record*);
bool ndef_has_id_length(ndef_record*);

#ifdef __cplusplus
}
#endif

#endif
