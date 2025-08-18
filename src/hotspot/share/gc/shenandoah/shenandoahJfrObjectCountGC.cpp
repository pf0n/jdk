#include "gc/shenandoah/shenandoahHeap.inline.hpp"
#include "gc/shenandoah/shenandoahJfrObjectCountGC.hpp"
#include "prims/jvmtiTagMap.hpp"
#include "gc/shenandoah/shenandoahVerifier.hpp"
#include "gc/shenandoah/shenandoahPhaseTimings.hpp"
#include "gc/shenandoah/shenandoahUtils.hpp"

void ShenandoahJfrObjectCountGC::op_final_mark() {
  ShenandoahHeap* const heap = ShenandoahHeap::heap();
  assert(ShenandoahSafepoint::is_at_shenandoah_safepoint(), "Should be at safepoint");
  assert(!heap->has_forwarded_objects(), "No forwarded objects on this path");

  if (ShenandoahVerify) {
    heap->verifier()->verify_roots_no_forwarded();
  }

  if (!heap->cancelled_gc()) {
    _mark.finish_mark();
    
    // Notify JVMTI that the tagmap table will need cleaning.
    JvmtiTagMap::set_needs_cleaning();

    if (ShenandoahVerify) {
      ShenandoahTimingsTracker v(ShenandoahPhaseTimings::final_mark_verify);
      heap->verifier()->verify_after_concmark();
    }
  }

  {
    ShenandoahTimingsTracker timing(ShenandoahPhaseTimings::final_mark_propagate_gc_state);
    heap->propagate_gc_state_to_all_threads();
  }
}

bool ShenandoahJfrObjectCountGC::collect(GCCause::Cause cause) {
  ShenandoahHeap* const heap = ShenandoahHeap::heap();
  
  entry_reset();

  vmop_entry_init_mark();

  entry_scan_remembered_set();

  entry_mark_roots();
  if (check_cancellation_and_abort(ShenandoahDegenPoint::_degenerated_roots)) {
    return false;
  }

  entry_mark();
  if (check_cancellation_and_abort(ShenandoahDegenPoint::_degenerated_mark)) {
    return false;
  }

  vmop_entry_final_mark();
  entry_reset_after_collect();
  return true;
}
