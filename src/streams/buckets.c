/*
  +----------------------------------------------------------------------+
  | pthreads                                                             |
  +----------------------------------------------------------------------+
  | Copyright (c) Joe Watkins 2018                                       |
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
#ifndef HAVE_PTHREADS_STREAMS_BUCKETS
#define HAVE_PTHREADS_STREAMS_BUCKETS

#ifndef HAVE_PTHREADS_H
#	include <src/pthreads.h>
#endif

#ifndef HAVE_PTHREADS_STREAM_H
#	include <src/streams.h>
#endif

#ifndef HAVE_PTHREADS_STREAMS_BUCKETS_H
#	include <src/streams/buckets.h>
#endif


pthreads_stream_bucket_brigade *pthreads_stream_bucket_brigade_alloc() {
	pthreads_stream_bucket_brigade *brigade;

	brigade = (pthreads_stream_bucket_brigade*)malloc(sizeof(pthreads_stream_bucket_brigade));
	brigade->head = brigade->tail = NULL;

	return brigade;
}

void pthreads_stream_bucket_brigade_free(pthreads_stream_bucket_brigade *brigade) {
	free(brigade);
}

pthreads_stream_bucket *pthreads_stream_bucket_alloc(char *buf, size_t buflen) {
	pthreads_stream_bucket *bucket;

	bucket = (pthreads_stream_bucket*)malloc(sizeof(pthreads_stream_bucket));
	bucket->next = bucket->prev = NULL;

	/* all data in a persistent bucket must also be persistent */
	bucket->buf = malloc(buflen);
	memcpy(bucket->buf, buf, buflen);
	bucket->buflen = buflen;
	bucket->brigade = NULL;

	return bucket;
}

void pthreads_stream_bucket_free(pthreads_stream_bucket *bucket) {
	if (bucket->buf) {
		free(bucket->buf);
	}
	free(bucket);
}

void pthreads_stream_bucket_prepend(pthreads_stream_bucket_brigade_t *threaded_brigade, pthreads_stream_bucket_t *threaded_bucket) {
	pthreads_stream_bucket_brigade *brigade = PTHREADS_FETCH_STREAMS_BRIGADE(threaded_brigade);
	pthreads_stream_bucket *bucket = PTHREADS_FETCH_STREAMS_BUCKET(threaded_bucket);
	pthreads_stream_bucket *head;
	pthreads_stream_bucket_t *threaded_head;

	if(pthreads_streams_aquire_double_lock(threaded_bucket, threaded_brigade)) {
		if(bucket->brigade != NULL && threaded_brigade != bucket->brigade) {

			// Error

			pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
			return;
		}
		threaded_head = brigade->head;

		if(!threaded_head) {
			pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
			return;
		}
		head = PTHREADS_FETCH_STREAMS_BUCKET(threaded_head);

		if(head == bucket) {
			pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
			return;
		}
		bucket->next = threaded_head;
		bucket->prev = NULL;

		if (head) {
			head->prev = threaded_bucket;
		} else {
			brigade->tail = threaded_bucket;
		}
		zval obj;
		ZVAL_OBJ(&obj, PTHREADS_STD_P(threaded_bucket));
		Z_ADDREF(obj);

		brigade->head = threaded_bucket;
		bucket->brigade = threaded_brigade;

		pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
	}
}

void pthreads_stream_bucket_append(pthreads_stream_bucket_brigade_t *threaded_brigade, pthreads_stream_bucket_t *threaded_bucket) {
	pthreads_stream_bucket_brigade *brigade = PTHREADS_FETCH_STREAMS_BRIGADE(threaded_brigade);
	pthreads_stream_bucket *bucket = PTHREADS_FETCH_STREAMS_BUCKET(threaded_bucket);
	pthreads_stream_bucket *tail;
	pthreads_stream_bucket_t *threaded_tail;

	if(pthreads_streams_aquire_double_lock(threaded_bucket, threaded_brigade)) {
		if(bucket->brigade != NULL && threaded_brigade != bucket->brigade) {

			// Error

			pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
			return;
		}
		threaded_tail = brigade->tail;

		if (!threaded_tail) {
			pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
			return;
		}
		tail = PTHREADS_FETCH_STREAMS_BUCKET(threaded_tail);

		if (tail == bucket) {
			pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
			return;
		}
		bucket->prev = threaded_tail;
		bucket->next = NULL;

		if (tail) {
			tail->next = threaded_bucket;
		} else {
			brigade->head = threaded_bucket;
		}
		zval obj;
		ZVAL_OBJ(&obj, PTHREADS_STD_P(threaded_bucket));
		Z_ADDREF(obj);

		brigade->tail = threaded_bucket;
		bucket->brigade = threaded_brigade;

		pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
	}
}

void pthreads_stream_bucket_unlink(pthreads_stream_bucket_t *threaded_bucket) {
	pthreads_stream_bucket *bucket = PTHREADS_FETCH_STREAMS_BUCKET(threaded_bucket);
	pthreads_stream_bucket_brigade_t *threaded_brigade = bucket->brigade;

	if(pthreads_streams_aquire_double_lock(threaded_bucket, threaded_brigade)) {
		if (bucket->prev) {
			PTHREADS_FETCH_STREAMS_BUCKET(bucket->prev)->next = bucket->next;
		} else if (bucket->brigade) {
			PTHREADS_FETCH_STREAMS_BRIGADE(bucket->brigade)->head = bucket->next;
		}
		if (bucket->next) {
			PTHREADS_FETCH_STREAMS_BUCKET(bucket->next)->prev = bucket->prev;
		} else if (bucket->brigade) {
			PTHREADS_FETCH_STREAMS_BRIGADE(bucket->brigade)->tail = bucket->prev;
		}
		bucket->brigade = NULL;
		bucket->next = bucket->prev = NULL;

		pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
	}
}

void pthreads_stream_bucket_destroy(pthreads_stream_bucket_t *threaded_bucket) {
	pthreads_stream_bucket *bucket = PTHREADS_FETCH_STREAMS_BUCKET(threaded_bucket);
	pthreads_stream_bucket_brigade_t *threaded_brigade = bucket->brigade;
	int destruct = 0;

	if(pthreads_streams_aquire_double_lock(threaded_bucket, threaded_brigade)) {
		if (bucket->prev) {
			PTHREADS_FETCH_STREAMS_BUCKET(bucket->prev)->next = bucket->next;
		} else if (bucket->brigade) {
			PTHREADS_FETCH_STREAMS_BRIGADE(bucket->brigade)->head = bucket->next;
		}
		if (bucket->next) {
			PTHREADS_FETCH_STREAMS_BUCKET(bucket->next)->prev = bucket->prev;
		} else if (bucket->brigade) {
			PTHREADS_FETCH_STREAMS_BRIGADE(bucket->brigade)->tail = bucket->prev;
		}
		zval obj;
		ZVAL_OBJ(&obj, PTHREADS_STD_P(threaded_bucket));

		if(Z_REFCOUNT(obj) <= 1) {
			destruct = 1;
		} else {
			Z_DELREF(obj);
		}
		bucket->brigade = NULL;
		bucket->next = bucket->prev = NULL;

		pthreads_streams_release_double_lock(threaded_bucket, threaded_brigade);
	}

	if(destruct)
		pthreads_ptr_dtor(threaded_bucket);
}

#endif
