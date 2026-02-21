#define AUDIODRIVER_NULL
#include "it2play/audiodrivers/null/nulldriver.c"

#include "it2play/it2drivers/sb16.c"
#include "it2play/it2drivers/sb16_m.c"
#include "it2play/it2drivers/sb16mmx.c"
#include "it2play/it2drivers/sb16mmx_m.c"
#include "it2play/it2drivers/zerovol.c"

#include "it2play/it_tables.c"
#include "it2play/it_structs.c"
#include "it2play/it_music.c"
#include "it2play/it_m_eff.c"
#include "it2play/it_d_rm.c"

#include "it2play/loaders/it.c"
#include "it2play/loaders/s3m.c"
#include "it2play/loaders/mmcmp/mmcmp.c"
