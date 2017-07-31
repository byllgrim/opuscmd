#include <ogg/ogg.h>
#include <stdio.h> /* TODO shouldn't be needed */
#include <unistd.h>

int
main(void)
{
	ogg_sync_state oy;
	char *buf;
	size_t n;
	ogg_page og;
	size_t i;
	int pageout;
	char running;

	ogg_sync_init(&oy); /* TODO {0} instead */

	running = 1;
	pageout = 0;
	while (running) {
		/* TODO refactor? */

		if (pageout != -1); {
			buf = ogg_sync_buffer(&oy, BUFSIZ);
			/* TODO check errors */
			n = read(STDIN_FILENO, buf, BUFSIZ);
			ogg_sync_wrote(&oy, n);

			running = (n == BUFSIZ);
		}

		pageout = ogg_sync_pageout(&oy, &og);

		if (pageout) {
			for (i = 0; i < 4; i++)
				putchar(og.header[i]);
			printf(" %d\n", ogg_page_pageno(&og));
		}
	}

	return 0;
}
