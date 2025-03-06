package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyDict;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myStack.MyIStack;
import Model.dataStructures.myStack.MyStack;
import Model.prgState.PrgState;
import Model.types.Type;
import Model.values.Value;

public class forkStmt implements  IStmt{

    IStmt stmt;

    public  forkStmt(IStmt _stmt){
        this.stmt = _stmt;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {
        MyIStack<IStmt> forkStmt = new MyStack<>();
        MyIDict<String, Value> symTable = state.getSymTable();
        MyIDict<String, Value> forkSymTable = symTable.clone();
        return new PrgState(forkStmt, forkSymTable, state.getOut(), state.getFileTable(), state.getHeap(), this.stmt);
    }

    @Override
    public String toString(){
        return "Fork( " + this.stmt.toString() + " )";
    }

    @Override
    public IStmt deepCopy() {
        return new forkStmt(this.stmt.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        stmt.typeCheck(typeEnv);
        return typeEnv;
    }
}
