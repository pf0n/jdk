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

#include "utilities/macros.hpp"
#if INCLUDE_JFR
#include "gc/shenandoah/shenandoahHeap.inline.hpp"
#include "gc/shenandoah/shenandoahKlassInfoRecorder.hpp"
#include "runtime/mutexLocker.hpp"

void ShenandoahKlassInfoRecorder::merge_table() {
  KlassInfoTable* heap_cit = ShenandoahHeap::heap()->get_cit();
  if (heap_cit == nullptr || heap_cit->allocation_failed() || _cit.allocation_failed()) {
    return;
  }

  MutexLocker x(ObjectCountMerge_lock, Mutex::_no_safepoint_check_flag);
  bool success = heap_cit->merge(&_cit);
  if (!success) {
    log_warning(gc, jfr)("ObjectCountAfterGC: could not merge all of the thread-local KlassInfoTable entries."
                         " Emitted object counts may be incomplete.");
  }
}
#endif // INCLUDE_JFR
