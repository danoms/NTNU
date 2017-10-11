#include "game_types.h"

#ifndef dma_H
#define dma_H

void updateControl(volatile dma_descriptor* dma_descr, volatile channel_cfg* cfg);
void setupDMA( volatile dma_descriptor* dma_descr);

#endif