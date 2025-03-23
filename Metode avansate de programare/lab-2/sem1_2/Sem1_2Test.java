package sem1_2;

import sem1_2.decorator.DelayTaskRunner;
import sem1_2.decorator.PrinterTaskRunner;
import sem1_2.decorator.StrategyTaskRunner;
import sem1_2.decorator.TaskRunner;
import sem1_2.factory.Strategy;
import sem1_2.model.*;

import java.time.LocalDateTime;

public class Sem1_2Test {
    public static MessageTask[] createMessages() {
        MessageTask msg1 = new MessageTask("1", "feedback lab 2", "Te-ai descurcat bine", "teacher", "student", LocalDateTime.now());
        MessageTask msg2 = new MessageTask("2", "feedback lab 3", "Te-ai descurcat bine", "teacher", "student", LocalDateTime.now());
        MessageTask msg3 = new MessageTask("3", "feedback lab 4", "Te-ai descurcat bine", "teacher", "student", LocalDateTime.now());
        MessageTask msg4 = new MessageTask("4", "feedback lab 5", "Te-ai descurcat bine", "teacher", "student", LocalDateTime.now());
        MessageTask msg5 = new MessageTask("5", "feedback lab 6", "Te-ai descurcat bine", "teacher", "student", LocalDateTime.now());

        return new MessageTask[]{msg1, msg2, msg3, msg4, msg5};
    }


    public static void main(String[] args) {
        MessageTask[] messageTasks = createMessages();
        Strategy containerStrategy = Strategy.valueOf(args[0]);

        TaskRunner strategyTaskRunner = new StrategyTaskRunner(containerStrategy);
        System.out.println("STRATEGY TASK RUNNER:");
        for (MessageTask m : messageTasks) {
            strategyTaskRunner.addTask(m);
        }
        for (MessageTask messageTask : messageTasks) {
            System.out.println(messageTask);
        }
        System.out.println("\n");

        System.out.println("PRINTER TASK RUNNER:");
        TaskRunner printerTaskRunner = new PrinterTaskRunner(strategyTaskRunner);
        printerTaskRunner.executeAll();
        System.out.println("\n");

        System.out.println("DELAY TASK RUNNER:");
        TaskRunner delayTaskRunner = new DelayTaskRunner(strategyTaskRunner);
        for (MessageTask m : messageTasks) {
            delayTaskRunner.addTask(m);
        }
        delayTaskRunner.executeAll();
        System.out.println("\n");

        System.out.println("SORTING TASK");
        int[] numbers = {3, 1, 4, 50, 1, 45, -2, -1, 5, 7, 22, 70, 1, 2, 3};
        AbstractSorter sorter;
        switch (args[1]){
            case "BUBBLE SORT" -> sorter = new BubbleSort();
            case "QUICK SORT" -> sorter = new QuickSort();
            default -> {
                System.out.println("Unknown sorting algorithm. Please choose between BUBBLE SORT and QUICK SORT");
                return;
            }
        }

        SortingTask sortingTask= new SortingTask("1","Sorting",sorter,numbers);
        strategyTaskRunner.addTask(sortingTask);
        strategyTaskRunner.executeAll();

    }
}
