#ifndef MODEL_NUCLT_DIST_H
#define MODEL_NUCLT_DIST_H

#include "imm/imm.h"
#include "model/rc.h"

struct nuclt_dist
{
    struct imm_nuclt_lprob nucltp;
    struct imm_codon_marg codonm;
};

struct lip_file;

static inline void nuclt_dist_init(struct nuclt_dist *nucltd,
                                   struct imm_nuclt const *nuclt)
{
    nucltd->nucltp.nuclt = nuclt;
    nucltd->codonm.nuclt = nuclt;
}

enum model_rc nuclt_dist_write(struct nuclt_dist const *ndist,
                               struct lip_file *);

enum model_rc nuclt_dist_read(struct nuclt_dist *ndist, struct lip_file *);

#endif
