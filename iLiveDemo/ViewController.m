//
//  ViewController.m
//  iLiveDemo
//
//  Created by Easer Liu on 2019/9/29.
//  Copyright © 2019 Easer Liu. All rights reserved.
//

#import "ViewController.h"

//#import <PI_iRoom/PIiRoomPeer.h>

#import <PI_iRoom/PIiRoom.h>
#import <PI_iRoom/PIiRoomPeer.h>
@interface ViewController ()<PILayoutController,PIUserWindowUpdateListener, PeerDelegate>

@property PIiRoomPeer *peer;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor lightGrayColor];
    [self config];
        // Do any additional setup after loading the view.
    }
    -(void) config{
        self.peer = [[PIiRoomPeer alloc]initWithUid:@"1" withPreviewAtStart:true withCallback:self];
        // PIPIiRoomConfig 使用默认配置
        PIPIiRoomConfig_Builder* room_config_builder = [PIPIiRoomConfig builder];
        PIPIiRoomConfig* config = [room_config_builder build];

        // 使用APP层布局控制
        PIiRoomViewConfig* viewConfig = [[PIiRoomViewConfig alloc] init];
        viewConfig.layoutController = self;
        viewConfig.userWindowUpdateListener = self;
        viewConfig.layoutType = PI_LAYOUT_TYPE_APP;

        //推流参数设置，使用默认值
        PIProcessSetParam* param = [[PIProcessSetParam alloc] init];
        //视频推流参数设置
        PIProcessVideoSetParam* videoParam = [[PIProcessVideoSetParam alloc] init];
        //音频推流参数设置
        PIProcessAudioSetParam* audioParam = [[PIProcessAudioSetParam alloc] init];

        [[Transcoder tcs] setAudioTrackid:0 forDataSourceid:DATASOURCEID_RAW_MIC_AUDIO];
        [[Transcoder tcs] setAudioTrackid:1 forDataSourceid:DATASOURCEID_MIXED_AUDIO];
        param.video_param = @[ videoParam ];
        param.audio_param = @[ audioParam ];
        // 相机参数设置
        INTERFACE_CAMERA_PARAMS* cameraParam = [[INTERFACE_CAMERA_PARAMS alloc] init];
        cameraParam.avcap_preset = 0;   //采集分辨率
        cameraParam.cam_direction = 0;  //摄像头方向
        cameraParam.capture_fps = videoParam.video_fps;
        cameraParam.video_external_process = true;  //视频数据是否回调
        //配置 PIiRoomPeer
        [self.peer configurePIiRoomConfig:config
                             previewParam:cameraParam
                          processSetParam:param
                           roomViewConfig:viewConfig];
    }


    #pragma mark --PILayoutController
    - (id)createWindowContainer:(NSString *)rid uid:(NSString *)uid veName:(NSString *)veName {
        NSLog(@"func is -- %s", __func__);
        return self.view;
    }

    #pragma mark --PIUserWindowUpdateListener

    - (void)onWindowAdded:(PIUserWindow *)window {
        
    }

    - (void)onWindowMoved:(PIUserWindow *)before After:(PIUserWindow *)after {
        
    }

    - (void)onWindowRemoved:(PIUserWindow *)window {
        
    }

    #pragma mark --PeerDelegate

    - (void)onReceivePeerVideoSuccess2:(NSString *)roomId
                                andUid:(NSString *)uid{
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onReceivePeerAudioSuccess2:(NSString *)roomId
                                andUid:(NSString *)uid{
                                    NSLog(@"func is ---- %s", __func__);
        
    }

    - (void)onPeerLeft2:(NSString *)roomId
                 andUid:(NSString *)uid{

                     NSLog(@"func is ---- %s", __func__);
                 }

    - (void)onKickout:(NSString *)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onMainVeLeft:(NSString *)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onPeerVeJoined:(NSString *)roomId
                    andUid:(NSString *)uid
                 andVeName:(NSString *)veName{
                     
                     NSLog(@"func is ---- %s", __func__);
                 }

    - (void)onPeerVeLeft:(NSString *)roomId
                  andUid:(NSString *)uid
               andVeName:(NSString *)veName{
                   
                   NSLog(@"func is ---- %s", __func__);
               }

    - (void)onLeftiRoom2:(NSString *)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onJoinediRoom2:(NSString *)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onLeftAlliRoom{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onMessageOutput3:(NSString *)roomId
              withReceiveUid:(NSString *)receiverUid
          withReceiverVeName:(NSString *)veName
                 withMessage:(NSString *)message{
                     
                     NSLog(@"func is ---- %s", __func__);
                 }

    - (void)onRsSuccess:(NSString *)rsReqId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onError:(jint)code
            andData:(NSString *)data{
                
                NSLog(@"func is ---- %s", __func__);
            }

    - (void)onAecStatusChanged:(jboolean)enabled{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onAudioDeviceChanged:(PIAudioDevice *)audioDevice{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)oniRoomDestroyed2:(NSString *)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onTranscoderCreated{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onReceiveAppPrivateData:(NSString *)data{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onPsTimerFired:(NSString *)data{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onReceiveAppMessageWithRid:(NSString *)rid
                           withFromUid:(NSString *)fromUid
                        withFromVeName:(NSString *)fromVeName
                              withData:(NSString *)data{
                                  
                                  NSLog(@"func is ---- %s", __func__);
                              }

    - (void)onChangeVeName:(NSString *)roomId
                   withUid:(NSString *)uid
             withOldVeName:(NSString *)oldVeName
             withNewVeName:(NSString *)newVeName{
                 
                 NSLog(@"func is ---- %s", __func__);
             }

    - (void)onVeNameChanged:(NSString *)roomId
                    withUid:(NSString *)uid
              withOldVeName:(NSString *)oldVeName
              withNewVeName:(NSString *)newVeName{
                  
                  NSLog(@"func is ---- %s", __func__);
              }

    - (void)onSelfAxModeChanged:(jint)axMode{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onRoomAxModeChanged:(jint)axMode{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onReceiveEventFromPusher:(NSString *)roomId
                              andUid:(NSString *)uid
                     andEventContent:(NSString *)eventContent{
                         
                         NSLog(@"func is ---- %s", __func__);
                     }

    - (void)onReceiveEventFromPlayer:(NSString *)data{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onChangeExternalState:(NSString *)data{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onChangeSelfExternalState:(NSString *)data{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onPushStreamingSuccess:(NSString *)roomId
                            andUid:(NSString *)uid{
                                NSLog(@"func is ---- %s", __func__);
                            }

    - (void)onUserCapResult:(id<JavaUtilMap>)result {
        NSLog(@"func is ---- %s", __func__);
    }
    - (void)onNetStatusResult:(NSString *)uid
                    andVeName:(NSString *)veName
                   andContent:(NSString *)content{
                       
                       NSLog(@"func is ---- %s", __func__);
                   }

    - (void)onA50StateChange:(jint)a50State{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onA50StateChangeSuccess:(jint)a50State{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onReceivePeerVideoSuccess:(jlong)roomId
                               andUid:(NSString *)uid{
                                   
                                   NSLog(@"func is ---- %s", __func__);
                               }

    - (void)onReceivePeerAudioSuccess:(jlong)roomId
                               andUid:(NSString *)uid{
                                   
                                   NSLog(@"func is ---- %s", __func__);
                               }

    - (void)onIAEvent:(jlong)roomId
               andUid:(NSString *)uid
      andEventContent:(NSString *)eventContent{
          
          NSLog(@"func is ---- %s", __func__);
      }

    - (void)onPeerLeft:(jlong)roomId
                andUid:(NSString *)uid{
                    
                    NSLog(@"func is ---- %s", __func__);
                }

    - (void)onLeftiRoom:(jlong)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onJoinediRoom:(jlong)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onMessageOutput:(jlong)roomId
             withReceiveUid:(NSString *)receiverUid
                withMessage:(NSString *)message{
                    
                    NSLog(@"func is ---- %s", __func__);
                }

    - (void)onMessageOutput2:(NSString *)roomId
              withReceiveUid:(NSString *)receiverUid
                 withMessage:(NSString *)message{
                     
                     NSLog(@"func is ---- %s", __func__);
                 }

    - (void)oniRoomDestroyed:(jlong)roomId{
        
        NSLog(@"func is ---- %s", __func__);
    }

    - (void)onIAEvent2:(NSString *)roomId
                andUid:(NSString *)uid
       andEventContent:(NSString *)eventContent{
           
           NSLog(@"func is ---- %s", __func__);
       }

    @end
