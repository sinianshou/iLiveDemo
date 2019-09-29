
#ifndef PI_ILIVEBASE_GLOBALAU_CH
#define PI_ILIVEBASE_GLOBALAU_CH


typedef void(*cleanCallback)(void *data);

void GlobalAU_addAudioUnitCount();

void GlobalAU_decreaseAudioUnitCount();

void GlobalAU_addAudioUnittoList(void *audiounit);

void GlobalAU_addAudioUnittoListwithCallback(void *audiounit, cleanCallback callback, void *data);

void GlobalAU_cleanAudioUnitList();

#endif
