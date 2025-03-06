package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.expressions.Exp;
import Model.expressions.RelationalExp;
import Model.expressions.VarExp;
import Model.prgState.PrgState;
import Model.types.BoolType;
import Model.types.IntType;
import Model.types.Type;
import Model.values.BoolValue;
import Model.values.IntValue;
import Model.values.Value;

public class forStmt implements IStmt{

    String var;
    IStmt stmt;
    Exp exp1;
    Exp exp2;
    Exp exp3;

    public forStmt(String _var, Exp _exp1, Exp _exp2, Exp _exp3, IStmt _stmt){
        this.var = _var;
        this.exp1 = _exp1;
        this.exp2 = _exp2;
        this.exp3 = _exp3;
        this.stmt = _stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {

        IStmt NewStmt = new CompStmt(
                new VarDeclStmt(var, new IntType()),
                new CompStmt(
                        new AssignStmt(var, exp1),
                        new whileStatement(
                                new RelationalExp(new VarExp(var), exp2, 1),
                                new CompStmt(
                                        this.stmt,
                                        new AssignStmt(var, exp3)
                                )
                        )
                )
        );
        state.getExeStack().push(NewStmt);
        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new forStmt(this.var, this.exp1.deepCopy(), this.exp2.deepCopy(), this.exp3.deepCopy(), this.stmt.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type exp1Type = this.exp1.typeCheck(typeEnv);
        Type exp2Type = this.exp2.typeCheck(typeEnv);
        Type exp3Type = this.exp3.typeCheck(typeEnv);
        if (!exp1Type.equals(new IntType())) {
            throw new MyException("ForStmt: Exp1 doesn't evaluate to int!");
        }
        if (!exp2Type.equals(new IntType())) {
            throw new MyException("ForStmt: Exp2 doesn't evaluate to int!");
        }
        if (!exp3Type.equals(new IntType())) {
            throw new MyException("ForStmt: Exp3 doesn't evaluate to int!");
        }
        return typeEnv;
    }

    @Override
    public String toString(){
        return "for(" + this.var + "=" + this.exp1.toString() + ";" + this.var + "<" + this.exp2 + ";" + this.var + "=" + this.exp3 + ") {" + this.stmt.toString() + "}";
    }
}
