#include "src/wasm/wasm-native-external-refs.h"

namespace v8 {
namespace internal {
namespace wasm {

bool find_native_function(const char* find_name, FunctionSig* sig, ExternalReference (**ref)()) {
  return true;
}

}  // namespace wasm
}  // namespace internal
}  // namespace v8
