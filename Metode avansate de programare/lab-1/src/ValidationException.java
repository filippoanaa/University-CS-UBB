import java.util.ArrayList;

public class ValidationException extends Exception {
    ArrayList<String> errorsList;

    public ValidationException(ArrayList<String> errorsList) {
        this.errorsList = errorsList;
    }

    @Override
    public String getMessage() {
        StringBuilder message = new StringBuilder();
        for (String s : errorsList) {
            message.append(s).append("\n");
        }
        return message.toString();
    }
}
