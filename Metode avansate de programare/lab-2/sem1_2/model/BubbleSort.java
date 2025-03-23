package sem1_2.model;

public class BubbleSort extends AbstractSorter {

    @Override
    public void sort(int[] numbers) {
        int i, j, temp;
        boolean swapped;
        for (i = 0; i < numbers.length - 1; i++) {
            swapped = false;
            for (j = 0; j < numbers.length - i - 1; j++) {
                if (numbers[j] > numbers[j + 1]) {

                    temp = numbers[j];
                    numbers[j] = numbers[j + 1];
                    numbers[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }
}
