package Model.statements;

import Exceptions.MyException;
import Model.dataStructures.myDictionary.MyIDict;
import Model.dataStructures.myStack.MyIStack;
import Model.expressions.Exp;
import Model.prgState.PrgState;
import Model.types.Type;
import Model.values.Value;

public class AssignStmt implements IStmt{

    String id;
    Exp exp;

    public AssignStmt(String _id, Exp _exp){
        this.id = _id;
        this.exp = _exp;
    }


    @Override
    public String toString(){
        return this.id + " = " + exp.toString();
    }

    @Override
    public IStmt deepCopy() {
        return new AssignStmt(this.id, this.exp.deepCopy());
    }

    @Override
    public MyIDict<String, Type> typeCheck(MyIDict<String, Type> typeEnv) throws MyException {
        Type typeVar = typeEnv.lookup(id);
        Type typeExp = exp.typeCheck(typeEnv);
        if(typeVar.equals(typeExp))
            return typeEnv;
        else
            throw new MyException("Different types for LHS and RHS in Assign Stmt");
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {

        MyIDict<String, Value> symTbl = state.getSymTable();

        if(symTbl.isDefined(id)){
            Value val = exp.eval(symTbl, state.getHeap());
            Type typeId = (symTbl.lookup(id)).getType();
            Type typeId2 = val.getType();
            if(typeId2.toString().equals(typeId.toString()))
                symTbl.update(id, val);
            else
                throw new MyException("Declared type of the variable " + id + " and type of the assigned expression do not match!");
        }
        else
            throw new MyException("The used variable " + id + " was not declared before!");
        return null;
    }
}
