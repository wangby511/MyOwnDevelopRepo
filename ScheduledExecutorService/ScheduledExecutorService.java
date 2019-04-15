import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;

public class ScheduledExecutorService {
    private class Task implements Runnable, Comparable<Task> {

        private long startTime;
        private Runnable runnable;

        public Task(Runnable runnable) {
            this.runnable = runnable;
        }

        @Override
        public void run() {
            this.runnable.run();
        }

        public long getStartTime() {
            return startTime;
        }

        public void setStartTime(long startTime) {
            this.startTime = startTime;
        }

        @Override
        public int compareTo(Task o) {
            return Long.compare(this.getStartTime(), o.getStartTime());
        }

        @Override
        public String toString() {
            return "Task [startTime=" + startTime + "]";
        }
    }

    private class BackgroundScheduler extends Thread {

        @Override
        public void run() {
            while (ScheduledExecutorService.this.alive) {
                synchronized (ScheduledExecutorService.this) {
                    try {
                        while (ScheduledExecutorService.this.alive &&
                                ScheduledExecutorService.this.tasks.isEmpty()) {
                            ScheduledExecutorService.this.wait();
                        }
                        if (!ScheduledExecutorService.this.alive) {
                            return;
                        }
                        long now = System.currentTimeMillis();
                        Task task = tasks.peek();
                        if (task.getStartTime() <= now) {
                            tasks.poll();
                            new Thread(task).start();
                        } else {
                            System.out.println("waitTime = " + (task.getStartTime() - now) + "ms");
                            ScheduledExecutorService.this.wait(task.getStartTime() - now);
                        }
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                }
            }
        }
    }

    private PriorityQueue<Task> tasks;
    private final BackgroundScheduler backgroundScheduler;
    private volatile boolean alive;

    public ScheduledExecutorService() {
        this.tasks = new PriorityQueue<>();
        this.backgroundScheduler = new BackgroundScheduler();
        this.alive = true;
        this.backgroundScheduler.start();
    }

    /**
     * Creates and executes a one-shot action that becomes enabled after the given
     * delay.
     *
     * @param command
     *            the task to execute
     * @param delay
     *            the time from now to delay execution
     * @param unit
     *            the time unit of the delay parameter
     */
    public void schedule(Runnable command, long delay, TimeUnit unit) {
        long startTime = System.currentTimeMillis() + unit.toMillis(delay);
        Task task = new Task(command);
        task.setStartTime(startTime);
        synchronized (this) {
            this.tasks.offer(task);
            this.notifyAll();
        }
        System.out.println("Scheduled task " + task);
    }

    public void stop() throws InterruptedException {
        synchronized (this) {
            this.alive = false;
            this.notifyAll();
        }
        this.backgroundScheduler.join();
    }
}
