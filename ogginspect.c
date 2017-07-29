#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

/* TODO put in shared .h file */
struct __attribute__((__packed__)) ogg_header {
	uint8_t capture_pattern[4];
	uint8_t version;
	uint8_t header_type;
	uint64_t granule_position;
	uint32_t bitstream_serial_number;
	uint32_t page_sequence_number;
	uint32_t CRC_checksum;
	uint8_t page_segments;
};

int
main(void)
{
	struct ogg_header oh;

	read(STDIN_FILENO, &oh, sizeof(oh));
	printf("pattern = %s\n", oh.capture_pattern);
	printf("type = %d\n", oh.header_type);
	printf("segments = %d\n", oh.page_segments);

	return 0;
}
