#pragma once

#include <cstdint>

//

extern "C" void hpc_prepare_bool  (const char *key, bool           arg);
extern "C" void hpc_prepare_int64 (const char *key, int64_t        arg);
extern "C" void hpc_prepare_double(const char *key, double         arg);
extern "C" void hpc_prepare_string(const char *key, const char    *arg);
extern "C" void hpc_prepare_bytes (const char *key, const uint8_t *data, int64_t size);

//

extern "C" void hpc_add_call_proc    (bool (*proc)(int64_t session_id));
extern "C" void hpc_add_callback_proc(bool (*proc)(int64_t session_id));

//

extern "C" const char    *hpc_call_name     (int64_t session_id);
extern "C" bool           hpc_arg_bool      (int64_t session_id, const char *key);
extern "C" int64_t        hpc_arg_int64     (int64_t session_id, const char *key);
extern "C" double         hpc_arg_double    (int64_t session_id, const char *key);
extern "C" const char    *hpc_arg_string    (int64_t session_id, const char *key);
extern "C" const uint8_t *hpc_arg_bytes_data(int64_t session_id, const char *key);
extern "C" int64_t        hpc_arg_bytes_size(int64_t session_id, const char *key);

extern "C" void hpc_return_bool  (int64_t session_id, const char *key, bool           ret);
extern "C" void hpc_return_int64 (int64_t session_id, const char *key, int64_t        ret);
extern "C" void hpc_return_double(int64_t session_id, const char *key, double         ret);
extern "C" void hpc_return_string(int64_t session_id, const char *key, const char    *ret);
extern "C" void hpc_return_bytes (int64_t session_id, const char *key, const uint8_t *data, int64_t size);

extern "C" void hpc_callback(int64_t session_id);

//

extern "C" int64_t hpc_call(const char *name);

extern "C" bool           hpc_returned_bool      (int64_t session_id);
extern "C" int64_t        hpc_returned_int64     (int64_t session_id);
extern "C" double         hpc_returned_double    (int64_t session_id);
extern "C" const char    *hpc_returned_string    (int64_t session_id);
extern "C" const uint8_t *hpc_returned_bytes_data(int64_t session_id);
extern "C" int64_t        hpc_returned_bytes_size(int64_t session_id);

extern "C" void hpc_release_returned(int64_t session_id);
