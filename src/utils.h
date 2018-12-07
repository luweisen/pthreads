#ifndef HAVE_PTHREADS_UTILS_H
#define HAVE_PTHREADS_UTILS_H

zend_string *pthreads_addslashes(zend_string *str);
zend_string* zval_get_string_func(zval *op);
zend_string *zval_get_tmp_string(zval *op, zend_string **tmp);

#endif
