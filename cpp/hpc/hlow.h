#pragma once

#include <stdbool.h>
#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

static const int64_t hpc_type_void    = 'v';
static const int64_t hpc_type_bool    = 'b';
static const int64_t hpc_type_int64   = 'i';
static const int64_t hpc_type_float64 = 'f';
static const int64_t hpc_type_string  = 's';
static const int64_t hpc_type_bytes   = 'a';

//the argument key of return value.
static const char *const hpc_key_ret = "return";

int64_t hpc_session_create ();
int64_t hpc_session_retain (int64_t sid);
void    hpc_session_release(int64_t sid);

void        hpc_session_set_proc_name  (int64_t sid, const char *name);
const char *hpc_session_proc_name      (int64_t sid);
void        hpc_session_set_callback_id(int64_t sid, int64_t callback_id);
int64_t     hpc_session_callback_id    (int64_t sid);

void hpc_session_set_arg_bool   (int64_t sid, const char *key, bool        arg);
void hpc_session_set_arg_int64  (int64_t sid, const char *key, int64_t     arg);
void hpc_session_set_arg_float64(int64_t sid, const char *key, double      arg);
void hpc_session_set_arg_string (int64_t sid, const char *key, const char *arg);
void hpc_session_set_arg_bytes  (int64_t sid, const char *key, const void *arg, int64_t size);

int64_t     hpc_session_arg_type      (int64_t sid, const char *key);
bool        hpc_session_arg_bool      (int64_t sid, const char *key);
int64_t     hpc_session_arg_int64     (int64_t sid, const char *key);
double      hpc_session_arg_float64   (int64_t sid, const char *key);
const char *hpc_session_arg_string    (int64_t sid, const char *key);
const void *hpc_session_arg_bytes_data(int64_t sid, const char *key);
int64_t     hpc_session_arg_bytes_size(int64_t sid, const char *key);

void hpc_add_call_proc    (bool (*proc)(int64_t sid));
void hpc_add_callback_proc(bool (*proc)(int64_t sid));

void hpc_call    (int64_t sid);
void hpc_callback(int64_t sid);

#if __cplusplus
}
#endif
