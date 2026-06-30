/*
 * Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTCLOSURE_HPP
#define SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTCLOSURE_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR
#include "memory/heapInspection.hpp"
#include "oops/access.hpp"
#include "oops/compressedOops.inline.hpp"
#include "oops/oop.inline.hpp"

// Thread-local closure that records per-Klass instance counts and sizes during
// marking, accumulating into a thread-local KlassInfoTable. On destruction the
// local table is merged into the heap's KlassInfoTable.
class ShenandoahObjectCountClosure {
private:
  KlassInfoTable _cit;

  template <class T>
  inline void do_oop_work(T* p) {
    T o = RawAccess<>::oop_load(p);
    if (!CompressedOops::is_null(o)) {
      oop obj = CompressedOops::decode_not_null(o);
      _cit.record_instance(obj);
    }
  }

  // Merges the heap's KlassInfoTable with the thread's KlassInfoTable.
  void merge_table();

public:
  ShenandoahObjectCountClosure() : _cit(false) {}

  // Record the object's instance in the KlassInfoTable
  inline void do_oop(narrowOop* o) { do_oop_work(o); }
  inline void do_oop(oop* o) { do_oop_work(o); }

  ~ShenandoahObjectCountClosure() {
    merge_table();
  }
};
#endif // INCLUDE_JFR

#endif // SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTCLOSURE_HPP
