#include "global/config.h"

#include "struct_defs/move_data.h"
#include "move_data.h"
#include "savedata_misc.h"

// Configure the build to reduce move's accuracy, power, both, or neither
#define MOVE_ACCURACY_REDUCTION;
#define MOVE_POWER_REDUCTION;

// configure how much to reduce it
#define MOVE_ACCURACY_REDUCTION_AMOUNT 1;
#define MOVE_POWER_REDUCTION_AMOUNT 1;

// Allocate a new MoveData Block
MoveDataBlock *MoveData_New(u32 heapId) {
    MoveDataBlock *moveData = Heap_AllocFromHeap(heapId, sizeof(MoveDataBlock));
    MoveDataBlock_Init(moveData); // prob not needed but options did it so whatev
    return moveData;
}

// Initialze the data structure for a new game ()
void MoveDataBlock_Init(MoveDataBlock* data) {
    // 0 out everything as no moves have been called yet
    memset(data, 0, sizeof(MoveDataBlock));
}

// Copy the data block
void MoveData_Copy(MoveDataBlock *src, const MoveDataBlock *dst) {
    MI_CpuCopy8(src, dst, sizeof(MoveDataBlock));
}

// Get the current power of a move for a menu
// Note: BattleSys is optional, and should only be passed if in a battle context (otherwise 0)
#ifdef MOVE_POWER_REDUCTION
u8 GetMenuMovePower(u32 move, BattleSystem* battleSys) {
    // (If battleSys is NULL must pull from save data block instead)
    int loss = (battleSys ? battleSys->moveData : MiscSaveBlock_GetMoveData(SaveData_Ptr()))->counter[move];
    loss *= MOVE_POWER_REDUCTION_AMOUNT;

    int power = MoveTable_LoadParam(move, MOVEATTRIBUTE_POWER);

    // Moves with a power of 0 or 1 are either status moves or variable power moves
    //   thus, if we want it to report 0, or 1, we must use special flags for that instead
    if (power < 2)
        return MOVEDATA_VALUE_IS_0 + power;

    power -= loss;
    return (u8) ((power > 0)? power : 0);
}

// Apply power adjustment to a move which is being called in battle.
u16 AdjustBattleMoveEffectivePower(int move, int powerIn, BattleSystem* battleSys){
    int reduction = battleSys->moveData->counter[move] * MOVE_POWER_REDUCTION_AMOUNT;
    return (u16) ((powerIn - reduction > 0)? powerIn - reduction : 0);
}

#else

// Functions that dont change anything, for when power adjustment is turned off
u8 GetMenuMovePower(u32 move, BattleSystem* battleSys) {
    u8 power = (u8) MoveTable_LoadParam(move, MOVEATTRIBUTE_POWER);

    // Even if adjustment is off, menus still expect this
    if (power < 2)
        return MOVEDATA_VALUE_IS_0 + power;

    return (u8) MoveTable_LoadParam(move, MOVEATTRIBUTE_POWER);
}

u16 AdjustBattleMoveEffectivePower(int move, int powerIn, BattleSystem* battleSys){
    return (u16) powerIn;
}
#endif

// Get the current accuracy of a move for a menu
// Note: BattleSys is optional, and should only be passed if in a battle context (otherwise 0)
#ifdef MOVE_ACCURACY_REDUCTION
u8 GetMenuMoveAccuracy(u32 move, BattleSystem* battleSys) {
    // (If battleSys is NULL must pull from save data block instead)
    int loss = (battleSys ? battleSys->moveData : MiscSaveBlock_GetMoveData(SaveData_Ptr()))->counter[move];
    loss *= MOVE_ACCURACY_REDUCTION_AMOUNT;

    int accuracy = MoveTable_LoadParam(move, MOVEATTRIBUTE_ACCURACY);
    
    // Internally, accuracy for "always hit" moves is 0, so treat these as a step above 100 instead
    if (!accuracy)
        accuracy = 100 + MOVE_ACCURACY_REDUCTION_AMOUNT;

    return (u8) ((accuracy - loss > 0)? accuracy - loss : 0);
}

// Get the current accuracy of a move which is being called in battle
u16 GetBattleMoveEffectiveAccuracy(int move, BattleSystem* battleSys) {
    int accuracyIn = MoveTable_LoadParam(move, MOVEATTRIBUTE_ACCURACY);
    
    if (!accuracyIn) // adjust "sure hit" moves
        accuracyIn = 100 + MOVE_ACCURACY_REDUCTION_AMOUNT;

    int reduction = battleSys->moveData->counter[move] * MOVE_ACCURACY_REDUCTION_AMOUNT;
    return (u16) ((accuracyIn - reduction > 0)? accuracyIn - reduction : 0);
}

#else
// Accuracy adjustments disabled, just return the normal values
u8 GetMenuMoveAccuracy(u32 move, BattleSystem* battleSys) {
    u8 accuracy = (u8) MoveTable_LoadParam(move, MOVEATTRIBUTE_ACCURACY);

    // Even if accuracy adjustment is off, menus still expect this
    if (!accuracy)
        return 101;
    else
        return accuracy;
}
u16 GetBattleMoveEffectiveAccuracy(int move, BattleSystem* battleSys){
    return GetMenuMoveAccuracy(move, battleSys);
}
#endif

// Decrement Power/Accuracy to match the ammount of pp used.
void AdjustMoveBasedOnPPLoss(u32 move, int pp, BattleSystem* battleSys) {
    u32 value = battleSys->moveData->counter[move] + pp;
    battleSys->moveData->counter[move] = ((value > 0xFF)? 0xFF : value) & 0xFF;
}