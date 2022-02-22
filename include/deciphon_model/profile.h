#ifndef MODEL_PROFILE_H
#define MODEL_PROFILE_H

#include "deciphon_model/rc.h"
#include "imm/imm.h"

struct lip_file;
struct profile;

struct profile_vtable
{
    int typeid;
    void (*del)(struct profile *prof);
    enum model_rc (*read)(struct profile *prof, struct lip_file *);
    struct imm_dp const *(*null_dp)(struct profile const *prof);
    struct imm_dp const *(*alt_dp)(struct profile const *prof);
};

struct profile
{
    struct profile_vtable vtable;
    imm_state_name *state_name;
    struct imm_code const *code;
};

void profile_del(struct profile *prof);

enum model_rc profile_unpack(struct profile *prof, struct lip_file *);

int profile_typeid(struct profile const *prof);
struct imm_dp const *profile_null_dp(struct profile const *prof);
struct imm_dp const *profile_alt_dp(struct profile const *prof);

void profile_init(struct profile *prof, struct imm_code const *code,
                  struct profile_vtable vtable, imm_state_name *state_name);

void profile_set_state_name(struct profile *prof, imm_state_name *state_name);

#endif
