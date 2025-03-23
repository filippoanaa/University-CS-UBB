package sem1_2.model;


import java.util.Arrays;

public class SortingTask extends Task {
    private AbstractSorter abstractSorter;
    private int[] numbers;

   public SortingTask(String id, String description, AbstractSorter abstractSorter, int[] numbers) {
       super(id, description);
       this.abstractSorter = abstractSorter;
       this.numbers = numbers;
   }


    @Override
    public void execute() {
        abstractSorter.sort(numbers);
        System.out.println(Arrays.toString(numbers) + "\n");

    }
}
