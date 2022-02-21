#include "nuclt_dist.h"
#include "lite_pack/file/file.h"
#include "lite_pack/lite_pack.h"

enum model_rc nuclt_dist_write(struct nuclt_dist const *ndist,
                               struct lip_file *file)
{
    enum model_rc rc = MODEL_EFAIL;
    lip_write_array_size(file, 2);
    if (imm_nuclt_lprob_pack(&ndist->nucltp, file)) return rc;
    if (imm_codon_marg_pack(&ndist->codonm, file)) return rc;
    return MODEL_OK;
}

enum model_rc nuclt_dist_read(struct nuclt_dist *ndist, struct lip_file *file)
{
    enum model_rc rc = MODEL_EFAIL;
    unsigned size = 0;
    lip_read_array_size(file, &size);
    assert(size == 2);
    if (imm_nuclt_lprob_unpack(&ndist->nucltp, file)) return rc;
    if (imm_codon_marg_unpack(&ndist->codonm, file)) return rc;
    return MODEL_OK;
}
