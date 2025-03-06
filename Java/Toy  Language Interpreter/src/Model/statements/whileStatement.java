package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.BoolType;
import Model.types.Type;
import Model.values.BoolValue;
import Model.values.Value;

public class whileStatement implements IStmt{

    Exp exp;
    IStmt stmt;

    public whileStatement(Exp _exp, IStmt _stmt){
        this.exp = _exp;
        this.stmt = _stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIDict<String, Value> symTable = state.getSymTable();
        MyIHeap<Integer, Value> heap = state.getHeap();
        Value val = this.exp.eval(symTable, heap);

        if (!val.getType().equals(new BoolType())) {
            throw new MyException("Expression does not evaluate to bool value in while statement.");
        }

        BoolValue boolValue = (BoolValue) val;

        if (boolValue.getVal()) {
            state.getExeStack().push(this);
            state.getExeStack().push(this.stmt);
        }

        return null;
    }

    @Override
    public IStmt deepCopy() {
        return new whileStatement(this.exp.deepCopy(), this.stmt.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type expType = this.exp.typeCheck(typeEnv);
        if (!expType.equals(new BoolType())) {
            throw new MyException("WhileStmt: Exp doesn't evaluate to bool");
        }
        return typeEnv;
    }

    @Override
    public String toString() {
        return "while(" + this.exp.toString() + ") {" + this.stmt.toString() + "}";
    }
}
