public class MultiplyExpression extends ComplexExpression {
    MultiplyExpression(ComplexNumber[] args) {
        super(Operation.MULTIPLY, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.multiply(nr2);
    }
}
