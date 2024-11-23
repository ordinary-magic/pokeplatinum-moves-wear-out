#ifndef POKEPLATINUM_FIELD_BATTLE_DATA_TRANSFER_H
#define POKEPLATINUM_FIELD_BATTLE_DATA_TRANSFER_H

#include "constants/battle.h"
#include "consts/map.h"

#include "struct_decls/pokedexdata_decl.h"
#include "struct_decls/struct_02027F8C_decl.h"
#include "struct_decls/struct_0202C878_decl.h"
#include "struct_decls/struct_0206D140_decl.h"
#include "struct_decls/struct_020797DC_decl.h"
#include "struct_decls/struct_party_decl.h"
#include "struct_defs/chatot_cry.h"
#include "struct_defs/move_data.h"
#include "struct_defs/trainer_data.h"

#include "field/field_system_decl.h"

#include "bag.h"
#include "game_options.h"
#include "game_records.h"
#include "journal.h"
#include "poketch_data.h"
#include "rtc.h"
#include "savedata.h"
#include "trainer_info.h"

typedef struct BattleRecords {
    int totalTurns;
    int totalFainted;
    int totalDamage;
} BattleRecords;

typedef struct FieldBattleDTO {
    u32 battleType;
    Party *parties[MAX_BATTLERS];
    int resultMask;
    int trainerIDs[MAX_BATTLERS];
    TrainerData trainerData[MAX_BATTLERS];
    TrainerInfo *trainerInfo[MAX_BATTLERS];
    Bag *bag;
    BagCursor *bagCursor;
    PokedexData *pokedex;
    PCBoxes *pcBoxes;
    MoveDataBlock *moveData;
    ChatotCry *chatotCries[MAX_BATTLERS];
    PoketchData *poketchData;
    UnkStruct_0202C878 *unk_104;
    Options *options;
    UnkStruct_0206D140 *unk_10C;
    BattleRecords battleRecords;
    GameRecords *records;
    Journal *journal;
    UnkStruct_02027F8C *unk_124;
    int background;
    enum Terrain terrain;
    int mapLabelTextID;
    int mapHeaderID;
    enum TimeOfDay timeOfDay;
    int mapEvolutionMethod;
    BOOL visitedContestHall;
    BOOL metBebe;
    int caughtBattlerIdx;
    int fieldWeather;
    int leveledUpMonsMask;
    u32 systemVersion[MAX_BATTLERS];
    u32 battleStatusMask;
    int countSafariBalls;
    u32 rulesetMask;
    void *unk_170;
    u32 seed;
    int unk_178[MAX_BATTLERS];
    u16 networkID;
    u8 unk_18A;
    u8 dummy18B;
    int totalTurnsElapsed;
    u8 *subscreenCursorOn;
    u8 unk_194[MAX_BATTLERS];
    SaveData *saveData;
    u32 unk_19C;
} FieldBattleDTO;

FieldBattleDTO *FieldBattleDTO_New(enum HeapId heapID, u32 battleType);
FieldBattleDTO *FieldBattleDTO_NewSafari(enum HeapId heapID, int countSafariBalls);
FieldBattleDTO *FieldBattleDTO_NewPalPark(enum HeapId heapID, int countParkBalls);
FieldBattleDTO *FieldBattleDTO_NewCatchingTutorial(enum HeapId heapID, const FieldSystem *fieldSystem);
void FieldBattleDTO_Free(FieldBattleDTO *dto);
void FieldBattleDTO_AddPokemonToBattler(FieldBattleDTO *dto, Pokemon *src, int battler);
void FieldBattleDTO_CopyPartyToBattler(FieldBattleDTO *dto, const Party *src, int battler);
void FieldBattleDTO_CopyTrainerInfoToBattler(FieldBattleDTO *dto, const TrainerInfo *src, int battler);
void FieldBattleDTO_CopyChatotCryToBattler(FieldBattleDTO *dto, const ChatotCry *src, int battler);
void FieldBattleDTO_InitFromGameState(FieldBattleDTO *dto, const FieldSystem *fieldSystem, SaveData *save, enum MapHeader mapHeaderID, Journal *journal, BagCursor *bagCursor, u8 *subscreenCursorOn);
void FieldBattleDTO_Init(FieldBattleDTO *dto, const FieldSystem *fieldSystem);
void FieldBattleDTO_InitWithNormalizedMonLevels(FieldBattleDTO *dto, const FieldSystem *fieldSystem, int level);
void FieldBattleDTO_InitWithPartyOrder(FieldBattleDTO *dto, const FieldSystem *fieldSystem, const Party *party, const u8 *partyOrder);
void FieldBattleDTO_InitWithPartyOrderFromSave(FieldBattleDTO *dto, const FieldSystem *fieldSystem, const u8 *partyOrder);
void FieldBattleDTO_UpdateFieldSystem(const FieldBattleDTO *dto, FieldSystem *fieldSystem);
void FieldBattleDTO_UpdatePokedex(const FieldBattleDTO *dto, FieldSystem *fieldSystem);
void FieldBattleDTO_SetWaterTerrain(FieldBattleDTO *dto);
BOOL CheckPlayerWonBattle(u32 battleResult);
BOOL CheckPlayerLostBattle(u32 battleResult);
BOOL CheckPlayerDidNotCaptureWildMon(u32 battleResult);
void FieldBattleDTO_CopyPlayerInfoToTrainerData(FieldBattleDTO *dto);

#endif // POKEPLATINUM_FIELD_BATTLE_DATA_TRANSFER_H
