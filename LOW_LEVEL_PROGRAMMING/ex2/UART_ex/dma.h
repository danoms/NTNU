#include "game_types.h"
#include "per_typedef.h"

#ifndef dma_H
#define dma_H

void updateControl(volatile dma_descriptor_t* dma_descr, volatile channel_cfg_t* cfg);
void setupDMA( volatile dma_descriptor_t* dma_descr);

#endif