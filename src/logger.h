#ifndef MODEL_LOGGER_H
#define MODEL_LOGGER_H

#include "compiler.h"
#include "model_rc.h"

typedef void logger_print_t(char const *msg, void *arg);
void logger_setup(logger_print_t *print, void *arg);

#define __WARN_FMT(rc, msg) LOCAL(__LINE__) ":" #rc ": " msg
enum model_rc __logger_warn(enum model_rc rc, char const *msg);
#define warn(rc, msg) __logger_warn(rc, __WARN_FMT(rc, msg))

// #define __INFO_FMT(msg) LOCAL(__LINE__) ":" msg
//  void __logger_info(char const *msg);
// #define info(msg) __logger_info(__INFO_FMT(msg))

#define __ERROR_FMT(rc, msg) LOCAL(__LINE__) ":" #rc ": " msg
enum model_rc __logger_error(enum model_rc rc, char const *msg);
#define error(rc, msg) __logger_error(rc, __ERROR_FMT(rc, msg))

#define efail(what) error(MODEL_EFAIL, "failed to " what)
#define eio(what) error(MODEL_EIO, "failed to " what)
#define enomem(what) error(MODEL_ENOMEM, "failed to " what)
#define eparse(what) error(MODEL_EPARSE, "failed to " what)

#endif
