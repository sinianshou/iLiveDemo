//
//  cropSamplebuf.h
//  PIProcess
//
//  Created by HUO on 2018/9/4.
//  Copyright © 2018 powersmart. All rights reserved.
//

#ifndef cropSamplebuf_h
#define cropSamplebuf_h

#define IPHONEXHAIRLENGTH   64

#import "PIProcessDefines.h"


@interface samplebufCropper: NSObject

+ (CMSampleBufferRef) centralCropSampleBuffer: (CMSampleBufferRef)inputbuffer cropWidth: (int)cropWidth cropHeight: (int)cropHeight withHearLength: (int)hairLength;

@end


#endif /* cropSamplebuf_h */
