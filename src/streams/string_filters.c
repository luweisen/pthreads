#ifndef HAVE_PTHREADS_STREAMS_STRING_FILTERS
#define HAVE_PTHREADS_STREAMS_STRING_FILTERS

/* {{{ rot13 stream filter implementation */
static const char rot13_from[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char rot13_to[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";

static pthreads_stream_filter_status_t pthreads_strfilter_rot13_filter(
	pthreads_stream_t *threaded_stream,
	pthreads_stream_filter_t *threaded_thisfilter,
	pthreads_stream_bucket_brigade_t *threaded_buckets_in,
	pthreads_stream_bucket_brigade_t *threaded_buckets_out,
	size_t *bytes_consumed,
	int flags
	)
{
	php_stream_bucket *bucket;
	size_t consumed = 0;

	while (buckets_in->head) {
		bucket = php_stream_bucket_make_writeable(buckets_in->head);

		php_strtr(bucket->buf, bucket->buflen, rot13_from, rot13_to, 52);
		consumed += bucket->buflen;

		php_stream_bucket_append(buckets_out, bucket);
	}

	if (bytes_consumed) {
		*bytes_consumed = consumed;
	}

	return PTHREADS_SFS_PASS_ON;
}

#endif
