#ifndef HIJK_IJKPLAYER_FLV_TO_MP4_H
#define HIJK_IJKPLAYER_FLV_TO_MP4_H

#ifdef __cplusplus
extern "C" {
#endif

#if __APPLE__
__attribute__((visibility ("default")))
#endif
int flv_to_mp4_cut_tail(const char *in_filename,const char *out_filename,double cut_tail_sec);

#ifdef __cplusplus
}
#endif

#endif //HIJK_IJKPLAYER_FLV_TO_MP4_H
