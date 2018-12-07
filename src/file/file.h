#ifndef HAVE_PTHREADS_FILE_H
#define HAVE_PTHREADS_FILE_H

#define PTHREADS_META_DEF_BUFSIZE 8192

#define PTHREADS_FILE_USE_INCLUDE_PATH 1
#define PTHREADS_FILE_IGNORE_NEW_LINES 2
#define PTHREADS_FILE_SKIP_EMPTY_LINES 4
#define PTHREADS_FILE_APPEND 8
#define PTHREADS_FILE_NO_DEFAULT_CONTEXT 16

/* See http://www.w3.org/TR/html4/intro/sgmltut.html#h-3.2.2 */
#define PTHREADS_META_HTML401_CHARS "-_.:"

typedef struct _pthreads_meta_tags_data {
	pthreads_stream_t *stream;
	int ulc;
	int lc;
	char *input_buffer;
	char *token_data;
	int token_len;
	int in_meta;
} pthreads_meta_tags_data;

php_meta_tags_token pthreads_next_meta_token(pthreads_meta_tags_data *);


int pthreads_copy_file_ctx(const char *src, const char *dest, int src_flg, pthreads_stream_context_t *threaded_ctx);
size_t pthreads_fputcsv(pthreads_stream_t *threaded_stream, zval *fields, char delimiter, char enclosure, char escape_char);
void pthreads_fgetcsv(pthreads_stream_t *threaded_stream, char delimiter, char enclosure, char escape_char, size_t buf_len, char *buf, zval *return_value);

#endif
