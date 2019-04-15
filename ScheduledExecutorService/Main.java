import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        ScheduledExecutorService scheduledExecutorService = new ScheduledExecutorService();
        long start = System.currentTimeMillis();
        scheduledExecutorService.schedule(() -> {
            System.out.println((System.currentTimeMillis() - start) + "ms, 5 second delay");
        }, 5, TimeUnit.SECONDS);
        scheduledExecutorService.schedule(() -> {
            System.out.println((System.currentTimeMillis() - start) + "ms, 1 second delay started");
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
            }
            System.out.println((System.currentTimeMillis() - start) + "ms, 1 second delay stopped");
        }, 1, TimeUnit.SECONDS);
        scheduledExecutorService.schedule(() -> {
            System.out.println((System.currentTimeMillis() - start) + "ms, 3 second delay");
        }, 3, TimeUnit.SECONDS);
        scheduledExecutorService.schedule(() -> {
            System.out.println((System.currentTimeMillis() - start) + "ms, 10 second delay");
        }, 10, TimeUnit.SECONDS);
    }
}
