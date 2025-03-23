//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        ExpressionParser parser = new ExpressionParser(args);
        ComplexExpression expression = parser.parseComplexExpression();
        if(expression != null)
            expression.execute();
    }
}