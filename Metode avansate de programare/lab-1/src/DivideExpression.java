public class DivideExpression extends ComplexExpression {
    public DivideExpression(ComplexNumber[] args) {
        super(Operation.DIVIDE, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.divide(nr2);
    }
}
