
#ifndef psTimer_hpp
#define psTimer_hpp

typedef void (*psTaskCallback)(char* jsonstr, void* refCon);


extern "C" int psTimerInit();

#if (defined ANDROID_VERSION || defined NT_VERSION)
extern "C" int psAddPsTask(int64_t pzvt, char *jsonstr, JavaVM *g_VM, jmethodID onFired, jobject callback);
#else
extern "C" int psAddPsTask(int64_t pzvt, psTaskCallback taskCallback, char *jsonstr, void *param);
#endif

extern "C" int removePsTask(int taskid);

extern "C" void psTimerRelease();

#endif /* psTimer_hpp */
