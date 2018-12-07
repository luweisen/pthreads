#ifndef HAVE_PTHREADS_URL_H
#define HAVE_PTHREADS_URL_H

typedef struct _pthreads_url {
	zend_string *scheme;
	zend_string *user;
	zend_string *pass;
	zend_string *host;
	unsigned short port;
	zend_string *path;
	zend_string *query;
	zend_string *fragment;
} pthreads_url;

void pthreads_url_free(pthreads_url *theurl);
pthreads_url *pthreads_url_parse(char const *str);
pthreads_url *pthreads_url_parse_ex(char const *str, size_t length);
char *pthreads_replace_controlchars_ex(char *str, size_t len);

#endif
