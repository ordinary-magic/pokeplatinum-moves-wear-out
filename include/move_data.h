#ifndef POKEPLAT_MOVEDAT_SAVEBLOCK
#define POKEPLAT_MOVEDAT_SAVEBLOCK

#include "struct_decls/battle_system.h"
#include "struct_defs/battle_system.h"

#include "struct_defs/move_data.h"

// Flags for handling special cases of 0/1 power/accuracy moves
#define MOVEDATA_VALUE_IS_0 254
#define MOVEDATA_VALUE_IS_1 255

// Save block functions
void MoveDataBlock_Init(MoveDataBlock* data);
void MoveData_Copy(MoveDataBlock *src, const MoveDataBlock *dst);
MoveDataBlock *MoveData_New(u32 heapId);

// Wrapper and helper functions
void AdjustMoveBasedOnPPLoss(u32 move, int pp, BattleSystem* battleSys);
u8 GetMenuMovePower(u32 move, BattleSystem* battleSys);
u8 GetMenuMoveAccuracy(u32 move, BattleSystem* battleSys);
u16 AdjustBattleMoveEffectivePower(int move, int powerIn, BattleSystem* battleSys);
u16 GetBattleMoveEffectiveAccuracy(int move, BattleSystem* battleSys);

#endif // POKEPLAT_MOVEDAT_SAVEBLOCK