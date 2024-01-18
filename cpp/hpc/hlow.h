#pragma once

#include <stdbool.h>
#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

static const int64_t h_type_void    = 'v';
static const int64_t h_type_bool    = 'b';
static const int64_t h_type_int64   = 'i';
static const int64_t h_type_float64 = 'f';
static const int64_t h_type_string  = 's';
static const int64_t h_type_bytes   = 'a';

//the parameter key of return value.
static const char *const h_key_return = "return";

int64_t h_session_create ();
int64_t h_session_retain (int64_t sid);
void    h_session_release(int64_t sid);

void        h_session_set_procedure_name(int64_t sid, const char *name);
const char *h_session_procedure_name    (int64_t sid);
void        h_session_set_callback_id   (int64_t sid, int64_t callback_id);
int64_t     h_session_callback_id       (int64_t sid);

void h_session_set_param_bool   (int64_t sid, const char *key, bool        value);
void h_session_set_param_int64  (int64_t sid, const char *key, int64_t     value);
void h_session_set_param_float64(int64_t sid, const char *key, double      value);
void h_session_set_param_string (int64_t sid, const char *key, const char *value);
void h_session_set_param_bytes  (int64_t sid, const char *key, const void *value, int64_t size);

int64_t     h_session_param_type      (int64_t sid, const char *key);
bool        h_session_param_bool      (int64_t sid, const char *key);
int64_t     h_session_param_int64     (int64_t sid, const char *key);
double      h_session_param_float64   (int64_t sid, const char *key);
const char *h_session_param_string    (int64_t sid, const char *key);
const void *h_session_param_bytes_data(int64_t sid, const char *key);
int64_t     h_session_param_bytes_size(int64_t sid, const char *key);

void h_add_call_procedure    (bool (*procedure)(int64_t sid));
void h_add_callback_procedure(bool (*procedure)(int64_t sid));

void h_call    (int64_t sid);
void h_callback(int64_t sid);

#if __cplusplus
}
#endif
