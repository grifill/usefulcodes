/*    Moscow State Technical University n.a. N.E. Bauman
 *    RL1 Students Design Office
 *
 *    Filename:       crc16.c
 *    License:        GPL (see LICENSE file)
 *    Author(s):      Koroteev Dmitry and Internet
 *    Created:        10-2007
 *    Description:    CRC16 calculation tools
 *
 */

#include "crc16.h"

/*---------------------------------------------------------------------------*/
u16 crc16(
          u16      fcs,            /* initialization value */
          const    u16   xor_out,  /* finalization value */
          const char*    data,     /* data buffer */
          int            len,      /* size of buffer */
          const    u16*  table     /* pointer to CRC16 fast calculation table */
         )
{
    /* reverse algorithm */
    /*while (len--) fcs = (fcs >> 8) ^ fcstab[(fcs ^ *cp++) & 0xff];*/

    /* direct algorithm */
    while (len--) fcs = table[((fcs>>8)^*data++)&0xff] ^ (fcs<<8);
    fcs ^= xor_out;
    return (fcs);
}

/*---------------------------------------------------------------------------*/
void crc16_build_table(
                            const u16 polinom,  /* polinom */
                            u16 *table /* pointer to CRC16 fast calc table */
                       )
{
u16 d, i, k, fcs;
 for (i=0; i<256; i++)
  {
   fcs=0x00;
   d = i<<8;
   for (k=0; k<8; k++)
    {
     if ((fcs ^ d) & 0x8000)
       fcs = (fcs << 1) ^ polinom;
     else
       fcs = (fcs << 1);
     d <<= 1;
    }
   table[i] = fcs;
  }
}


/*---------------------------------------------------------------------------*/
u16 crc16_sr(
            u16 fcs,     /* initial register value */
            const u16 xor_out,  /* finalization xor value */
            const u16 polinom,  /* polinom */
            const char *data,   /* data buffer, */
            int  len     /* size of buffer */
         )
{
u16 d, i, k;
 for (i=0; i<len; i++)
  {
  d = *data++ << 8;
  for (k=0; k<8; k++)
   {
    if ((fcs ^ d) & 0x8000)
      fcs = (fcs << 1) ^ polinom;
    else
      fcs = (fcs << 1);
    d <<= 1;
   }
  }
  fcs^=xor_out;

 return fcs;
}

/*---------------------------------------------------------------------------*/
u16 crc16_8005_ffff(
          const char*   data,      /* data buffer */
          int            len       /* size of buffer */
                    )
{
    u16 fcs=0xffff;
    while (len--) fcs = crc16_8005_table[((fcs>>8)^*data++)&0xff] ^ (fcs<<8);
    return (fcs);
}
int crc16_805_ffff_cp9ba(	const char* src,
								  char*	dst,
								  int	len
							)
{
    u16 fcs=0xffff;
    u16 idx_src = 0;
    u16 idx_dst = 0;

    //	Encode frame
    while(idx_src < len)
    {
    	fcs = crc16_8005_table[((fcs>>8)^(src[idx_src]))&0xff] ^ (fcs<<8);
    	dst[idx_dst] = src[idx_src];
    	switch(dst[idx_dst])
    	{
    	case 0x7E:
    		dst[idx_dst] = 0x7D;
    		idx_dst++;
    		dst[idx_dst] = 0x5E;
    		break;
    	case 0x7D:
    		dst[idx_dst] = 0x7D;
    		idx_dst++;
    		dst[idx_dst] = 0x5D;
    		break;
    	default:
    		break;
    	}
		idx_dst++;
    	idx_src++;
    }

    //	Encode CRC LSB
    dst[idx_dst] = fcs & 0xFF;
	switch(dst[idx_dst])
	{
	case 0x7E:
		dst[idx_dst] = 0x7D;
		idx_dst++;
		dst[idx_dst] = 0x5E;
		break;
	case 0x7D:
		dst[idx_dst] = 0x7D;
		idx_dst++;
		dst[idx_dst] = 0x5D;
		break;
	default:
		break;
	}
    idx_dst++;

    //	Encode CRC MSB
    dst[idx_dst] = (fcs >> 8) & 0xFF;
	switch(dst[idx_dst])
	{
	case 0x7E:
		dst[idx_dst] = 0x7D;
		idx_dst++;
		dst[idx_dst] = 0x5E;
		break;
	case 0x7D:
		dst[idx_dst] = 0x7D;
		idx_dst++;
		dst[idx_dst] = 0x5D;
		break;
	default:
		break;
	}
    idx_dst++;

    return (idx_dst);
}
/*---------------------------------------------------------------------------*/
