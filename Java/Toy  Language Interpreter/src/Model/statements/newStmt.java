package Model.statements;

import Exceptions.MyException;
import Exceptions.MyIOException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myHeap.MyIHeap;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.RefType;
import Model.types.Type;
import Model.values.RefValue;
import Model.values.Value;

public class newStmt implements IStmt{

    String varName;
    Exp expression;

    public newStmt(String _varName, Exp _expression){
        this.varName = _varName;
        this.expression = _expression;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {
        MyIDict<String, Value> symTable = state.getSymTable();
        MyIHeap<Integer, Value> heap = state.getHeap();

        if (!symTable.isDefined(this.varName)) {
            throw new MyException("Variable " + this.varName + " is not defined to be used inside newStmt!");
        }

        Value symTableVal = symTable.lookup(this.varName);
        if (!(symTableVal instanceof RefValue)) {
            throw new MyException("Variable " + this.varName + " is not a RefType to be used inside newStmt!");
        }

        RefValue refValue = (RefValue) symTableVal;
        Value val;
        try {
            val = this.expression.eval(state.getSymTable(), state.getHeap());
        } catch (MyException error) {
            throw new MyException(error.getMessage());
        }

        if (!refValue.getLocationType().equals(val.getType())) {
            throw new MyException("The type of the expression doesn't match the ref type inside newStmt!");
        }

        Integer nextFreeAddress = heap.firstFree();
        symTable.update(varName, new RefValue(nextFreeAddress, val.getType()));
        heap.update(nextFreeAddress, val);
        return null;

    }

    @Override
    public IStmt deepCopy() {
        return new newStmt(this.varName, this.expression.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typVar = typeEnv.lookup(varName);
        Type typExp = expression.typeCheck(typeEnv);
        if(typVar.equals(new RefType(typExp)))
            return typeEnv;
        else
            throw new MyException("New stmt: right hand side and left hand side different types");
    }

    @Override
    public String toString(){
        return "HeapAlloc(" + this.varName + " " + this.expression + ")";
    }
}
