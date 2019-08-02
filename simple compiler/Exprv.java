/**
 *
 * @author Jeremiah Jacobson
 * CS 3180 TK Prasad 
 * Assignment 2 Part 2
 */
import java.io.*;
import java.util.ArrayList;
import java.util.Stack;

public class Exprv {

    static BufferedReader in;
    static StreamTokenizer inTok;

    public static void main(String[] args) throws IOException {
        
        
        //Command line arguments
        int i = Integer.parseInt(args[1]);
        double a = Double.parseDouble(args[2]);
        int j = Integer.parseInt(args[3]);
        
        //byte code list
        ArrayList<String> byteCodes = new ArrayList<>();
        
        
        in = new BufferedReader(new FileReader(args[0]));
        inTok = new StreamTokenizer(in);
        inTok.eolIsSignificant(true);
        inTok.nextToken();
        
        
        while (inTok.ttype != inTok.TT_EOF) {
            while (inTok.ttype != inTok.TT_EOL) {
                int lineNum = inTok.lineno() - 1;
                if(inTok.ttype == '_'){
                    byteCodes.set(lineNum, byteCodes.get(lineNum) + "_");
                }
                else if(inTok.ttype == inTok.TT_NUMBER){
                    byteCodes.set(lineNum, byteCodes.get(lineNum) + (int)inTok.nval);
                }else{
                    byteCodes.add(inTok.sval);
                }
                
                
                
                
                inTok.nextToken();

            }
            inTok.nextToken();

        }
        

        

        
        
        double f = f(byteCodes, i, a, j);

        System.out.println(f);
        

        

    }
    public static double f(ArrayList<String> bc, int i, double a, int j){
        Stack<Double> stack = new Stack<>();
        stack.push(0.0);
        double total = 0.0;
        for (String string : bc) {
            if("iload_0".equals(string)){
                stack.push((double)i);
                total = stack.peek();
            }
            if("dload_1".equals(string)){
                stack.push(a);
                total = stack.peek();
            }
            if("iload_3".equals(string)){
                stack.push((double)j);
                total = stack.peek();
            }
            if("i2d".equals(string)){
                stack.push((double)stack.pop());
                total = stack.peek();
            }
            if("iadd".equals(string)){
                stack.push(stack.pop() + stack.pop());
                total = stack.peek();
                
            }
            if("imul".equals(string)){
                stack.push(stack.pop() * stack.pop());
                total = stack.peek();
            }
            if("dadd".equals(string)){
                stack.push(stack.pop() + stack.pop());
                total = stack.peek();
            }
            if("dmul".equals(string)){
                stack.push(stack.pop() * stack.pop());
                total = stack.peek();
            }
            
        }
        return total;
    }

}
