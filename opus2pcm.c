#include <ogg/ogg.h>
#include <opus/opus.h>
#include <stdio.h> /* TODO shouldn't be needed */
#include <unistd.h>

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

	ogg_sync_init(&oy); /* TODO {0} instead */

	running = 1;
	pageout = 0;
	while (running) {
		if (pageout != -1);
			running = read2buf(&oy, BUFSIZ);

		pageout = ogg_sync_pageout(&oy, &og);

		if (pageout) { /* TODO == 1? */
			for (i = 0; i < 4; i++)
				putchar(og.header[i]);
			printf(" %d\n", ogg_page_pageno(&og));
		}
	}

	return 0;
}
