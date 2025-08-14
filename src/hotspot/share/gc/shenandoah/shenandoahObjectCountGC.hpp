#ifndef SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTGC_HPP
#define SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTGC_HPP

#include "gc/shared/gcCause.hpp"
#include "gc/shenandoah/shenandoahConcurrentGC.hpp"
#include "gc/shenandoah/shenandoahConcurrentMark.hpp"
#include "gc/shenandoah/shenandoahGC.hpp"
#include "gc/shenandoah/shenandoahHeap.hpp"

class ShenandoahObjectCountGC : public ShenandoahConcurrentGC {
  public:
    ShenandoahObjectCountGC(ShenandoahGeneration* generation, bool do_old_gc_bootstrap = false)
      : ShenandoahConcurrentGC(generation, do_old_gc_bootstrap) {}
    bool collect(GCCause::Cause cause) override;
};

#endif // SHARE_GC_SHENANDOAH_SHENANDOAHOBJECTCOUNTGC_HPP
