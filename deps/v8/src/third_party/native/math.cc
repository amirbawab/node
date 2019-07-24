#include "src/third_party/native/math.h"
#include "src/v8memory.h"
#include "src/globals.h"
#include "src/base/ieee754.h"

namespace v8 {
namespace internal {
namespace wasm {

void add_i32(Address mem, Address data) {
  int32_t* data_i32 = reinterpret_cast<int32_t*>(data);
  auto l = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_i32));
  auto r = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_i32+1));
  WriteUnalignedValue<int32_t>(reinterpret_cast<Address>(data_i32+2), l + r);
}

void sigmoid(Address mem, Address data) {
  const double* res = reinterpret_cast<double*>(data) + 1;
  WriteUnalignedValue<double>(reinterpret_cast<Address>(res), 
      1 / (1 + base::ieee754::exp(-ReadUnalignedValue<double>(data))));
}

}
}
}

