public class ComplexNumber {
    private double re;
    private double im;

    public ComplexNumber(double re, double im) {
        this.re = re;
        this.im = im;
    }

    public double getRe() {
        return re;
    }

    public double getIm() {
        return im;
    }

    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(this.re + other.getRe(), this.im + other.getIm());
    }

    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(this.re - other.getRe(), this.im - other.getIm());
    }

    public ComplexNumber multiply(ComplexNumber other) {
        double re = this.re * other.getRe() - this.im * other.getIm();
        double im = this.im * other.getRe() + this.re * other.getIm();
        return new ComplexNumber(re, im);
    }

    public ComplexNumber conjugate() {
        return new ComplexNumber(this.re, -this.im);
    }

    public ComplexNumber divide(ComplexNumber other) {
        ComplexNumber numerator = this.multiply(other.conjugate());
        double denominator = Math.pow(other.getRe(), 2) + Math.pow(other.getIm(), 2);
        double re = numerator.getRe() / denominator;
        double im = numerator.getIm() / denominator;
        return new ComplexNumber(re, im);
    }

    @Override
    public String toString() {
        if (this.re == 0) {
            return this.im + "*i";
        }
        if (this.im == 0) {
            return "" + this.re;
        }
        if (this.im > 0) {
            return this.re + "+" + this.im + "*i";
        } else {
            return this.re + "" + this.im + "*i";
        }
    }


}
