/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-05-05T22:14:16+0500
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[50] = {
  0x3fa7ed0d3d1bc9f3U, 0xbe4c3f5139c8fff7U, 0xbc63e0b83da3c429U, 0xbfdfb87cbe9b9fedU,
  0x3f9f8467bca28021U, 0xbf874dcd3b5f2102U, 0x3f9b72bdbc0bf84fU, 0x3ea38605bef98191U,
  0xbeda27213f0aee10U, 0x3fa6b6f73d5a3a6bU, 0xbea75f44bf378a7cU, 0x3f01361cba8f8929U,
  0x3eb5ed3cbe9c05e0U, 0x3ef200aa3e71ee04U, 0xbfb19065bce5963dU, 0xbfb9ed70bcf89d27U,
  0xbe640efc3f92f7fdU, 0x3e4d69a2bdf10990U, 0x3f3d872ebe291844U, 0x3f32094b3c9859ceU,
  0x3f8e18cb3f580824U, 0xbec75ea93e430544U, 0xbe0bc0c23f3abcc7U, 0xbe9d0968be9762d1U,
  0xbebbc08cbfdcf0bdU, 0x3f0d860dbecffb8fU, 0x3f8b0597be5f9847U, 0xbf61aec83d6e64eaU,
  0xbfa758253e261307U, 0xbda2c254be7b429eU, 0x3e6af1c5bf4d6104U, 0x3fc42b593fb9445eU,
  0xbe29adb73f246a0bU, 0xbf859d80be58b58cU, 0xbe20b2a1bf9673adU, 0x3f051945bef724a7U,
  0x3f5309913f53f41fU, 0xbfe7ed8b3ddfb105U, 0xbf68c1713eb80f5dU, 0xbfa8a130bfb17568U,
  0x3d8153f73f32faeaU, 0xbfa540f43ef6c33aU, 0xc0083fe73f43606fU, 0x3e73a63b3f98281fU,
  0x3f3510bfbf2d7b3aU, 0x3dbb6075bed0da39U, 0xbdeb882fbe661034U, 0xbf31c298bee44fa0U,
  0x3f2d2449bea7399cU, 0xbf0977afU,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

