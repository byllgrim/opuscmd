/* this is based on the specs in RFC 3533 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
die(char *msg)
{
	fprintf(stderr, msg);
	exit(EXIT_FAILURE);
}

void
read_segment_table(int fd, uint8_t n)
{
	size_t i;
	uint8_t size;
	uint8_t data[0xFF]; /* TODO better denotion of uint8_t maxval */

	for (i = 0; i < n; i++) {
		fprintf(stderr, "segment %d\n", i);
		read(fd, &size, sizeof(size));
		fprintf(stderr, "\tsize = %d = 0x%02X\n", size, size);

		/* TODO assert size <= sizeof(data) */
		if (read(fd, data, size) != size)
			die("error: segment size mismatch");

		fprintf(stderr,
		        "\tbytes = 0x%02X 0x%02X 0x%02X ...\n",
		        data[0], data[1], data[2]);
	}

}

int
main(void)
{
	struct ogg_header oh;

	while (read(STDIN_FILENO, &oh, sizeof(oh))) {
		if (strncmp(oh.capture_pattern, "OggS", 4))
			die("error: invalid ogg header\n");

		fprintf(stderr, "pattern = %s\n", oh.capture_pattern);
		fprintf(stderr, "type = %d\n", oh.header_type);
		fprintf(stderr, "segments = %d\n", oh.page_segments);

		read_segment_table(STDIN_FILENO, oh.page_segments);
		// TODO return error codes

		fprintf(stderr, "\n");
	}

	return EXIT_SUCCESS;
}
