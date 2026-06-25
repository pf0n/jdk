package jdk.jfr.event.gc.objectcount;
import jdk.test.lib.jfr.GCHelper;

/**
 * @test
 * @requires vm.flagless
 * @requires vm.hasJFR
 * @requires (vm.gc == "Shenandoah" | vm.gc == null)
 *           & vm.opt.ExplicitGCInvokesConcurrent != true
 * @library /test/lib /test/jdk
 * @run main/othervm -XX:+UseShenandoahGC -XX:-UseCompressedOops -XX:-UseCompressedClassPointers jdk.jfr.event.gc.objectcount.TestObjectCountAfterGCEventWithShenandoah
 */
public class TestObjectCountAfterGCEventWithShenandoah {
    public static void main(String[] args) throws Exception {
        ObjectCountAfterGCEvent.test(GCHelper.gcShenandoah);
    }
}
