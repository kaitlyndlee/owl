// ======================================================================== //
// Copyright 2019 Ingo Wald                                                 //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

// gdt
#include "gdt/math/AffineSpace.h"
#include "gdt/parallel/parallel_for.h"
// std
#include <vector>
#include <memory>
#include <mutex>
#include <map>


#define OPTIX_COMPATIBILITY 7

#include <cuda_runtime.h>

#include <optix.h>
#include <optix_function_table.h>
#include <optix_stubs.h>

//------------------------------------------------------------------------------
//
// Local functions
// TODO: some of these should move to sutil or optix util header
//
//------------------------------------------------------------------------------

#define OPTIX_CHECK( call )                                             \
  {                                                                     \
    OptixResult res = call;                                             \
    if( res != OPTIX_SUCCESS )                                          \
      {                                                                 \
        fprintf( stderr, "Optix call (%s) failed with code %d (line %d)\n", #call, res, __LINE__ ); \
        exit( 2 );                                                      \
      }                                                                 \
  }

#define OPTIX_CHECK_LOG( call )                                         \
  {                                                                     \
    OptixResult res = call;                                             \
    if( res != OPTIX_SUCCESS )                                          \
      {                                                                 \
        fprintf( stderr, "Optix call (%s) failed with code %d (line %d)\n", #call, res, __LINE__ ); \
        fprintf( stderr, "Log:\n%s\n", log );                           \
        exit( 2 );                                                      \
      }                                                                 \
  }

#define CUDA_CHECK( call )                                              \
  {                                                                     \
    cudaError_t error = call;                                           \
    if( error != cudaSuccess )                                          \
      {                                                                 \
        fprintf( stderr, "CUDA call (%s) failed with code %d (line %d): %s\n", #call, error, __LINE__, cudaGetErrorString( error ) ); \
        exit( 2 );                                                      \
      }                                                                 \
  }

#define CUDA_CHECK2( where, call )                                       \
  {                                                                     \
    cudaError_t error = call;                                           \
    if( error != cudaSuccess )                                          \
      {                                                                 \
        if(where) fprintf( stderr, "at %s: CUDA call (%s) failed with code %d (line %d): %s\n", where,#call, error, __LINE__, cudaGetErrorString( error ) ); \
        fprintf( stderr, "CUDA call (%s) failed with code %d (line %d): %s\n", #call, error, __LINE__, cudaGetErrorString( error ) ); \
        exit( 2 );                                                      \
      }                                                                 \
  }

#define CUDA_SYNC_CHECK()                                               \
  {                                                                     \
    cudaDeviceSynchronize();                                            \
    cudaError_t error = cudaGetLastError();                             \
    if( error != cudaSuccess )                                          \
      {                                                                 \
        fprintf( stderr, "error (%s: line %d): %s\n", __FILE__, __LINE__, cudaGetErrorString( error ) ); \
        exit( 2 );                                                      \
      }                                                                 \
  }


#define OWL_NOTIMPLEMENTED throw std::runtime_error(std::string(__PRETTY_FUNCTION__)+\
                                                    " : not yet implemented")

