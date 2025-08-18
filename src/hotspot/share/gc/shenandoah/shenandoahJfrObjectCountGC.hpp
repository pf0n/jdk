#ifndef SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTGC_HPP
#define SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTGC_HPP

#include "gc/shared/gcCause.hpp"
#include "gc/shenandoah/shenandoahConcurrentGC.hpp"
#include "gc/shenandoah/shenandoahConcurrentMark.hpp"
#include "gc/shenandoah/shenandoahGC.hpp"
#include "gc/shenandoah/shenandoahHeap.hpp"

// A pseudo Shenandoah GC where only the marking phase is initiated
// without any memory reclamation. This GC is used specifically for
// the Java Flight Recorder's ObjectCount event.
class ShenandoahJfrObjectCountGC : public ShenandoahConcurrentGC {
  public:
    ShenandoahJfrObjectCountGC(ShenandoahGeneration* generation, bool do_old_gc_bootstrap = false)
      : ShenandoahConcurrentGC(generation, do_old_gc_bootstrap) {}

    // Only make use of the mark phase in Shenandoah and does not reclaim any garbage
    bool collect(GCCause::Cause cause) override;

  protected:
    void op_final_mark() override;
};

#endif // SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTGC_HPP
