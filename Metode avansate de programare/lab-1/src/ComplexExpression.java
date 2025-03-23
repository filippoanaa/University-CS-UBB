import java.lang.reflect.Array;

public abstract class ComplexExpression {
    private Operation operation;
    private ComplexNumber[] args;

    public ComplexExpression(Operation operation, ComplexNumber[] args) {
        this.operation = operation;
        this.args = args;
    }

    protected abstract ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2);

    public ComplexNumber execute() {
        ComplexNumber result = args[0];
        for (int i = 1; i < args.length; i++) {
            result = executeOneOperation(result, args[i]);
        }
        System.out.println("Result: " + result);
        return result;
    }
}
