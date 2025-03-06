package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myList.MyIList;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.Type;
import Model.values.Value;

public class PrintStmt implements IStmt{
    Exp exp;

    public PrintStmt(Exp _exp){
        this.exp = _exp;
    }

    public String toString(){
        return "print << " + this.exp.toString();
    }

    @Override
    public IStmt deepCopy() {
        return new PrintStmt(this.exp.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        exp.typeCheck(typeEnv);
        return typeEnv;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIList<Value> out = state.getOut();
        MyIDict<String, Value> symTable = state.getSymTable();
        out.add(exp.eval(symTable, state.getHeap()));
        return null;
    }
}
