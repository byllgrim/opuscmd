/* this is based on the specs in RFC 3533 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* TODO put in shared .h file */
struct __attribute__((__packed__)) ogg_header {
	char capture_pattern[4]; /* TODO assuming 8bit char? */
	uint8_t version;
	uint8_t header_type;
	uint64_t granule_position;
	uint32_t bitstream_serial_number;
	uint32_t page_sequence_number;
	uint32_t CRC_checksum;
	uint8_t page_segments;
};

void
die(char *msg)
{
	fprintf(stderr, msg);
	exit(EXIT_FAILURE);
	/* TODO don't use escape ropes */
}

void
read_segment_table(int fd, uint8_t n)
{
	size_t i;
	uint8_t size[0xFF];
	uint8_t buf[0xFF];

	read(fd, size, n);

	for (i = 0; i < n; i++)
		read(fd, buf, size[i]); /* TODO check return value */

	/* TODO inspect individual segments? */
}

void
print_ogg_header(struct ogg_header *oh)
{
	/* TODO assuming valid header? */
	/* TODO endianness */

	printf("magic:    %s\n", oh->capture_pattern);
	printf("version:  %d\n", oh->version);
	printf("type:     %d\n", oh->header_type); /* TODO text descr */
	printf("granule:  %d\n", oh->granule_position);
	printf("serial:   0x%08X\n", oh->bitstream_serial_number);
	printf("sequence: %d\n", oh->page_sequence_number);
	printf("CRC:      0x%08X\n", oh->CRC_checksum);
	printf("segments: %d\n", oh->page_segments);
}


int
main(void)
{
	struct ogg_header oh;

	while (read(STDIN_FILENO, &oh, sizeof(oh))) {
		if (strncmp(oh.capture_pattern, "OggS", 4))
			die("error: invalid ogg header\n");

		/* TODO verify checksum? */

		print_ogg_header(&oh);

		read_segment_table(STDIN_FILENO, oh.page_segments);
		/* TODO check return error codes? */
		/* TODO print segment content? */

		printf("\n"); /* TODO puts? */
	}

	return EXIT_SUCCESS;
}
