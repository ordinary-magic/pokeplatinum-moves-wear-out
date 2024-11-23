#ifndef POKEPLAT_MOVEDAT_STRUCTDEF
#define POKEPLAT_MOVEDAT_STRUCTDEF

#include <nnsys.h>
#include "consts/moves.h"

// Track how many times a move has been called, and use that as its power/accuracy loss
typedef struct MoveDataBlock_t {
    u8 counter[MAX_MOVES];
} MoveDataBlock;

#endif //POKEPLAT_MOVEDAT_STRUCTDEF