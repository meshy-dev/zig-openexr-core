/*
 * Stub implementation for HT (JPEG-HT) compression.
 * We don't include OpenJPH dependency, so HT compression is not supported.
 */

#include "openexr.h"

exr_result_t
internal_exr_apply_ht (exr_encode_pipeline_t* encode)
{
    (void)encode;
    return EXR_ERR_FEATURE_NOT_IMPLEMENTED;
}

exr_result_t
internal_exr_undo_ht (
    exr_decode_pipeline_t* decode,
    const void*            compressed_data,
    uint64_t               comp_buf_size,
    void*                  uncompressed_data,
    uint64_t               uncompressed_size)
{
    (void)decode;
    (void)compressed_data;
    (void)comp_buf_size;
    (void)uncompressed_data;
    (void)uncompressed_size;
    return EXR_ERR_FEATURE_NOT_IMPLEMENTED;
}
