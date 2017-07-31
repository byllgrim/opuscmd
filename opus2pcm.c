#include <ogg/ogg.h>
#include <opus/opus.h>
#include <stdio.h> /* TODO shouldn't be needed */
#include <unistd.h>

enum {
	SAMPLE_RATE = 48000, /* TODO 16000 */
	CHANNELS = 2,
};

static int
read2buf(ogg_sync_state *oy, size_t size)
{
	char *buf;
	size_t n;

	buf = ogg_sync_buffer(oy, size); /* TODO check errors */
	n = read(STDIN_FILENO, buf, size);
	ogg_sync_wrote(oy, n);

	return n == size;
}

int
main(void)
{
	ogg_sync_state oy;
	ogg_page og;
	size_t i;
	int pageout;
	char running;
	OpusDecoder *st;
	int err;

	ogg_sync_init(&oy); /* TODO {0} instead */
	opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
	/* TODO check returns */

	running = 1;
	pageout = 0;
	while (running) {
		if (pageout != -1);
			running = read2buf(&oy, BUFSIZ);

		pageout = ogg_sync_pageout(&oy, &og);

		if (pageout) { /* TODO && granule TODO == 1? */
			/* TODO refactor */

			/*
			opus_decode(st,
			            og.body,
			            og.body_len,
			*/
		}
	}

	/* TODO opus_decoder_destroy etc */
	return 0;
}
