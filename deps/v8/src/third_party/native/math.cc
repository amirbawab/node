#include "src/third_party/native/math.h"
#include "src/v8memory.h"
#include "src/globals.h"
#include "src/base/ieee754.h"
#include "../eigen-git-mirror/Eigen/Dense"

namespace v8 {
namespace internal {
namespace wasm {

void mat_mul_f32(Address mem, Address data) {
  int32_t* data_i32 = reinterpret_cast<int32_t*>(data);
  auto o1 = *data_i32;
  auto o2 = *(data_i32+1);
  auto o3 = *(data_i32+2);
  auto side = *(data_i32+3);
  float* data_f32 = reinterpret_cast<float*>(mem);

  float* mat1 = data_f32 + o1;
  float* mat2 = data_f32 + o2;
  float* mat3 = data_f32 + o3;

  for(int r=0; r < side; ++r) {
    for(int c=0; c < side; ++c) {
      float resCell = 0;
      for(int cr=0; cr < side; ++cr) {
        resCell +=  *(mat1 + r * side + cr) +
                    *(mat2 + cr * side + c);
      }
      *(mat3++) = resCell;
    }
  }
}

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

void dot_product_f32(Address mem, Address data) {
  // Load parameters
  int32_t* data_int32_p = reinterpret_cast<int32_t*>(data);
  int32_t lhs_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t rhs_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t dst_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t lhs_row = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t lhs_col = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t rhs_col = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p));

  // Locate buffers
  byte* mem_byte_p = reinterpret_cast<byte*>(mem);
  float* lhs_p = reinterpret_cast<float*>(mem_byte_p + lhs_addr);
  float* rhs_p = reinterpret_cast<float*>(mem_byte_p + rhs_addr);
  float* dst_p = reinterpret_cast<float*>(mem_byte_p + dst_addr);

  // Perform dot product
  auto lhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(lhs_p, lhs_row, lhs_col);
  auto rhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(rhs_p, lhs_col, rhs_col);
  Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(dst_p, lhs_row, rhs_col) = lhs * rhs;
}

void dot_product_rt_f32(Address mem, Address data) {
  // Load parameters
  int32_t* data_int32_p = reinterpret_cast<int32_t*>(data);
  int32_t lhs_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t rhs_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t dst_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t lhs_row = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t lhs_col = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t rhs_col = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p));

  // Locate buffers
  byte* mem_byte_p = reinterpret_cast<byte*>(mem);
  float* lhs_p = reinterpret_cast<float*>(mem_byte_p + lhs_addr);
  float* rhs_p = reinterpret_cast<float*>(mem_byte_p + rhs_addr);
  float* dst_p = reinterpret_cast<float*>(mem_byte_p + dst_addr);

  // Perform dot product
  if(lhs_col == 1) {
    auto lhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, 1>>(lhs_p, lhs_row, lhs_col);
    auto rhs = Eigen::Map<Eigen::Matrix<float, 1, Eigen::Dynamic>>(rhs_p, lhs_col, rhs_col);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(dst_p, lhs_row, rhs_col) = lhs * rhs;
  } else {
    auto lhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(lhs_p, lhs_row, lhs_col);
    auto rhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(rhs_p, lhs_col, rhs_col);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(dst_p, lhs_row, rhs_col) = lhs * rhs;
  }
}

void dot_product_lt_f32(Address mem, Address data) {
  // Load parameters
  int32_t* data_int32_p = reinterpret_cast<int32_t*>(data);
  int32_t lhs_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t rhs_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t dst_addr = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t lhs_row = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t lhs_col = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p++));
  int32_t rhs_col = ReadUnalignedValue<int32_t>(reinterpret_cast<Address>(data_int32_p));

  // Locate buffers
  byte* mem_byte_p = reinterpret_cast<byte*>(mem);
  float* lhs_p = reinterpret_cast<float*>(mem_byte_p + lhs_addr);
  float* rhs_p = reinterpret_cast<float*>(mem_byte_p + rhs_addr);
  float* dst_p = reinterpret_cast<float*>(mem_byte_p + dst_addr);

  // Perform dot product
  auto lhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>>(lhs_p, lhs_row, lhs_col);
  auto rhs = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(rhs_p, lhs_col, rhs_col);
  Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>(dst_p, lhs_row, rhs_col) = lhs * rhs;
}

}
}
}

