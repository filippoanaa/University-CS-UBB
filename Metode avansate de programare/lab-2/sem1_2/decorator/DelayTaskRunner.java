package sem1_2.decorator;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DelayTaskRunner extends AbstractTaskRunner {
    private static final DateTimeFormatter TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm:ss");
    public DelayTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }
    @Override
    public void executeOneTask() {
        try{
            Thread.sleep(3000);
            System.out.println("Delayed Task executed at: " + LocalDateTime.now().format(TIME_FORMATTER));

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.executeOneTask();


    }
}
