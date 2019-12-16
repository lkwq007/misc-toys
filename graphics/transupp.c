#define JPEG_INTERNALS

#include "jinclude.h"
#include "jpeglib.h"
#include "transupp.h" /* My own external interface */
#include <ctype.h>    /* to declare isdigit() */

LOCAL(void)
do_nothing(j_decompress_ptr srcinfo, j_compress_ptr dstinfo,
                  jvirt_barray_ptr *src_coef_arrays)
/* Horizontal flip; done in-place, so no separate dest array is required.
 * NB: this only works when y_crop_offset is zero.
 */
{
  JDIMENSION MCU_cols, comp_width, blk_x, blk_y, x_crop_blocks;
  int ci, k, offset_y;
  JBLOCKARRAY buffer;
  JCOEFPTR ptr1, ptr2;
  JCOEF temp1, temp2;
  jpeg_component_info *compptr;
  JCOEF buf[64];
  int len;

  /* Horizontal mirroring of DCT blocks is accomplished by swapping
   * pairs of blocks in-place.  Within a DCT block, we perform horizontal
   * mirroring by changing the signs of odd-numbered columns.
   * Partial iMCUs at the right edge are left untouched.
   */
  // fscanf(stdin,"%s",&buf);
  MCU_cols = srcinfo->output_width /
             (dstinfo->max_h_samp_factor * dstinfo->min_DCT_h_scaled_size);
  for (ci = 0; ci < dstinfo->num_components; ci++)
  {
    compptr = dstinfo->comp_info + ci;
    comp_width = MCU_cols * compptr->h_samp_factor;
    // fprintf(stderr,"%s ci %d %dx%d offsety:%d\n",buf,ci,compptr->height_in_blocks, comp_width, compptr->v_samp_factor);

    for (blk_y = 0; blk_y < compptr->height_in_blocks;
         blk_y += compptr->v_samp_factor)
    {
      buffer = (*srcinfo->mem->access_virt_barray)((j_common_ptr)srcinfo, src_coef_arrays[ci], blk_y,
                                                   (JDIMENSION)compptr->v_samp_factor, TRUE);
      for (offset_y = 0; offset_y < compptr->v_samp_factor; offset_y++)
      {
        /* Do the mirroring */
        for (blk_x = 0; blk_x < comp_width; blk_x++)
        {
          ptr1 = buffer[offset_y][blk_x];
          /* this unrolled loop doesn't need to know which row it's on... */
          len=fread(buf,sizeof(JCOEF),64,stdin);
          for (k = 0; k < DCTSIZE2; k += 1)
          {

            // if(blk_y==0&&blk_x==0)
            // {
            //   if(k%8==0)
            //   {
            //     fprintf(stderr,"\n");
            //   }
            //   fprintf(stderr,"%3d ",*ptr1);
            // }
            if(offset_y==1&&ci==0)
            {
              *ptr1=0;
            }
            ptr1++;
          }
        }
      }
    }
  }
}
