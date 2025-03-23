public class ExpressionFactory {
    private static ExpressionFactory instance = null;

    private ExpressionFactory() {
    }

    public static ExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }


    public ComplexExpression createExpression(Operation operation, ComplexNumber[] args) {
        return switch (operation) {
            case ADD -> new AdditionExpression(args);
            case SUBTRACT -> new SubstractExpression(args);
            case MULTIPLY -> new MultiplyExpression(args);
            case DIVIDE -> new DivideExpression(args);
        };
    }
}
