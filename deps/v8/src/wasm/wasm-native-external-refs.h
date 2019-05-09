// Copyright 2016 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_WASM_WASM_NATIVE_EXTERNAL_REFS_H_
#define V8_WASM_WASM_NATIVE_EXTERNAL_REFS_H_

#include "src/external-reference.h"
#include "src/wasm/value-type.h"
#include "src/v8memory.h"

namespace v8 {
namespace internal {
namespace wasm {

typedef void (*native_t)(Address, Address);

// find native function and set its index
bool find_native_function(const char* find_name, FunctionSig* sig, ExternalReference (**ref)());

}  // namespace wasm
}  // namespace internal
}  // namespace v8

#endif
