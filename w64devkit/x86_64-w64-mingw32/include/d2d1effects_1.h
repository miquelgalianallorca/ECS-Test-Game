/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#ifndef _D2D1_EFFECTS_1_
#define _D2D1_EFFECTS_1_

#ifndef _D2D1_EFFECTS_
#include <d2d1effects.h>
#endif

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

DEFINE_GUID(CLSID_D2D1YCbCr, 0x99503cc1, 0x66c7, 0x45c9, 0xa8, 0x75, 0x8a, 0xd8, 0xa7, 0x91, 0x44, 0x01);

typedef enum D2D1_YCBCR_PROP {
  D2D1_YCBCR_PROP_CHROMA_SUBSAMPLING = 0,
  D2D1_YCBCR_PROP_TRANSFORM_MATRIX = 1,
  D2D1_YCBCR_PROP_INTERPOLATION_MODE = 2,
  D2D1_YCBCR_PROP_FORCE_DWORD = 0xffffffff
} D2D1_YCBCR_PROP;

typedef enum D2D1_YCBCR_CHROMA_SUBSAMPLING {
  D2D1_YCBCR_CHROMA_SUBSAMPLING_AUTO = 0,
  D2D1_YCBCR_CHROMA_SUBSAMPLING_420 = 1,
  D2D1_YCBCR_CHROMA_SUBSAMPLING_422 = 2,
  D2D1_YCBCR_CHROMA_SUBSAMPLING_444 = 3,
  D2D1_YCBCR_CHROMA_SUBSAMPLING_440 = 4,
  D2D1_YCBCR_CHROMA_SUBSAMPLING_FORCE_DWORD = 0xffffffff
} D2D1_YCBCR_CHROMA_SUBSAMPLING;

typedef enum D2D1_YCBCR_INTERPOLATION_MODE {
  D2D1_YCBCR_INTERPOLATION_MODE_NEAREST_NEIGHBOR = 0,
  D2D1_YCBCR_INTERPOLATION_MODE_LINEAR = 1,
  D2D1_YCBCR_INTERPOLATION_MODE_CUBIC = 2,
  D2D1_YCBCR_INTERPOLATION_MODE_MULTI_SAMPLE_LINEAR = 3,
  D2D1_YCBCR_INTERPOLATION_MODE_ANISOTROPIC = 4,
  D2D1_YCBCR_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC = 5,
  D2D1_YCBCR_INTERPOLATION_MODE_FORCE_DWORD = 0xffffffff
} D2D1_YCBCR_INTERPOLATION_MODE;

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */

#endif /* _D2D1_EFFECTS_1_ */
