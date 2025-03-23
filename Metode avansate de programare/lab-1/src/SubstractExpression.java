public class SubstractExpression extends ComplexExpression {
    public SubstractExpression(ComplexNumber[] args) {
        super(Operation.SUBTRACT, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.subtract(nr2);
    }
}
