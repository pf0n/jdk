#include "gc/shenandoah/shenandoahHeap.inline.hpp"
#include "gc/shenandoah/shenandoahObjectCountGC.hpp"

bool ShenandoahObjectCountGC::collect(GCCause::Cause cause) {
  ShenandoahHeap* const heap = ShenandoahHeap::heap();
  
  entry_reset();
  vmop_entry_init_mark();

  // TASKQUEUE_STATS_ONLY(_mark.task_queues()->reset_taskqueue_stats());

  entry_scan_remembered_set();
  entry_mark_roots();
  if (check_cancellation_and_abort(ShenandoahDegenPoint::_degenerated_roots)) {
    return false;
  }

  entry_mark();
  if (check_cancellation_and_abort(ShenandoahDegenPoint::_degenerated_mark)) {
    return false;
  }
  return true;
}
