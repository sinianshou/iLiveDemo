#ifndef _EASY_FILE_LOGGER_
#define _EASY_FILE_LOGGER_

#define FLOG_DEBUG		5
#define FLOG_WARNING	4
#define FLOG_NORMAL		3
#define FLOG_SEVERE		2
#define FLOG_ERR			1
#define FLOG_OFF			0

MEDIACORE_API int32_t	log_data_to_file(char*logfile, void*buf, uint32_t size, bool append=false);
MEDIACORE_API void	PSL_log_to_file(int32_t level, const char *str, ...);
MEDIACORE_API void	PSL_set_log_level(int32_t level, int32_t flushcount);
MEDIACORE_API void	PSL_set_log_filename(const char *filename);
MEDIACORE_API void	PSL_set_log_pathname(const char *pathname);

MEDIACORE_API void	PSL_set_log_size(int32_t count, int32_t size);

#define log_to_file PSL_log_to_file

extern bool	PSL_path_set;

#endif
