package sem1_2.model;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class QueueContainer extends AbstractContainer {
    @Override
    public Task remove() {
        if (!tasks.isEmpty()) {
            return tasks.remove(0);
        } else {
            return null;
        }
    }

}
