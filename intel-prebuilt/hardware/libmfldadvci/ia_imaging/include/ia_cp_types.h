/*
 * Copyright 2012-2013 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _IA_CP_TYPES_H_
#define _IA_CP_TYPES_H_

#include "ia_aiq_types.h"

/** @file ia_cp_types.h
 * This file declares data types used for computational photography.
 * These data types are declared in a separate header file to allow re-use
 * across components in the software stack.
 */

#ifdef __cplusplus
extern "C" {
#endif

#define IA_CP_HISTOGRAM_SIZE    256

/** @brief Histogram and related statistics.
 *
 * The structure to hold the plane histogram and the corresponding
 * cumulative distribution function (CDF).
 */
typedef struct
{
    int data[IA_CP_HISTOGRAM_SIZE];       /**< Histogram values */
    int cdf[IA_CP_HISTOGRAM_SIZE];        /**< Normalized CDF for the histogram */
    int levels[IA_CP_HISTOGRAM_SIZE + 1]; /**< Histogram levels */
    int size;                             /**< Total number of samples in all bins */
} ia_cp_histogram;

/** @brief Local contrast enhancement controls
 *
 * Contrast enhancement can be applied as part of the computational photography pipelines.
 * This is usually done as a post-processing step to make up for a loss in sharpness and
 * texture details introduced by composition of multiple images. This can be achieved either
 * as a multi-level sharpening, or as a pixel modification based on its local neighbourhood.
 */
typedef enum
{
    ia_cp_contrast_none,              /**< No contrast enhancement */
    ia_cp_contrast_sharpening,        /**< Enable sharpening */
    ia_cp_contrast_details,           /**< Enable texture enhancement */
    ia_cp_contrast_all,               /**< Enable both sharpening and texture enhancement */
} ia_cp_contrast;

/** @brief Vividness enhancement
 *
 * Vividness enhancement can be enabled in certain CP features to boost color saturation.
 * Processing operates on the S channel (HSV color space) and increases its value while
 * preserving the color gammut. Saturation is not applied to skin tones.
 */
typedef enum
{
    ia_cp_vividness_off,      /**< Color saturation enhancement disabled */
    ia_cp_vividness_on,       /**< Color saturation enhancement enabled */
} ia_cp_vividness;

/**
 * @brief ULL single frame noise reduction
 *
 * Single frame algorithm is used as a part of ull processing pipe.
 * It's results will be visible mostly on moving part of a scene.
 * Guided filter provides sufficient filterng for lower performance cost.
 * MNR algorithm preservs details better but is processing more expensive.
 * There is also option to switch off single frame de-noising part of the ull pipe,
 */
typedef enum
{
    ia_cp_ull_sfnr_guided, /**< Guided filter is used for single frame noise reduction */
    ia_cp_ull_sfnr_mnr,    /**< MNR algoritm is used for single frame noise reduction */
    ia_cp_ull_sfnr_off     /**< Single frame noise reduction stage is disabled */
} ia_cp_ull_sfnr_algorithm_t;

/** @brief HDR configuration interface
 *
 * This structure contains HDR runtime parameters computed by the
 * AIQ+ module or obtain differently (e.g. read from the disk). These
 * settings represent HDR runtime control interface.
 */
typedef struct
{
    ia_aiq_gbce_results gbce;                   /**< Result of the GBCE module computation */
} ia_cp_hdr_cfg;

/** @brief ULL configuration interface
 *
 * This structure contains ULL runtime parameters computed by the
 * AIQ+ module or obtain differently (e.g. read from the disk). These
 * settings represent ULL runtime control interface.
 */
typedef struct
{
    ia_aiq_exposure_parameters exposure;        /**< Generic exposure parameters for the input captures */
    int * imreg_fallback;                       /**< List of frames to ignore when using external alignment estimation (NULL for internal) */
    unsigned int zoom_factor;                   /**< Zoom factor */
} ia_cp_ull_cfg;

/** @brief Global motion estimation model
 *
 * This enumerator lists valid global motion estimation models
 * which can be specified during the global motion estimation process.
 */
typedef enum
{
    ia_cp_me_translation,                /**< Pure in-plane translation model */
    ia_cp_me_translation_rotation,       /**< Pure in-plane translation and rotation model */
    ia_cp_me_affine,                     /**< General affine model */
    ia_cp_me_projective                  /**< General projective (homography) model */
} ia_cp_me_model;

/** @brief Global motion estimation configuration interface
 *
 * This structure contains global motion estimation parameters. These
 * settings control the execution of the algorithm at runtime.
 */
typedef struct
{
    int pyr_depth;             /**< Depth of the pyramid for coarse-to-fine search */
    ia_cp_me_model model;      /**< Transformation model */
} ia_cp_me_cfg;

/** @brief Results of the global motion estimation
 *
 * This structure contains results of the global motion estimation.
 */
typedef struct
{
    double transform[3][3];        /**< Resulting 3x3 transformation matrix */
    int fallback;                  /**< Flag to indicate large global motion */
} ia_cp_me_result;

/** @brief Processing unit target
 *
 * This enumerator lists valid targets for execution of CP applications.
 */
typedef enum
{
    ia_cp_tgt_ia,        /**< Intel Architecture (IA) host */
    ia_cp_tgt_ipu,       /**< Image Processing Unit */
    ia_cp_tgt_gpu,       /**< Graphics Processing Unit */
    ia_cp_tgt_ate,       /**< ATE C bitexact reference model */
    ia_cp_tgt_ref        /**< Generic C reference model */
} ia_cp_target;

#ifdef __cplusplus
}
#endif

#endif /* _IA_CP_TYPES_H_ */
