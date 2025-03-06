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

public class writeHeapStmt implements IStmt{

    String varName;
    Exp exp;

    public writeHeapStmt(String _varName, Exp _exp){
        this.varName = _varName;
        this.exp = _exp;
    }


    @Override
    public PrgState execute(PrgState state) throws MyException, MyIOException {
        MyIDict<String, Value> symTbl = state.getSymTable();
        MyIHeap<Integer, Value> heap = state.getHeap();

        if (!symTbl.isDefined(varName))
            throw new MyException("The variable name used in write heap statement isn't defined in symTable!");
        Value val = symTbl.lookup(varName);
        if (!(val instanceof RefValue))
            throw new MyException("The type of the value isn't the required one for heap to be used inside write heap statement");
        RefValue rVal = (RefValue) val;
        if (!heap.isDefined(rVal.getAddr()))
            throw new MyException("The address of Ref Value from Sym Table isn't defined inside Heap Table. [Write Heap Statement]");

        Value expVal;
        try {
            expVal = exp.eval(symTbl, heap);
        } catch (MyException error){
            throw new MyException(error.toString());
        }

        if(!rVal.getLocationType().equals(expVal.getType()))
            throw new MyException("The type of evaluated expression in write heap statement doesn't match the required one for a Heap");

        heap.update(rVal.getAddr(), expVal);
        return null;
    }

    public String toString(){
        return "writeHeap(" + this.varName + " -> " + this.exp + ")";
    }

    @Override
    public IStmt deepCopy() {
        return new writeHeapStmt(this.varName, this.exp);
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.lookup(this.varName);
        Type typeExp = this.exp.typeCheck(typeEnv);

        if (!typeVar.equals(new RefType(typeExp))) {
            throw new MyException("WriteHeapStmt: RHS and LHS have diff types");
        }
        return typeEnv;
    }
}
