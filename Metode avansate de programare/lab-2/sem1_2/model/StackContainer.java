package sem1_2.model;

import java.util.ArrayList;
import java.util.List;

public class StackContainer extends AbstractContainer {
    @Override
    public Task remove() {
        if (!tasks.isEmpty()) {
            return tasks.remove(tasks.size() - 1);
        } else {
            return null;
        }
    }

}
