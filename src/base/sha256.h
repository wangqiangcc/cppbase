// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_SHA256_H_
#define BASE_SHA256_H_

#include <stdint.h>
#include "base/macros.h"
#include "base/strings/string_util.h"

namespace base {

class SHA256 {
 public:
  SHA256() { Init(); }
  ~SHA256() {}

  enum {
    kDigestSize = 32,
    kBlockSize = 64
  };

  void Init();
  void Update(const void* data, size_t nbytes);
  void Final();

  int DigestSize() const;
  int BlockSize() const;

  // 32 bytes of message digest.
  const unsigned char* Digest() const {
    return buf_;
  }

 private:
  void Pad();
  void Transform(const unsigned char block[64]);

  uint32_t state_[8];
  uint32_t count_[2];
  unsigned char buf_[64];
};

std::string SHA256HexString(const base::StringPiece& str);

}  // namespace base

#endif // BASE_SHA256_H_ 
