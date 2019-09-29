
#ifndef PI_ILIVEBASE_GLOBALAU_H
#define PI_ILIVEBASE_GLOBALAU_H


typedef void(*cleanCallback)(void *data);

@interface PI_iLiveBase_GlobalAU : NSObject

+(PI_iLiveBase_GlobalAU*)sharedInstance;

-(void) addAudioUnitCount;
-(void) decreaseAudioUnitCount;

-(void) addAudioUnittoList:(AudioUnit)unit;
-(void) addAudioUnittoList:(AudioUnit)unit withCallback:(cleanCallback)callback withData:(void*)data;
-(void) cleanAudioUnitList;

@end

#endif
