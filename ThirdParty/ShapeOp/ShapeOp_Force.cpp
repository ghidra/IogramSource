///////////////////////////////////////////////////////////////////////////////
// This file is part of ShapeOp, a lightweight C++ library
// for static and dynamic geometry processing.
//
// Copyright (C) 2014 Sofien Bouaziz <sofien.bouaziz@gmail.com>
// Copyright (C) 2014 LGG EPFL
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
///////////////////////////////////////////////////////////////////////////////
#include "ShapeOp_Force.h"
///////////////////////////////////////////////////////////////////////////////
namespace ShapeOp {
///////////////////////////////////////////////////////////////////////////////
SHAPEOP_INLINE GravityForce::GravityForce(const Vector3 &f) :
  f_(f) {
}
///////////////////////////////////////////////////////////////////////////////
SHAPEOP_INLINE Vector3 GravityForce::get(const Matrix3X &/*positions*/, int /*id*/) const {
  return f_;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SHAPEOP_INLINE VertexForce::VertexForce(const Vector3 &f, int id) :
  f_(f), id_(id) {
}
///////////////////////////////////////////////////////////////////////////////
SHAPEOP_INLINE Vector3 VertexForce::get(const Matrix3X &/*position*/, int id) const {
  if (id == id_)
    return f_;
  else
    return Vector3::Zero();
}
///////////////////////////////////////////////////////////////////////////////
SHAPEOP_INLINE void VertexForce::setId(int id) {
  id_ = id;
}
///////////////////////////////////////////////////////////////////////////////
SHAPEOP_INLINE void VertexForce::setForce(const Vector3 &f) {
  f_ = f;
}
///////////////////////////////////////////////////////////////////////////////
} // namespace ShapeOp
///////////////////////////////////////////////////////////////////////////////
