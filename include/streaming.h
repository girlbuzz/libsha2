#ifndef __SHA2_STREAMING_H
#define __SHA2_STREAMING_H

enum SHA2StreamBehavior {
    /* Uses the time since last call to know if it should increase buffer size of just compute the hash now. */
    SHA2_AUTOMATIC = 0,

    /* Will favor resizing the buffer over actually computing the hash until it absolutely has to. */
    SHA2_AGGRESSIVE_MEMORY_USAGE = 1,

    /* Will favor just computing the hash over resizing the buffer. */
    SHA2_CONSERVATIVE_MEMORY_USAGE = 2,
};

struct SHA2StreamState {
    /* Public fields. These are initialized by sha2*_stream_init. They are untouched by sha2*_stream_init_no_defaults. */
    size_t max_buf_cap; /* Maximum buffer size in SHA256MessageBlocks. */
    enum SHA2StreamBehavior behavior; /* How SHA2 should buffer data. */

    /* Private fields */
    size_t _data_size;
    size_t _message_block_cap;
    void *_message_blocks;

    clock_t _last, _lastlast;
};

/** Initializes a SHA2StreamState and SHA256Digest for use in streaming data.
 * @param st State to initialize. Call `sha256_stream_deinit`. Can also optionally be NULL.
 * @param H Digest to initialize.
*/
void sha256_stream_init(struct SHA2StreamState *st, SHA256Digest H);

/** Initializes a SHA2StreamState and SHA256Digest for use in streaming data. This will not override public fields in st.
 * @param st State to initialize. Call `sha256_stream_deinit`. Can also optionally be NULL.
 * @param H Digest to initialize.
*/
void sha256_stream_init_no_defaults(struct SHA2StreamState *st, SHA256Digest H);

/** Streams data into a current digest.
 * @param data Data to stream in.
 * @param nbytes Size of the data in bytes.
 * @param st State of stream.
 * @param H Current digest.
*/
void sha256_stream(const void *data, size_t nbytes, struct SHA2StreamState* st, SHA256Digest H);

/** Deinitializes a streaming state object.
 * @param st State to deinitialize. This will be free'd too and should not be used anymore.
 * @param H Digest to write final hash into.
*/
void sha256_stream_finish(struct SHA2StreamState *st, SHA256Digest H);

#endif /* __SHA2_STREAMING_H */