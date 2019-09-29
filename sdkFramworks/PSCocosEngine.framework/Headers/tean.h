//本文件包括了一些密码加密、错误输出和字符串处理函数

/**********************************************************
   TEA - Tiny Encryption Algorithm
   Feistel cipher by David Wheeler & Roger M. Needham
   (extended version)
 **********************************************************/

#define ROUNDS 2
#define ENCODE 0
#define DECODE 1

//后缀名字符串的最大长度
#define  MAX_LENGTH_OF_EXT    10

void sean(char *v, int32_t N, int32_t flag);

void cl_enc_block(char *v); 

void cl_dec_block(char *v); 

//封装加密和解密程序，
//i为ENCODE，加密，为DECODE，解密
void cipher(char *v, int i);

/*
  入口：char *sPtr
  出口：char *sPtr
  功能：删除字符串头和尾的空格
*/
void TrimSpace(char *sPtr);

//如果密码长度不够8位，后面补上空格
void addSpace(char * str);

void error_back(char *sError);

void ok_back(char *sOK,char *q);
/*入口: char * source
  出口: char *destination
  功能:如果字符串长度大于n，将其长度截短为n，且最后三个字符为...
  实现:先将source strcpy 给destination,判断destination长度是否大于n，
  如果大于n，则将最后三个字符改为...
  ellipsis函数将输出的目录或者文件名控制在n个字符以内
*/
char *ellipsis(char *source, char *destination, int n);

/*入口: char * filename
  出口: char * trimmed
  功能:截掉文件的后缀名
  实现:将filename拷贝给trimmed，找到trimmed中最后一个'.'
       将其置为'\0'
  例: filename:  aaa.txt, trimmed: aaa
*/
char * TrimExt(char *filename, char * trimmed);

/*入口:char *path
  出口:char *temp
  功能:得到一个路径字符串中的最后一个子目录
  实现:找到最后一个'/'或'\'，此字符的后面即为最后一个子目录
  例：path: d:\other\art\art1   返回字符串: art1
 */

char * GetLastSubDir(char * path, char * temp);

/*
  入口： char *path
  出口:  char *path
  功能：为方便处理路径字符串， 将所有从配置文件中读取出来的
        实际路径名中的字符'\'转换为字符'/'
        例: path="c:\video\aaa" ，转换为: "c:/video/aaa"
*/

void convert(char *path);

/*
   入口：char *str
   出口: char *str
   功能: 检查字符串末尾是否有\或/，如果形如:  c:\video\ 或c:\video/   
         则改为  c:\video
*/

char *CheckStr(char *str);
/*
   入口：char **strs 字符串数组
         int n  数组中字符串的个数
   功能：释放字符串数组strs所分配的内存
*/

void FreeStrings(char **strs, int n);
/*
  入口：char *filename 存储文件类型设置的配置文件，一般为extension.ini
        char **exts  字符串数组指针
  出口： char **exts 分配好了内存，并存储了若干个文件后缀名的字符串数组
         int *n      从文件读取的字符串的个数

  功能：从文件filename中读取后缀名字符串到exts数组中
  实现：先浏览文件filename，获得后缀名字符串的个数，然后
        为char **exts分配相应的内存，再浏览文件filename，读取
		并存储所有的后缀名字符串
*/
char** ReadExt(char *filename, char **exts, int *n);


/*入口: char **exts  存储后缀名字符串的数组
        char *ExtsNume  exts数组中字符串的个数
		char *filename  带后缀的文件名
  出口: int 为1，表示 filename的后缀名存在于exts数组中，
            为0， 不存在
  功能：判断一个文件的文件类型是否为exts数组中的类型  
*/
int IsInExt(char **exts, int ExtsNum, char *filename);

/*
  入口：char *msg  待输出的信息
  功能：按固定的格式，输出给定的信息
        同时，提供一个返回按钮，改按钮的行为由此函数
		所在页面的subform()函数给定
*/
void PrintMsg(char *msg);

/*
   入口：const void *p1 字符串指针
         const void *p2 字符串指针
   出口：int 比较结果
   功能：字符串比较函数，用于排序函数qsort
          scmp: string compare of *p1 and *p2
*/
int scmp(const void *p1, const void *p2);
