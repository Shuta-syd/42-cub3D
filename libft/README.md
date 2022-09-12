# libft

## 関数一覧

### MANDATORY PART

- `void *ft_memset(void *b, int c, size_t len)`  
  メモリ領域 b を len バイト数 c で埋める関数<br><br>
- `void ft_bzero(void *b, size_t len)`  
  メモリ領域 b を len バイト数 0 で初期化する関数<br><br>
- `void *ft_calloc(size_t count, size_t size)`  
  count(要素数) x size(バイト数)のメモリを確保し、同時に 0 で初期化する関数<br><br>
- `void *ft_memcpy(void *dst, const void *src, size_t n)`  
  メモリ領域 src の先頭 n バイトをメモリ領域 dest にコピーする関数<br><br>
- `void *ft_memccpy(void *dst, const void *src, int c, size_t n)`  
  メモリ領域 src からメモリ領域 dest に最大で n バイトのコピーする関数  
  n バイトコピーする前に文字 c が見つかると、そこでコピーを中止する<br><br>
- `void *ft_memmove(void *dst, const void *src, size_t n)`  
  メモリ領域 src の先頭 n バイトをメモリ領域 dest にコピーする関数  
  メモリ領域が重なった場合（src が前、dst が後場合）一時的な配列から dst にバイトのコピーが行われたかのように、コピーが行われる<br><br>
- `void *ft_memchr(const void *s, int c, size_t n)`  
  メモリ領域 s から n バイト数において文字 c を探索する関数<br><br>
- `int ft_memcmp(const void *s1, const void *s2, size_t n)`  
  メモリ領域 s1 と s2 の n バイトを比較する関数<br><br>
- `size_t ft_strlen(const char *s)`  
  文字列 s の要素するを求める関数<br><br>
- `char *ft_strcpy(char *dst, const char *src)`  
  文字列 src を文字列 dst にコピーする関数<br><br>
- `char *ft_strncpy(char *dst, const char *src, size_t len)`  
  文字列 src を文字列 dst に len バイト数コピーする関数<br><br>
- `size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)`  
  文字列 src から文字列 dst まで dstsize -1 文字までコピーする関数 src の長さを返す<br><br>
- `char *ft_strdup(const char *s1)`  
  文字列 s の複製である新しい文字列へのポインタを返す関数<br><br>
- `char *ft_strcat(char *dst, const char *src)`  
  文字列 dst の末尾に文字列 src を連結する関数<br><br>
- `char *ft_strncat(char *dst, const char *src, size_t n)`  
  文字列 dst の末尾に文字列 src を n バイト数だけ連結する関数<br><br>
- `size_t ft_strlcat(char *dst, const char *src, size_t dstsize)`  
  dstsize - strlen(dst) - 1 のバイト数分のみ文字列 dst の末尾に文字列 src を連結する関数  
  dst の初期値 + src の長さを返す<br><br>
- `char *ft_strchr(const char *s, int c)`  
  文字列 s 中に最初に文字 c が現れた位置へのポインターを求める関数<br><br>
- `char *ft_strchr_rev(const char *s, int c)`  
  文字列 s 中に最初に文字 c でない文字が現れた位置へのポインターを求める関数<br><br>
- `char *ft_strrchr(const char *s, int c)`  
  文字列 s 中に最後に文字 c が現れた位置へのポインターを求める関数<br><br>
- `char *ft_strstr(const char *haystack, const char *needle)`  
  文字列 needle が文字列 haystack 中で最初に現れる位置を求める関数<br><br>
- `char *ft_strnstr(const char *haystack, const char *needle, size_t n)`  
  文字列 needle が文字列 haystack の n バイト数の中で最初に現れる位置を求める関数<br><br>
- `int ft_strcmp(const char *s1, const char *s2)`  
  二つの文字列 s1 と s2 を比較する関数<br><br>
- `int ft_strncmp(const char *s1, const char *s2, size_t n)`  
  二つの文字列 s1 と s2 の n バイト数だけ比較する関数<br><br>
- `int ft_atoi(const char *str)`  
  char 型の数値 str を int 型の数値に変換する関数<br><br>
- `char *ft_itoa(int n)`  
  int 型の数値 n を char 型の数値に変換する関数<br><br>
- `int ft_isalpha(int c)`  
  文字 c が英字であるか調べる関数<br><br>
- `int ft_isdigit(int c)`  
  文字 c が数字（0 ~ 9）であるか調べる関数<br><br>
- `int ft_isalnum(int c)`  
  文字 c が英字または数字であるか調べる関数<br><br>
- `int ft_isascii(int c)`  
  文字 c が ASCII コードに合致するか調べる関数<br><br>
- `int ft_isprint(int c)`  
  文字 c が表示文字であるか調べる関数<br><br>
- `int ft_toupper(int c)`  
  文字 c が小文字の場合、大文字に変換する関数<br><br>
- `int ft_tolower(int c)`  
  文字 c が大文字の場合、小文字に変換する関数<br><br>
- `char *ft_strnew(size_t size)`  
  0 で初期化され、size バイトを確保した文字列へのポインタを返す関数<br><br>
- `void ft_striteri(char *s, void (*f)(unsigned int, char *))`  
  文字列 s を関数ポインタ f に適用し、修正する関数<br><br>
- `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))`  
  文字列 s を関数ポインタ f に適用し、その戻り値を収容した文字列を返す関数<br><br>
- `char *ft_substr(char const *s, unsigned int start, size_t len)`  
  文字列 s の index 番号 start から len バイト数だけ抽出した文字列を返す関数<br><br>
- `char *ft_strjoin(char const *s1, char const *s2)`  
  2 つの文字列 s1 と s2 を連結した新しい文字列を返す関数<br><br>
- `char *ft_strtrim(char const *s1, char const *set)`  
  文字列 s1 の前後に文字列 set がある場合それらを削除した文字列を返す関数<br><br>
- `char **ft_split(char const *s, char c)`  
  文字列 s を区切り文字 c で区切った二次元配列を返す関数<br><br>
- `void ft_putchar(char c)`  
  文字 c を標準出力する関数<br><br>
- `void ft_putchar_fd(char c, int fd)`  
  文字 c をファイルディスクリプタ fd に出力する関数<br><br>
- `void ft_putstr(char const *s)`  
  文字列 s を標準出力する関数<br><br>
- `void ft_putstr_fd(char const *s, int fd)`  
  文字列 s をファイルディスクリプタ fd に出力する関数<br><br>
- `void ft_putendl(char const *s);`  
  文字列 s（改行を含む）を標準出力する関数<br><br>
- `void ft_putendl_fd(char const *s, int fd)`  
  文字列 s（改行を含む）をファイルディスクリプタ fd に出力する関数<br><br>
- `void ft_putnbr(int n)`  
  int 型の数値 n を標準出力する関数<br><br>
- `void ft_putnbr_fd(int n, int fd)`  
  int 型の数値 n をファイルディスクリプタ fd に出力する関数<br><br>

### BONUS PART

- `t_list *ft_lstnew(void const *content)`  
  メンバを初期化した t_list を返す関数<br><br>
- `void ft_lstadd_front(t_list **lst, t_list *new)`  
  メンバを初期化した t_list を返す関数<br><br>
- `void ft_lstadd_front(t_list **lst, t_list *new)`  
  lst の先頭に new を追加する関数<br><br>
- `int ft_lstsize(t_list *lst)`  
  lst に含まれるサイズを求める関数<br><br>
- `t_list *ft_lstlast(t_list *lst)`  
  lst 最後の list を返す関数<br><br>
- `void ft_lstadd_back(t_list **lst, t_list *new)`  
  lst の最後の list に new を追加する関数<br><br>
- `void ft_lstdelone(t_list *lst, void (*del)(void *))`  
  del()および free(3)を用いて lst のメモリを解放する関数  
  lst のメンバ next は解放してはならない<br><br>
- `void ft_lstclear(t_list **lst, void (*del)(void *))`  
  del()および free(3)を用いて lst の全メモリを解放する関数  
  すべての lst は NULL で初期化される<br><br>
- `void ft_lstiter(t_list *lst, void (*f)(void *))`  
  lst のメンバ各 content に f()を適用する関数<br><br>
- `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))`  
  f()を適用した新しい list を返す関数<br><br>
