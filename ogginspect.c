#include <alloca.h> /* TODO don't use alloca */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* TODO put in shared .h file */
struct __attribute__((__packed__)) ogg_header {
	uint8_t capture_pattern[4]; /* TODO make char? */
	uint8_t version;
	uint8_t header_type;
	uint64_t granule_position;
	uint32_t bitstream_serial_number;
	uint32_t page_sequence_number;
	uint32_t CRC_checksum;
	uint8_t page_segments;
};

void
read_segment_table(int fd)
{
	uint8_t size;
	uint8_t *data;

	/* TODO don't assume just 1 segment */

	read(fd, &size, sizeof(size));
	data = alloca(size);
	read(fd, data, size);

	printf("segment size = %d\n", size + 1); /* + 1 for size byte */
}

int
main(void)
{
	struct ogg_header oh;

	while (read(STDIN_FILENO, &oh, sizeof(oh))) {
		printf("valid pattern = %d\n",
		       !strncmp(oh.capture_pattern, "OggS", 4));
		//printf("pattern = %s\n", oh.capture_pattern);
		printf("type = %d\n", oh.header_type);
		printf("segments = %d\n", oh.page_segments);

		read_segment_table(STDIN_FILENO); // TODO return error codes
	}

	return 0;
}
