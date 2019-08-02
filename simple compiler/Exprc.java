

// Author:Jeremiah Jacobson from t.k.prasad@wright.edu (9/11/2012)
// Input: Multiple arithmetic expressions from file "exprEg.dat"
//        Arithmetic expression  containing integer variables (i and j),
//        double variable (a) and binary infix operators (+ and *).
//      <expr>   ->  <term>   { + <term> }
//      <term>   -> <factor>  { * <factor> }
//      <factor> ->  a | i  | j  |  ( <expr> )
//
// From the code generated by the "compiler" applet, the associativity
// of "+" and "*" are Left Associative for both.
//////////////////////////////////////////////////////
// Context:  static double f(int i, double a, int j) {...}
// Output : Equivalent Java bytecodes in file "exprEg.bc"

/* Example input expression:
       i + a * (((a) * i + j)) + (((i + a)* a) + j)
 */
import java.io.*;

public class Exprc {

    static BufferedReader in;
    static StreamTokenizer inTok;

    public static void main(String[] args) throws IOException {
        in = new BufferedReader(new FileReader("exprEg.dat"));
        inTok = new StreamTokenizer(in);

        inTok.eolIsSignificant(true);
        inTok.nextToken();  // lookahead token
        // processes a sequence of expressions holding onto the translation of the last expression
        while (inTok.ttype != inTok.TT_EOF) {
            if (inTok.ttype != inTok.TT_EOL) {
                PrintWriter out = new PrintWriter(
                        new FileWriter(inTok.lineno() + ".jbc"), true);
                try {
                    Node ae = expr();
                    
                    ae.code(out);
                    
                    
                    out.flush();
                } catch (Exception e) {
                    System.out.println(" \t\t Error =>  " + e);
                } finally {
                   //This is an infinite loop
                    while (inTok.ttype != inTok.TT_EOL) {
                        inTok.nextToken();
                    }
                }
            }
            inTok.nextToken();
        }
    }

    public static Node expr() throws Exception {
        // PRE: Expects lookahead token.
        // POST: Lookahead token available.
        Node temp = term();
        Node temp1;
        while ((inTok.ttype == '+')) {
            inTok.nextToken();

            temp1 = term();

            temp = new OpNode(temp, '+', temp1);
        }
        if (inTok.ttype == ')') {
            inTok.nextToken();

        }
        return temp;
    }


    public static Node term() throws Exception {
        // PRE: Expects lookahead token.
        // POST: Lookahead token available.
        Node temp = factor();
        Node temp1;
        while (inTok.ttype == '*') {
            inTok.nextToken();

            temp1 = factor();

            temp = new OpNode(temp, '*', temp1);
        }
        if (inTok.ttype == ')') {
            inTok.nextToken();

        }
        return temp;

    }

    public static Node factor() throws Exception {
        // PRE: Expects lookahead token.
        // POST: Reads in a lookahead token.
        Node temp = null;
        if (inTok.ttype != '(') {
            if (inTok.ttype == inTok.TT_WORD) {
                char ch = inTok.sval.charAt(0);
                if ((inTok.sval.length() == 1) && ((ch == 'i') || (ch == 'a') || (ch == 'j'))) {//changed JJ

                    
                    temp = new VarNode(ch);
                    inTok.nextToken();

                } else {
                    throw new Exception("Illegal Variable Name");
                }
            } else {
                throw new Exception("Variable Token Expected");
            }
                    
                    

        }else{
            inTok.nextToken();
            temp = expr();
        }

        return temp;
    }
}

interface Node {

    double value();

    public void setType(String type);

    String type();

    void code(PrintWriter out);
}

// Recall that, ideally, OOP avoids switch.
class VarNode implements Node {

    private char id;
    private String type = "";
    boolean coercion = false;

    public VarNode(char _id) {
        id = _id;
        if (id == 'a') {
            this.type = "double";
        } else {
            this.type = "int";
        }
    }

    @Override
    public void setType(String tp) {
        if (this.type.equals("int") && tp.equals("double")) {
            this.setCoercion(true);
        }
        this.type = tp;
    }

    public void setCoercion(boolean coercion) {
        this.coercion = coercion;
    }

    @Override
    public double value() {
        // TO BE CHANGED
        return 2;
    }

    @Override
    public String type() {

        return type;
    }

    @Override
    public void code(PrintWriter out) {
        // TO BE CHANGED
        if (id == 'i') {
            out.print("\tiload_0\n");
            if (coercion == true) {
                out.print("\ti2d\n");
            }
        }
        if (id == 'a') {
            out.print("\tdload_1\n");
        }
        if (id == 'j') {
            out.print("\tiload_3\n");
            if (coercion == true) {
                out.print("\ti2d\n");
            }
        }

    }
;

}

 class OpNode implements Node {

    private Node LNode, RNode;
    private char op;
    private String type = "";

    public OpNode(Node _LNode, char _op, Node _RNode) {
        LNode = _LNode;
        op = _op;
        RNode = _RNode;
        if (LNode.type().equals("double") || RNode.type().equals("double")) {
            this.setType("double");
            LNode.setType("double");
            RNode.setType("double");

        }

    }

    // TO BE CHANGED - IMPLEMENT INTERFACE
    @Override
    public double value() {

        double value = 0.0;
        if (op == '+') {
            value = LNode.value() + RNode.value();
        } else if (op == '*') {
            value = LNode.value() * RNode.value();
        }
        return value;
    }

    public void setType(String type) {
        this.type = type;
    }

    @Override
    public String type() {
        // TO BE CHANGED
        return this.type;
    }

    ;
    @Override
    public void code(PrintWriter out) {
        // TO BE CHANGED//IF op is '*' the imul, if a, 'a' is present dmul etc..
        LNode.code(out);
        RNode.code(out);
        //Need to account for if is a double;
        if (op == '+') {
            if (type.equals("double")) {
                out.print("\tdadd\n");
            } else {
                out.print("\tiadd\n");
            }

        }
        if (op == '*') {
            if (type.equals("double")) {
                out.print("\tdmul\n");
            } else {
                out.print("\timul\n");
            }

        }

    }
;
}