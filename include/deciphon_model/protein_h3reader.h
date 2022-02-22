#ifndef MODEL_PROTEIN_H3READER_H
#define MODEL_PROTEIN_H3READER_H

#include "deciphon_model/metadata.h"
#include "deciphon_model/protein_cfg.h"
#include "deciphon_model/protein_model.h"
#include "deciphon_model/rc.h"
#include "hmr/hmr.h"
#include "imm/imm.h"
#include <stdio.h>

struct protein_h3reader
{
    struct hmr hmr;
    struct hmr_prof prof;
    imm_float null_lprobs[IMM_AMINO_SIZE];
    struct protein_model model;
};

void protein_h3reader_init(struct protein_h3reader *reader,
                           struct imm_amino const *amino,
                           struct imm_nuclt_code const *code,
                           struct protein_cfg cfg, FILE *fp);

enum model_rc protein_h3reader_next(struct protein_h3reader *reader);
void protein_h3reader_del(struct protein_h3reader const *reader);

struct metadata protein_h3reader_metadata(struct protein_h3reader const *r);

#endif
