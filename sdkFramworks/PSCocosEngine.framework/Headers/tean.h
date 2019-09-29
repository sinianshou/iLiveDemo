//���ļ�������һЩ������ܡ�����������ַ���������

/**********************************************************
   TEA - Tiny Encryption Algorithm
   Feistel cipher by David Wheeler & Roger M. Needham
   (extended version)
 **********************************************************/

#define ROUNDS 2
#define ENCODE 0
#define DECODE 1

//��׺���ַ�������󳤶�
#define  MAX_LENGTH_OF_EXT    10

void sean(char *v, int32_t N, int32_t flag);

void cl_enc_block(char *v); 

void cl_dec_block(char *v); 

//��װ���ܺͽ��ܳ���
//iΪENCODE�����ܣ�ΪDECODE������
void cipher(char *v, int i);

/*
  ��ڣ�char *sPtr
  ���ڣ�char *sPtr
  ���ܣ�ɾ���ַ���ͷ��β�Ŀո�
*/
void TrimSpace(char *sPtr);

//������볤�Ȳ���8λ�����油�Ͽո�
void addSpace(char * str);

void error_back(char *sError);

void ok_back(char *sOK,char *q);
/*���: char * source
  ����: char *destination
  ����:����ַ������ȴ���n�����䳤�Ƚض�Ϊn������������ַ�Ϊ...
  ʵ��:�Ƚ�source strcpy ��destination,�ж�destination�����Ƿ����n��
  �������n������������ַ���Ϊ...
  ellipsis�����������Ŀ¼�����ļ���������n���ַ�����
*/
char *ellipsis(char *source, char *destination, int n);

/*���: char * filename
  ����: char * trimmed
  ����:�ص��ļ��ĺ�׺��
  ʵ��:��filename������trimmed���ҵ�trimmed�����һ��'.'
       ������Ϊ'\0'
  ��: filename:  aaa.txt, trimmed: aaa
*/
char * TrimExt(char *filename, char * trimmed);

/*���:char *path
  ����:char *temp
  ����:�õ�һ��·���ַ����е����һ����Ŀ¼
  ʵ��:�ҵ����һ��'/'��'\'�����ַ��ĺ��漴Ϊ���һ����Ŀ¼
  ����path: d:\other\art\art1   �����ַ���: art1
 */

char * GetLastSubDir(char * path, char * temp);

/*
  ��ڣ� char *path
  ����:  char *path
  ���ܣ�Ϊ���㴦��·���ַ����� �����д������ļ��ж�ȡ������
        ʵ��·�����е��ַ�'\'ת��Ϊ�ַ�'/'
        ��: path="c:\video\aaa" ��ת��Ϊ: "c:/video/aaa"
*/

void convert(char *path);

/*
   ��ڣ�char *str
   ����: char *str
   ����: ����ַ���ĩβ�Ƿ���\��/���������:  c:\video\ ��c:\video/   
         ���Ϊ  c:\video
*/

char *CheckStr(char *str);
/*
   ��ڣ�char **strs �ַ�������
         int n  �������ַ����ĸ���
   ���ܣ��ͷ��ַ�������strs��������ڴ�
*/

void FreeStrings(char **strs, int n);
/*
  ��ڣ�char *filename �洢�ļ��������õ������ļ���һ��Ϊextension.ini
        char **exts  �ַ�������ָ��
  ���ڣ� char **exts ��������ڴ棬���洢�����ɸ��ļ���׺�����ַ�������
         int *n      ���ļ���ȡ���ַ����ĸ���

  ���ܣ����ļ�filename�ж�ȡ��׺���ַ�����exts������
  ʵ�֣�������ļ�filename����ú�׺���ַ����ĸ�����Ȼ��
        Ϊchar **exts������Ӧ���ڴ棬������ļ�filename����ȡ
		���洢���еĺ�׺���ַ���
*/
char** ReadExt(char *filename, char **exts, int *n);


/*���: char **exts  �洢��׺���ַ���������
        char *ExtsNume  exts�������ַ����ĸ���
		char *filename  ����׺���ļ���
  ����: int Ϊ1����ʾ filename�ĺ�׺��������exts�����У�
            Ϊ0�� ������
  ���ܣ��ж�һ���ļ����ļ������Ƿ�Ϊexts�����е�����  
*/
int IsInExt(char **exts, int ExtsNum, char *filename);

/*
  ��ڣ�char *msg  ���������Ϣ
  ���ܣ����̶��ĸ�ʽ�������������Ϣ
        ͬʱ���ṩһ�����ذ�ť���İ�ť����Ϊ�ɴ˺���
		����ҳ���subform()��������
*/
void PrintMsg(char *msg);

/*
   ��ڣ�const void *p1 �ַ���ָ��
         const void *p2 �ַ���ָ��
   ���ڣ�int �ȽϽ��
   ���ܣ��ַ����ȽϺ���������������qsort
          scmp: string compare of *p1 and *p2
*/
int scmp(const void *p1, const void *p2);
