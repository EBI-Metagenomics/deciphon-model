#ifndef MODEL_STANDARD_PROFILE_H
#define MODEL_STANDARD_PROFILE_H

#include "deciphon_model/profile.h"
#include "deciphon_model/rc.h"
#include <stdio.h>

struct standard_profile
{
    struct profile super;

    struct
    {
        struct imm_dp null;
        struct imm_dp alt;
    } dp;
};

void standard_profile_init(struct standard_profile *, struct imm_code const *);
enum model_rc standard_profile_read(struct standard_profile *prof, FILE *fp);
enum model_rc standard_profile_write(struct standard_profile const *prof,
                                     struct lip_file *);

#endif
