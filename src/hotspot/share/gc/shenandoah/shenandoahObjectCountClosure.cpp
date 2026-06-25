#include "gc/shenandoah/shenandoahClosures.inline.hpp"
#include "gc/shenandoah/shenandoahObjectCountClosure.hpp"
#include "runtime/mutexLocker.hpp"

#if INCLUDE_JFR

void ShenandoahObjectCountClosure::merge_table() {
  KlassInfoTable* heap_cit = ShenandoahHeap::heap()->get_cit();
  assert(heap_cit != nullptr, "Heap KlassInfoTable is not initialized");

  MutexLocker x(ObjectCountMerge_lock, Mutex::_no_safepoint_check_flag);
  bool success = heap_cit->merge(&_cit);
  assert(success, "Failed to merge thread-local table");
}

#endif // INCLUDE_JFR
