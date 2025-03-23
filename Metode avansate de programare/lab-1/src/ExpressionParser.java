import java.beans.Expression;
import java.util.ArrayList;
import java.util.Objects;


public class ExpressionParser {
    private final String[] args;

    public ExpressionParser(String[] args) {
        this.args = args;
    }

    private void isValid(String[] expression) throws ValidationException {
        ArrayList<String> errors = new ArrayList<>();
        if (expression.length < 2)
            errors.add("Invalid expression! It must have at least 2 operands and an operator");
        if (expression.length % 2 == 0)
            errors.add("Invalid expression");

        for (int i = 1; i < expression.length; i += 2) {
            if (!args[i].matches("[+-/*]"))
                errors.add("Invalid operator");
        }

        String op = args[1];
        for (int i = 1; i < expression.length; i += 2) {
            if (!Objects.equals(op, args[i])) {
                errors.add("The operator must be the  same!");
                break;
            }

        }

        if (!errors.isEmpty())
            throw new ValidationException(errors);
    }

    public ComplexExpression parseComplexExpression() {
        try {
            isValid(args);

            String op = args[1];
            ComplexNumber[] numbers = new ComplexNumber[(args.length + 1) / 2];
            for (int i = 0; i < args.length; i++) {
                if (i % 2 == 0) {
                    double re,im;
                    int asteriskPos = args[i].indexOf("*");
                    if (asteriskPos != -1) {
                        String nr = args[i].substring(0, asteriskPos);
                        int lastSignPos;
                        int minusPos = nr.lastIndexOf("-");
                        int plusPos = nr.lastIndexOf("+");
                        if (plusPos == -1) {
                            lastSignPos = minusPos;
                        } else if (minusPos == -1) {
                            lastSignPos = plusPos;
                        } else lastSignPos = Math.max(nr.indexOf("+"), nr.indexOf("-"));

                        re = Double.parseDouble(nr.substring(0, lastSignPos));
                        im = Double.parseDouble(nr.substring(lastSignPos));
                        ComplexNumber complexNumber = new ComplexNumber(re, im);
                        numbers[i / 2] = complexNumber;
                    } else throw new NumberFormatException("The operand must have an imaginary part");
                } else {
                    op = args[i];
                }
            }

            ExpressionFactory instance = ExpressionFactory.getInstance();
            return switch (op) {
                case "+" -> instance.createExpression(Operation.ADD, numbers);
                case "-" -> instance.createExpression(Operation.SUBTRACT, numbers);
                case "*" -> instance.createExpression(Operation.MULTIPLY, numbers);
                case "/" -> instance.createExpression(Operation.DIVIDE, numbers);
                default -> null;
            };

        } catch (ValidationException | NumberFormatException e) {
            System.out.println(e.getMessage());
        }
        return null;
    }

}


