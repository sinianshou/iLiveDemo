//
//  Uploadfile.h
//  Uploadfile
//
//  Created by PowerSmart on 15/11/5.
//  Copyright © 2015年 PowerSmart. All rights reserved.
//
#import <Foundation/Foundation.h>

#ifndef Uploadfile_h
#define Uploadfile_h

typedef NS_ENUM(int, PSLogUploadResult) {
    PSLogUploadResult_Sucess = 0,
    PSLogUploadResult_ERR_INI_SIZE = -1,
    PSLogUploadResult_ERR_FORM_SIZE = -2,
    PSLogUploadResult_ERR_PARTIAL = -3,
    PSLogUploadResult_ERR_NO_FILE = -4,
    PSLogUploadResult_ERR_FILESIZE_0 = -5,
    PSLogUploadResult_ERR_NO_TMP_DIR = -6,
    PSLogUploadResult_ERR_CANT_WRITE = -7,
    PSLogUploadResult_WrongID = -8,
    PSLogUploadResult_Error = -10
};

typedef NS_ENUM(int, PSLogCleanResult) {
    PSLogCleanResult_Sucess = 0,
    PSLogCleanResult_WrongID = -1,
};

@protocol PSLogUploadDelegate <NSObject>
//此回调在子线程中
-(void)didUploadLogResult:(PSLogUploadResult)result;
-(void)didCleanLog:(PSLogCleanResult)result;

@end

@interface PSLogManager:NSObject
@property (nonatomic,weak)id<PSLogUploadDelegate> delegate;
@property (nonatomic,readonly)double progress;                  //返回上传进度百分比
@property (nonatomic,readonly)uint64_t logsSize;                //返回压缩包大小
@property (nonatomic,readonly)int zipState;                     //返回压缩状态，1代表压缩完成，0未完成

- (instancetype)init NS_UNAVAILABLE;

/**
 init

 @param delegate UploadDelegate
 @return self
 */
- (instancetype)initWithDelegate:(id<PSLogUploadDelegate>)delegate;

/**
 init

 @param delegate PSLogUploadDelegate
 @param path 日志的路径（绝对路径,absolute pat
 @return self
 */
- (instancetype)initWithDelegate:(id<PSLogUploadDelegate>)delegate logPath:(NSString*)path;

/**
 init

 @param serverTopDomain 日志上传的一级域名
 @param delegate PSLogUploadDelegate
 @return self
 */
- (instancetype)initWithServerTopDomain:(NSString*)serverTopDomain Delegate:(id<PSLogUploadDelegate>)delegate;

/**
 init

 @param serverTopDomain 日志上传的一级域名
 @param delegate PSLogUploadDelegate
 @param path 日志的路径（绝对路径,absolute path）
 @return self
 */
- (instancetype)initWithServerTopDomain:(NSString *)serverTopDomain Delegate:(id<PSLogUploadDelegate>)delegate logPath:(NSString*)path;

/**
 上传接口

 @param ID          ID为“080P31001”
 @param device      device为设备型号，如iphone5s
 @param zipname     zipname为上传的压缩包自定义命名字符串
 @param logpath     logpath传入NULL即可
 @param ndselect    ndselect为日志服务器
 @param port        port为服务器端口
 */
- (void)uploadLogsWithId:(const char*)ID deviceName:(const char*)device zipName:(const char*)zipname path:(const char*)logpath ndselect:(int)ndselect port:(int)port;

/**
 清理日志接口

 @param ID          ID为“080P31001”
 @param logpath     logpath传入NULL即可
 */
- (void)cleanLogsWithId:(const char*)ID logpath:(const char*)logpath;

@end

#endif /* Uploadfile_h */
