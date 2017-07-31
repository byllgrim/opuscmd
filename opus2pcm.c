#include <stdio.h>
#include <ogg/ogg.h>

int
main(void)
{
	printf("opus2pcm\n");
	/* TODO decode and print raw pcm */

	ogg_sync_pageout(0, 0);
	ogg_stream_pagein(0, 0);
	ogg_stream_packetout(0, 0);

	return 0;
}
