#include "deciphon_model/model.h"
#include "hope/hope.h"
#include "imm/imm.h"

int main(void)
{
    unsigned core_size = 3;
    struct imm_amino const *amino = &imm_amino_iupac;
    struct imm_nuclt const *nuclt = imm_super(&imm_dna_iupac);
    struct imm_nuclt_code code;
    imm_nuclt_code_init(&code, nuclt);
    struct protein_cfg cfg = {ENTRY_DIST_OCCUPANCY, 0.01f};
    imm_float null_lprobs[IMM_AMINO_SIZE];
    imm_float null_lodds[IMM_AMINO_SIZE];
    imm_float match_lprobs1[IMM_AMINO_SIZE];
    imm_float match_lprobs2[IMM_AMINO_SIZE];
    imm_float match_lprobs3[IMM_AMINO_SIZE];
    struct protein_trans t[4];

    struct imm_rnd rnd = imm_rnd(942);
    imm_lprob_sample(&rnd, IMM_AMINO_SIZE, null_lprobs);
    imm_lprob_sample(&rnd, IMM_AMINO_SIZE, null_lodds);
    imm_lprob_sample(&rnd, IMM_AMINO_SIZE, match_lprobs1);
    imm_lprob_sample(&rnd, IMM_AMINO_SIZE, match_lprobs2);
    imm_lprob_sample(&rnd, IMM_AMINO_SIZE, match_lprobs3);

    for (unsigned i = 0; i < 4; ++i)
    {
        imm_lprob_sample(&rnd, PROTEIN_TRANS_SIZE, t[i].data);
        imm_lprob_normalize(PROTEIN_TRANS_SIZE, t[i].data);
    }

    struct protein_model model;
    protein_model_init(&model, amino, &code, cfg, null_lprobs);

    EQ(protein_model_setup(&model, core_size), MODEL_OK);

    EQ(protein_model_add_node(&model, match_lprobs1, '-'), MODEL_OK);
    EQ(protein_model_add_node(&model, match_lprobs2, '-'), MODEL_OK);
    EQ(protein_model_add_node(&model, match_lprobs3, '-'), MODEL_OK);

    EQ(protein_model_add_trans(&model, t[0]), MODEL_OK);
    EQ(protein_model_add_trans(&model, t[1]), MODEL_OK);
    EQ(protein_model_add_trans(&model, t[2]), MODEL_OK);
    EQ(protein_model_add_trans(&model, t[3]), MODEL_OK);

    struct protein_profile prof;
    protein_profile_init(&prof, amino, &code, cfg);

    EQ(protein_profile_absorb(&prof, &model), MODEL_OK);

    profile_del((struct profile *)&prof);
    protein_model_del(&model);
    return hope_status();
}
