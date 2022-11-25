#include <common/sys/types.h>

/** CRC table for the CRC-7. The poly is 0X09  */
// crc7 generator polynomial : G(x)=x7+x3+1
const uint8_t crc7_table[256] = {
	0X00, 0X09, 0X12, 0X1B, 0X24, 0X2D, 0X36, 0X3F, 0X48, 0X41, 0X5A, 0X53, 0X6C, 0X65, 0X7E, 0X77,
	0X19, 0X10, 0X0B, 0X02, 0X3D, 0X34, 0X2F, 0X26, 0X51, 0X58, 0X43, 0X4A, 0X75, 0X7C, 0X67, 0X6E,
	0X32, 0X3B, 0X20, 0X29, 0X16, 0X1F, 0X04, 0X0D, 0X7A, 0X73, 0X68, 0X61, 0X5E, 0X57, 0X4C, 0X45,
	0X2B, 0X22, 0X39, 0X30, 0X0F, 0X06, 0X1D, 0X14, 0X63, 0X6A, 0X71, 0X78, 0X47, 0X4E, 0X55, 0X5C,
	0X64, 0X6D, 0X76, 0X7F, 0X40, 0X49, 0X52, 0X5B, 0X2C, 0X25, 0X3E, 0X37, 0X08, 0X01, 0X1A, 0X13,
	0X7D, 0X74, 0X6F, 0X66, 0X59, 0X50, 0X4B, 0X42, 0X35, 0X3C, 0X27, 0X2E, 0X11, 0X18, 0X03, 0X0A,
	0X56, 0X5F, 0X44, 0X4D, 0X72, 0X7B, 0X60, 0X69, 0X1E, 0X17, 0X0C, 0X05, 0X3A, 0X33, 0X28, 0X21,
	0X4F, 0X46, 0X5D, 0X54, 0X6B, 0X62, 0X79, 0X70, 0X07, 0X0E, 0X15, 0X1C, 0X23, 0X2A, 0X31, 0X38,
	0X41, 0X48, 0X53, 0X5A, 0X65, 0X6C, 0X77, 0X7E, 0X09, 0X00, 0X1B, 0X12, 0X2D, 0X24, 0X3F, 0X36,
	0X58, 0X51, 0X4A, 0X43, 0X7C, 0X75, 0X6E, 0X67, 0X10, 0X19, 0X02, 0X0B, 0X34, 0X3D, 0X26, 0X2F,
	0X73, 0X7A, 0X61, 0X68, 0X57, 0X5E, 0X45, 0X4C, 0X3B, 0X32, 0X29, 0X20, 0X1F, 0X16, 0X0D, 0X04,
	0X6A, 0X63, 0X78, 0X71, 0X4E, 0X47, 0X5C, 0X55, 0X22, 0X2B, 0X30, 0X39, 0X06, 0X0F, 0X14, 0X1D,
	0X25, 0X2C, 0X37, 0X3E, 0X01, 0X08, 0X13, 0X1A, 0X6D, 0X64, 0X7F, 0X76, 0X49, 0X40, 0X5B, 0X52,
	0X3C, 0X35, 0X2E, 0X27, 0X18, 0X11, 0X0A, 0X03, 0X74, 0X7D, 0X66, 0X6F, 0X50, 0X59, 0X42, 0X4B,
	0X17, 0X1E, 0X05, 0X0C, 0X33, 0X3A, 0X21, 0X28, 0X5F, 0X56, 0X4D, 0X44, 0X7B, 0X72, 0X69, 0X60,
	0X0E, 0X07, 0X1C, 0X15, 0X2A, 0X23, 0X38, 0X31, 0X46, 0X4F, 0X54, 0X5D, 0X62, 0X6B, 0X70, 0X79};

/**
 * @brief 计算crc7
 *
 * @param crc crc初始值
 * @param buffer 输入缓冲区
 * @param len buffer大小（bytes）
 * @return uint8_t crc
 */
uint8_t crc7(uint8_t crc, const uint8_t *buffer, size_t len)
{
	while (len--)
	{
		crc = crc7_table[(crc << 1) ^ *buffer++];
	}
	return (crc);
}
