/*
  +----------------------------------------------------------------------+
  | pthreads                                                             |
  +----------------------------------------------------------------------+
  | Copyright (c) Joe Watkins 2012 - 2015                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Bastian Schneider <b.schneider@badnoob.com>                  |
  +----------------------------------------------------------------------+
 */
#ifndef HAVE_PTHREADS_HASH_H
#define HAVE_PTHREADS_HASH_H
/*
#ifndef HAVE_PTHREADS_THREAD_H
#	include <src/thread.h>
#endif

#ifndef HAVE_PTHREADS_OBJECT_H
#	include <src/object.h>
#endif
*/

//#	include <src/pthreads.h>

typedef struct _pthreads_hashtable pthreads_hashtable;
typedef struct _pthreads_object_t pthreads_object_t;

struct _pthreads_hashtable {
	pthreads_monitor_t *monitor;
	HashTable ht;
};

#define PTHREADS_SEPARATE_ARRAY(zv) do {				\
		zval *_zv = (zv);								\
		zend_array *_arr = Z_ARR_P(_zv);				\
		if (UNEXPECTED(GC_REFCOUNT(_arr) > 1)) {		\
			if (Z_REFCOUNTED_P(_zv)) {					\
				GC_DELREF(_arr);						\
			}											\
			ZVAL_ARR(_zv, pthreads_array_dup(_arr));	\
		}												\
	} while (0)

#define pthreads_array_init(arg)				ZVAL_ARR((arg), pthreads_new_array(0))
#define pthreads_array_init_size(arg, size)		ZVAL_ARR((arg), pthreads_new_array(size))

void pthreads_hashtable_init(pthreads_hashtable *pht, uint32_t size, dtor_func_t pDestructor);
void pthreads_free_hashtable(pthreads_hashtable *pht);

HashTable* pthreads_new_array(uint32_t size);
HashTable* pthreads_array_dup(HashTable *source);

pthreads_object_t *_pthreads_array_to_volatile_map(zval *array);
zval *_pthreads_volatile_map_to_array(pthreads_object_t *map, zval *array);

#endif
