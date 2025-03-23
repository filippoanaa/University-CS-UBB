public class AdditionExpression extends ComplexExpression {
    public AdditionExpression(ComplexNumber[] args) {
        super(Operation.ADD, args);
    }

    @Override
    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.add(nr2);
    }
}
