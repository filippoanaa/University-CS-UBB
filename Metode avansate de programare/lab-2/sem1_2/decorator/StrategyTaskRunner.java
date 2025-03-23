package sem1_2.decorator;

import sem1_2.model.Container;
import sem1_2.model.Task;
import sem1_2.factory.TaskContainerFactory;
import sem1_2.factory.Strategy;

public class StrategyTaskRunner implements TaskRunner {

    private Container container;

    public StrategyTaskRunner(Strategy strategy) {
        container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask() {
        Task task = container.remove();
        if(task != null) {
            task.execute();
        }else{
            System.out.println("No task found");
        }

    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
