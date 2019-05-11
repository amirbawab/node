#include "src/third_party/native/system.h"
#include "src/v8memory.h"
#include "src/globals.h"
#include <chrono>
#include <iostream>

namespace v8 {
namespace internal {
namespace wasm {

#define PRINT_FUNC(sfx, type) \
void prints_##sfx(Address mem, Address data) { \
  std::cout << ReadUnalignedValue<type>(data) << std::endl; \
}
PRINT_FUNC(i32, int32_t)
PRINT_FUNC(i64, int64_t)
PRINT_FUNC(f32, float)
PRINT_FUNC(f64, double)

void time_ms(Address mem, Address data) {
  WriteUnalignedValue<int64_t>(data, std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count());
}

}
}
}

